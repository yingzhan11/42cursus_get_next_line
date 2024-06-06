/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:30:12 by yzhan             #+#    #+#             */
/*   Updated: 2024/06/05 16:42:04 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdio.h>
#include <fcntl.h>

int	ft_any_line(char *line, int n)
{
	int i;

	i = 0;
	while (i < n && line)
	{
		if (line[i])
			return (1);
		i++;
	}
	return (0);
}

#define n (ac - 1)

int	main(int ac, char **av)
{
	int		fd[n];
	char	*line[n];
	int		nb_line[n];
	int		i;

    printf("-----BUFFER_SIZE: %d-----\n", BUFFER_SIZE);
	if (ac == 1)
    {
        i = 1;
        printf("-fd is %d-\n", STDIN_FILENO);
        printf("Enter input here (CTRL+D to end input): \n");
        line[n] = get_next_line(STDIN_FILENO);
        if (!line[n])
		    printf("ERROR: line %d -> %s\n", i++, line[n]);
	    while (line[n])
	    {
	    	printf("line %d -> %s", i++, line[n]);
			free(line);
	    	line[n] = get_next_line(STDIN_FILENO);
	    }
    }
	else if (ac > 1)
	{
		printf("-----running bonus test: open multiple files-----\n");
		i = 0;
		while (i < n)
		{
			fd[i] = open(av[i + 1], O_RDONLY);
			if (fd[i] < 0)
			{
				printf("fd %d: Error FD of the av[%d] file\n", fd[i], i + 1);
				return (0);
			}
			nb_line[i] = 1;
			i++;
		}
		i = 0;
		while (i < n)
		{
			line[i] = get_next_line(fd[i]);
			i++;
		}
		while (ft_any_line(*line, n) == 1)
		{
			i = 0;
			while (i < n)
			{
				if (!line[i])
					printf("fd %d: EOF -> %s\n", fd[i], line[i]);
				else
				{
					printf("fd %d: line %d -> %s", fd[i], nb_line[i]++, line[i]);
					free(line);
					line[i] = get_next_line(fd[i]);
				}
				i++;
			}
		}
	}
	printf("-----TEST END-----\n");
	if (*line)
		free(line);
	return (0);
}
