# This file intentionally blank
BOOTLOADER = stm32-dfu
COMBO_ENABLE = yes
SRC += combo/typo_ignore_combo.c
SRC += process/move_layer.c
SRC += process/ime_change.c
SRC += process/windows_remap.c
SRC += state/manage_esc_state.c
CONSOLE_ENABLE = yes
OS_DETECTION_ENABLE = yes

