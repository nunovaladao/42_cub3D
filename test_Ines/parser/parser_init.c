/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:40:19 by inesalves         #+#    #+#             */
/*   Updated: 2023/11/25 21:41:01 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * @brief loops until every value is saved
 * @param test -> for gnl
 * @param map -> struct of map
 * @param fd -> file descriptor
 * @return int 
 */
int	check_text(char *test, t_map *map, int fd)
{
	while (!map->e_texture || !map->w_texture || !map->s_texture \
	|| !map->n_texture || !map->color_c || !map->color_f)
	{
		test = get_next_line(fd);
		if (!test)
		{
			printf("Error!\nMissing Values\n");
			return (1);
		}
		test = cleaning_func(test);
		if (save_value(test, map))
		{
			free(test);
			test = NULL;
			return (1);
		}
		free(test);
		test = NULL;
	}
	free(test);
	test = NULL;
	return (0);
}

char	*get_to_map(char *test, int fd)
{
	int	i;

	i = 0;
	while (!test)
	{
		test = get_next_line(fd);
		if (test[i] == ' ' || test[i] == '\t' || test[i] == '\n')
		{
			if (test[0] == '\n')
			{
				free(test);
				test = NULL;
			}
			else
				test = test_spaces(test);
		}
	}
	return (test);
}

/**
 * @brief main function
 * @param fd -> file descriptor
 * @param map -> map struct
 * @return int 
 */
int	parse_gnl(int fd, t_map *map)
{
	char	*test;

	test = NULL;
	if (check_text(test, map, fd))
		return (1);
	test = get_to_map(test, fd);
	if (!test)
	{
		printf("Error!\nMap: No map!\n");
		return (1);
	}
	if (start_map(test, fd, map))
		return (1);
	printf("%s\n", map->n_texture);
	printf("%s\n", map->s_texture);
	printf("%s\n", map->e_texture);
	printf("%s\n", map->w_texture);
	printf("%s\n", map->color_c);
	printf("%s\n", map->color_f);
	map->c_color = get_base_10(map->color_c);
	map->f_color = get_base_10(map->color_f);
	printf("%d\n", map->c_color);
	printf("%d\n", map->f_color);
	int i = 0;
    while (map->worldmap[i] != 0)
    {
        printf("%d, %s\n", i, map->worldmap[i]);
        i++;
    }
	return (0);
}
/*	int i = 0;
    while (map->worldmap[i] != 0)
    {
        printf("%d, %s\n", i, map->worldmap[i]);
        i++;
    }*/

int	start_parser(char *argv[])
{
	int		fd;
	t_map	*map;

	fd = open(argv[1], O_RDWR);
	map = (t_map *)malloc(sizeof(t_map));
	map->e_texture = NULL; //esta nos inits tirar
	map->s_texture = NULL;
	map->n_texture = NULL;
	map->w_texture = NULL;
	map->color_c = NULL;
	map->color_f = NULL;
	map->worldmap = 0;
	if (parse_gnl(fd, map))
	{
		free_map(map);
		return (1);
	}
	free_map(map);
	return (0);
}

int	main(int argc, char *argv[])
{
	(void)argc;
	if (start_parser(argv))
		return (1);
	return (0);
}
