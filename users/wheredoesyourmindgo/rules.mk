# LEADER_ENABLE = yes 		# + Leaders
TAP_DANCE_ENABLE = yes 		# + Tap Dance
MOUSEKEY_ENABLE = yes 		# + Mouse keys
EXTRAKEY_ENABLE = yes 		# + Audio control and System control
AUTO_SHIFT_ENABLE = no 		# - Auto Shift
# LTO_ENABLE = yes
# CONSOLE_ENABLE = yes
# COMBO_ENABLE = yes # Combos
# SWAP_HANDS_ENABLE = yes # Swap Hands
# WINDOW_MGT = yes

ifeq ($(strip $(KEYBOARD)), planck/rev6)
	OPT_DEFS += -DPLANCK_KEYBOARD
	RGBLIGHT_ENABLE = yes
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
# CONSOLE_ENABLE = yes
	ENCODER_ENABLE = yes
	SRC += layout_4x12_enc.c
endif

ifeq ($(strip $(KEYBOARD)), boardsource/technik_o)
	OPT_DEFS += -DTECHNIK_KEYBOARD
# CONSOLE_ENABLE = yes
# RGB_MATRIX_ENABLE = no
	LTO_ENABLE = yes
	SRC += layout_4x12.c
endif

ifeq ($(strip $(KEYBOARD)), signum/3_0/elitec)
	OPT_DEFS += -DSIGNUM_KEYBOARD
	SRC += layout_4x12.c
endif



SRC += wheredoesyourmindgo.c

ifeq ($(strip $(MENU_ON_HIGHEST)), yes)
  OPT_DEFS += -DMENU_ON_HIGHEST
endif

ifeq ($(strip $(COLEMAK_DH_OA)), yes)
  OPT_DEFS += -DCOLEMAK_DH_OA
endif

ifeq ($(strip $(QWERTY_BASE)), yes)
  OPT_DEFS += -DQWERTY_BASE
endif

