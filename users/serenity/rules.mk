USER_NAME := serenity

# Features
MOUSEKEY_ENABLE = yes
EXTRAKEY_ENABLE = yes    # Audio and system control
KEY_LOCK_ENABLE = yes
CAPS_WORD_ENABLE = yes
LAYER_LOCK_ENABLE = yes
TAP_DANCE_ENABLE = no
AUTO_SHIFT_ENABLE = no
COMMAND_ENABLE = no

# Save space (the Ristretto is close to full)
LTO_ENABLE = yes
SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE = no
# If more space is needed, see https://docs.qmk.fm/squeezing_avr
# MAGIC_ENABLE = no

SRC += serenity.c
SRC += helpers.c
SRC += long_press.c
SRC += tapping.c
SRC += rotary_encoder.c
SRC += features/oneshot_mods.c
SRC += features/custom_shift_keys.c
SRC += features/magic_shift.c
SRC += features/cmd_tab_switcher.c
SRC += features/symbol_rolls.c
SRC += features/mash_arrows.c
SRC += features/mo_ext.c

# Build with `-e QWERTY_BASE=yes` to start on the QWERTY layer
ifeq ($(strip $(QWERTY_BASE)), yes)
    OPT_DEFS += -DQWERTY_BASE
endif
