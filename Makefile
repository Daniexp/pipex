NAME	= pipex
CC	= gcc
RM	= rm -f
FLAGS	= -Wall -Werror -Wextra -I.
DLIB	= ./src/libft/
NLIB	= libft.a
DSRC	= ./src/
SRC 	= pipex.c
OBJ 	= $(DSRC)$(SRC:.c=.o)

all 	:	$(NAME)

$(NAME)	:	$(OBJ)
			@make bonus -C $(DLIB)
			@$(CC) $(FLAGS) -o $(NAME) $(DLIB)$(NLIB) $(OBJ)
clean	:
			@make clean -C $(DLIB)
			@$(RM) $(OBJ)
fclean	:	clean
			@make fclean -C $(DLIB)
			@$(RM) $(NAME)
re	:	fclean $(NAME)

bonus	:

.PHONY	:	all clean fclean re bonus
