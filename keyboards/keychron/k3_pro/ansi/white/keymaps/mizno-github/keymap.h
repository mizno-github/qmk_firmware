#ifndef KEYMAP_H
#define KEYMAP_H
#include <stdbool.h>
extern uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS];
extern uint16_t CONTROLL_KEY;

enum layers { MAC_BASE, MAC_FN, MAC_TENKEY, MAC_NAV, WIN_BASE, WIN_FN };
enum custom_keycodes {
    SET_WIN,
    SET_MAC,
};

// 長押しキー制御
extern bool is_key_long_hold;
extern uint16_t press_start_time;
extern uint16_t hold_keycode;
extern bool is_esc_pressed;

extern uint16_t FN_W_KEY;
extern uint16_t CONTROLL_KEY;
extern uint16_t WINDOWS_KEY;
extern uint16_t COMMAND_LKEY;
extern uint16_t COMMAND_RKEY;

#endif