#!/usr/bin/env python3
"""Align every LAYOUT(...) in the Serenity keymaps into a readable grid.

Each keyboard maps a row's key count to the grid columns those keys occupy, so
short rows (thumb clusters, 2u keys, staggered rows) line up under the right
keys. Columns are sized per layer, and a wider gap separates the left and
right halves.

Usage: scripts/format_keymaps.py            # rewrite keymaps in place
       scripts/format_keymaps.py --check    # exit 1 if anything would change
"""

import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
INDENT = " " * 8
GAP = " " * 6


def cols(*ranges):
    out = []
    for r in ranges:
        out += list(r) if isinstance(r, range) else [r]
    return out


ORTHO_12 = {"slots": {12: cols(range(12))}, "gaps": [5]}

BOARDS = {
    "boardsource/technik_o": ORTHO_12,
    "foostan/cornelius": ORTHO_12,
    "planck": ORTHO_12,
    "signum/3_0": ORTHO_12,
    "vitamins_included": ORTHO_12,
    # 3 thumb keys per side, under the inner columns
    "crkbd": {"slots": {12: cols(range(12)), 6: cols(range(3, 9))}, "gaps": [5]},
    # Encoder button sits in its own center column
    "ristretto": {"slots": {12: cols(range(6), range(7, 13)), 13: cols(range(13))}, "gaps": [5, 6]},
    # Bottom row has two 2u spacebars, each starting a 2-column slot
    "boardwalk": {"slots": {14: cols(range(14)), 12: cols(range(6), 7, range(9, 14))}, "gaps": [6]},
    # Staggered 60% boards: no halves, keys placed under their physical neighbors
    "dztech/dz60rgb_ansi": {
        "slots": {14: cols(range(14)), 13: cols(range(12), 13), 12: cols(0, range(2, 12), 13), 8: cols(0, 1, 2, 6, 10, 11, 12, 13)},
        "gaps": [],
    },
    "hhkb/ansi": {
        "slots": {15: cols(range(15)), 14: cols(range(14)), 13: cols(range(13)), 5: cols(1, 2, 6, 11, 12)},
        "gaps": [],
    },
}


def split_args(s):
    """Split a macro body on top-level commas, keeping LT(x, y) etc. intact."""
    out, depth, cur = [], 0, ""
    for ch in s:
        depth += ch == "("
        depth -= ch == ")"
        if ch == "," and depth == 0:
            out.append(cur.strip())
            cur = ""
        else:
            cur += ch
    if cur.strip():
        out.append(cur.strip())
    return out


def strip_comments(s):
    s = re.sub(r"/\*.*?\*/", "", s, flags=re.S)
    return re.sub(r"//[^\n]*", "", s)


def find_layouts(src):
    """Yield (body_start, body_end, header_comment) for each LAYOUT call in the keymaps array."""
    for m in re.finditer(r"\[\w+\]\s*=\s*LAYOUT\w*\(", src):
        i = j = m.end()
        depth = 1
        while depth:
            depth += {"(": 1, ")": -1}.get(src[j], 0)
            j += 1
        body = src[i : j - 1]
        first_line, _, _ = body.partition("\n")
        header = first_line.strip() if first_line.strip().startswith("//") else ""
        yield i, j - 1, header, body


def format_file(path, board):
    src = path.read_text()
    layouts = list(find_layouts(src))
    layers = []
    for _, _, _, body in layouts:
        rows = [split_args(line) for line in strip_comments(body).split("\n") if line.strip()]
        placed = []
        for row in rows:
            if len(row) not in board["slots"]:
                sys.exit(f"{path}: no column map for a {len(row)}-key row")
            row = [re.sub(r",\s*", ", ", key) for key in row]  # LT(A,B) -> LT(A, B)
            placed.append(dict(zip(board["slots"][len(row)], row)))
        layers.append(placed)

    ncols = 1 + max(c for slots in board["slots"].values() for c in slots)

    new_bodies = []
    for (_, _, header, _), placed in zip(layouts, layers):
        width = [0] * ncols
        for row in placed:
            for c, key in row.items():
                width[c] = max(width[c], len(key) + 1)  # +1 for the comma
        lines = []
        for r, row in enumerate(placed):
            last_row = r == len(placed) - 1
            last_col = max(row)
            cells = []
            for c in range(ncols):
                key = row.get(c, "")
                if key and not (last_row and c == last_col):
                    key += ","
                cells.append(key.ljust(width[c]))
                if c in board["gaps"]:
                    cells.append(GAP)
            lines.append((INDENT + " ".join(cells)).rstrip())
        lead = f" {header}" if header else ""
        new_bodies.append(lead + "\n" + "\n".join(lines) + "\n    ")

    out = src
    for (start, end, _, _), new in reversed(list(zip(layouts, new_bodies))):
        out = out[:start] + new + out[end:]

    # Consistent indentation for layer lines, and keep clang-format from reflowing the grid
    out = re.sub(r"^\t(\[\w+\]\s*=)", r"    \1", out, flags=re.M)
    out = re.sub(r"\n    \)\};", "\n    )\n};", out)
    if "clang-format off" not in out:
        out = re.sub(r"^(const uint16_t PROGMEM keymaps)", r"// clang-format off\n\1", out, flags=re.M)
        out = re.sub(r"(\n\};\n)", r"\1// clang-format on\n", out, count=1)
    return src, out


def main():
    check = "--check" in sys.argv
    changed = []
    for board, cfg in BOARDS.items():
        path = ROOT / "keyboards" / board / "keymaps" / "serenity" / "keymap.c"
        before, after = format_file(path, cfg)
        if before != after:
            changed.append(path.relative_to(ROOT))
            if not check:
                path.write_text(after)
    for p in changed:
        print(("would reformat " if check else "reformatted ") + str(p))
    sys.exit(1 if check and changed else 0)


if __name__ == "__main__":
    main()
