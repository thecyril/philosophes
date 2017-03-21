##
## Makefile for  in /home/cyril/work/technique
##
## Made by Cyril
## Login   <cyril.puccio@epitech.eu>
##
## Started on  Fri Mar  3 20:39:06 2017 Cyril
## Last update Wed Mar 15 20:11:22 2017 Matthias Prost
##

CC	=	gcc -D _DEFAULT_SOURCE

RM	=	rm -rf

NAME	=	philo

CFLAGS	=	-Wall -W -Wextra -I./include

LDFLAG	=	-L. -lriceferee -lpthread

SRC	=	src/main.c	\
		src/thread.c	\
		src/my_str_is_num.c \

OBJ	=	$(SRC:.c=.o)

all	:	$(NAME)

$(NAME)	:	$(OBJ)
		$(CC) $(OBJ) -o $(NAME) $(LDFLAG)

clean	:
		$(RM) $(OBJ)

fclean	:	clean
		$(RM) $(NAME)

re	:	fclean all

.PHONY	:	all clean fclean re
