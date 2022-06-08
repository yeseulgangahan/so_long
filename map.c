/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehan <yehan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 21:24:07 by dha               #+#    #+#             */
/*   Updated: 2022/06/09 07:19:32 by yehan            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

static void	check_char(t_map *map, char	c)
{
	if (c != '0' && c != '1' && c != 'C' && c != 'E' && c != 'P')
		ft_error_exit("Error\n  Map must be composed of only 5 possible characters..");
	if (c == 'E')
		map->cnt_exit++;
	else if (c == 'P')
		map->cnt_start++;
	else if (c == 'C')
		map->cnt_collectible++;
}

static void	check_map(t_map *map)
{
	int	col;
	int	line;

	line = 0;
	while (line < map->row)
	{
		col = 0;
		while (col < map->column)
		{
			if (((line == 0 || line == map->row - 1) && map->map[line][col] != '1')
				|| ((col == 0 || col == map->column - 1) && map->map[line][col] != '1'))
				ft_error_exit("Error\n  Map must be surrounded by walls..");
			if (col == map->column - 1 && map->map[line][col + 1])
				ft_error_exit("Error\n  Map must be rectangular..");
			check_char(map, map->map[line][col]);
			col++;
		}
		line++;
	}
	if (map->cnt_exit < 1)
		ft_error_exit("Error\n  Map must have at least 1 exit..");
	if (map->cnt_start != 1)
		ft_error_exit("Error\n Map must have 1 starting position..");
	if (map->cnt_collectible < 1)
		ft_error_exit("Error\n Map must have at least 1 collectible..");
}

static void	get_map(t_map *map, int fd)
{
	char	*line;
	char	*lines;
	char	*temp;

	line = NULL;
	lines = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		temp = lines;
		lines = ft_strjoin(lines, line);
		free(line);
		free(temp);
	}
	map->map = ft_split(lines, '\n');
	free(lines);
	close(fd);
}

void	map_init(t_map *map, int fd)
{
	int	i;

	get_map(map, fd);
	map->column = ft_strlen(map->map[0]);
	i = 0;
	while (map->map[i])
		i++;
	map->row = i;
	map->cnt_collectible = 0;
	map->cnt_exit = 0;
	map->cnt_start = 0;
	check_map(map);
}

void	game_init(t_game *game, char *map_file)
{
	t_map	map;
	int		fd;

	fd = open(map_file, O_RDONLY);
	if (fd < 2)
		ft_error_exit("Error\n  open(): Failed..");
	map_init(&map, fd);
	game->init = 0;
	game->map = map;
	game->width = map.column * GAME_BIT;
	game->height = map.row * GAME_BIT;
}
