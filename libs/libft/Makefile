# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bghandri <bghandri@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/08 19:04:31 by bghandri          #+#    #+#              #
#    Updated: 2023/07/30 10:40:02 by bghandri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := libft.a
CC := cc
CFLAGS := -Wall -Wextra -Werror -fno-builtin -ffreestanding

SDIR := src/
ODIR := bin/
IDIR := inc/

BONUS :=	bonus/ft_lstdelone.c \
			bonus/ft_lstmap.c \
			bonus/ft_lstadd_back.c \
			bonus/ft_lstsize.c \
			bonus/ft_lstiter.c \
			bonus/ft_lstclear.c \
			bonus/ft_lstadd_front.c \
			bonus/ft_lstnew.c \
			bonus/ft_lstlast.c

CTYPE :=	ctype/ft_isprint.c \
			ctype/ft_tolower.c \
			ctype/ft_toupper.c \
			ctype/ft_isupper.c \
			ctype/ft_isalpha.c \
			ctype/ft_isdigit.c \
			ctype/ft_ispunct.c \
			ctype/ft_isxdigit.c \
			ctype/ft_isspace.c \
			ctype/ft_iscntrl.c \
			ctype/ft_islower.c \
			ctype/ft_isalnum.c \
			ctype/ft_isgraph.c

GNL :=		get_next_line/get_next_line.c \
			get_next_line/get_next_line_utils.c

STRING :=	string/ft_strncpy.c \
			string/ft_memcmp.c \
			string/ft_bzero.c \
			string/ft_strcpy.c \
			string/ft_memchr.c \
			string/ft_strncmp.c \
			string/ft_memcpy.c \
			string/ft_strcmp.c \
			string/ft_strlen.c \
			string/ft_strlcpy.c \
			string/ft_memset.c \
			string/ft_memmove.c \
			string/ft_strlcat.c \
			string/ft_strcat.c \
			string/ft_strrchr.c \
			string/ft_strndup.c \
			string/ft_strnstr.c \
			string/ft_strnlen.c \
			string/ft_strchr.c

STDIO :=	stdio/ft_fprintf/ft_fprintf.c \
			stdio/ft_fprintf/ft_putnbr_fd.c \
			stdio/ft_fprintf/ft_putstr_fd.c \
			stdio/ft_fprintf/ft_putptr_fd.c \
			stdio/ft_fprintf/ft_putunbr_fd.c \
			stdio/ft_fprintf/ft_puthex_fd.c \
			stdio/ft_fprintf/ft_putchar_fd.c \
			stdio/ft_fprintf/ft_putnbr_base_fd.c

STDLIB :=	stdlib/ft_realloc.c \
			stdlib/ft_atoll.c \
			stdlib/ft_atoi.c \
			stdlib/ft_strdup.c \
			stdlib/ft_atof.c \
			stdlib/ft_atol.c \
			stdlib/ft_calloc.c

LIBFT :=	libft/ft_putnbr_fd.c \
			libft/ft_strmapi.c \
			libft/ft_putstr_fd.c \
			libft/ft_len_array.c \
			libft/ft_putchar_fd.c \
			libft/ft_itoa.c \
			libft/ft_substr.c \
			libft/ft_strjoin.c \
			libft/ft_split.c \
			libft/ft_striteri.c \
			libft/ft_putendl_fd.c \
			libft/ft_strtrim.c \
			libft/ft_free_array.c \
			libft/ft_strmapi.c

CFILE := 	$(addprefix $(SDIR), $(BONUS)) \
			$(addprefix $(SDIR), $(CTYPE)) \
			$(addprefix $(SDIR), $(GNL)) \
			$(addprefix $(SDIR), $(STRING)) \
			$(addprefix $(SDIR), $(STDIO)) \
			$(addprefix $(SDIR), $(STDLIB)) \
			$(addprefix $(SDIR), $(LIBFT))

OFILE :=	$(addprefix $(ODIR), $(BONUS:.c=.o)) \
			$(addprefix $(ODIR), $(CTYPE:.c=.o)) \
			$(addprefix $(ODIR), $(GNL:.c=.o)) \
			$(addprefix $(ODIR), $(STRING:.c=.o)) \
			$(addprefix $(ODIR), $(STDIO:.c=.o)) \
			$(addprefix $(ODIR), $(STDLIB:.c=.o)) \
			$(addprefix $(ODIR), $(LIBFT:.c=.o))

DEP :=		$(OFILE:.o=.d)

DEFAULT := \033[0m
BOLD := \033[1m
UNDERLINE := \033[4m
BLACK := \033[30m
RED := \033[31m
GREEN := \033[32m
YELLOW := \033[33m
BLUE := \033[34m
MAGENTA := \033[35m
CYAN := \033[36m
WHITE := \033[37m

# progress bar variables
TOTAL_FILES := $(words $(CFILE))
CURRENT_FILE := 0
PERCENTAGE := 0
PROGRESS_BAR_LENGTH := 50

# fonction qui permet de mettre à jour la barre de progression
# la fonction est appelée à chaque fois qu'un fichier est compilé et est converti en .o
# 1 on incrémente le nombre de fichiers compilés
# 2 on calcule le pourcentage de fichiers compilés
# 3 on calcule le nombre de # à afficher dans la barre de progression
# 4 on calcule le nombre d'espace à afficher dans la barre de progression
# 5 on affiche la barre de progression le \r permet de revenir au début de la ligne a chaque fois
define update_progress
	$(eval CURRENT_FILE=$(shell echo $$(($(CURRENT_FILE)+1))))
	$(eval PERCENTAGE=$(shell echo $$(($(CURRENT_FILE)*100/$(TOTAL_FILES)))))
	$(eval NB_BAR=$(shell echo $$(($(PERCENTAGE)*$(PROGRESS_BAR_LENGTH)/100))))
	$(eval NB_SPACE=$(shell echo $$(($(PROGRESS_BAR_LENGTH)-$(NB_BAR)))))
	@printf "\r\033[K[$(YELLOW)"
	@printf "%*s" $(NB_BAR) | tr ' ' '#'
	@printf "%*s" $(NB_SPACE) | tr ' ' '-'
	@printf "$(DEFAULT)] $(YELLOW)%d%%$(DEFAULT) ($(YELLOW)%d$(DEFAULT)/$(YELLOW)%d$(DEFAULT)) $(BOLD)$(UNDERLINE)$(BLUE)%s$(DEFAULT)" $(PERCENTAGE) $(CURRENT_FILE) $(TOTAL_FILES) $<
endef

all: $(NAME)

$(NAME): $(OFILE)
	@ar rc $(NAME) $(OFILE)
	@ranlib $(NAME)
	@printf "\r\033[K$(BOLD)$(GREEN)$(NAME)$(DEFAULT) $(GREEN)compiled successfully !$(DEFAULT)\n"

-include $(DEP)

$(ODIR)%.o: $(SDIR)%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -I $(IDIR) -MMD -MP -MF"$(@:%.o=%.d)" -o $@ -c $<
	@$(call update_progress)

clean:
	@rm -rf $(ODIR)
	@printf "$(BOLD)$(RED)$(NAME)$(DEFAULT) $(RED)object files deleted$(DEFAULT)\n"

fclean: clean
	@rm -f $(NAME)
	@printf "$(BOLD)$(RED)$(NAME)$(DEFAULT) $(RED)deleted$(DEFAULT)\n"

re: fclean all

.PHONY: all clean fclean re
