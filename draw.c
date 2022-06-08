/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dha <dha@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 22:56:36 by dha               #+#    #+#             */
/*   Updated: 2022/03/04 16:12:36 by dha              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

static void	put_image_to_window(t_game *game, char c, t_coord coord)
{
	if (c == '1')
		mlx_put_image_to_window(game->mlx, game->win, game->wall.img, \
				coord.x * GAME_BIT, coord.y * GAME_BIT);
	else if (c == 'C')
		mlx_put_image_to_window(game->mlx, game->win, game-> \
				collectible.img, coord.x * GAME_BIT, coord.y * GAME_BIT);
	else if (c == 'E')
		mlx_put_image_to_window(game->mlx, game->win, game->exit.img, \
				coord.x * GAME_BIT, coord.y * GAME_BIT);
	else if (c == 'P')
	{
		mlx_put_image_to_window(game->mlx, game->win, game-> \
				character.img, coord.x * GAME_BIT, coord.y * GAME_BIT);
		game->position.x = coord.x;
		game->position.y = coord.y;
		if (!(game->init))
		{
			game->movement = 0;
			game->collected = 0;
			game->init++;
		}
	}
}

void	draw_map(t_game *game)
{
	t_coord	coord;

	mlx_put_image_to_window(game->mlx, game->win, game->scr.img, 0, 0);
	coord.y = -1;
	while (++coord.y < game->map.row)
	{
		coord.x = -1;
		while (++coord.x < game->map.column)
			put_image_to_window(game, game->map.map[coord.y][coord.x], coord);
	}
}
