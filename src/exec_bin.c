/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 13:51:54 by clala             #+#    #+#             */
/*   Updated: 2021/03/07 20:23:49 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <errno.h>
void 	print_error_bin(char *s)
{
 	ft_printf("%s: %s: %s\n", SHELL_NAME, MSG_CMD_NOT_FOUND, s);
}

static char			**get_argv_from_s(const char* program, const char* arg)
{
	char			*temp;
	char			**splitted;

	temp = ft_strnew(ft_strlen(program) + 1 + ft_strlen(arg));
	ft_strcpy(temp, program);
	ft_strcat(temp, " ");
    ft_strcat(temp, arg);
	splitted = ft_strsplit(temp, ' ');
	free(temp);
	return (splitted);
}

void run(const char* program, const char* arg)
{
    pid_t pid;
	extern char	**environ;
	char		**argv;		
 
	pid = fork();
    if (pid == -1)
        fprintf(stderr, "Unable to fork\n");
    else if (pid > 0) {
        printf("P> I am parent %d\n", getpid());
        printf("P> Child is %d\n", pid);
        int status;
        // wait(&status);
        waitpid(pid, &status, 0);
        printf("P> Wait OK\n");
        if (WIFEXITED(status)) {
            printf("P> Exit code = %d\n", WEXITSTATUS(status));
        }
        printf("\n");
    } else {
        // we are the child            
        printf("C> I am child %d of %d\n", getpid(), getppid());
		//if (execlp(program, program, arg, NULL) == -1)
		argv = get_argv_from_s(program, arg);
        if (execve(program, argv, environ) == -1) {
            fprintf(stderr, "Unable to exec\n");
        }
		free_2dchararr_terminated(argv);
        _exit(42);
    }
}

int exec_prog(char **argv, char **env)
{
 	pid_t   my_pid;
 	int 	 status, timeout /* unused ifdef WAIT_FOR_COMPLETION */;
	int res;

	res = -22;
	ft_printf("%d\n", res);
	my_pid = fork();
	char *a[] = {NULL};
	//char *b[] = {"b", "a", NULL};
	ft_printf("%d errno\n", errno);
 	if (-1 < my_pid)
 	{
		ft_printf("%s hello!\n", argv[1]);
		res = execve("/bin/echo", a, NULL);
		ft_printf("%d\n", res);
 	 	if (-1 == res)
 	 	{
			kill(my_pid, SIGTERM);
			print_error_bin(argv[0]);
			return -1;
 	 	}
 	}

 	
 	timeout = 3000;
 	while (0 == waitpid(my_pid , &status , WNOHANG))
 	{
 	 	if ( --timeout < 0 )
 	 	{
 	 	 	 	perror("timeout");
 	 	 	 	return -1;
 	 	}
 	 	sleep(1);
 	}

 	//printf("%s WEXITSTATUS %d WIFEXITED %d [status %d]\n",
 	// 	 	argv[0], WEXITSTATUS(status), WIFEXITED(status), status);

 	if (1 != WIFEXITED(status) || 0 != WEXITSTATUS(status)) {
 	 	 	perror("%s failed, halt system");
 	 	 	return -1;
 	}
 	kill(my_pid, SIGINT);
 	free_2dchararr_terminated(env);
 	return 0;
}

int				exec_command(t_shell *shell)
{
	char	*s;

	s = shell->cmd.cmd;
	if (ft_strequ("exit", s))
		exit(0);
	if ((ft_strequ(s, "env") || ft_strequ(s, "setenv") || 
	ft_strequ(s, "unsetenv")))
		do_environ(shell);
	else if (ft_strequ(s, "echo"))
		do_echo(shell->cmd);
	else if (ft_strequ(s, "cd"))
		do_cd(shell, s);
	else
		run(shell->cmd.cmd, shell->cmd.args);
	return (0);
}

void 	exec_bin()
{
 	;
}

int			do_echo(t_curr_cmd cmd)
{
	if (cmd.args)
		ft_printf("%s");
	ft_putchar('\n');
	return (1);
}