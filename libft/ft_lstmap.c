/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adgutier <adgutier@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 21:25:16 by adgutier          #+#    #+#             */
/*   Updated: 2022/09/30 10:08:20 by adgutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lista_pito;
	t_list	*aunxiliar_pito;

	if (!lst || !f || !del)
		return (0);
	lista_pito = ft_lstnew((*f)(lst->content));
	if (!lista_pito)
		return (0);
	aunxiliar_pito = lista_pito;
	lst = lst->next;
	while (lst)
	{
		lista_pito->next = ft_lstnew((*f)(lst->content));
		if (!lista_pito->next)
		{
			ft_lstclear(&aunxiliar_pito, del);
			return (0);
		}
		lista_pito = lista_pito->next;
		lst = lst->next;
	}
	lista_pito->next = NULL;
	return (aunxiliar_pito);
}
