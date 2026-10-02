savedcmd_WorkQueueDynamic.mod := printf '%s\n'   WorkQueueDynamic.o | awk '!x[$$0]++ { print("./"$$0) }' > WorkQueueDynamic.mod
