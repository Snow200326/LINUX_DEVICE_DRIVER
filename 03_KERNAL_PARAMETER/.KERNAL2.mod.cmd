savedcmd_KERNAL2.mod := printf '%s\n'   KERNAL2.o | awk '!x[$$0]++ { print("./"$$0) }' > KERNAL2.mod
