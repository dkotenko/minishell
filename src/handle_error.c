#include "minishell.h"

int		handle_error(char *s)
{
	ft_dprintf(STDERR_FILENO, "ERROR:\t%s\n", s);
	exit(0);
}