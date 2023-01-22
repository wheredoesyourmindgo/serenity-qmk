USER_NAME := wheredoesyourmindgo


# LEADER_ENABLE = yes 		# + Leaders
# TAP_DANCE_ENABLE = yes 		# + Tap Dance
TAP_DANCE_ENABLE = no 		# + Tap Dance
MOUSEKEY_ENABLE = yes 		# + Mouse keys
EXTRAKEY_ENABLE = yes 		# + Audio control and System control
AUTO_SHIFT_ENABLE = no 		# - Auto Shift
KEY_LOCK_ENABLE = yes 		# Key lock
LTO_ENABLE = yes
COMMAND_ENABLE = no			# - Command Mode
# free up some space for ristretto
SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE = no
# If more space is needed consider the following option. See https://github.com/qmk/qmk_firmware/blob/develop/docs/squeezing_avr.md for more info.
# MAGIC_ENABLE = no
CAPS_WORD_ENABLE = yes

# LTO_ENABLE = yes
# CONSOLE_ENABLE = yes
# COMBO_ENABLE = yes # Combos
# SWAP_HANDS_ENABLE = yes # Swap Hands
# WINDOW_MGT = yes

ifneq ($(strip $(KEYBOARD)), binepad/bn003)
	SRC += wheredoesyourmindgo.c
# use caps word/sentence
# SRC += features/caps_word.c
# SRC += features/caps_sentence.c
# use oneshot mods fix
	SRC += features/oneshot_mods.c
	SRC += features/custom_shift_keys.c
	SRC += features/custom_gui_keys.c
	SRC += features/magic_shift.c
	SRC += features/cmd_tab_switcher.c
	SRC += features/symbol_rolls.c
	SRC += features/layer_lock.c
	SRC += features/hide_and_mute.c
endif

ifeq ($(strip $(KEYBOARD)), planck/rev6)
	OPT_DEFS += -DPLANCK_KEYBOARD
	RGBLIGHT_ENABLE = no
# SRC += muse.c
# SRC += layout_4x12.c
endif

# ifeq ($(strip $(SWAP_HANDS_ENABLE)), yes)
# 	SRC += swap_hands.c
# endif

ifeq ($(strip $(KEYBOARD)), boardwalk)
	OPT_DEFS += -DBOARDWALK_KEYBOARD
	RGBLIGHT_ENABLE = no
# SRC += layout_boardwalk_hs.c
endif

ifeq ($(strip $(KEYBOARD)), foostan/cornelius)
	OPT_DEFS += -DCORNELIUS_KEYBOARD
# SRC += layout_4x12.c
endif

ifeq ($(strip $(KEYBOARD)), checkerboards/quark)
	OPT_DEFS += -DQUARK_KEYBOARD
# SRC += layout_4x12.c
endif

# with usb startup disabled we won't be able to wake computer from sleep but we will be able to use key lock
ifeq ($(strip $(KEYBOARD)), ristretto)
	OPT_DEFS += -DRISTRETTO_KEYBOARD
	CONSOLE_ENABLE = no
# KEY_LOCK_ENABLE = yes
# NO_USB_STARTUP_CHECK = yes
	ENCODER_ENABLE = yes
# SRC += layout_4x12_enc.c
endif

ifeq ($(strip $(KEYBOARD)), boardsource/technik_o)
	OPT_DEFS += -DTECHNIK_KEYBOARD
# CONSOLE_ENABLE = no
	RGB_MATRIX_ENABLE = no
# KEY_LOCK_ENABLE = no
# SRC += layout_4x12.c
endif

ifeq ($(strip $(KEYBOARD)), signum/3_0/elitec)
	OPT_DEFS += -DSIGNUM_KEYBOARD
# SRC += layout_4x12.c
endif

ifeq ($(strip $(KEYBOARD)), binepad/bn003)
	TAP_DANCE_ENABLE = no
	MOUSEKEY_ENABLE = no
	EXTRAKEY_ENABLE = no
	KEY_LOCK_ENABLE = no
    ifeq ($(strip $(BN003_USB_LEFT)), yes)
    	OPT_DEFS += -DBN003_USB_LEFT
	endif
endif

ifeq ($(strip $(KEYBOARD)), vitamins_included/rev2)
	OPT_DEFS += -DVITAMINS_INCLUDED_KEYBOARD
# KEY_LOCK_ENABLE = no
	AUDIO_ENABLE = no
	RGBLIGHT_ENABLE = no
# NKRO_ENABLE = no
# SRC += layout_4x12.c
endif

ifeq ($(strip $(EXECUTE_ON_FUNC)), yes)
  OPT_DEFS += -DEXECUTE_ON_FUNC
endif

ifeq ($(strip $(QWERTY_BASE)), yes)
  OPT_DEFS += -DQWERTY_BASE
endif



