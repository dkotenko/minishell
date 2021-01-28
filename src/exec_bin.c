#include "minishell.h"

/*
int pid = fork();
if (pid=0){
    int err;
    char *env[1] = { 0 };
    char *argv[3] = { "ls", "-l", 0 };
    err = execve("/bin/ls", argv, env);  //syscall, libc has simpler wrappers (man exec)
    exit(err); //if it got here, it's an error
} else if(pid<0) {
    printf("fork failed with error code %d\n", pid)
    exit(-1);
}

int status;
wait(&status); //simplest one, man wait for others
printf("child pid was %d, it exited with %d\n", pid, status);
exit(0);
*/

void    print_error_bin(char *s)
{
    ft_printf("minishell: command not found: %s\n", s);
}

int exec_prog(char **argv)
{
    pid_t   my_pid;
    int     status, timeout /* unused ifdef WAIT_FOR_COMPLETION */;

    if (0 == (my_pid = fork())) {
            if (-1 == execve(argv[0], (char **)argv , NULL)) {
                    print_error_bin(argv[0]);
                    return -1;
            }
    }

    
    timeout = 3000;
    while (0 == waitpid(my_pid , &status , WNOHANG)) {
            if ( --timeout < 0 ) {
                    perror("timeout");
                    return -1;
            }
            sleep(1);
    }

    //printf("%s WEXITSTATUS %d WIFEXITED %d [status %d]\n",
    //        argv[0], WEXITSTATUS(status), WIFEXITED(status), status);

    if (1 != WIFEXITED(status) || 0 != WEXITSTATUS(status)) {
            perror("%s failed, halt system");
            return -1;
    }
    return 0;
}



void    exec_bin()
{
    ;
}