savedcmd_KERNAL_PRA.mod := printf '%s\n'   KERNAL_PRA.o | awk '!x[$$0]++ { print("./"$$0) }' > KERNAL_PRA.mod
