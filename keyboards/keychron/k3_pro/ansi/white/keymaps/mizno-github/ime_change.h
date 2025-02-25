#ifndef IME_CHANGE_H
#define IME_CHANGE_H

#include QMK_KEYBOARD_H

typedef uint8_t os_t;
enum {
    BASE_WIN = 0,
    BASE_MAC = 1
};
extern os_t os_type;

extern uint16_t CONTROLL_KEY;
extern uint16_t WINDOWS_KEY;
extern uint16_t COMMAND_LKEY;
extern uint16_t COMMAND_RKEY;


void reset_cmd_pressed(void);
bool lcmd_push_ime_off(uint16_t keycode, keyrecord_t *record);
bool rcmd_push_ime_on(uint16_t keycode, keyrecord_t *record);
bool caps_push_to_esc(uint16_t keycode, keyrecord_t *record);
bool judge_os_type(uint16_t keycode, keyrecord_t *record);

#endif