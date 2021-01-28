#include "minishell.h"

int			is_cd_command(char *s)
{
	if (ft_strnequ(s, "cd", 2) && (s[2] == ' ' || s[2] == 0))
		return (1);
	return (0);

}

void		do_cd(char *s)
{
	char	*dir_path;

	if (s[2] == ' ')
		s += ft_strlen("cd ");
	else
		s += ft_strlen("cd");
	dir_path = ft_strnew(ft_strlen(s));
	ft_memcpy(dir_path, s, ft_strlen(s));
	chdir("");
	free(dir_path);
}

