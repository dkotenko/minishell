/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 13:51:54 by clala             #+#    #+#             */
/*   Updated: 2021/04/23 20:35:36 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run(t_shell *shell)
{
	char	**argv;
	pid_t	pid;
	int		state;
	char	**environ;

	environ = get_environ(shell);
	argv = get_argv(shell, &shell->cmd);
	pid = fork();
	if (pid == -1)
		exit(ft_printf("fork error\n"));
	if (!pid)
	{
		if (!argv[0] || -1 == execve(argv[0], argv, environ))
			ft_printf("%s: %s: %s\n", SHELL_NAME, MSG_CMD_NOT_FOUND, argv[0]);
		exit(EXIT_SUCCESS);
	}
	else
		waitpid(pid, &state, 0);
	free_2dchararr_terminated(argv);
	free_2dchararr_terminated(environ);
}

int	exec_command(t_shell *shell)
{
	char	*s;

	s = shell->cmd.cmd;
	if (!s || !ft_strlen(s))
		return (0);
	if (ft_strequ("exit", s))
		exit(0);
	if (ft_strequ(s, "env") || ft_strequ(s, "setenv") || \
	ft_strequ(s, "unsetenv") || ft_strequ(s, "unset") || \
	ft_strequ(s, "export"))
		do_environ(shell);
	else if (ft_strequ(s, "echo"))
		do_echo(&shell->cmd);
	else if (ft_strequ(s, "cd"))
		do_cd(shell);
	else if (ft_strequ(s, "pwd"))
		do_pwd(shell, shell->cmd);
	else if (ft_strequ(s, "type"))
		do_type(shell, shell->cmd);
	else
		run(shell);
	return (0);
}
