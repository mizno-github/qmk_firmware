#include "move_layer.h"
#include "os_detection.h"
#include QMK_KEYBOARD_H
#include "../keymap.h"

bool move_layer(keyrecord_t *record, int layer) {
  if (record->event.pressed) {
    if (is_esc_pressed) {
      is_esc_pressed = false;
      layer_move(layer);

      return false;
    } else {
      return true;
    }
  } else {
    return true;
  }
}

bool io_layer(keyrecord_t *record, int layer) {
  if (record->event.pressed) {
    layer_on(layer);
    return false;
  } else {
    layer_off(layer);
    return false;
  }
}
