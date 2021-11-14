# LEADER_ENABLE = yes 		# + Leaders
TAP_DANCE_ENABLE = yes 		# + Tap Dance
MOUSEKEY_ENABLE = yes 		# + Mouse keys
EXTRAKEY_ENABLE = yes 		# + Audio control and System control
AUTO_SHIFT_ENABLE = no 		# - Auto Shift
KEY_LOCK_ENABLE = yes 		# Key lock
# LTO_ENABLE = yes
# CONSOLE_ENABLE = yes
# COMBO_ENABLE = yes # Combos
# SWAP_HANDS_ENABLE = yes # Swap Hands
# WINDOW_MGT = yes

ifeq ($(strip $(KEYBOARD)), planck/rev6)
	OPT_DEFS += -DPLANCK_KEYBOARD
	RGBLIGHT_ENABLE = no
	# SRC += muse.c
	SRC += layout_4x12.c
endif

# ifeq ($(strip $(SWAP_HANDS_ENABLE)), yes)
# 	SRC += swap_hands.c
# endif

ifeq ($(strip $(KEYBOARD)), boardwalk)
	OPT_DEFS += -DBOARDWALK_KEYBOARD
	RGBLIGHT_ENABLE = no
	LTO_ENABLE = yes
	SRC += layout_boardwalk_hs.c
endif

ifeq ($(strip $(KEYBOARD)), foostan/cornelius)
	OPT_DEFS += -DCORNELIUS_KEYBOARD
	SRC += layout_4x12.c
endif

ifeq ($(strip $(KEYBOARD)), ristretto)
	OPT_DEFS += -DRISTRETTO_KEYBOARD
	LTO_ENABLE = yes
	CONSOLE_ENABLE = no
	KEY_LOCK_ENABLE = yes
	EXTRAKEY_ENABLE = no
	ENCODER_ENABLE = yes
	SRC += layout_4x12_enc.c
endif

ifeq ($(strip $(KEYBOARD)), boardsource/technik_o)
	OPT_DEFS += -DTECHNIK_KEYBOARD
# CONSOLE_ENABLE = yes
# RGB_MATRIX_ENABLE = no
	KEY_LOCK_ENABLE = no
	LTO_ENABLE = yes
	SRC += layout_4x12.c
endif

ifeq ($(strip $(KEYBOARD)), signum/3_0/elitec)
	OPT_DEFS += -DSIGNUM_KEYBOARD
	SRC += layout_4x12.c
endif

ifeq ($(strip $(KEYBOARD)), binepad/bn003)
	TAP_DANCE_ENABLE = no
	MOUSEKEY_ENABLE = no
	EXTRAKEY_ENABLE = no
	KEY_LOCK_ENABLE = no
else
	SRC += wheredoesyourmindgo.c
endif

ifeq ($(strip $(MENU_ON_HIGHEST)), yes)
  OPT_DEFS += -DMENU_ON_HIGHEST
endif

ifeq ($(strip $(COLEMAK_DH_OA)), yes)
  OPT_DEFS += -DCOLEMAK_DH_OA
endif

ifeq ($(strip $(COLEMAK_DH_RING)), yes)
  OPT_DEFS += -DCOLEMAK_DH_RING
endif

ifeq ($(strip $(REMAP_PASTE)), yes)
  OPT_DEFS += -DREMAP_PASTE
endif

ifeq ($(strip $(REMAP_PARENS)), yes)
  OPT_DEFS += -DREMAP_PARENS
endif

ifeq ($(strip $(QWERTY_BASE)), yes)
  OPT_DEFS += -DQWERTY_BASE
endif

