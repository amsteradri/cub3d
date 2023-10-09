/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsignbr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adgutier <adgutier@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 16:08:47 by adgutier          #+#    #+#             */
/*   Updated: 2022/10/03 16:08:47 by adgutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_decimal_unsig(unsigned int nb)
{
	char	*str;
	int		i;

	i = 0;
	str = ft_itoa_base(nb, "0123456789");
	i = i + ft_putstr(str);
	free (str);
	return (i);
}
