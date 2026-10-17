#!/usr/bin/env python3
"""Build one clangd compile database covering every keyboard in qmk.json.

`qmk compile --compiledb` describes a single keyboard, overwrites the previous
database, and deletes the previous keyboard's generated headers. Keymaps never
appear in it either, because QMK #includes them from a generated file. So this
builds each target, keeps a copy of its generated headers, adds an entry for
its keymap, and merges everything into compile_commands.json.

Usage: scripts/compiledb.py                          # every keyboard in qmk.json
       scripts/compiledb.py planck/rev6 crkbd/rev1  # rebuild just these
"""

import json
import re
import shutil
import subprocess
import sys
from functools import partial
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
DB = ROOT / "compile_commands.json"
STASH = ROOT / ".build" / "compiledb"
OBJ_SRC = re.compile(r"\.build/(obj_[^/\"]+)/src")
KEYMAP_C = re.compile(r'^-DOTHER_KEYMAP_C="(.+)"$')
DEP_FLAGS = {"-MMD", "-MP"}


def build(keyboard, keymap):
    """Compile one target and return its database entries."""
    subprocess.run(
        ["qmk", "compile", "--compiledb", "-kb", keyboard, "-km", keymap],
        check=True,
        stdout=subprocess.DEVNULL,
    )
    return json.loads(DB.read_text())


def relocate(entries):
    """Copy generated headers out of qmk_firmware/.build and repoint entries at the copies."""
    copied = set()

    def repoint(match, directory):
        obj = match.group(1)
        dest = STASH / obj / "src"
        if obj not in copied:
            shutil.rmtree(dest, ignore_errors=True)
            shutil.copytree(Path(directory) / ".build" / obj / "src", dest)
            copied.add(obj)
        return str(dest)

    for e in entries:
        fix = partial(OBJ_SRC.sub, partial(repoint, directory=e["directory"]))
        args, skip = [], False
        for a in e["arguments"]:
            if skip:
                skip = False
            elif a == "-MF":
                skip = True
            elif a not in DEP_FLAGS:
                args.append(fix(a))
        e["arguments"] = args
        e["file"] = fix(e["file"])
    return entries


def keymap_entry(entries):
    """Make an entry for the keymap from the flags used to compile the userspace."""
    for e in entries:
        for a in e["arguments"]:
            if m := KEYMAP_C.match(a):
                return {**e, "file": m.group(1)}
    return None


def main():
    targets = json.loads((ROOT / "qmk.json").read_text())["build_targets"]
    previous = []
    if sys.argv[1:]:
        targets = [t for t in targets if t[0] in sys.argv[1:]]
        if DB.exists():
            previous = json.loads(DB.read_text())  # keep the other keyboards

    merged = {}
    for keyboard, keymap in targets:
        print(f"Building {keyboard}:{keymap}")
        entries = relocate(build(keyboard, keymap))
        if km := keymap_entry(entries):
            entries.append(km)
        for e in entries:
            path = str((Path(e["directory"]) / e["file"]).resolve())
            merged.setdefault(path, e)  # shared files keep the first board's flags
    for e in previous:
        merged.setdefault(str((Path(e["directory"]) / e["file"]).resolve()), e)

    DB.write_text(json.dumps(list(merged.values()), indent=2))
    print(f"Wrote {len(merged)} entries for {len(targets)} keyboards to {DB.name}")


if __name__ == "__main__":
    main()
