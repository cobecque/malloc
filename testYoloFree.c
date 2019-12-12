#include <stdlib.h>

int		main(void)
{
	char	*addr;
	int		i;

	i = 0;
	while (i < 1024)
	{
		addr = (char *)malloc(sizeof(char) * 1024);
		addr = realloc(0, 416);
		i++;
	}
	free(addr);
	return (0);
}
