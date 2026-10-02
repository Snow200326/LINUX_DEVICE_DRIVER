savedcmd_Sysfile.mod := printf '%s\n'   Sysfile.o | awk '!x[$$0]++ { print("./"$$0) }' > Sysfile.mod
