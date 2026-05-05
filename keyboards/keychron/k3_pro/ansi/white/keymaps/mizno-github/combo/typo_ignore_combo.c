#include "typo_ignore_combo.h"
#include "os_detection.h"
#include QMK_KEYBOARD_H
#include "../keymap.h"

typedef const uint16_t comb_keys_t[];

static PROGMEM comb_keys_t
    // enter + |, ], 'の同時押しをタイポとみなし何も入力していないことにする
    cancel_ent_bsls_combo = {KC_ENT, KC_BSLS, COMBO_END},
    cancel_ent_rbrc_combo = {KC_ENT, KC_RBRC, COMBO_END},
    cancel_ent_quot_combo = {KC_ENT, KC_QUOT, COMBO_END},
    // マイナス + 0, =の同時押しをタイポとみなし何も入力していないことにする
    cancel_mins_0_combo = {KC_MINS, KC_0, COMBO_END},
    cancel_mins_eql_combo = {KC_MINS, KC_EQL, COMBO_END},
    // windowsのalt単押しの挙動ができなくなってしまったため別の操作でalt単押しを実現する
    alt_spc_to_alt_for_win_combo = {KC_RALT, KC_SPC, COMBO_END},
    set_win_combo = {KC_HOME, KC_END, COMBO_END},
    set_mac_combo = {KC_PGUP, KC_PGDN, COMBO_END},
    set_ubu_combo = {KC_HOME, KC_PGDN, COMBO_END},

    // ctrl  + ◯ を j + ◯ でできるようにする
    set_ctrl_right_base_combo = {KC_J, KC_K, COMBO_END},
    set_ctrl_right_nav_combo = {KC_DOWN, KC_UP, COMBO_END},
    set_ctrl_right_tenkey_combo = {KC_4, KC_5, COMBO_END},
    set_ctrl_left_base_combo = {KC_D, KC_F, COMBO_END},

    // s + dでnavlayerに移行する
    move_navlayer_s_d_combo = {KC_S, KC_D, COMBO_END},
    move_navlayer_shift_s_d_f_combo = {KC_S, KC_D, KC_F, COMBO_END},
    move_tenkeylayer_w_e_f_combo = {KC_W, KC_E, COMBO_END};

// comboを追加する場合、config.hの設定も変更すること
combo_t key_combos[COMBO_COUNT] = {
    COMBO(cancel_ent_bsls_combo, KC_F13),  // Enter + | → F13
    COMBO(cancel_ent_rbrc_combo, KC_F13),  // Enter + ] → F13
    COMBO(cancel_ent_quot_combo, KC_F13),  // Enter + ' → F13
    COMBO(cancel_mins_0_combo, KC_F13),  // マイナス + 0 → F13
    COMBO(cancel_mins_eql_combo, KC_F13),  // マイナス + = → F13
    COMBO(alt_spc_to_alt_for_win_combo, KC_RALT), // alt + spc → KC_ALT
    COMBO(set_win_combo, SET_WIN),
    COMBO(set_mac_combo, SET_MAC),
    COMBO(set_ubu_combo, SET_UBU),
    // 右系コントロール
    COMBO(set_ctrl_right_base_combo, SET_CTRL),
    COMBO(set_ctrl_right_nav_combo, SET_CTRL),
    COMBO(set_ctrl_right_tenkey_combo, SET_CTRL),
    // 左系コントロール
    COMBO(set_ctrl_left_base_combo, SET_CTRL),
    // レイヤー系
    COMBO(move_navlayer_s_d_combo, MOVE_NAV),
    COMBO(move_navlayer_shift_s_d_f_combo, MOVE_NAV_SHIFT),
    COMBO(move_tenkeylayer_w_e_f_combo, MOVE_TENKEY),
};
