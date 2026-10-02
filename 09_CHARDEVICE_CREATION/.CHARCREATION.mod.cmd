savedcmd_CHARCREATION.mod := printf '%s\n'   CHARCREATION.o | awk '!x[$$0]++ { print("./"$$0) }' > CHARCREATION.mod
