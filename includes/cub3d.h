/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandri <bghandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 03:11:10 by bghandri          #+#    #+#             */
/*   Updated: 2023/08/14 15:27:02 by bghandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// MINILIBX
# include "mlx.h"
//# include "mlx_int.h" // a voir si besoin
# include "../libs/libft/inc/ft_bonus.h"
# include "../libs/libft/inc/ft_color.h"
# include "../libs/libft/inc/ft_ctype.h"
# include "../libs/libft/inc/ft_gnl.h"
# include "../libs/libft/inc/ft_libft.h"
# include "../libs/libft/inc/ft_stdio.h"
# include "../libs/libft/inc/ft_stdlib.h"
# include "../libs/libft/inc/ft_string.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>

# define ERROR_MALLOC "Error\nMalloc failed\n"
# define ERROR_WINDOW "Error\nWindow initialization failed\n"

# define WIN_WIDTH 800
# define WIN_HEIGHT 600

# define STDIN 0
# define STDOUT 1
# define STDERR 2

typedef struct s_texture
{
	char		*path;
	int			width;
	int			height;
	int			**data;
}				t_texture;

typedef struct s_vector
{
	float		x;
	float		y;
}				t_vector;

typedef struct s_player
{
	t_vector	pos;
	t_vector	dir;
	t_vector	plan;
}				t_player;

typedef struct s_win
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*img_data;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
}				t_win;

typedef struct s_data
{
	t_texture	*north;
	t_texture	*south;
	t_texture	*west;
	t_texture	*east;
	int			floor_color;
	int			ceiling_color;
	char		**map;
	int			map_width;
	int			map_height;
	t_player	*player;
	t_win		win_infos;
	int			x;
}				t_data;

void			ft_free_data_s(t_data *data);
void			ft_free(void **ptr);
void			ft_free_strs(char **strs);
void			ft_free_strs_n(char **strs, int n);
void			ft_free_tabs(int **tabs, int n);
int				ft_error(char *str);
int				ft_count_nb_line(char **files);
int				ft_error(char *str);
void			ft_close(int *fd);
void			ft_set_vector(t_vector *vector, float x, float y);

#endif
