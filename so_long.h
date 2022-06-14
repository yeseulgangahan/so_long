/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehan <yehan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 15:50:26 by yehan             #+#    #+#             */
/*   Updated: 2022/06/14 09:34:13 by yehan            ###   ########seoul.kr  */
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

# define L 0
# define C 1

typedef struct s_imgs {
	void	*empty;
	void	*wall;
	void	*collectible;
	void	*exit;
	void	*player;
}	t_imgs;

typedef struct s_game
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_imgs	*imgs;
	char	**map;
	int		line;
	int		col;
	int		collectible;
	int		exit;
	int		player;
	int		pos[2];
	int		movement;
}	t_game;

/* setmap.c */
void	map_init(t_game *game, char *filename);

/* setimg.c */
void	xpm_file_to_image(t_game *game);
void	put_image_to_window_all(t_game *game);

/* keypress.c */
int		exit_game(t_game *game);
int		key_hook(int keycode, t_game *game);
void	change_map(int key, t_game *game);

#endif