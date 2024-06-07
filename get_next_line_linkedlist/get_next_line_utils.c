/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 11:36:40 by yzhan             #+#    #+#             */
/*   Updated: 2024/06/03 14:33:27 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_find_newline(t_list *list)
{
	int	i;

	if (!list)
		return (0);
	while (list)
	{
		i = 0;
		while (list->str[i] && i < BUFFER_SIZE)
		{
			if (list->str[i] == '\n')
				return (1);
			i++;
		}
		list = list->next;
	}
	return (0);
}

t_list	*ft_lstlast(t_list *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

void	ft_add_list(t_list **list, char *buffer)
{
	t_list	*new;
	t_list	*last;

	//check exist
	if (!list || !buffer)
		return ;
	//initialize new node
	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return ;
	//to last node
	last = ft_lstlast(*list);
	if (!last)
		*list = new;
	else
		last->next = new;
	//new node content
	new->str = buffer;
	new->next = NULL;
}

int	ft_strlen_newline(t_list *list)
{
	int	len;
	int	i;

	if (!list)
		return (0);
	len = 0;
	while (list)
	{
		i = 0;
		while (list->str[i])
		{
			if (list->str[i] == '\n')
			{
				len++;
				return (len);
			}
			i++;
			len++;
		}
		list = list->next;
	}
	return (len);
}

void	ft_clean_list(t_list **list, t_list *clean, char *buffer)
{
	t_list	*tmp;

	if (!*list)
		return ;
	while (*list)
	{
		tmp = (*list)->next;
		free((*list)->str);
		free(*list);
		*list = tmp;
	}
	*list = NULL;
	if (clean->str[0])
		*list = clean;
	else
	{
		free(buffer);
		free(clean);
	}
}
