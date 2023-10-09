/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adgutier <adgutier@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 10:32:11 by adgutier          #+#    #+#             */
/*   Updated: 2022/09/30 10:03:05 by adgutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		free(matrix[i]);
	free(matrix);
}

static int	countwords(const char *str, char charset)
{
	int	i;
	int	counter;

	counter = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i + 1] == charset || str[i + 1] == '\0') == 1
			&& (str[i] == charset || str[i] == '\0') == 0)
			counter++;
		i++;
	}
	return (counter);
}

unsigned int	countlet(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != c)
			i++;
	return (i);
}

static void	compara_split(char **matrix, const char *s, char c, int words)
{
	int	n;
	int	j;

	n = 0;
	j = 0;
	while (j < words)
	{
		while (*s == c)
			s++;
		matrix[j] = ft_calloc(countlet(s, c) + 1, sizeof(char));
		if (!matrix[j])
		{
			free_matrix(matrix);
			return ;
		}	
		while (*s != c && *s)
			matrix[j][n++] = *s++;
		n = 0;
		j++;
	}
}

char	**ft_split(char *s, char c)
{
	char	**matrix;
	int		words;

	if (!s)
		return (0);
	words = countwords(s, c);
	matrix = (char **)ft_calloc(words + 1, sizeof(char *));
	if (!matrix)
		return (0);
	compara_split(matrix, s, c, words);
	free(s);
	return (matrix);
}

/*
int		main(void)
{
	int i = 0;
	char **tab;
		
	tab = ft_split("me cago en to q no tira", ' ' );
	while (i < 7)
	{
		printf("string %d : %s\n", i, tab[i]);
		i++;
	}
	return (0);
}*/