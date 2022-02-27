#!/bin/sh
OPTS='-j 2 -e EXECUTE_ON_HIGHEST=yes -e QWERTY_BASE=no'
qmk compile -kb binepad/bn003 -km wheredoesyourmindgo
# qmk compile -kb binepad/bnr1 -km wheredoesyourmindgo
qmk compile -kb boardwalk -km wheredoesyourmindgo $OPTS
qmk compile -kb ristretto -km wheredoesyourmindgo $OPTS
qmk compile -kb boardsource/technik_o -km wheredoesyourmindgo $OPTS
qmk compile -kb vitamins_included/rev2 -km wheredoesyourmindgo $OPTS
qmk compile -kb foostan/cornelius -km wheredoesyourmindgo $OPTS
qmk compile -kb signum/3_0/elitec -km wheredoesyourmindgo $OPTS
qmk compile -kb planck/rev6 -km wheredoesyourmindgo $OPTS
# qmk compile -kb planck/rev6 -km wheredoesyourmindgo -j 2 -e EXECUTE_ON_HIGHEST=yes -e QWERTY_BASE=yes
