NAME	= 	pipex
CC		= 	gcc
RM		= 	rm -f
CFLAGS	= 	-Wall -Werror -Wextra -Iinc -Isrc/libft/ -Isrc/libft/gnl/
LDFLAGS =	-L src/libft -lft
DLIB	= 	src/libft/
NLIB	= 	libft.a
SRC	=	pipex.c pipex_utils.c parse_arg.c exec_utils.c
DSRC	=	$(addprefix ./src/,$(SRC))
OBJ 	=	$(DSRC:%.c=%.o)

all 	:	$(NAME)

$(NAME)	:	$(OBJ)
			@make bonus -C $(DLIB)
			$(CC) $^ -o $(NAME) $(CFLAGS) $(LDFLAGS)

clean	:
			@make clean -C $(DLIB)
			@$(RM) $(OBJ) $(BOBJ)

fclean	:	clean
			@make fclean -C $(DLIB)
			@$(RM) $(NAME)

bonus	:	$(NAME)

re	:	fclean $(NAME)

.PHONY	:	all clean fclean re bonus .
