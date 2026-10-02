savedcmd_Mutex_datta.mod := printf '%s\n'   Mutex_datta.o | awk '!x[$$0]++ { print("./"$$0) }' > Mutex_datta.mod
