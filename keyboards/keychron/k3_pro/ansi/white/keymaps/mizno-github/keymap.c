/* Copyright 2023 @ Keychron (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

 /*
  * brew install qmk/qmk/qmk
  * qmk setup
  * https://github.com/Keychron/qmk_firmware/tree/bluetooth_playground/keyboards/keychron/k3_pro からフォーク
  * git remote add upstream https://github.com/Keychron/qmk_firmware.git      
  * git fetch upstream bluetooth_playground   
  * git checkout bluetooth_playground    
  * git remote remove upstream 
  * qmk compile -kb keychron/k3_pro/ansi/white -km default  
  * qmk config user.keymap=mizno-github      
  * qmk config user.keyboard=keychron/k3_pro/ansi/white       
  * qmk new-keymap
  * qmk compile -kb keychron/k3_pro/ansi/white      
  * 
  * https://docs.qmk.fm/keycodes_basic
  * 
  * https://qmk.fm/toolbox toolbox公式
 */

#include "os_detection.h"
#include "keymap.h"
#include QMK_KEYBOARD_H
#define DEBUG_ENABLE
#include "ime_change.h"
#include "windows_remap.h"
uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS];

// #ifdef WIN_BASE
//     xprintf("for windows");
//     #define CONTROLL_KEY KC_LCTL
//     #define WINDOWS_KEY KC_LCMMD
//     #define COMMAND_LKEY KC_LOPTN
//     #define COMMAND_RKEY KC_ROPTN
// #else
//     #define CONTROLL_KEY KC_LCMMD
//     #define WINDOWS_KEY KC_LOPTN
//     #define COMMAND_LKEY KC_LCMMD
//     #define COMMAND_RKEY KC_RCMMD
// #endif

void matrix_scan_user(void) {}

// keyを押された時、離された時にtrueを返すとkeyが押された、離されたという挙動になる
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // 押したキーの位置を取得して表示
    uint8_t row = record->event.key.row;
    uint8_t col = record->event.key.col;

    // シリアル出力で位置を表示
    xprintf("Key pressed: row = %d, col = %d, keycode = %d\n", row, col, keycode);

    // xprintf("Keycode: %d, Pressed: %d\n", keycode, record->event.pressed);
    if (keycode == COMMAND_LKEY) {
        return lcmd_push_ime_off(keycode, record);
    }
    if (keycode == COMMAND_RKEY) {
        return rcmd_push_ime_on(keycode, record);
    }
    switch(keycode) {
        case KC_CAPS:
            return caps_push_to_esc(keycode, record);
        case KC_F13:
            return judge_os_type(keycode, record);
    }
    
    reset_cmd_pressed();

    // printf("Size of os_type: %zu\n", sizeof((int)os_type));  // サイズを確認
    // printf("Value of os_type: %d\n", (int)os_type);  // 値を確認
    // printf("Size of BASE_WIN: %zu\n", sizeof((int)BASE_WIN));  // サイズを確認
    // printf("Value of BASE_WIN: %d\n", (int)BASE_WIN);  // 値を確認


    // xprintf("currentLayer: %d, %d\n", (int)os_type, (int)BASE_WIN);
    if((int)os_type == (int)BASE_WIN) {
        printf("only windows\n");
        return windows_remap(keycode, record);
    }

    return true;
}

uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
     [MAC_BASE] = LAYOUT_ansi_84(
          KC_ESC,   KC_BRID,  KC_BRIU,  KC_MCTL,  KC_LPAD,  BL_DOWN,  BL_UP,    KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  KC_SNAP,  KC_DEL,   BL_STEP,
          KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,            KC_PGUP,
          KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,            KC_PGDN,
          KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,             KC_HOME,
          KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,            KC_RSFT,  KC_UP,    KC_END,
          0,        0,        0,                                      KC_SPC,                                 0,        MO(MAC_FN),KC_RCTL, KC_LEFT,  KC_DOWN,  KC_RGHT
     ),

     [MAC_FN] = LAYOUT_ansi_84(
          KC_TRNS,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_TRNS,  KC_TRNS,  KC_F13,
          KC_TRNS,  BT_HST1,  BT_HST2,  BT_HST3,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
          BL_TOGG,  BL_STEP,  BL_UP,    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
          KC_TRNS,  KC_TRNS,  BL_DOWN,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,            KC_TRNS,
          KC_TRNS,            KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  BAT_LVL,  NK_TOGG,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,  KC_TRNS,  KC_TRNS,
          KC_TRNS,  KC_TRNS,  KC_TRNS,                                KC_TRNS,                                KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS
     ),

     [WIN_BASE] = LAYOUT_ansi_84(
          KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_PSCR,  KC_DEL,   BL_STEP,
          KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,            KC_PGUP,
          KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,            KC_PGDN,
          KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,             KC_HOME,
          KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,            KC_RSFT,  KC_UP,    KC_END,
          KC_LCTL,  KC_LGUI,  KC_LALT,                                KC_SPC,                                 KC_RALT, MO(WIN_FN),KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT
     ),

     [WIN_FN] = LAYOUT_ansi_84(
          KC_TRNS,  KC_BRID,  KC_BRIU,  KC_TASK,  KC_FILE,  BL_DOWN,  BL_UP,    KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  KC_TRNS,  KC_TRNS,  BL_TOGG,
          KC_TRNS,  BT_HST1,  BT_HST2,  BT_HST3,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
          BL_TOGG,  BL_STEP,  BL_UP,    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
          KC_TRNS,  KC_TRNS,  BL_DOWN,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,            KC_TRNS,
          KC_TRNS,            KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  BAT_LVL,  NK_TOGG,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,  KC_TRNS,  KC_TRNS,
          KC_TRNS,  KC_TRNS,  KC_TRNS,                                KC_TRNS,                                KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS
     )
};
