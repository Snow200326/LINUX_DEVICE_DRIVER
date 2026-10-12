savedcmd_SignalSend.mod := printf '%s\n'   SignalSend.o | awk '!x[$$0]++ { print("./"$$0) }' > SignalSend.mod
