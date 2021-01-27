#include "minishell.h"

int			print_entry(void)
{
	ft_printf("$> ");
	return (1);
}

int			do_exit(void)
{
	kill(getppid(), SIGKILL);
	exit(0);
    
}

int			do_echo(char *s)
{
	ft_printf("%s\n", s);
	return (1);
}





int			main(void)
{
	char	*s;

	while (print_entry() && get_next_line(STDIN_FILENO, &s))
	{
		handle_quotes(&s);
		do_echo(s);
		free(s);
	}
	return (0);
}