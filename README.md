# Serenity

My personal QMK firmware: a shared userspace (`users/serenity`) plus a keymap per keyboard, built as a [QMK external userspace](https://docs.qmk.fm/newbs_external_userspace).

This repo holds only my code. QMK itself lives in a separate, unmodified clone.

**Layout reference:** interactive diagrams of every layer, plus the feature list, are at [serenity-layout.fyi/firmware](https://www.serenity-layout.fyi/firmware) ([source](https://github.com/wheredoesyourmindgo/serenity-web)).

## Layers

The website uses friendlier names for some layers than the code does:

| Code (`serenity.h`) | Website | Reached by |
|---|---|---|
| `BASE` | Base | default |
| `QWRTY` | Qwerty | `TGL_LYT` on Hardware, or build with `-e QWERTY_BASE=yes` |
| `NUMNAV` | Num/Nav | left thumb, beside Space |
| `SYMBL` | Symbol | right thumb, beside Space |
| `ACTN` | Action | left, beside Num/Nav |
| `HRDWR` | Hardware | right, beside Symbol |
| `OS` | OS | Num/Nav + Symbol (tri-layer) |
| `FUNC` | Function | Action + Hardware (tri-layer) |
| `MOUSE` | Mouse | hold Escape |
| `BASE_L`, `BASE_R` | — | tap then hold Symbol / Num/Nav (temporary home-row mods) |

## Layout

| Path | What |
|---|---|
| `users/serenity/` | Shared layers, custom keycodes and features used by every keyboard |
| `keyboards/<kb>/keymaps/serenity/` | Per-keyboard layout (calls into the shared userspace) |
| `modules/getreuer/` | [Getreuer's community modules](https://github.com/getreuer/qmk-modules) (git submodule); only `custom_shift_keys` is used |
| `vendor/foostan/corneliuskbd/` | foostan's Cornelius rev1/rev2 keyboard definitions (copied from [foostan/kbd_firmware](https://github.com/foostan/kbd_firmware); see [Cornelius](#cornelius)) |
| `scripts/format_keymaps.py` | Aligns each `LAYOUT(...)` into a split grid (`--check` to verify) |
| `scripts/update_foostan.sh`, `scripts/link_foostan.sh` | Refresh the Cornelius definitions; link them into the QMK clone |
| `qmk.json` | List of keyboards to build (`qmk userspace-list`) |

## One-time setup

```sh
git clone --recurse-submodules https://github.com/wheredoesyourmindgo/serenity-qmk.git ~/Development/serenity-qmk
git clone https://github.com/qmk/qmk_firmware.git ~/Development/qmk_firmware
cd ~/Development/qmk_firmware && make git-submodule
qmk config user.qmk_home="$HOME/Development/qmk_firmware"
qmk config user.overlay_dir="$HOME/Development/serenity-qmk"
~/Development/serenity-qmk/scripts/link_foostan.sh   # makes the Cornelius buildable (see below)
brew install avrdude dfu-util   # flashing tools (dfu-programmer is also needed)
```

## Everyday use

```sh
qmk userspace-compile                   # build every keyboard in qmk.json
qmk flash -kb crkbd/rev1 -km serenity   # build + flash one keyboard
```

Build options go after `-e`, e.g. `-e QWERTY_BASE=yes`.

After editing a keymap, re-align its grid with `scripts/format_keymaps.py`.

## Editor setup (VS Code + clangd)

On each computer, after the one-time setup above:

1. Accept VS Code's prompt to install the recommended extensions (includes clangd). If Microsoft's C/C++ extension is installed, leave it — its IntelliSense is disabled for this workspace so it won't conflict.
2. Generate a compile database for the keyboard you're editing:

   ```sh
   qmk compile --compiledb -kb planck/rev6 -km serenity
   ```

`compile_commands.json` is gitignored and holds machine-specific paths, so every computer generates its own. Each run overwrites it, so re-run with a different `-kb` when you switch boards, then **clangd: Restart language server**. Shared code in `users/` and `modules/` works with any board's database.

## Updating QMK

```sh
cd ~/Development/qmk_firmware && git pull && make git-submodule
```

If a QMK change breaks the build, fix it here — there is nothing to merge.

## Updating Getreuer's modules

`modules/getreuer` is a git submodule pinned to one commit of [getreuer/qmk-modules](https://github.com/getreuer/qmk-modules), so upstream changes only arrive when you pull them:

```sh
cd ~/Development/serenity-qmk
git submodule update --remote modules/getreuer   # fetch the latest upstream
git -C modules/getreuer log --oneline -5         # see what changed
qmk userspace-compile                            # make sure everything still builds
git commit -am "Update getreuer modules" && git push
```

To undo an update before committing, run `git submodule update modules/getreuer` (goes back to the pinned commit).

If `modules/getreuer` is ever empty (e.g. after a plain `git clone`), run `git submodule update --init`.

Custom Shift Keys is enabled by the `modules` entry in each keymap's `keymap.json`. Its key table is in `users/serenity/shift_keys.c` and its options are in `users/serenity/config.h`.

## Cornelius

Both Cornelius boards build from foostan's own definitions in [foostan/kbd_firmware](https://github.com/foostan/kbd_firmware), not upstream QMK's `foostan/cornelius`. Upstream has only rev1, and foostan's rev1 is newer (it turns NKRO on, for example).

| Target | Board | Output | Flash |
|---|---|---|---|
| `foostan/corneliuskbd/rev1` | Cornelius (ATmega32u4) | `.hex` | `qmk flash -kb foostan/corneliuskbd/rev1 -km serenity` |
| `foostan/corneliuskbd/rev2` | Cornelius Low-profile (RP2040) | `.uf2` | Hold the top-left key while plugging in, then copy the `.uf2` onto the `RPI-RP2` drive |

QMK only reads keyboard definitions from its own tree, so `scripts/link_foostan.sh` links `vendor/foostan/corneliuskbd` into the QMK clone at `keyboards/foostan/corneliuskbd` and hides it from that clone's `git status`. Run it once per QMK clone (GitHub Actions runs it for you). If you see `Invalid keyboard: foostan/corneliuskbd/...`, run it again.

The keyboard files are a copy rather than a submodule, because foostan's repo has its own QMK and Vial submodules that `--recurse-submodules` would download. `vendor/foostan/corneliuskbd/SOURCE` records which foostan commit they came from. To pick up foostan's changes:

```sh
cd ~/Development/serenity-qmk
scripts/update_foostan.sh                  # fetch foostan's latest definitions
git diff vendor                            # see what changed
qmk userspace-compile                      # make sure everything still builds
git add vendor && git commit -m "Update foostan Cornelius definitions" && git push
```

To undo an update before committing, run `git checkout vendor`.

## GitHub Actions

Every push builds all targets in `qmk.json` and publishes the firmware files on the Releases page.
