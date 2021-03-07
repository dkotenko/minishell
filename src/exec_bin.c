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

int			exec_implemented_commands(t_shell *shell)
{
	char	*s;

	s = shell->cmd.cmd;
	if (ft_strequ("exit", s))
		exit(0);
	if ((ft_strequ(s, "env") || ft_strequ(s, "setenv") ||
	ft_strequ(s, "unsetenv")) && do_environ(shell))
		return (1);
	if (ft_strequ(s, "echo") && do_echo(shell->cmd))
		return (1);
	if (ft_strequ(s, "cd") && do_cd(shell, s))
		return (1);
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