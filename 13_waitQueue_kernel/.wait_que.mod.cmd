savedcmd_wait_que.mod := printf '%s\n'   wait_que.o | awk '!x[$$0]++ { print("./"$$0) }' > wait_que.mod
