/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 13:51:54 by clala             #+#    #+#             */
/*   Updated: 2020/02/15 21:53:21 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void 	print_error_bin(char *s)
{
 	ft_printf("minishell: command not found: %s\n", s);
}

int exec_prog(char **argv, char **env)
{
 	pid_t   my_pid;
 	int 	 status, timeout /* unused ifdef WAIT_FOR_COMPLETION */;

 	if (0 == (my_pid = fork()))
 	{
 	 	if (-1 == execve(argv[0], argv , env))
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

int			exec_implemented_commands(t_shell *shell, char *s)
{
	ft_strequ("exit", s) ? do_exit() : 0;
	if (ft_strequ(s, "env") || ft_strequ(s, "setenv ") ||
	ft_strequ(s, "unsetenv "))
		return (do_environ(shell, s));
	if (ft_strequ(s, "echo") && ft_printf("%s\n", s))
		return (1);
	if (ft_strequ(s, "echo ") && do_echo(s))
		return (1);
	if ((ft_strequ(s, "cd") || ft_strnequ(s, "cd ", 3)) && do_cd(shell, s))
		return (1);
	return (0);
}

void 	exec_bin()
{
 	;
}

int			do_exit()
{	
	//kill(getppid(), SIGKILL); // close terminal
	exit(0);
}

int			do_echo(char *s)
{
	char	**splitted;

	splitted = ft_strsplit(s, ' ');
	ft_printf("%s\n", splitted[1]);
	free_2dchararr_terminated(splitted);
	return (1);
}