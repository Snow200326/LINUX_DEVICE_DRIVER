savedcmd_interrup.mod := printf '%s\n'   interrup.o | awk '!x[$$0]++ { print("./"$$0) }' > interrup.mod
