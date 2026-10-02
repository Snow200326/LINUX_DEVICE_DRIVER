savedcmd_STATIC.mod := printf '%s\n'   STATIC.o | awk '!x[$$0]++ { print("./"$$0) }' > STATIC.mod
