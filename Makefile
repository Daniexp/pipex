NAME	= 	pipex
CC		= 	gcc
RM		= 	rm -f
FLAGS	= 	-Wall -Werror -Wextra -I.
DLIB	= 	./src/libft/
NLIB	= 	libft.a
SRC 	= 	pipex.c parse_command_line.c pipex_utils.c
ASRC	=	$(addprefix ./src/,$(SRC))
OBJ 	=	$(ASRC:.c=.o)

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
