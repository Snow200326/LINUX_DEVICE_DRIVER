savedcmd_STARTSTOP.mod := printf '%s\n'   START.o STOP.o | awk '!x[$$0]++ { print("./"$$0) }' > STARTSTOP.mod
