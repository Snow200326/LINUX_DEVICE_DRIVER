savedcmd_Profs_file.mod := printf '%s\n'   Profs_file.o | awk '!x[$$0]++ { print("./"$$0) }' > Profs_file.mod
