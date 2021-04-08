#include "libft.h"

int main()
{
	int i = 0;
	char *s;
	while (get_next_line(STDIN_FILENO, &s))
	{
		//if (ft_strequ(s, "exit"))
		//	exit(0);
		
		if (++i == 3)
			break ;
		free(s);
		
	}
	exit(0);
}
