# Notes

## Fix Chibios Errors

### Step 1. Clone qmk_firmware repo

`gh repo clone qmk/qmk_firmware`

### Step 2. Copy over .git/modules/lib/* from cloned repo into project repo

`cp -R ./qmk_firmware/.git/modules/lib ./serenity_qmk/.git/modules/lib`

### Step 3. Reset the git submodules

```shell
cd ./serenity_qmk
git submodule deinit -f .
git submodule update --init
```
