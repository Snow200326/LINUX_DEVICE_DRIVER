savedcmd_ADVANC.mod := printf '%s\n'   ADVANC.o | awk '!x[$$0]++ { print("./"$$0) }' > ADVANC.mod
