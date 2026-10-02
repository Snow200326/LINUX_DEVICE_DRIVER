savedcmd_WorkQueuStatic.mod := printf '%s\n'   WorkQueuStatic.o | awk '!x[$$0]++ { print("./"$$0) }' > WorkQueuStatic.mod
