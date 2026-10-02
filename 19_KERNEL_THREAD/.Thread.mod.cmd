savedcmd_Thread.mod := printf '%s\n'   Thread.o | awk '!x[$$0]++ { print("./"$$0) }' > Thread.mod
