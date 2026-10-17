#!/bin/sh
# Copy foostan's latest Cornelius rev1/rev2 keyboard definitions into vendor/.
# They live in foostan/kbd_firmware, not upstream QMK. Review with `git diff vendor`.
set -e

repo_url=https://github.com/foostan/kbd_firmware.git
src_path=keyboards/cornelius/qmk/qmk_firmware
root=$(cd "$(dirname "$0")/.." && pwd)
dest="$root/vendor/foostan/corneliuskbd"

tmp=$(mktemp -d)
trap 'rm -rf "$tmp"' EXIT

# Shallow, sparse, no nested submodules: only the files we need
git clone --quiet --depth 1 --filter=blob:none --sparse "$repo_url" "$tmp/kbd_firmware"
git -C "$tmp/kbd_firmware" sparse-checkout set "$src_path"
src="$tmp/kbd_firmware/$src_path"

rm -rf "$dest"
mkdir -p "$dest/rev1" "$dest/rev2"
cp "$src/readme.md" "$dest/"
cp "$src/rev1/keyboard.json" "$dest/rev1/"
cp "$src/rev2/keyboard.json" "$dest/rev2/"

commit=$(git -C "$tmp/kbd_firmware" log -1 --format='%H %cs')
printf '%s\n' "$repo_url $src_path" "$commit" > "$dest/SOURCE"
echo "Updated vendor/foostan/corneliuskbd to foostan/kbd_firmware $commit"
