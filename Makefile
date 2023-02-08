NAME	= miniRT

CC		= gcc
CFLAGS	= -g -o3
EFLAGS	= -Wall -Wextra -Werror
LFLAGS	=
RM		= rm -rf

PINK	= \033[0;35m
PURPLE	= \033[0;34m
BLUE	= \033[94m
RESET	= \033[0m

SRC		= src/main.c src/errors.c
OBJ		= $(addprefix obj/, $(SRC:src/%.c=%.o))
LIBFT	= libft/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(EFLAGS) $(OBJ) -o $(NAME) $(LIBFT) $(LFLAGS)
	@echo "$(BLUE)MiniRT compiled!$(RESET)"

$(LIBFT):
	@make --no-print-directory -C src/libft

obj/%.o: src/%.c
	@mkdir -p obj
	$(CC) $(EFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ) obj
	@echo "$(BLUE)MiniRT cleaned!$(RESET)"

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