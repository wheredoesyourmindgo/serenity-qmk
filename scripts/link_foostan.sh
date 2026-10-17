#!/bin/sh
# Link vendor/foostan/corneliuskbd into the QMK clone as keyboards/foostan/corneliuskbd.
# QMK only reads keyboard definitions from its own tree, so this is needed once per
# QMK clone (also run by GitHub Actions). Safe to re-run.
set -e

root=$(cd "$(dirname "$0")/.." && pwd)
qmk_home=$(qmk config -ro user.qmk_home | sed 's/^[^=]*=//; s/ (.*)$//')
src="$root/vendor/foostan/corneliuskbd"
dest="$qmk_home/keyboards/foostan/corneliuskbd"

if [ -e "$dest" ] && [ ! -L "$dest" ]; then
    echo "$dest exists and isn't a link; leaving it alone" >&2
    exit 1
fi
ln -sfn "$src" "$dest"

# Keep the QMK clone's `git status` clean (local-only ignore, never committed)
exclude="$qmk_home/.git/info/exclude"
if [ -f "$exclude" ] && ! grep -qx 'keyboards/foostan/corneliuskbd' "$exclude"; then
    echo 'keyboards/foostan/corneliuskbd' >> "$exclude"
fi
echo "Linked $dest -> $src"
