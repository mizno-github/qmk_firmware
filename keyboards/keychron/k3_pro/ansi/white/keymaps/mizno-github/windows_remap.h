#ifndef WINDOWS_REMAP_H
#define WINDOWS_REMAP_H

#include QMK_KEYBOARD_H
extern uint16_t FN_W_KEY;

bool windows_remap(uint16_t keycode, keyrecord_t *record);

#endif