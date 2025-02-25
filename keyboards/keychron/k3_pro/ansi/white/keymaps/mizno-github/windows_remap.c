#include "windows_remap.h"
bool windows_remap(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case KC_2:
                print("input KC_2\n");
                if (get_mods() & MOD_MASK_SHIFT) {
                    uint8_t mods = get_mods();
                    clear_mods();
                    print("true shift in KC_2\n");
                    tap_code(KC_LBRC); // Shift + 2 → @
                    set_mods(mods);
                } else {
                    print("false shift in KC_2\n");
                    tap_code(KC_2);
                }
                return false;
            case KC_6:
                if (get_mods() & MOD_MASK_SHIFT) {
                    uint8_t mods = get_mods();
                    clear_mods();
                    tap_code(KC_EQL); // Shift + 6 → ^
                    set_mods(mods);
                } else {
                    tap_code(KC_6);
                }
                return false;
            case KC_7:
                if (get_mods() & MOD_MASK_SHIFT) {
                    tap_code16(S(KC_6)); // Shift + 7 → &
                } else {
                    tap_code(KC_7);
                }
                return false;
            case KC_8:
                if (get_mods() & MOD_MASK_SHIFT) {
                    tap_code16(S(KC_QUOT)); // Shift + 8 → *
                } else {
                    tap_code(KC_8);
                }
                return false;
            case KC_9:
                if (get_mods() & MOD_MASK_SHIFT) {
                    tap_code16(S(KC_8)); // Shift + 9 → (
                } else {
                    tap_code(KC_9);
                }
                return false;
            case KC_0:
                if (get_mods() & MOD_MASK_SHIFT) {
                    tap_code16(S(KC_9)); // Shift + 0 → )
                } else {
                    tap_code(KC_0);
                }
                return false;
            case KC_MINS:
                if (get_mods() & MOD_MASK_SHIFT) {
                    tap_code16(S(KC_INT1)); // Shift + - → _
                } else {
                    tap_code(KC_MINS);
                }
                return false;
            case KC_EQL:
                if (get_mods() & MOD_MASK_SHIFT) {
                    tap_code16(S(KC_SCLN)); // Shift + = → +
                } else {
                    tap_code16(S(KC_MINS)); // =
                }
                return false;
            case KC_LBRC:
                if (get_mods() & MOD_MASK_SHIFT) {
                    tap_code16(S(KC_RBRC)); // Shift + [ → {
                } else {
                    tap_code(KC_RBRC); // [
                }
                return false;
            case KC_RBRC:
                if (get_mods() & MOD_MASK_SHIFT) {
                    tap_code16(S(KC_NUHS)); // Shift + ] → }
                } else {
                    tap_code(KC_NUHS);
                }
                return false;
            case KC_BSLS:
                if (get_mods() & MOD_MASK_SHIFT) {
                    tap_code16(S(KC_INT3)); // Shift + \ → |
                } else {
                    // back slash
                    tap_code(KC_INT3);
                }
                return false;
            case KC_SCLN:
                if (get_mods() & MOD_MASK_SHIFT) {
                    uint8_t mods = get_mods();
                    clear_mods();
                    tap_code(KC_QUOT); // Shift + ; → :
                    set_mods(mods);
                } else {
                    tap_code(KC_SCLN);
                }
                return false;
            case KC_QUOT:
                if (get_mods() & MOD_MASK_SHIFT) {
                    tap_code16(S(KC_2)); // Shift + ' → "
                } else {
                    tap_code16(S(KC_7));
                }
                return false;
        }
        print("not matched\n");
        xprintf("keycode: %d\n", keycode);

    }
    return true;
}
