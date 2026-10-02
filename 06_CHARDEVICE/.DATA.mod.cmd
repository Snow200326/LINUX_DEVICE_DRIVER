savedcmd_DATA.mod := printf '%s\n'   DATA.o | awk '!x[$$0]++ { print("./"$$0) }' > DATA.mod
