NAME	= miniRT

CC		= gcc
CFLAGS	= -g -o3
EFLAGS	= -Wall -Wextra -Werror
LFLAGS	= -lm
RM		= rm -rf

OS		= $(shell uname)

ifeq ($(OS), Linux)
	MLXFLAGS	= #-Lmlx -lmlx -L/usr/lib -Imlx -lXext -lX11
	MLX			= #mlx/minilibx-linux
else
	MLXFLAGS = #-Lmlx -lmlx -framework OpenGL -framework AppKit
endif

SRCFILE	= 	calc_intersection.c\
			calc_vector1.c\
			calc_vector2.c\
			main.c\
			objlist.c\
			parsing_lightsandcam.c\
			parsing_objects.c\
			parsing_utils.c\
			parsing.c\
			shutdown.c\
			utils_print1.c\
			utils_print2.c
SRC		=	$(addprefix src/, $(SRCFILE))
OBJ		= 	$(addprefix obj/, $(SRCFILE:%.c=%.o))
LIBFT	= 	libft/libft.a

PINK	= \033[0;35m
PURPLE	= \033[0;34m
BLUE	= \033[94m
RESET	= \033[0m

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) #$(MLX)
	@$(CC) $(CFLAGS) $(EFLAGS) $(OBJ) $(MLXFLAGS) $(DEFINEFLAGS) -o $(NAME) $(LFLAGS) $(LIBFT)
	@echo "$(BLUE)miniRT compiled.$(RESET)"

$(LIBFT):
	@make --no-print-directory -C libft/

obj/%.o: src/%.c
	@mkdir -p obj
	$(CC) $(EFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ) obj
	@echo "$(BLUE)miniRT cleaned.$(RESET)"

fclean: clean
	@$(RM) $(NAME)

re: fclean all

git:
	git add .
	git commit -m "auto add & push"
	git push
	@echo "$(BLUE)git auto add & push performed.$(RESET)"

mgit:
	git add .
	@read -p "Enter the commit message: " halp; \
	git commit -m "$$halp"
	git push
	@echo "$(BLUE)git auto add & push with message performed.$(RESET)"

.SILENT: $(OBJ)