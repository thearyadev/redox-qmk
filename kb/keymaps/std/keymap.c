#include <stdalign.h>
#include QMK_KEYBOARD_H
#include "print.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9,
                 KC_0, LT(2, KC_MINS), KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T,
                 TG(3), KC_NO, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_EQL, CW_TOGG,
                 KC_A, KC_S, KC_D, KC_F, KC_G, KC_DEL, KC_PSCR, KC_H, KC_J,
                 KC_K, KC_L, KC_SCLN, KC_QUOT, KC_LSFT, KC_Z, KC_X, KC_C, KC_V,
                 KC_B, KC_NO, OSL(2), LGUI(KC_LEFT), LGUI(KC_RGHT), KC_N, KC_M,
                 KC_COMM, KC_DOT, KC_SLSH, KC_DQUO, KC_LGUI, KC_PPLS, KC_PMNS,
                 MO(1), KC_LSFT, KC_LCTL, RCS(KC_F), KC_BSPC, KC_SPC, KC_ENT,
                 KC_TILD, KC_GRV, KC_BSLS, RALT(KC_ENT)),
    [1] = LAYOUT(KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_LPRN, KC_RPRN, KC_TRNS, KC_TRNS, KC_MNXT, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_INS, KC_TRNS,
                 KC_LCBR, KC_RCBR, KC_TRNS, KC_TRNS, KC_MRWD, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_LBRC, KC_RBRC, KC_TRNS, KC_UP, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, DB_TOGG, QK_BOOT,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT),
    [2] = LAYOUT(KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F8, KC_F9,
                 KC_F10, KC_F11, KC_F12, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_F6, KC_F7, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
    [3] =
        LAYOUT(KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
               KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
               KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
               KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_TRNS,
               KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
               KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
               KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
               KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
               KC_M, KC_TRNS, KC_H, KC_TRNS, KC_SPC, KC_K, LCTL(KC_F10),
               KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)};

uint8_t signature[] = {0, 1, 1, 2, 1};
uint8_t signature_length = 5;

void log_sig_mismatch(uint8_t *data, uint8_t *sig, uint8_t siglen) {
  uprintf("raw_hid_receive(): Signature missmatch. ");
  uprintf("\tgot (");
  for (int i = 0; i < siglen; i++) {
    uprintf("%u ", data[i]);
  }
  uprintf(") expected (");

  for (int i = 0; i < siglen; i++) {
    uprintf("%u ", sig[i]);
  }
  uprintf(")\n");
}

void raw_hid_receive(uint8_t *data, uint8_t length) {
  if (length < signature_length + 1) {
    uprintf("raw_hid_receive(): got message with %u length. Expected 32.\n",
            length);
    return; // not enough bytes for signature + layer id
  }
  for (int i = 0; i < signature_length; i++) {
    if (data[i] != signature[i]) {
      log_sig_mismatch(data, signature, signature_length);
      return; // signature mismatch
    }
  }
  uint8_t layer_target = data[signature_length];
  uprintf("raw_hid_receive(): host requested layer modification to %u\n",
          layer_target);
  layer_move(layer_target);
}
