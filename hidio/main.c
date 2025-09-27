#include <hidapi/hidapi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#define _GNU_SOURCE
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define BUFLEN 32

static const int SIGNATURE[] = {0, 0, 1, 1, 2, 1};
static const int SIGLEN = 6;
bool active_window_is_overwatch = false;

unsigned char *sign_buffer(unsigned char *buf, unsigned int layerNum) {
  for (int i = 0; i < SIGLEN; i++) {
    buf[i] = SIGNATURE[i];
  }
  buf[SIGLEN] = layerNum;
  return buf;
}

hid_device *get_handle(unsigned int vid, unsigned int pid) {
  if (hid_init()) {
    return NULL;
  }
  struct hid_device_info *devs = hid_enumerate(vid, pid);
  struct hid_device_info *cur = devs;
  hid_device *handle = NULL;

  while (cur) {
    if (cur->usage_page == 0xFF60) {
      handle = hid_open_path(cur->path);
      break;
    }
    cur = cur->next;
  }
  hid_free_enumeration(devs);

  return handle;
}

void request_layer_switch(unsigned int vid, unsigned int pid,
                          unsigned int layer) {
  hid_device *handle = get_handle(vid, pid);

  // ask kb to switch to a layer
  unsigned char buf[BUFLEN] = {0};
  sign_buffer(buf, layer);
  hid_write(handle, buf, BUFLEN);
}

static void handle(const char *line, unsigned int vid, unsigned int pid) {
  if (strncmp(line, "activewindow>>", 14) == 0) {
    size_t len = strlen(line);
    const char *last_9 = line + (len - 9);
    if (strcmp(last_9, "Overwatch") == 0) {
      // activated ow
      request_layer_switch(vid, pid, 3);
    } else {
      // deactivated OW or activated some other window
      request_layer_switch(vid, pid, 0);
    }
  }
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Usage: %s <VID hex> <PID hex>\n", argv[0]);
    return 1;
  }
  unsigned int vid = (unsigned int)strtoul(argv[1], NULL, 16);
  unsigned int pid = (unsigned int)strtoul(argv[2], NULL, 16);
  // on start, make sure layer 0. Likely when this program is run, overwatch is
  // not running
  request_layer_switch(vid, pid, 0);

  // start listening for hyprland events
  const char *xdg_runtime = getenv("XDG_RUNTIME_DIR");
  const char *signature = getenv("HYPRLAND_INSTANCE_SIGNATURE");
  if (!xdg_runtime || !signature) {
    fprintf(stderr, "Missing environment variables XDG_RUNTIME_DIR or "
                    "HYPRLAND_INSTANCE_SIGNATURE");
    return 1;
  }
  char socket_path[512];
  snprintf(socket_path, sizeof(socket_path), "%s/hypr/%s/.socket2.sock",
           xdg_runtime, signature);
  int fd = socket(AF_UNIX, SOCK_STREAM, 0);
  if (fd == -1) {
    perror("socket");
    return 1;
  }

  struct sockaddr_un addr;
  memset(&addr, 0, sizeof(addr));
  addr.sun_family = AF_UNIX;
  strncpy(addr.sun_path, socket_path, sizeof(addr.sun_path) - 1);
  if (connect(fd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
    perror("connect");
    close(fd);
    return 1;
  }
  FILE *steam = fdopen(fd, "r");
  if (!steam) {
    perror("fdopen");
    close(fd);
    return 1;
  }

  char *line = NULL;
  size_t len = 0;
  while (getline(&line, &len, steam) != -1) {
    line[strcspn(line, "\n")] = '\0';
    handle(line, vid, pid);
  }

  return 0;
}
