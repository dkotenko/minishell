#include "minishell.h"

int			print_entry(void)
{
	ft_printf("$> ");
	return (1);
}

int			main(void)
{
	char	*s;

	while (print_entry() && get_next_line(STDIN_FILENO, &s))
	{
		;
	}
	return (0);
}