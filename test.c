#include <stdio.h>
#include <unistd.h>
#define M (1024 * 1024)

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		ft_putchar(str[i]);
		i++;
	}
}

int		main()
{
	char *str;
	int	i;

	i = 0;
	while (i < 1024)
	{
		str = (char *)malloc(sizeof(char) * 1024);
		i++;
	}
	return (0);
}
