#include "minishell.h"

int			print_entry(void)
{
	ft_printf("$> ");
	return (1);
}

int			do_exit(void)
{
	//kill(getppid(), SIGKILL); // close terminal
	exit(0);
    
}

int			handle_tilde(char *s)
{
	(void)s;
	//get $HOME from environ
	return (0);
}

int			do_echo(char *s)
{
	ft_printf("%s\n", s);
	return (1);
}

t_shell		*t_shell_new(void)
{
	t_shell	*new;

	if (!(new = (t_shell *)malloc(sizeof(t_shell))))
		handle_error(ERR_MALLOC);
	new->env = t_htable_init(INIT_HTABLE_SIZE, &cmp_func, &get_hash);
	if (!new->env)
		handle_error(ERR_MALLOC);
	return (new);
}

void		parse_environ(t_shell *shell, char **env)
{
	int		i;
	char	**splitted;
	char	*key;
	char	*value;

	i = 0;
	int j = 0;
	while (env[i])
	{
		splitted = ft_strsplit(env[i], '=');
		key = ft_strdup(splitted[0]);
		value = ft_strdup(splitted[1]);
		j = t_htable_add(shell->env->hash(key, shell->env->size),
			value, &shell->env);
		free_2dchararr_terminated(splitted);
		i++;
	}
	if ((i = t_htable_find(shell->env->hash(key, shell->env->size), value, shell->env)))
		ft_printf("%s\n", shell->env->table[i]);
	else
		ft_printf("no key\n");
	exit(0);
}

int			main(int argc, char **argv, char **env)
{
	char	*s;
	char	**splitted;
	t_shell	*shell;

	(void)argc;
	(void)argv;
	shell = t_shell_new();
	parse_environ(shell, env);
	while (print_entry() && get_next_line(STDIN_FILENO, &s))
	{
		//handle_quotes(&s);
		//do_echo(s);
		
		if (is_cd_command(s))
			do_cd(s);
		else 
		{
			splitted = ft_strsplit(s, ' ');
			exec_prog(splitted);
		}
		free(s);
	}
	return (0);
}
