# Microdox

![boardsource Microdox](https://i.imgur.com/AliShkvl.jpg)

* Keyboard Maintainer: [Boardsource](https://github.com/daysgobye) 
* Hardware Supported: microdox v1
* Hardware Availability: this keyboard is available from the [Boardsource store](https://boardsource.xyz/store/5f2e7e4a2902de7151494f92)

Make example for this keyboard (after setting up your build environment):

    make boardsource/microdox:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Build Firmware

    make boardsource/microdox:wheredoesyourmindgo

## Convert Keymap to JSON for use with QMK Configurator

    qmk c2json -km wheredoesyourmindgo -kb boardsource/microdox -o microdox_wheredoesyourmindgo.json keyboards/boardsource/microdox/keymaps/wheredoesyourmindgo/keymap.c

## Compile JSON Configuration into Keymap

    qmk json2c microdox_wheredoesyourmindgo.json -o keyboards/boardsource/microdox/keymaps/wheredoesyourmindgo/keymap_NEW.c
