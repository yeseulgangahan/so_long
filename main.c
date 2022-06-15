/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehan <yehan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 15:50:01 by yehan             #+#    #+#             */
/*   Updated: 2022/06/15 15:35:00 by yehan            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	is_valid_arg(int argc, char *filename)
{
	if (argc != 2 || ft_strlen(filename) < 5 || (ft_strrchr(filename, '.')
			&& ft_strncmp(ft_strrchr(filename, '.'), ".ber", 5)))
		return (false);
	return (true);
}

static void	game_init(t_game *game, char *filename)
{
	map_init(game, filename);
	game->mlx_ptr = mlx_init();
	if (game->mlx_ptr == NULL)
		ft_pstr_exit("Error\n: mlx_init() failed..");
	game->win_ptr = mlx_new_window(game->mlx_ptr,
			game->mapsize[C] * PIXEL, game->mapsize[L] * PIXEL, "so_long");
	if (game->win_ptr == NULL)
		ft_pstr_exit("Error\n: mlx_new_window() failed..");
	xpm_file_to_image(game);
	put_image_to_window_all(game);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	if (is_valid_arg(argc, argv[1]) == false)
		ft_pstr_exit("Error\n: Argument must be like ./so_long *.ber");
	game = ft_calloc(1, sizeof(t_game));
	game_init(game, argv[1]);
	mlx_hook(game->win_ptr, KEY_PRESS, 0, &key_hook, game);
	mlx_hook(game->win_ptr, DESTROY_NOTIFY, 0, &exit_game, game);
	mlx_loop(game->mlx_ptr);
}
