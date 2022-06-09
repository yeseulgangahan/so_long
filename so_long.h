/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: han-yeseul <han-yeseul@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 16:03:50 by dha               #+#    #+#             */
/*   Updated: 2022/06/09 19:05:08 by han-yeseul       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <fcntl.h>
# include <mlx.h>
# include "./libft/include/libft.h"
# include "./libft/include/get_next_line.h"

# define ESC 53
# define A 0
# define S 1
# define D 2
# define W 13

# define GAME_BIT 64

# define X_EVENT_KEY_PRESS 2
# define X_EVENT_KEY_EXIT 17

# define l 0
# define c 1

typedef struct s_img {
	void	*empty;
	void	*wall;
	void	*collectible;
	void	*exit;
	void	*player;
}	t_img;

typedef struct s_game
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	*img;
	char	**map;
	int		map_line;
	int		map_col;
	int		player_pos[2];
	int		collectible;
	int		exit;
	int		player;
	int		movement;
}	t_game;

/* main.c */
int	exit_game(t_game *game);

/* img.c */
void	xpm_file_to_image(t_game *game);
void	put_image_to_window_all(t_game *game);

/* changes.c */
void	change_map(int key, t_game *game);

/* map.c */
void	map_init(t_game *game, char *filename);

#endif
