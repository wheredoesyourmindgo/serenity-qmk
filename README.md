# Serenity

My personal QMK firmware: a shared userspace (`users/serenity`) plus a keymap per keyboard, built as a [QMK external userspace](https://docs.qmk.fm/newbs_external_userspace).

This repo holds only my code. QMK itself lives in a separate, unmodified clone.

## Layout

| Path | What |
|---|---|
| `users/serenity/` | Shared layers, custom keycodes and features used by every keyboard |
| `keyboards/<kb>/keymaps/serenity/` | Per-keyboard layout (calls into the shared userspace) |
| `qmk.json` | List of keyboards to build (`qmk userspace-list`) |

## One-time setup

```sh
git clone https://github.com/qmk/qmk_firmware.git ~/Development/qmk_firmware
cd ~/Development/qmk_firmware && make git-submodule
qmk config user.qmk_home="$HOME/Development/qmk_firmware"
qmk config user.overlay_dir="$HOME/Development/serenity-qmk"
brew install avrdude dfu-util   # flashers (dfu-programmer is also needed)
```

## Everyday use

```sh
qmk userspace-compile                   # build every keyboard in qmk.json
qmk flash -kb crkbd/rev1 -km serenity   # build + flash one keyboard
```

Build options go after `-e`, e.g. `-e QWERTY_BASE=yes`.

## Updating QMK

```sh
cd ~/Development/qmk_firmware && git pull && make git-submodule
```

If a QMK change breaks the build, fix it here — there is nothing to merge.

## Cornelius rev2

Cornelius rev2 (RP2040) isn't in upstream QMK yet. The QMK clone carries it as one local commit on the `serenity` branch (`git pull` rebases it automatically). Because GitHub Actions builds against upstream QMK, rev2 is not in `qmk.json`; build it locally:

```sh
qmk compile -kb foostan/cornelius/rev2 -km serenity
```

## GitHub Actions

Every push builds all targets in `qmk.json` and publishes the firmware files on the Releases page.
