savedcmd_CHARD_FO.mod := printf '%s\n'   CHARD_FO.o | awk '!x[$$0]++ { print("./"$$0) }' > CHARD_FO.mod
