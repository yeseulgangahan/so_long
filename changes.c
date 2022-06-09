/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   changes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehan <yehan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 13:41:04 by dha               #+#    #+#             */
/*   Updated: 2022/06/09 13:57:02 by yehan            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

static void	move_player(t_game *game, int newline, int newcol)
{
	game->map[game->pos[l]][game->pos[c]] = '0';
	game->pos[l] = newline;
	game->pos[c] = newcol;
	game->map[game->pos[l]][game->pos[c]] = 'P';
	game->movement += 1;
	printf("your current number of movements: %d\n", game->movement);
}

void	change_map(int key, t_game *game)
{
	int	col[4] = {-1, 0, 1, 0};
	int	line[4] = {0, -1, 0, 1};
	int	newline;
	int	newcol;
	int	newpos;

	newline = game->pos[l] + line[key];
	newcol = game->pos[c] + col[key];
	newpos = game->map[newcol][newline];
	if (newpos == '1'
		|| (newpos == 'E' && game->collectible_done != game->collectible_goal))
		return ;
	if (newpos == 'E' && game->collectible_done == game->collectible_goal)
	{
		move_player(game, newline, newcol);
		put_image_to_window_all(game);
		exit_game(game);
	}
	if (newpos == 'C')
		game->collectible_done += 1;
	move_player(game, newline, newcol);
	put_image_to_window_all(game);
}
