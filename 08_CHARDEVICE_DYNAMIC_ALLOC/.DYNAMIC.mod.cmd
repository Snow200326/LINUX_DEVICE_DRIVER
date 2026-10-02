savedcmd_DYNAMIC.mod := printf '%s\n'   DYNAMIC.o | awk '!x[$$0]++ { print("./"$$0) }' > DYNAMIC.mod
