#include <stdio.h>

int		main()
{
	char	*str;

	str = malloc(10);
	strcpy(str, "Coucou lel lol");
	puts(str);
	free(str);
}
