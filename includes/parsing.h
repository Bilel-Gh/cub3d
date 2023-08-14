/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandri <bghandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 03:11:14 by bghandri          #+#    #+#             */
/*   Updated: 2023/08/14 15:27:12 by bghandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "cub3d.h"

# define ERROR_EMPTY "Error\nEmpty file\n"
# define ERROR_XPM_COLOR "Error\nXPM color is invalid\n"

enum		e_extention
{
	CUB,
	XPM
};

enum		e_direction
{
	NORTH,
	SOUTH,
	EAST,
	WEST
};

enum		e_item
{
	NO,
	SO,
	EA,
	WE,
	F,
	C
};

enum		e_map
{
	EMPTY,
	WALL,
	SPACE,
	SPAWN
};

typedef struct s_xpm
{
	char	character;
	int		value;
}			t_xpm;

typedef struct s_map
{
	int		**map;
	int		x_max;
	int		y_max;
	int		**valide_case;
}			t_map;

typedef struct s_parsing
{
	int		fd;
	char	*file_content;
	char	**file_content_split;
	char	**texture_path;
}			t_parsing;

int			ft_parsing(t_data *data, char *file_name);
int			ft_read_file(char **file_content, int *fd);
int			ft_check_file(char *file_name, int *fd, int type_of_ext);
char		**ft_split_newline(char *str);
int			ft_check_file_infos(t_data *data, t_parsing *parsing);
int			is_invalid_map(char **map);
int			ft_get_nb_infos_recup(int *is_infos_found);
void		ft_get_spawn_info(t_data *data, int **map_ints);
int			ft_check_map_valid(t_data *data, int **map_ints);
int			ft_check_map_border(t_map *map);
int			ft_create_and_init_map(t_data *data, char **file_content);
int			ft_check_texture_path(t_data *data, t_parsing *parsing);
int			ft_get_texture_info(t_texture *texture, char **files);
char		*ft_remove_quote_and_comma(char *str);
int			ft_get_xpm_value(char *line);
int			ft_get_color_value(t_xpm *xpm, char c, int nb_colors);
int			ft_get_value_of_rgb_code(char *str);
int			ft_get_code_of_color_name(char *str);
int			ft_atoi_base(char *str, char *base);
int			ft_str_lowercase(char *str);
int			ft_check_and_read_file(char **file_name, t_parsing *parsing);
int			ft_get_file_content_split(t_parsing *parsing);
int			ft_do_check_file_infos(t_data *data, t_parsing *parsing);
int			ft_do_remove_info_from_file(t_parsing *parsing);
int			ft_do_create_and_init_map(t_data *data, t_parsing *parsing);
void		free_parsing_s(t_parsing *parsing, bool is_texture_in_data);
int			ft_remove_infos_from_file_content(char ***file_content);

#endif
