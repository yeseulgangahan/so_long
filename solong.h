/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehan <yehan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 16:03:50 by dha               #+#    #+#             */
/*   Updated: 2022/06/08 16:14:15 by yehan            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLONG_H
# define SOLONG_H

# include <stdio.h>
# include <fcntl.h>
# include <mlx.h>
# include "./libft/libft.h"

# define SCR_COLOR 0xABCDEF
# define GAME_BIT 64
# define ESC 53
# define A 0
# define S 1
# define D 2
# define W 13

typedef struct s_coord
{
	int	x;
	int	y;
}				t_coord;

typedef struct s_data
{
	void	*img;
	int		*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_map
{
	char	**map;
	int		row;
	int		column;
	int		cnt_exit;
	int		cnt_collectible;
	int		cnt_start;
}				t_map;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	t_map	map;
	int		init;
	int		width;
	int		height;
	int		movement;
	int		collected;
	t_data	scr;
	t_data	wall;
	t_data	exit;
	t_data	collectible;
	t_data	character;
	t_coord	position;
}				t_game;

void	game_init(t_game *game, char *map_file);
void	init_img(t_game *game);
void	draw_map(t_game *game);
void	move(int dir, t_game *game);
void	end_game(t_game *game);

#endif