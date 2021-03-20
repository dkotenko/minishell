#include "libft.h"

int main()
{
	//ft_printf("ghehe\n");
	t_htable *t = t_htable_init(1, &cmp_func, &hash_func_fnv_1a_32);
	//ft_printf("%d\n", t == NULL);

	char *a = ft_strdup("13");
	char *b = ft_strdup("13");
	char *c;
	for (int i = 1; i < 255; i++)
	{
		c = ft_strnew(1);
		c[0] = (i % 59) + 50;
		t_htable_set(&t, c, c);
	}
	t_htable_add(&t, a, a);
	t_htable_add(&t, b, b);
	t_htable_add(&t, b, b);
	t_htable_add(&t, b, b);
	t_htable_add(&t, b, b);

	char **keys = (char **)t_htable_get_keys(t);
	int i = 0;
	while (keys[i])
	{
		ft_printf("%d %s\n", i, keys[i]);
		i++;
	}
	return (0);
}
