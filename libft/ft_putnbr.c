/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adgutier <adgutier@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:09:51 by adgutier          #+#    #+#             */
/*   Updated: 2022/10/03 13:09:51 by adgutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_negative(int *value)
{
	int	i;

	i = 0;
	if (*value == INT_MIN)
	{
		i = 1;
		ft_putchar('-');
		ft_putchar('2');
		*value = 147483648;
		i++;
	}
	else if (*value < 0)
	{
		ft_putchar('-');
		*value *= -1;
		i++;
	}
	return (i);
}

int	ft_decimal(int nb)
{
	char	*str;
	int		i;

	i = ft_negative(&nb);
	str = ft_itoa_base(nb, "0123456789");
	i = i + ft_putstr(str);
	free (str);
	return (i);
}
