savedcmd_spinlock.mod := printf '%s\n'   spinlock.o | awk '!x[$$0]++ { print("./"$$0) }' > spinlock.mod
