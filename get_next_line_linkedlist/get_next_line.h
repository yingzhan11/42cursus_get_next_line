/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 11:16:18 by yzhan             #+#    #+#             */
/*   Updated: 2024/06/03 14:33:25 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

//buffer_size
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 3
# endif

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>

//linked list
typedef struct s_list
{
	char	*str;
	struct s_list	*next;
} t_list;

char	*get_next_line(int fd);
int		ft_find_newline(t_list *list);
t_list	*ft_lstlast(t_list *list);
void	ft_add_list(t_list **list, char *buffer);
int		ft_strlen_newline(t_list *list);
void	ft_clean_list(t_list **list, t_list *clean, char *buffer);
void ft_lstclear(t_list **list);

# endif
