savedcmd_KERNAL.mod := printf '%s\n'   KERNAL.o | awk '!x[$$0]++ { print("./"$$0) }' > KERNAL.mod
