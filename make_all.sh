#!/bin/sh
OPTS='-e EXECUTE_ON_FUNC=yes -e QWERTY_BASE=no'
# qmk compile -kb binepad/bn003 -km wheredoesyourmindgo
# # qmk compile -kb binepad/bn003 -km wheredoesyourmindgo -e BN003_USB_LEFT=yes
# qmk compile -kb binepad/bnr1 -km wheredoesyourmindgo
qmk compile -kb boardwalk -km wheredoesyourmindgo $OPTS
qmk compile -kb ristretto -km wheredoesyourmindgo $OPTS
qmk compile -kb boardsource/technik_o -km wheredoesyourmindgo $OPTS
# qmk compile -kb boardsource/technik_o -km wheredoesyourmindgo -j 2 -e EXECUTE_ON_FUNC=yes -e QWERTY_BASE=no -e RGB_MATRIX_ENABLE=yes
qmk compile -kb vitamins_included/rev2 -km wheredoesyourmindgo $OPTS
qmk compile -kb foostan/cornelius -km wheredoesyourmindgo $OPTS
qmk compile -kb crkbd -km wheredoesyourmindgo $OPTS -e CONVERT_TO=elite_pi
qmk compile -kb crkbd -km wheredoesyourmindgo $OPTS
qmk compile -kb signum/3_0/elitec -km wheredoesyourmindgo $OPTS
# qmk compile -kb checkerboards/quark -km wheredoesyourmindgo $OPTS
# qmk compile -kb planck/rev6 -km wheredoesyourmindgo $OPTS -e ENCODER_ENABLE=yes
qmk compile -kb planck/rev6 -km wheredoesyourmindgo $OPTS
# qmk compile -kb planck/rev6 -km wheredoesyourmindgo -j 2 -e EXECUTE_ON_FUNC=yes -e QWERTY_BASE=no -e ENCODER_ENABLE=no
