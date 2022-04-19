NAME	= 	pipex
BNM		=	.
CC		= 	gcc
RM		= 	rm -f
FLAGS	= 	-Wall -Werror -Wextra -I.
DLIB	= 	./src/libft/
NLIB	= 	libft.a
SRC 	= 	pipex.c parse_command_line.c pipex_utils.c
BSRC	=	pipex_bonus.c utils_bonus.c parse_bonus.c
ASRC	=	$(addprefix ./src/,$(SRC))
BSR		=	$(addprefix ./src/bonus/,$(BSRC))
OBJ 	=	$(ASRC:.c=.o)
BOBJ	=	$(BSR:.c=.o)

all 	:	$(NAME)

$(NAME)	:	$(OBJ)
			@make bonus -C $(DLIB)
			@$(CC) $(FLAGS) -o $(NAME) $(DLIB)$(NLIB) $(OBJ) ./src/libft/*.o

clean	:
			@make clean -C $(DLIB)
			@$(RM) $(OBJ) $(BOBJ)

fclean	:	clean
			@make fclean -C $(DLIB)
			@$(RM) $(NAME)

bonus	:	$(BNM)
	
$(BNM)	:	$(BOBJ)
			@make bonus -C $(DLIB)
			$(CC) $(FLAGS) -o $(NAME) $(DLIB)$(NLIB) $(BOBJ) ./src/libft/*.o

re	:	fclean $(NAME)

.PHONY	:	all clean fclean re bonus .
