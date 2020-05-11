


NAME = ft_traceroute

SRC = 	main.c \
		parcing.c \
		parcing_options.c \
		traceroute.c \
		socket.c \
		display.c \
		exit.c \
		tools.c

SRC_DIR = srcs/

OBJ_DIR = objects/

OBJ := $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

SRC := $(addprefix $(SRC_DIR), $(SRC))

INC = includes

INCLUDES = $(INC)/ft_traceroute.h

LIB = libft

INC_FLAG = -I$(INC) -I$(LIB)

LIB_FLAG = -L ./$(LIB) -lft

GCC = gcc -Wall -Wextra -Werror

.SILENT:

all: lib $(NAME)

$(NAME): $(OBJ)
	$(GCC) $(INC_FLAG) -o $(NAME) $(SRC) $(LIB_FLAG)
	printf '\033[32m[ ✔ ] %s\n\033[0m' "Create ft_traceroute"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INCLUDES) $(LIB)/libft.a
	mkdir -p $(OBJ_DIR)
	$(GCC) $(INC_FLAG) -c $< -o $@
	printf '\033[0m[ ✔ ] %s\n\033[0m' "$<"

lib:
	make -C libft

clean:
	make -C libft clean
	rm -f $(OBJ)
	rm -Rf $(OBJ_DIR)
	printf '\033[31m[ ✔ ] %s\n\033[0m' "Clean ft_traceroute"

fclean: clean
	make -C libft fclean
	rm -f $(NAME)
	printf '\033[31m[ ✔ ] %s\n\033[0m' "Fclean ft_traceroute"

re: fclean all

.PHONY: all clean fclean re

