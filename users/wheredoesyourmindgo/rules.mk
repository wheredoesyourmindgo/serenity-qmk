LEADER_ENABLE = yes 		# + Leaders
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
	RGBLIGHT_ENABLE = yes
	# SRC += muse.c
endif

# ifeq ($(strip $(SWAP_HANDS_ENABLE)), yes)
# 	SRC += swap_hands.c
# endif

ifeq ($(strip $(KEYBOARD)), boardwalk)
	LTO_ENABLE = yes
endif

ifeq ($(strip $(KEYBOARD)), signum/3_0/elitec)
	OPT_DEFS += -DHALF_MOUSE_INTERVAL
endif

SRC += wheredoesyourmindgo.c

ifeq ($(strip $(HOME_ROW_MODS)), yes)
  OPT_DEFS += -DHOME_ROW_MODS
endif

ifeq ($(strip $(MENU_FUNCTION)), yes)
  OPT_DEFS += -DMENU_FUNCTION
endif
