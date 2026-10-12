savedcmd_HRTTIMER.mod := printf '%s\n'   HRTTIMER.o | awk '!x[$$0]++ { print("./"$$0) }' > HRTTIMER.mod
