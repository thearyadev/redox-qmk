CC = gcc
CFLAGS = -Wall -Wextra -O3 -march=native -flto -Os -s
LDFLAGS = -lhidapi-hidraw

TARGET = kb-writelayer

$(TARGET): main.c
	$(CC) $(CFLAGS) -o $(TARGET) main.c $(LDFLAGS)

clean:
	rm -f $(TARGET) *.o

run: $(TARGET)
	./$(TARGET) 4d44 5244

.PHONY: install bump

PKGBUILD := PKGBUILD

bump:
	@current=$$(grep -E '^pkgrel=' $(PKGBUILD) | head -n1 | cut -d= -f2); \
	if [ -z "$$current" ]; then \
		echo "pkgrel=1" >> $(PKGBUILD); \
		echo "Added pkgrel=1"; \
	else \
		new=$$((current + 1)); \
		sed -i "s/^pkgrel=.*/pkgrel=$$new/" $(PKGBUILD); \
		echo "Bumped pkgrel: $$current → $$new"; \
	fi

install: bump
	makepkg -si

