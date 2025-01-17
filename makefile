NAME = 		philosopher
OBJ_DIR = 	objs
CC = 		gcc
CFLAGS = 	-Wall -Wextra -Werror
MAIN_SRC =	philo/main.c \
			philo/message.c \
			philo/philo.c \
			philo/utils.c \

BONUS_SRC =	philo_bonus/main.c \
			philo_bonus/message.c \
			philo_bonus/philo.c \
			philo_bonus/utils.c

GRAY= 		\033[0;30m
RED= 		\033[1;31m
GREEN= 		\033[1;32m
PINK= 		\033[1;35m
PURPLE= 	\033[1;34m
BLUE= 		\033[1;36m
WHITE= 		\033[1;37m
NO_COLOR= 	\033[1m


OBJ = 		$(patsubst %.c, $(OBJ_DIR)/%.o, $(MAIN_SRC))
BONUS_OBJ = $(patsubst %.c, $(OBJ_DIR)/%.o, $(BONUS_SRC))

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

bonus: all $(BONUS_OBJ)
	@$(CC) $(CFLAGS) $(BONUS_OBJ) -o $(NAME)
	@echo "$(GREEN)█▀▀▄ █▀▀█ █▀▀█ █  █ █▀▀   █"
	@echo "$(GREEN)█▀▀▄ █  █ █  █ █  █ ▀▀█   ▀"
	@echo "$(GREEN)▀▀▀  ▀▀▀▀ ▀  ▀ ▀▀▀▀ ▀▀▀   ▀"
	@echo "\n$(GRAY) Philosophers with$(WHITE) processes$(GRAY) and$(WHITE) semaphores"

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
	@echo "\n$(GRAY) Philosophers with$(WHITE) threads$(GRAY) and$(WHITE) mutexes"
