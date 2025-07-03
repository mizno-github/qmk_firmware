#include "ime_change.h"
#include "os_detection.h"
#include QMK_KEYBOARD_H
#include "../keymap.h"

extern uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS]; 
static uint8_t  mac_keycode[4]    = {KC_LOPT, KC_ROPT, KC_LCMD, KC_RCMD};

os_t os_type = BASE_WIN; // 初期値（適宜変更）

// 左コマンドキーのみ押下でIMEをOFFにする
// コマンドキー＋何かでコマンド＋何かの動きになる
bool lcmd_push_ime_off(uint16_t keycode, keyrecord_t *record) {
    uint16_t new_keycode = mac_keycode[keycode - KC_LOPTN];
    if (record->event.pressed) {
        press_start_time = timer_read();
        hold_keycode = new_keycode;
        is_key_long_hold = true;
        return false;
    } else {
        if (is_key_long_hold) {
            if ((int)os_type == (int)BASE_WIN) {
                tap_code(KC_INT5);
                is_key_long_hold = false;
                press_start_time = 0;
                return false;
            } else {
                tap_code(KC_LNG2);          // IME 切り替え
                is_key_long_hold = false;
                press_start_time = 0;
                return true;
            }
        }

        unregister_code(new_keycode);
        return false;
    }
}

bool rcmd_push_ime_on(uint16_t keycode, keyrecord_t *record) {
    uint16_t new_keycode = mac_keycode[keycode - KC_LOPTN];
    if (record->event.pressed) {        
        press_start_time = timer_read();
        hold_keycode = new_keycode;
        is_key_long_hold = true;
        return false;
    } else {
        if (is_key_long_hold) {
            if ((int)os_type == (int)BASE_WIN) {
                tap_code(KC_INT4);
                is_key_long_hold = false;
                press_start_time = 0;
                return false;
            } else {
                tap_code(KC_LNG1);          // IME 切り替え
                is_key_long_hold = false;
                press_start_time = 0;
                return true;
            }
        }
        unregister_code(new_keycode);
        return false;
    }
}

bool caps_push_to_esc(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        return true;
    }

    if (get_mods() & MOD_MASK_SHIFT) {
        return true;
    } else {
        tap_code(KC_ESC);
    }

    return false;
}

bool judge_os_type (uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        return false;
    }

    wait_ms(100);
    // LEDの状態をチェック
    uint8_t leds = host_keyboard_leds();
    xprintf("leds: %d\n", leds);

    change_os_mode(leds);

    return false;
}

void change_os_mode (bool isWindows) {
    if (isWindows) {
        xprintf("change the windows etc...\n");
        CONTROLL_KEY = KC_LCTL;
        WINDOWS_KEY = KC_LCMMD;
        COMMAND_LKEY = KC_LOPTN;
        COMMAND_RKEY = KC_RALT;
        os_type = (os_t)BASE_MAC;
        xprintf("current is: %d\n", os_type);
    } else {
        xprintf("chage the mac\n");
        CONTROLL_KEY = KC_LCMMD;
        WINDOWS_KEY = KC_LOPTN;
        COMMAND_LKEY = KC_LCMMD;
        COMMAND_RKEY = KC_RCMMD;
        os_type = (os_t)BASE_MAC;
    }
    xprintf("key is : %d, %d\n", COMMAND_LKEY, KC_LCMMD);

    // NOTE: macの場合はshift + 2だがwindowsは違うため
    keymaps[MAC_FN][2][2] = FN_W_KEY;
    keymaps[MAC_BASE][5][0] = CONTROLL_KEY;
    keymaps[MAC_BASE][5][1] = WINDOWS_KEY;
    keymaps[MAC_BASE][5][2] = COMMAND_LKEY;
    keymaps[MAC_BASE][5][10] = COMMAND_RKEY;
}