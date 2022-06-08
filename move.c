/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dha <dha@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 13:41:04 by dha               #+#    #+#             */
/*   Updated: 2022/03/04 15:44:55 by dha              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

static void	move_and_draw(t_game *game, int ny, int nx)
{
	printf("movement: %d\n", ++game->movement);
	game->map.map[game->position.y][game->position.x] = '0';
	game->position.y = ny;
	game->position.x = nx;
	game->map.map[game->position.y][game->position.x] = 'P';
	draw_map(game);
}

void	move(int dir, t_game *game)
{
	const int	y[4] = {-1, 0, 1, 0};
	const int	x[4] = {0, -1, 0, 1};
	int			ny;
	int			nx;

	ny = game->position.y + y[dir];
	nx = game->position.x + x[dir];
	if (game->map.map[ny][nx] == '1')
		return ;
	if (game->map.map[ny][nx] == 'C')
		game->collected += 1;
	if (game->map.map[ny][nx] == 'E')
	{
		if (game->collected != game->map.cnt_collectible)
			return ;
		else
		{
			move_and_draw(game, ny, nx);
			end_game(game);
		}
	}
	move_and_draw(game, ny, nx);
}
