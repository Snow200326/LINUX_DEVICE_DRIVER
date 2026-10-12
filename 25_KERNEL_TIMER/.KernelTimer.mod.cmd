savedcmd_KernelTimer.mod := printf '%s\n'   KernelTimer.o | awk '!x[$$0]++ { print("./"$$0) }' > KernelTimer.mod
