NAME := philo

SRC := $(shell find . -name "*.c")

OBJ := $(SRC:%.c=%.o)

FLAGS := -Wall -Wextra -Werror -pthread #-fsanitize=thread -g

%.o : %.c philo.h
	cc $(FLAGS) -c $<

$(NAME) : $(OBJ)
	@cc $(OBJ) $(FLAGS) -o $(NAME)

all : $(NAME)

clean :
	@rm -f $(OBJ)

fclean : clean
	@rm -rf $(NAME)

re :	fclean all

.PHONY : all clean fclean re
