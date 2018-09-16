/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 20:53:03 by cobecque          #+#    #+#             */
/*   Updated: 2018/02/12 02:06:56 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		count_word(char const *s, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			while (s[i] == c)
				i++;
			if (s[i] != '\0')
				count++;
		}
		else
			i++;
	}
	if (count == 0 && s[i - 1])
		count = 1;
	return (count);
}

static char		**ft_split(char const *s, char **tab, char c, int i)
{
	int		k;
	int		nb_lettre;
	int		j;

	i = 0;
	k = 0;
	while (s[i] != '\0')
	{
		nb_lettre = 0;
		while (s[i] == c)
			i++;
		if (s[i] == '\0')
			return (tab);
		j = i;
		while (s[i] != c && s[i] != '\0')
		{
			i++;
			nb_lettre++;
		}
		if ((tab[k] = (char *)malloc(sizeof(char) * nb_lettre + 1)) == NULL)
			return (NULL);
		tab[k] = ft_strsub(s, j, i - j);
		k++;
	}
	return (tab);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**tab;
	int		i;

	if (s)
	{
		i = 0;
		tab = (char **)malloc(sizeof(char *) * count_word(s, c) + 1);
		if (tab == NULL)
			return (NULL);
		tab = ft_split(s, tab, c, i);
		tab[count_word(s, c)] = NULL;
		return (tab);
	}
	return (NULL);
}
