#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <signal.h>

#define SIGEXT 44

#define arg_val _IOWR('a', 'a', int32_t *)

 int done = 0;
int check = 0;

void ctrl_c_handler1(int n, siginfo_t *info , void * unsued)
{
    if (n == SIGINT)
    {
        printf("Received Ctrl-c \n");
        done = 1;
    }
}

void sig_event_handler(int n, siginfo_t *info , void * unsued)
{
    if (n == SIGEXT)
    {
        check = info->si_int;
        printf("Received signal from kernel : Value =  %u\n", check);
    }
}

int main()
{
    struct sigaction action;
    int32_t number;
    int fd;

    // ctrl-c interrupt
    sigemptyset(&action.sa_mask);
    action.sa_flags = (SA_SIGINFO | SA_RESETHAND);
    action.sa_sigaction = ctrl_c_handler1;
    sigaction(SIGEXT, &action, NULL);

    /* install custom signal handler */
    sigemptyset(&action.sa_mask);
    action.sa_flags = (SA_SIGINFO | SA_RESTART);
    action.sa_sigaction = sig_event_handler;
    sigaction(SIGEXT, &action, NULL);

    printf("Installed signal handler for SIGETX = %d\n", SIGEXT);

    fd = open("/dev/SignalName", O_RDWR);

    if (fd < 0)
    {
        // printf("Cannot open device file...\n");
        perror("open");
        return 0;
    }

    printf("Registering application ...");
    if (ioctl(fd, arg_val, &number))
    {
        printf("Failed\n");
        close(fd);
        exit(1);
    }

    printf("Done!!!\n");

    while (!done)
    {
        printf("Waiting for signal...\n");

        // blocking check
        while (!done && !check)
            ;
        check = 0;
    }
    printf("Closing Driver\n");

    close(fd);

    return 0;
}