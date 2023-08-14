# Nom de votre exécutable
NAME = cub3d

# Répertoire de la Minilibx
MLX_DIR = ./libs/minilibx-linux
LIBFT_DIR = ./libs/libft
SRC_DIR = src/
OBJET_DIR = obj/
INCLUDES = -Iincludes/ -I$(LIBFT_DIR) -I$(MLX_DIR)
LIBDIR = -L$(LIBFT_DIR) -L$(MLX_DIR)

# Options de compilation
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
CFLAGS += -I/opt/X11/include
LDFLAGS = -L$(LIBFT_DIR) -lft  -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit -L/usr/X11/lib -lX11 -lXext

#CASTING =

PARSING = parsing/parsing.c \
			parsing/ft_do_parsing.c \
			parsing/ft_check_file.c \
			parsing/ft_check_file_infos.c \
			parsing/ft_create_and_init_map.c \
			parsing/ft_check_map_valid.c \
			parsing/ft_check_map_border.c \
			parsing/ft_check_texture_path.c \
			parsing/ft_get_texture_info.c \
			parsing/ft_texture_utils.c \

UTILS = utils/free_data.c \
		utils/ft_split_newline.c \
		utils/utils.c \
		utils/utils_parsing.c \

GAME = game/init_and_start_game.c \
		game/game_utils.c \
		game/movement.c \
		game/raycasting.c \

# Fichiers source de votre programme
SRC = main.c \
		$(PARSING) \
		$(UTILS) \
		$(GAME) \


# Génère les noms des fichiers objets à partir des noms de fichiers source et les place dans le répertoire obj/
OBJ = $(SRC:%.c=$(OBJET_DIR)%.o)
# Fichiers de dépendances générés par le compilateur
DEP = $(OBJ:%.o=%.d)

NO_COLOR = \033[0m
BLACK = \033[0;30m
RED = \033[0;31m
GREEN = \033[0;32m
BROWN = \033[0;33m
BLUE = \033[0;34m
PURPLE = \033[0;35m
CYAN = \033[0;36m

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(CYAN)Compilation de la libft...$(NO_COLOR)"
	@$(MAKE) -C $(LIBFT_DIR)
	@echo "$(CYAN)Compilation de la Minilibx...$(NO_COLOR)"
	@$(MAKE) -C $(MLX_DIR) -s
	@echo "$(CYAN)Compilation de $(NAME)...$(NO_COLOR)"
	@$(CC) $(CFLAGS) $(LIBDIR) $(OBJ) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)$(NAME) compilé avec succès !$(NO_COLOR)"

$(OBJET_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -MF"$(@:%.o=%.d)" -o $@ -c $<
	@echo "$(GREEN)$(NAME)$(NO_COLOR) [$(GREEN)OK$(NO_COLOR)]: $(BROWN)$<$(NO_COLOR)"

-include $(DEP)

clean:
	@rm -rf $(OBJET_DIR)
	@make -C $(LIBFT_DIR) clean
	@make -C $(MLX_DIR) clean -s
	@echo "$(GREEN)$(OBJET_DIR)$(NO_COLOR) is deleted!"

fclean: clean
	@rm -rf $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo "$(GREEN)$(NAME)$(NO_COLOR) is deleted!"

re: fclean all

.PHONY: all clean fclean re
