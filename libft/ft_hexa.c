/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adgutier <adgutier@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 11:36:04 by adgutier          #+#    #+#             */
/*   Updated: 2022/10/04 11:36:04 by adgutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_hexa(unsigned int nb)
{
	char	*str;
	int		i;

	i = 0;
	str = ft_itoa_base(nb, "0123456789abcdef");
	i = ft_putstr(str);
	free (str);
	return (i);
}
