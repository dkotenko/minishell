/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 13:51:54 by clala             #+#    #+#             */
/*   Updated: 2021/03/13 00:11:06 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char			**get_argv_from_s(const char* program, const char* arg)
{
	char			*temp;
	char			**splitted;

	if (arg)
	{
		temp = ft_strnew(ft_strlen(program) + 1 + ft_strlen(arg));
		ft_strcpy(temp, program);
		ft_strcat(temp, " ");
    	ft_strcat(temp, arg);
	}
	else
		temp = (char *)program;
	//ft_printf("%s\n", temp);
	splitted = ft_strsplit(temp, ' ');
	free(temp);
	return (splitted);
}

int				exec_exists(const char* filename)
{
	struct stat	s_buffer;
	
    return (stat(filename,&s_buffer) == 0);
}

int				exec_has_access(char *filename)
{
    return (access(filename, X_OK ) == -1);
}

//unix ищет файл во всех папках с начала до конца, запускает первый
char			get_exec_path(char *program, char **environ)
{
	char		**splitted_path;
	char		*path;
	char		**temp;

	path = ft_getenv("PATH");
	free(path);
	temp = splitted_path;
	splitted_path = ft_strsplit(path, ';');
	while (*temp)
	{
		
		temp++;
	}
	free_2dchararr_terminated(splitted_path);
}
	

void run(const char* program, const char* arg)
{
	char	**argv;
	pid_t	pid;
	int		state;
	extern char	**environ;
	char		*program_path;
	
	//ft_printf("%s\n", program);
	program_path = NULL;
	pid = fork();
	if (pid == -1)
		exit(printf("error\n"));
	if (!pid)
	{
		program_path = get_exec_path(program, environ);
		argv = get_argv_from_s(program, arg);
		if (!program_path || -1 == execve(argv[0], argv, environ))
			ft_printf("%s: %s: %s\n", SHELL_NAME, MSG_CMD_NOT_FOUND, argv[0]);
		free_2dchararr_terminated(argv);
		exit(EXIT_SUCCESS);
	}
	else
		waitpid(pid, &state, 0);
	//(WIFSIGNALED(state)) ? shell_print_signal(WTERMSIG(state)) : 0;
}

int				exec_command(t_shell *shell)
{
	char	*s;

	s = shell->cmd.cmd;
	if (!s || !ft_strlen(s))
		return (0);
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

int			do_echo(t_curr_cmd cmd)
{
	if (cmd.args)
		ft_printf("%s");
	ft_putchar('\n');
	return (1);
}