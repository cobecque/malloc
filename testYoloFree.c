#include <stdlib.h>

int		main(void)
{
	char	*addr;
	int		i;

	i = 0;
	while (i < 1024)
	{
		addr = (char *)malloc(sizeof(char) * 1024);
		addr[0] = 'a';
		addr[1023] = 'b';
		i++;
	}
	free(addr);
	return (0);
}
