#include "manage_esc_state.h"
#include "os_detection.h"
#include QMK_KEYBOARD_H
#include "../keymap.h"

bool change_esc_state(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    is_esc_pressed = true;
    return false;
  } else {
    if (is_esc_pressed) {
      is_esc_pressed = false;
      tap_code(KC_ESC);
    }
    return false;
  }
}
