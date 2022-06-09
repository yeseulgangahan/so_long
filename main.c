/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehan <yehan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 16:03:29 by dha               #+#    #+#             */
/*   Updated: 2022/06/09 14:21:54 by yehan            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	game_init(t_game *game, char *filename)
{
	map_init(game, filename);
	game->mlx_ptr = mlx_init();
	game->win_ptr = mlx_new_window(game->mlx_ptr, 
		game->line * GAME_BIT, game->col * GAME_BIT, "yehan's so_long");
	xpm_file_to_image(game);
	put_image_to_window_all(game);
}

int	exit_game(t_game *game)
{
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	exit(EXIT_SUCCESS);
}

int	key_hook(int keycode, void *param)
{
	if (keycode == ESC)
		exit_game((t_game *)param);
	else if (keycode == W)
		change_map(0, (t_game *)param);
	else if (keycode == A)
		change_map(1, (t_game *)param);
	else if (keycode == S)
		change_map(2, (t_game *)param);
	else if (keycode == D)
		change_map(3, (t_game *)param);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2)
		ft_err_exit("Error\n  Argument must be like [map.ber]..");
	game = ft_calloc(1, sizeof(t_game));
	game_init(game, argv[1]);
	mlx_hook(game->win_ptr, X_EVENT_KEY_PRESS, 0, &key_hook, game);
	mlx_hook(game->win_ptr, X_EVENT_KEY_EXIT, 0, &exit_game, game);
	mlx_loop(game->mlx_ptr);
}
