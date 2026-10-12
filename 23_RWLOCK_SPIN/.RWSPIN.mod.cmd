savedcmd_RWSPIN.mod := printf '%s\n'   RWSPIN.o | awk '!x[$$0]++ { print("./"$$0) }' > RWSPIN.mod
