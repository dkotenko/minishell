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

int			do_echo(char *s)
{
	ft_printf("%s\n", s);
	return (1);
}



void		do_cd(char *s)
{
	char	*dir_path;

	s += ft_strlen("cd ");
	dir_path = ft_strnew(ft_strlen(s));
	ft_memcpy(dir_path, s, ft_strlen(s));
	chdir(dir_path);
	if (errno)
		perror("cd");
	
	
}



int			main(void)
{
	char	*s;
	char	**splitted;

	while (print_entry() && get_next_line(STDIN_FILENO, &s))
	{
		//handle_quotes(&s);
		//do_echo(s);
		
		if (ft_strnequ(s, "cd ", 3))
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