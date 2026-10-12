savedcmd_SpinlocokBt.mod := printf '%s\n'   SpinlocokBt.o | awk '!x[$$0]++ { print("./"$$0) }' > SpinlocokBt.mod
