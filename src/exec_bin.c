/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 13:51:54 by clala             #+#    #+#             */
/*   Updated: 2021/04/11 14:01:30 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				is_file_exists(const char* filename)
{
	struct stat	s_buffer;
	
    return (stat(filename,&s_buffer) == 0);
}

/*
int				is_file_access(char *filename, int access_type)
{
    return (access(filename, access_type ) == -1); //X_OK
}
*/
/*
void	get_dir_execs(char *dir_path)
{
	
}
*/



void run(t_shell *shell)
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
	//(WIFSIGNALED(state)) ? shell_print_signal(WTERMSIG(state)) : 0;
}

void			do_pwd(t_shell *shell, t_curr_cmd cmd)
{
	cmd.args = get_env(shell, ENV_PWD);
	do_echo(cmd);
}

int				is_builtin(char *name)
{
	char		*start;
	int			name_len;

	if (!(start = ft_strstr(BUILTIN_LIST, name)))
		return (0);
	name_len = ft_strlen(name);
	return (is_space_tab(*(start + name_len)) || !*(start + name_len));
}

void			do_type(t_curr_cmd cmd)
{
	(void)cmd;
	/*
	pwd is a shell builtin
oa-e3% type export
export is a reserved word
oa-e3% type varchar
varchar not found
oa-e3% type echo
echo is a shell builtin
*/
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
		do_cd(shell);
	else if (ft_strequ(s, "pwd"))
		do_pwd(shell, shell->cmd);
	else if (ft_strequ(s, "type"))
		do_type(shell->cmd);
	else
		run(shell);
	return (0);
}

int			do_echo(t_curr_cmd cmd)
{
	if (cmd.args)
		ft_printf("%s");
	ft_putchar('\n');
	return (1);
}