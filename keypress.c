/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehan <yehan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 15:49:38 by yehan             #+#    #+#             */
/*   Updated: 2022/06/15 14:52:38 by yehan            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	exit_game(t_game *game)
{
	mlx_destroy_image(game->mlx_ptr, game->imgs->empty);
	mlx_destroy_image(game->mlx_ptr, game->imgs->wall);
	mlx_destroy_image(game->mlx_ptr, game->imgs->collectible);
	mlx_destroy_image(game->mlx_ptr, game->imgs->exit);
	mlx_destroy_image(game->mlx_ptr, game->imgs->player);
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	exit(EXIT_SUCCESS);
}

int	key_hook(int keycode, t_game *game)
{
	if (keycode == ESC)
		exit_game(game);
	else if (keycode == W)
		change_map(0, game);
	else if (keycode == A)
		change_map(1, game);
	else if (keycode == S)
		change_map(2, game);
	else if (keycode == D)
		change_map(3, game);
	return (0);
}

static void	move_player(t_game *game, int newline, int newcol)
{
	game->map[game->pos[L]][game->pos[C]] = '0';
	game->pos[L] = newline;
	game->pos[C] = newcol;
	game->map[game->pos[L]][game->pos[C]] = 'P';
	game->movement += 1;
	printf("Your current number of movements: %d\n", game->movement);
}

void	change_map(int key, t_game *game)
{
	const int	line[4] = {-1, 0, 1, 0};
	const int	col[4] = {0, -1, 0, 1};
	int			newline;
	int			newcol;
	char		newpos;

	newline = game->pos[L] + line[key];
	newcol = game->pos[C] + col[key];
	newpos = game->map[newline][newcol];
	if (newpos == '1')
		return ;
	if (newpos == 'E' && game->collectible)
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
