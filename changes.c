/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   changes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: han-yeseul <han-yeseul@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 13:41:04 by dha               #+#    #+#             */
/*   Updated: 2022/06/09 19:01:23 by han-yeseul       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

static void	move_player(t_game *game, int newline, int newcol)
{
	game->map[game->player_pos[l]][game->player_pos[c]] = '0';
	game->player_pos[l] = newline;
	game->player_pos[c] = newcol;
	game->map[game->player_pos[l]][game->player_pos[c]] = 'P';
	game->movement += 1;
	printf("your current number of movements: %d\n", game->movement);
}

void	change_map(int key, t_game *game)
{
	int	line[4] = {-1, 0, 1, 0};
	int	col[4] = {0, -1, 0, 1};
	int	newline;
	int	newcol;
	int	newpos;

	newline = game->player_pos[l] + line[key];
	newcol = game->player_pos[c] + col[key];
	newpos = game->map[newcol][newline];
	if (newpos == '1' || (newpos == 'E' && !game->collectible))
		return ;
	if (newpos == 'E')
	{
		move_player(game, newline, newcol);
		put_image_to_window_all(game);
		exit_game(game);
	}
	if (newpos == 'C')
		game->collectible -= 1;
	move_player(game, newline, newcol);
	put_image_to_window_all(game);
}
