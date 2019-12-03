/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 10:52:06 by ashishae          #+#    #+#             */
/*   Updated: 2019/12/01 16:18:28 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include <unistd.h>

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}


void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list *last;

	if (*alst == NULL)
		*alst = new;
	else if (alst && new && *alst)
	{
		last = ft_lstlast(*alst);
		last->next = new;
	}
}


t_list	*ft_lstnew(void *content)
{
	t_list	*result;

	if (!(result = malloc(sizeof(t_list))))
		return (NULL);
	result->content = content;
	result->next = NULL;
	return (result);
}
