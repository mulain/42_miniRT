NAME	=	miniRT
CC		=	gcc
RM		=	rm -rf
CFLAGS	=	-g -O3 -Iincl -fsanitize=address
EFLAGS	=	-Wall -Wextra -Werror
LFLAGS	=	-lm $(LIBFT) $(MLXFLAGS)
LIBFT	= 	libft/libft.a

ifeq ($(shell uname), Linux)
	OS			=	Linux
	MLX			=	mlx/mlx_linux/libmlx.a
	MLXFLAGS	=	$(MLX) -L/usr/lib -lXext -lX11
	MLXCOMPILE	=	@make -C mlx/mlx_linux/
	DEFINEFLAGS	=	-DKEY_ESC=65307 
else
	OS			=	Mac
	MLX			=	mlx/mlx_mac/libmlx.a
	MLXFLAGS	=	$(MLX) -framework OpenGL -framework AppKit
	MLXCOMPILE	=	@make -C mlx/mlx_mac/
	DEFINEFLAGS	=	-DKEY_ESC=53
endif

SRCFILE	= 	calc_color.c\
			calc_vector1.c\
			calc_vector2.c\
			draw.c\
			hooks.c\
			intersect_util.c\
			intersect_2d.c\
			intersect_3d.c\
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

BLUE	=	\033[0;34m
RESET	=	\033[0m

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	@$(CC) $(CFLAGS) $(EFLAGS) $(OBJ) -o $(NAME) $(LFLAGS) 
	@echo "$(BLUE)$(NAME) compiled for $(OS).$(RESET)"

$(LIBFT):
	@make --no-print-directory -C libft/

$(MLX):
	$(MLXCOMPILE)
	@echo "$(BLUE)MLX compiled for $(OS).$(RESET)"

obj/%.o: src/%.c
	@mkdir -p obj
	$(CC) $(CFLAGS) $(EFLAGS) $(DEFINEFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ) obj
	@echo "$(BLUE)$(NAME) cleaned.$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(BLUE)$(NAME) fcleaned.$(RESET)"

re: fclean all

git:
	git add .
	git commit -m "auto add & push"
	git push
	@echo "$(BLUE)git auto add & push performed.$(RESET)"

mgit:
	git add .
	@read -p "Enter the commit message: " msg;\
	git commit -m "$$msg"
	git push
	@echo "$(BLUE)git auto add & push with message performed.$(RESET)"

.SILENT: $(OBJ)