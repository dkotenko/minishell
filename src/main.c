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
	//get $HOME from environ
}

int			do_echo(char *s)
{
	ft_printf("%s\n", s);
	return (1);
}

int			main(int argc, char **argv, char **env)
{
	char	*s;
	char	**splitted;

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
