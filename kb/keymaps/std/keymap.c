#include QMK_KEYBOARD_H
#include "print.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9,
                 KC_0, LT(2, KC_MINS), KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T,
                 TG(3), KC_NO, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_EQL, KC_CAPS,
                 KC_A, KC_S, KC_D, KC_F, KC_G, KC_DEL, KC_PSCR, KC_H, KC_J,
                 KC_K, KC_L, KC_SCLN, KC_QUOT, KC_LSFT, KC_Z, KC_X, KC_C, KC_V,
                 KC_B, KC_NO, OSL(2), KC_NO, KC_NO, KC_N, KC_M, KC_COMM, KC_DOT,
                 KC_SLSH, KC_DQUO, KC_LGUI, KC_PPLS, KC_PMNS, MO(1), KC_LSFT,
                 KC_LCTL, KC_NO, KC_BSPC, KC_SPC, KC_ENT, KC_TILD, KC_GRV,
                 KC_BSLS, KC_NO),
    [1] = LAYOUT(KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPRV, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_LPRN, KC_RPRN, KC_TRNS, KC_TRNS, KC_MNXT, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_INS, KC_TRNS,
                 KC_LCBR, KC_RCBR, KC_TRNS, KC_TRNS, KC_MRWD, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_LBRC, KC_RBRC, KC_TRNS, KC_UP, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, QK_BOOT,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT),
    [2] = LAYOUT(KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F8, KC_F9,
                 KC_F10, KC_F11, KC_F12, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_F6, KC_F7, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
    [3] =
        LAYOUT(KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
               KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
               KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
               KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
               KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
               KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
               KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
               KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
               KC_M, KC_TRNS, KC_H, KC_TRNS, KC_SPC, KC_LALT, KC_TRNS, KC_TRNS,
               KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)};

socd_cleaner_t socd_opposing_pairs[] = {
    {{KC_W, KC_S}, SOCD_CLEANER_LAST},
    {{KC_A, KC_D}, SOCD_CLEANER_LAST},
};

// static uint8_t current_layer = 0;
// layer_state_t layer_state_set_user(layer_state_t state) {
//   current_layer = get_highest_layer(state);
//   return state;
// }
// uint16_t last_send = 0;

// void matrix_scan_user(void) {
//   if (timer_elapsed(last_send) > 50) {
//     uint8_t payload[32] = {0};
//     payload[0] = current_layer;
//     host_raw_hid_send(payload, sizeof(payload));
//     last_send = timer_read();
//   }
// }
//
//
//
//

uint8_t signature[] = {0, 1, 1, 2, 1};
uint8_t signature_length = 5;

void raw_hid_receive(uint8_t *data, uint8_t length) {
  if (length < signature_length + 1) {
    return; // not enough bytes for signature + layer id
  }
  for (int i = 0; i < signature_length; i++) {
    if (data[i] != signature[i]) {
      return; // signature mismatch
    }
  }
  uint8_t layer_target = data[signature_length]; 
  layer_move(layer_target);
}
  // char msg[64];
  // snprintf(msg, sizeof(msg),
  //         "got %d %d %d %d %d %d expected %d %d %d %d %d",
  //          data[0], data[1], data[2], data[3], data[4], data[5],
  //          signature[0], signature[1],signature[2],signature[3], signature[4]);
  // send_string(msg);
