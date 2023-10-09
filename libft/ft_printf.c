/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adgutier <adgutier@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:14:34 by adgutier          #+#    #+#             */
/*   Updated: 2022/10/04 12:14:34 by adgutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_types(va_list args, const char format)
{
	int	i;

	i = 0;
	if (format == 'c')
		i = ft_char(va_arg(args, int));
	else if (format == 's')
		i = ft_putstr(va_arg(args, char *));
	else if (format == 'p')
		i = ft_void(va_arg(args, void *));
	else if (format == 'i' || format == 'd')
		i = ft_decimal(va_arg(args, int));
	else if (format == 'u')
		i = ft_decimal_unsig(va_arg(args, unsigned long));
	else if (format == 'x')
		i = ft_hexa(va_arg(args, unsigned long));
	else if (format == 'X')
		i = ft_hexamayus(va_arg(args, unsigned long));
	else if (format == '%')
		i = ft_printpercent();
	return (i);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	va_list	args;
	int		content;

	i = 0;
	content = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			content += ft_types(args, str[i + 1]);
			i++;
		}
		else
			content += ft_char(str[i]);
		i++;
	}
	va_end(args);
	return (content);
}

// int main()
// {
// 	ft_printf("First number: %d\n", 12345);
// }
