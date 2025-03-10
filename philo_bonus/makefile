NAME = 		philo_bonus
OBJ_DIR = 	../objs/philo_bonus
CC = 		gcc
CFLAGS = 	-Wall -Wextra -Werror
SRC =		main.c \
			message.c \
			philo.c \
			utils.c \
			init.c \

GRAY= 		\033[0;30m
RED= 		\033[1;31m
GREEN= 		\033[1;32m
PINK= 		\033[1;35m
PURPLE= 	\033[1;34m
BLUE= 		\033[1;36m
WHITE= 		\033[1;37m
NO_COLOR= 	\033[1m


OBJ = 		$(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))

all: $(NAME)
	@echo "\n"
	@clear
	@echo "$(PINK)██████╗ ██╗  ██╗██╗██╗      █████╗ $(PURPLE) ██████╗ █████╗ ██████╗ ██╗  ██╗███████╗██████╗  ██████╗"
	@echo "$(PINK)██╔══██╗██║  ██║██║██║     ██╔══██╗$(PURPLE)██╔════╝██╔══██╗██╔══██╗██║  ██║██╔════╝██╔══██╗██╔════╝"
	@echo "$(PINK)██████╔╝███████║██║██║     ██║  ██║$(PURPLE)╚█████╗ ██║  ██║██████╔╝███████║█████╗  ██████╔╝╚█████╗ "
	@echo "$(PINK)██╔═══╝ ██╔══██║██║██║     ██║  ██║$(PURPLE) ╚═══██╗██║  ██║██╔═══╝ ██╔══██║██╔══╝  ██╔══██╗ ╚═══██╗"
	@echo "$(PINK)██║     ██║  ██║██║███████╗╚█████╔╝$(PURPLE)██████╔╝╚█████╔╝██║     ██║  ██║███████╗██║  ██║██████╔╝"
	@echo "$(PINK)╚═╝     ╚═╝  ╚═╝╚═╝╚══════╝ ╚════╝ $(PURPLE)╚═════╝  ╚════╝ ╚═╝     ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚═════╝ "
	@echo "Ｉ  ｎｅｖｅｒ  ｔｈｏｕｇｈｔ  ｐｈｉｌｏｓｏｐｈｙ  ｗｏｕｌｄ  ｂｅ  ｓｏ  ｄｅａｄｌｙ\n $(NO_COLOR)"
	@echo "$(GREEN)█▀▀▄ █▀▀█ █▀▀█ █  █ █▀▀   █"
	@echo "$(GREEN)█▀▀▄ █  █ █  █ █  █ ▀▀█   ▀"
	@echo "$(GREEN)▀▀▀  ▀▀▀▀ ▀  ▀ ▀▀▀▀ ▀▀▀   ▀"
	@echo "\n$(GRAY)Philosophers with$(WHITE) processes$(GRAY) and$(WHITE) semaphores"

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

