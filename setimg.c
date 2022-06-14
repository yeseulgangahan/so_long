/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setimg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehan <yehan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 15:49:50 by yehan             #+#    #+#             */
/*   Updated: 2022/06/14 09:41:10 by yehan            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	xpm_file_to_image(t_game *game)
{
	int		wid;
	int		hei;

	game->imgs = ft_calloc(1, sizeof(t_imgs));
	game->imgs->empty
		= mlx_xpm_file_to_image(game->mlx_ptr, "./imgs/empty.xpm", &wid, &hei);
	game->imgs->wall
		= mlx_xpm_file_to_image(game->mlx_ptr, "./imgs/wall.xpm", &wid, &hei);
	game->imgs->collectible
		= mlx_xpm_file_to_image
		(game->mlx_ptr, "./imgs/collectible.xpm", &wid, &hei);
	game->imgs->exit
		= mlx_xpm_file_to_image(game->mlx_ptr, "./imgs/exit.xpm", &wid, &hei);
	game->imgs->player
		= mlx_xpm_file_to_image(game->mlx_ptr, "./imgs/player.xpm", &wid, &hei);
	if (!game->imgs->empty || !game->imgs->wall || !game->imgs->collectible
		|| !game->imgs->exit || !game->imgs->player)
		ft_err_exit("Error\n  mlx_xpm_file_to_image() failed..");
}

static void	put_image_to_window(t_game *game, int line, int col)
{
	void	*img_ptr;

	if (game->map[line][col] == '1')
		img_ptr = game->imgs->wall;
	else if (game->map[line][col] == 'C')
		img_ptr = game->imgs->collectible;
	else if (game->map[line][col] == 'E')
		img_ptr = game->imgs->exit;
	else if (game->map[line][col] == 'P')
		img_ptr = game->imgs->player;
	else
		img_ptr = game->imgs->empty;
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
		img_ptr, col * GAME_BIT, line * GAME_BIT);
}

void	put_image_to_window_all(t_game *game)
{
	int		line;
	int		col;

	line = 0;
	while (line < game->line)
	{
		col = 0;
		while (col < game->col)
		{
			put_image_to_window(game, line, col);
			col++;
		}
		line++;
	}
}
