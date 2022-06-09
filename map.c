#include "solong.h"

static void	check_char(t_game *game, int line, int col)
{
	char	a;

	a = game->map[line][col];
	if (a != '0' && a != '1' && a != 'C' && a != 'E' && a != 'P')
		ft_err_exit("Error\n  Map must be composed of only 5 possible characters..");
	if (a == 'C')
		game->collectible++;
	else if (a == 'E')
		game->exit++;
	else if (a == 'P')
	{
		game->player++;
		game->player_pos[l] = line;
		game->player_pos[c] = col;
	}
}

static void	check_map(t_game *game)
{
	int	col;
	int	line;

	line = 0;
	while (line < game->map_line)
	{
		col = 0;
		while (col < game->map_col)
		{
			if (((line == 0 || line == game->map_line - 1) && game->map[line][col] != '1')
				|| ((col == 0 || col == game->map_col - 1) && game->map[line][col] != '1'))
				ft_err_exit("Error\n  Map must be surrounded by walls..");
			if (col == game->map_col - 1 && game->map[line][col + 1])
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

static void	get_map(t_game *game, char *filename)
{
	int		fd;
	char	*line;
	char	*lines;
	char	*temp;

	fd = open(filename, O_RDONLY);
	if (fd < 2)
		ft_err_exit("Error\n  open() failed..");
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
	game->map = ft_split(lines, '\n');
	free(lines);
	close(fd);
}

void	map_init(t_game *game, char *filename)
{
	int	i;

	get_map(game, filename);
	game->map_col = ft_strlen(game->map[0]);
	i = 0;
	while (game->map[i])
		i++;
	game->map_line = i;
	check_map(game);
}
