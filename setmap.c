/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehan <yehan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 15:50:17 by yehan             #+#    #+#             */
/*   Updated: 2022/06/14 10:01:20 by yehan            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	get_map(t_game *game, char *filename)
{
	int			fd;
	static char	*line;
	static char	*lines;
	char		*temp;

	fd = open(filename, O_RDONLY);
	if (fd < 2)
		ft_err_exit("Error\n  open() failed..");
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		temp = lines;
		lines = ft_strjoin(lines, line);
		free(line);
		free(temp);
	}
	if (lines == NULL)
		ft_err_exit("Error\n  Map is empty..");
	game->map = ft_split(lines, '\n');
	free(lines);
	close(fd);
}

static void	check_char(t_game *game, int line, int col)
{
	char	a;

	a = game->map[line][col];
	if (a != '0' && a != '1' && a != 'C' && a != 'E' && a != 'P')
		ft_err_exit("Error\n  Map must be composed of 5 possible characters..");
	if (a == 'C')
		game->collectible++;
	else if (a == 'E')
		game->exit++;
	else if (a == 'P')
	{
		game->player++;
		game->pos[L] = line;
		game->pos[C] = col;
	}
}

static void	check_map(t_game *game)
{
	int	col;
	int	line;

	line = 0;
	while (line < game->line)
	{
		col = 0;
		while (col < game->col)
		{
			if (game->map[line][col] != '1' && (line == 0
				|| line == game->line - 1 || col == 0 || col == game->col - 1))
				ft_err_exit("Error\n  Map must be surrounded by walls..");
			if (col == game->col - 1 && game->map[line][col + 1])
				ft_err_exit("Error\n  Map must be rectangular..");
			check_char(game, line, col);
			col++;
		}
		line++;
	}
	if (game->collectible < 1)
		ft_err_exit("Error\n Map must have at least 1 collectible..");
	if (game->exit < 1)
		ft_err_exit("Error\n  Map must have at least 1 exit..");
	if (game->player != 1)
		ft_err_exit("Error\n Map must have 1 starting position..");
}

void	map_init(t_game *game, char *filename)
{
	int	i;

	get_map(game, filename);
	game->col = ft_strlen(game->map[0]);
	i = 0;
	while (game->map[i])
		i++;
	game->line = i;
	check_map(game);
}
