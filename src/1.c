#include "libft.h"
#include <stdlib.h>

int main()
{

	char *s;
	
	ft_printf("got: %s\n", "hello");
	
	while (get_next_line(STDIN_FILENO, &s))
	{
		//if (ft_strequ(s, "exit"))
		//	exit(0);
		ft_printf("got: %s\n", s);
		
		
		free(s);
		//if (++i == 3)
		//	break ;
		
	}
	exit(0);
	
}
