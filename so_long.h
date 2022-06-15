/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehan <yehan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 15:50:26 by yehan             #+#    #+#             */
/*   Updated: 2022/06/15 16:36:33 by yehan            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <fcntl.h>
# include <stdbool.h>
# include <errno.h>
# include "./libmlx/mlx.h"
# include "./libft/include/libft.h"
# include "./libft/include/get_next_line.h"

# define ESC 53
# define A 0
# define S 1
# define D 2
# define W 13

/* pixel per image */
# define PIXEL 64

# define KEY_PRESS 2
# define DESTROY_NOTIFY 17

/*  Used in pos[2] (L: line, C: col) */
# define L 0
# define C 1

extern int	errno;

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
	int		mapsize[2];
	int		pos[2];
	int		collectible;
	int		exit;
	int		player;
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