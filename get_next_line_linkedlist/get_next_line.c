/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 11:16:26 by yzhan             #+#    #+#             */
/*   Updated: 2024/06/03 14:33:28 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "get_next_line.h"

void ft_lstclear(t_list **list)
{
	t_list	*tmp;

	if (!list)
		return ;
	tmp = *list;
	while (tmp)
	{
		tmp = tmp->next;
		free(*list);
		*list = tmp;
	}
	*list = NULL;
}

static void	ft_create_list(t_list **list, int fd)
{
	int		chars;
	char	*buffer;

	chars = 1;
	//read chars into buffer, untill there is a '\n' in linked list string
	while ((*list && chars > 0 && !ft_find_newline(*list)) || !*list)
	{
		//initialize buffer
		buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buffer == NULL)
			return ;

		//read
		chars = read(fd, buffer, BUFFER_SIZE);

		//check read success or to EOF
		if (chars < 0)
		{
			free (buffer);
			ft_lstclear(list);
			return ;
		}
		//add '\0'
		buffer[chars] = '\0';
		//add buffer into linked list
		ft_add_list(list, buffer);
	}
	
}

static char	*ft_strdup_list(t_list *list)
{
	int		strlen;
	int		i;
	int		j;
	char	*next_line;

	if (list == NULL)
		return (NULL);
	strlen = ft_strlen_newline(list);
	//malloc strlenn + 1 to next_line
	next_line = (char *)malloc(sizeof(char) * (strlen + 1));
	if (!next_line)
		return (NULL);
	//copy string from list to next_line
	j = 0;
	while (list)
	{
		i = 0;
		while (list->str[i])
		{
			if (list->str[i] == '\n')
			{
				next_line[j++] = '\n';
				next_line[j] = '\0';
				return (next_line);
			}
			next_line[j++] = list->str[i++];
		}
		list = list->next;
	}
	next_line[j] = '\0';
	return (next_line);
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != 0)
		i++;
	return (i);
}

static void	ft_refresh_list(t_list **list)
{
	t_list	*last;
	t_list	*clean;
	int		i;
	int		j;
	char	*buffer;

	
	clean = malloc(sizeof(t_list));
	if (!clean)
		return ;
	last = ft_lstlast(*list);
	i = 0;
	j = 0;
	while (last->str[i] && last->str[i] != '\n')
		i++;
	if (last->str[i] && last->str[i] == '\n')
		i++;
	buffer = malloc(sizeof(char) * (ft_strlen(last->str) - i + 1));
	if (!buffer)
		return ;

	while (last->str[i])
		buffer[j++] = last->str[i++];
	buffer[j] = '\0';
	clean->str = buffer;
	clean->next = NULL;
	ft_clean_list(list, clean, buffer);
}

char	*get_next_line(int fd)
{
	//initialze
	static t_list	*list;
	char			*next_line;


	//check error: fd > 0, BUFFER_SIZE, read success
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0) == -1)
	{
		ft_lstclear(&list);
		return (NULL);
	}

	//create linked list untill it meet '\n'
	ft_create_list(&list, fd);

	//check
	if (!list)
		return (NULL);

	//put the chars before '\n' into string from list
	//strdup
	next_line = ft_strdup_list(list);
	/*if(!next_line)
	{
		ft_lstclear(&list);
		//free(next_line);
		return (NULL);
	}*/

	//refresh list for next read
	ft_refresh_list(&list);
	if (next_line[0] == '\0' && list != NULL)
	{
		free (next_line);
		ft_lstclear(&list);
		return (NULL);
	}
	return (next_line);
}
