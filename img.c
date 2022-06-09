#include "solong.h"

void	xpm_file_to_image(t_game *game)
{
	int		wid;
	int		hei;

	game->img = ft_calloc(1, sizeof(t_img));
	game->img->empty
		= mlx_xpm_file_to_image(game->mlx_ptr, "./imgs/empty.xpm", &wid, &hei);
	game->img->wall
		= mlx_xpm_file_to_image(game->mlx_ptr, "./imgs/wall.xpm", &wid, &hei);
	game->img->collectible
		= mlx_xpm_file_to_image(game->mlx_ptr, "./imgs/collectible.xpm", &wid, &hei);
	game->img->exit
		= mlx_xpm_file_to_image(game->mlx_ptr, "./imgs/exit.xpm", &wid, &hei);
	game->img->player
		= mlx_xpm_file_to_image(game->mlx_ptr, "./imgs/player.xpm", &wid, &hei);
}

static void	put_image_to_window(t_game *game, int line, int col)
{
	void	*img_ptr;

	if (game->map[line][col] == '1')
		img_ptr = game->img->wall;
	else if (game->map[line][col] == 'C')
		img_ptr = game->img->collectible;
	else if (game->map[line][col] == 'E')
		img_ptr = game->img->exit;
	else if (game->map[line][col] == 'P')
		img_ptr = game->img->player;
	else
		img_ptr = game->img->empty;
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
		img_ptr, col * GAME_BIT, line * GAME_BIT);

}

void	put_image_to_window_all(t_game *game)
{
	int		line;
	int		col;

	line = 0;
	while (line < game->map_line)
	{
		col = 0;
		while (col < game->map_col)
		{
			put_image_to_window(game, line, col);
			col++;
		}
		line++;
	}
}
