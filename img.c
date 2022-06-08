/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dha <dha@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 21:08:04 by dha               #+#    #+#             */
/*   Updated: 2022/03/04 13:16:42 by dha              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	init_img(t_game	*game)
{
	t_coord	coord;
	t_coord	tmp;

	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, game->width, game->height,
			"so_long");
	game->scr.img = mlx_new_image(game->mlx, game->width, game->height);
	game->scr.addr = (int *) mlx_get_data_addr(game->scr.img, &game->\
			scr.bits_per_pixel, &game->scr.line_length, &game->scr.endian);
	coord.y = -1;
	while (++coord.y < game->height)
	{
		coord.x = -1;
		while (++coord.x < game->width)
			game->scr.addr[coord.y * game->scr.line_length / 4 + coord.x] \
					= SCR_COLOR;
	}
	game->wall.img = mlx_xpm_file_to_image(game->mlx, \
			"wall.xpm", &tmp.x, &tmp.y);
	game->character.img = mlx_xpm_file_to_image(game->mlx, \
			"character.xpm", &tmp.x, &tmp.y);
	game->exit.img = mlx_xpm_file_to_image(game->mlx, \
			"exit.xpm", &tmp.x, &tmp.y);
	game->collectible.img = mlx_xpm_file_to_image(game->mlx, \
			"collectible.xpm", &tmp.x, &tmp.y);
}
