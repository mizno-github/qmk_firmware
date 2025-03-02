#include "ime_change.h"
#include "keymap.h" 
extern uint16_t CONTROLL_KEY;

uint16_t CONTROLL_KEY = KC_LCMMD;
uint16_t WINDOWS_KEY = KC_LOPTN;
uint16_t COMMAND_LKEY = KC_LCMMD;
uint16_t COMMAND_RKEY = KC_RCMMD;
uint16_t FN_W_KEY = S(KC_2);
extern uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS]; 


static bool lcmd_pressed = false;  // lcmd単独押しを検知するフラグ
static bool rcmd_pressed = false;  // rcmd単独押しを検知するフラグ
static bool lsft_pressed = false;  // lsft単独押しを検知するフラグ
os_t os_type = BASE_WIN; // 初期値（適宜変更）

void reset_cmd_pressed(void) {
    lcmd_pressed = false;
    rcmd_pressed = false;
    lsft_pressed = false;
}

// 左コマンドキーのみ押下でIMEをOFFにする
// コマンドキー＋何かでコマンド＋何かの動きになる
bool lcmd_push_ime_off(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        lcmd_pressed = true;
        return true; // 通常の lcmd の動作を維持する
    } else {
        if(lcmd_pressed) {
            uint8_t mods = get_mods();  // 現在の修飾キーを取得
            clear_mods();               // すべての修飾キーを解除
            if ((int)os_type == (int)BASE_WIN) {
                tap_code(KC_INT5);
                set_mods(mods);             // 元の修飾キー状態に戻す
                tap_code(KC_F13); // 適当なkeyを押してalt単押しの挙動をキャンセルする
            } else {
                tap_code(KC_LNG2);          // IME 切り替え
                set_mods(mods);             // 元の修飾キー状態に戻す
            }

        }
        lcmd_pressed = false;
        return true;
    }
}

bool rcmd_push_ime_on(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {        
        rcmd_pressed = true;
        return true; // 通常の lcmd の動作を維持する
    } else {
        if(rcmd_pressed) {
            uint8_t mods = get_mods();  // 現在の修飾キーを取得
            clear_mods();               // すべての修飾キーを解除
            if ((int)os_type == (int)BASE_WIN) {
                tap_code(KC_INT4);
                set_mods(mods);             // 元の修飾キー状態に戻す
                tap_code(KC_F13);
            } else {
                tap_code(KC_LNG1);          // IME 切り替え
                set_mods(mods);             // 元の修飾キー状態に戻す
            }
        }
        rcmd_pressed = false;
        return true;
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

    if (leds) {
        xprintf("change the windows etc...\n");
        CONTROLL_KEY = KC_LCTL;
        WINDOWS_KEY = KC_LCMMD;
        COMMAND_LKEY = KC_LOPTN;
        COMMAND_RKEY = KC_RALT;
        os_type = (os_t)BASE_WIN;
        xprintf("current is: %d\n", os_type);
    } else {
        xprintf("chage the mac\n");
        CONTROLL_KEY = KC_LCMMD;
        WINDOWS_KEY = KC_LOPTN;
        COMMAND_LKEY = KC_LCMMD;
        COMMAND_RKEY = KC_RCMMD;
        os_type = (os_t)BASE_MAC;
    }
    keymaps[MAC_FN][2][2] = FN_W_KEY;
    keymaps[MAC_BASE][5][0] = CONTROLL_KEY;
    keymaps[MAC_BASE][5][1] = WINDOWS_KEY;
    keymaps[MAC_BASE][5][2] = COMMAND_LKEY;
    keymaps[MAC_BASE][5][10] = COMMAND_RKEY;
    return false;
}
