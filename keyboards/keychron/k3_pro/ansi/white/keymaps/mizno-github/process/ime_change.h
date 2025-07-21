#ifndef IME_CHANGE_H
#define IME_CHANGE_H

#include QMK_KEYBOARD_H

typedef uint8_t os_t;
enum {
    BASE_WIN = 0,
    BASE_MAC = 1
};
extern os_t os_type;

bool lcmd_push_ime_off(uint16_t keycode, keyrecord_t *record);
bool rcmd_push_ime_on(uint16_t keycode, keyrecord_t *record);
bool caps_push_to_esc(uint16_t keycode, keyrecord_t *record);
bool judge_os_type(uint16_t keycode, keyrecord_t *record);
void change_os_mode(uint16_t os);

#endif