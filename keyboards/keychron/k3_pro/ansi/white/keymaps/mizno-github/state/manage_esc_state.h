#ifndef MANAGE_ESC_STATE_H
#define MANAGE_ESC_STATE_H

#include QMK_KEYBOARD_H

bool change_esc_state(uint16_t keycode, keyrecord_t *record);

#endif