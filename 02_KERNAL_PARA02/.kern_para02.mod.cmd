savedcmd_kern_para02.mod := printf '%s\n'   kern_para02.o | awk '!x[$$0]++ { print("./"$$0) }' > kern_para02.mod
