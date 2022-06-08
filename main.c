/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehan <yehan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 16:03:29 by dha               #+#    #+#             */
/*   Updated: 2022/06/08 16:53:15 by yehan            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	end_game(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	exit(EXIT_SUCCESS);
}

int	destory_hook(void *param)
{
	end_game((t_game *) param);
	return (0);
}

int	key_hook(int keycode, void *param)
{
	if (keycode == ESC)
		end_game((t_game *) param);
	else if (keycode == W)
		move(0, (t_game *) param);
	else if (keycode == A)
		move(1, (t_game *) param);
	else if (keycode == S)
		move(2, (t_game *) param);
	else if (keycode == D)
		move(3, (t_game *) param);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2
		|| ft_strncmp(".ber", ft_strrchr(argv[1], '.'), 5) || ft_strlen(argv[1]) < 5)
		ft_error_exit("Error\n  Wrong format: should be like [./so_long map.ber]");
	game_init(&game, argv[1]);
	init_img(&game);
	draw_map(&game);
	mlx_key_hook(game.win, key_hook, &game);
	mlx_hook(game.win, 17, 0, destory_hook, &game);
	mlx_loop(game.mlx);
}
