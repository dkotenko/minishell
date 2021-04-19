#include "minishell.h"

void	do_pwd(t_shell *shell, t_curr_cmd cmd)
{
	if (cmd.args)
	{
		ft_printf("pwd: %s\n", ERR_TOO_MANY_ARGS);
		return ;
	}
	cmd.args = get_env(shell, ENV_PWD);
	do_echo(&cmd);
}

static int	is_builtin(char *name)
{
	char		*start;
	int			name_len;

	start = ft_strstr(BUILTIN_LIST, name);
	if (!(start))
		return (0);
	name_len = ft_strlen(name);
	return (is_space_tab(*(start + name_len)) || !*(start + name_len));
}

void	do_type(t_shell *shell, t_curr_cmd cmd)
{
	char	*exec;

	if (!cmd.args)
		return ;
	exec = t_htable_get(shell->executables, cmd.args);
	if (exec)
		ft_printf("%s is %s\n", cmd.args, exec);
	else if (is_builtin(cmd.args))
		ft_printf("%s is a %s builtin\n", cmd.args, SHELL_NAME);
	else
		ft_printf("%s not found\n", cmd.args);
}

int	do_echo(t_curr_cmd *cmd)
{
	int		len;
	char	*s;
	char	*temp;

	if (cmd->args)
	{
		s = cmd->args;
		len = ft_strlen(s);
		if (len > 1 && \
			((s[0] == SYMBOL_SQUOTE && s[len - 1] == SYMBOL_SQUOTE) || \
			(s[0] == SYMBOL_DQUOTE && s[len - 1] == SYMBOL_DQUOTE)))
		{
			temp = cmd->args;
			cmd->args = ft_strnew(len - 2);
			ft_strncpy(cmd->args, temp + 1, len - 2);
			ft_free_int(temp);
		}
		ft_printf("%s", cmd->args);
	}	
	ft_putchar('\n');
	return (1);
}
