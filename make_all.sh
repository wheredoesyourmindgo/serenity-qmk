#!/bin/sh
OPTS='MENU_ON_HIGHEST=yes COLEMAK_DH_OA=yes REMAP_PASTE=yes'
make binepad/bn003:wheredoesyourmindgo
# make binepad/bnr1:wheredoesyourmindgo
make boardwalk:wheredoesyourmindgo $OPTS
make ristretto:wheredoesyourmindgo $OPTS
make boardsource/technik_o:wheredoesyourmindgo $OPTS
make foostan/cornelius:wheredoesyourmindgo $OPTS
make signum/3_0/elitec:wheredoesyourmindgo $OPTS
make planck/rev6:wheredoesyourmindgo $OPTS
