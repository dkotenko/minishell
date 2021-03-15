#include "libft.h"

int main()
{
	//ft_printf("ghehe\n");
	t_htable *t = t_htable_init(1, &cmp_func, &hash_func_fnv_1a_32);
	//ft_printf("%d\n", t == NULL);

	char *a = ft_strdup("13");
	char *b = ft_strdup("25");
	char *c;
	for (int i = 1; i < 255; i++)
	{
		c = ft_strnew(1);
		c[0] = i;
		t_htable_set(t, c, c);
	}
	
	

	
	t_htable_set(t, a, a);
	t_htable_set(t, b, b);
	return (0);
}
