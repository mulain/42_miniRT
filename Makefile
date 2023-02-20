NAME	=  miniRT

CC		= gcc
CFLAGS	= -g -o3
EFLAGS	= -Wall -Wextra -Werror #-fsanitize=address
LFLAGS	=
RM		= rm -rf

PINK	= \033[0;35m
PURPLE	= \033[0;34m
BLUE	= \033[94m
RESET	= \033[0m

OS		= $(shell uname)

ifeq ($(OS), Linux)
MLXFLAGS = #-Lmlx -lmlx -L/usr/lib -Imlx -lXext -lX11

DEFINEFLAGS =	-DKEY_ESC=65307 -DKEY_LEFT=65361 -DKEY_RIGHT=65363 -DKEY_UP=65362 -DKEY_DOWN=65364\
				-DKEY_W=119 -DKEY_A=97 -DKEY_S=115 -DKEY_D=100\
				-DKEY_I=105 -DKEY_O=111\
				-DKEY_C=99\
				-DMOUSE_LEFT=1 -DMOUSE_RIGHT=3 -DMOUSE_MIDDLE=2 -DMOUSE_SCR_UP=4 -DMOUSE_SCR_DOWN=5
else
MLXFLAGS = #-Lmlx -lmlx -framework OpenGL -framework AppKit
DEFINEFLAGS = 	-DKEY_ESC=53 -DKEY_LEFT=123 -DKEY_RIGHT=124 -DKEY_UP=126 -DKEY_DOWN=125\
				-DKEY_W=13 -DKEY_A= -DKEY_S=1 -DKEY_D=2\
				-DKEY_I=34 -DKEY_O=31\
				-DKEY_C=8\
				-DMOUSE_LEFT=1 -DMOUSE_RIGHT=2 -DMOUSE_MIDDLE=3 -DMOUSE_SCR_UP=5 -DMOUSE_SCR_DOWN=4
endif

SRCFILE	= 	errors.c\
			main.c\
			objlist.c\
			parsing.c\
			parsing_ambientlight.c\
			parsing_camera.c\
			parsing_light.c\
			parsing_sphere.c\
			parsing_plane.c\
			utils_is.c\
			utils_print1.c\
			utils_print2.c\
			utils_set.c\
			utils_str.c\
			shutdown.c\
			k_ite_ray.c\
			k_vectormath.c\
			k_render.c

# KRIS	=	ite_ray.c\
# 			vectormath.c
SRC		=	$(addprefix src/, $(SRCFILE))# $(addprefix src/kris_plane/, $(KRIS))

# OBJ		= 	$(addprefix obj/, $(SRCFILE:%.c=%.o)) $(addprefix obj/, $(KRIS:%.c=%.o))
OBJ		= 	$(addprefix obj/, $(SRCFILE:%.c=%.o))

LIBFT	= 	libft/libft.a

MLX		= ./miniLibX/
MLX_LNK	= -L $(MLX) -l mlx -framework OpenGL -framework AppKit
MLX_LIB	= mlx.a

all: $(MLX_LIB) $(NAME)

$(MLX_LIB) :
	@make -C $(MLX)

$(NAME): $(OBJ) $(LIBFT) #$(MLX)
	@$(CC) $(CFLAGS) $(EFLAGS) $(OBJ) $(MLX_LNK) $(MLXFLAGS) $(DEFINEFLAGS) -o $(NAME) $(LIBFT)
	@echo "$(BLUE)miniRT compiled!$(RESET)"

$(LIBFT):
	@make --no-print-directory -C libft/

obj/%.o: src/%.c
	@mkdir -p obj
	$(CC) -I $(MLX) $(EFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ) obj
	@echo "$(BLUE)miniRT cleaned!$(RESET)"

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