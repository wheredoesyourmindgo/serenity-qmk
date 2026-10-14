# Serenity

My personal QMK firmware: a shared userspace (`users/serenity`) plus a keymap per keyboard, built as a [QMK external userspace](https://docs.qmk.fm/newbs_external_userspace).

This repo holds only my code. QMK itself lives in a separate, unmodified clone.

## Layout

| Path | What |
|---|---|
| `users/serenity/` | Shared layers, custom keycodes and features used by every keyboard |
| `keyboards/<kb>/keymaps/serenity/` | Per-keyboard layout (calls into the shared userspace) |
| `modules/getreuer/` | [Getreuer's community modules](https://github.com/getreuer/qmk-modules) (git submodule); only `custom_shift_keys` is used |
| `scripts/format_keymaps.py` | Aligns each `LAYOUT(...)` into a split grid (`--check` to verify) |
| `qmk.json` | List of keyboards to build (`qmk userspace-list`) |

## One-time setup

```sh
git clone --recurse-submodules https://github.com/wheredoesyourmindgo/serenity-qmk.git ~/Development/serenity-qmk
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

After editing a keymap, re-align its grid with `scripts/format_keymaps.py`.

## Updating QMK

```sh
cd ~/Development/qmk_firmware && git pull && make git-submodule
```

If a QMK change breaks the build, fix it here — there is nothing to merge.

## Updating Getreuer's modules

`modules/getreuer` is a git submodule pinned to one commit of [getreuer/qmk-modules](https://github.com/getreuer/qmk-modules), so his changes only arrive when you pull them:

```sh
cd ~/Development/serenity-qmk
git submodule update --remote modules/getreuer   # fetch his latest
git -C modules/getreuer log --oneline -5         # see what changed
qmk userspace-compile                            # make sure everything still builds
git commit -am "Update getreuer modules" && git push
```

To undo an update before committing, run `git submodule update modules/getreuer` (goes back to the pinned commit).

If `modules/getreuer` is ever empty (e.g. after a plain `git clone`), run `git submodule update --init`.

Custom Shift Keys is enabled by the `modules` entry in each keymap's `keymap.json`. Its key table is in `users/serenity/shift_keys.c` and its options are in `users/serenity/config.h`.

## Cornelius rev2

Cornelius rev2 (RP2040) isn't in upstream QMK yet. The QMK clone carries it as one local commit on the `serenity` branch (`git pull` rebases it automatically). Because GitHub Actions builds against upstream QMK, rev2 is not in `qmk.json`; build it locally:

```sh
qmk compile -kb foostan/cornelius/rev2 -km serenity
```

## GitHub Actions

Every push builds all targets in `qmk.json` and publishes the firmware files on the Releases page.
