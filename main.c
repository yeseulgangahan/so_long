/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehan <yehan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 15:50:01 by yehan             #+#    #+#             */
/*   Updated: 2022/06/14 10:09:11 by yehan            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	game_init(t_game *game, char *filename)
{
	map_init(game, filename);
	game->mlx_ptr = mlx_init();
	game->win_ptr = mlx_new_window(game->mlx_ptr,
			game->col * GAME_BIT, game->line * GAME_BIT, "so_long");
	xpm_file_to_image(game);
	put_image_to_window_all(game);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2 || ft_strlen(argv[1]) < 5 || (ft_strrchr(argv[1], '.')
			&& ft_strncmp(ft_strrchr(argv[1], '.'), ".ber", 5)))
		ft_err_exit("Error\n  Argument must be like..: ./so_long *.ber");
	game = ft_calloc(1, sizeof(t_game));
	game_init(game, argv[1]);
	mlx_hook(game->win_ptr, X_EVENT_KEY_PRESS, 0, &key_hook, game);
	mlx_hook(game->win_ptr, X_EVENT_KEY_EXIT, 0, &exit_game, game);
	mlx_loop(game->mlx_ptr);
}
