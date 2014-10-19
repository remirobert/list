PATHSRC	=	src/

CFLAGS=		-Wextra -Iheader

SRCS 	= 	$(PATHSRC)list.c 		\
		$(PATHSRC)map_list.c 		\
		$(PATHSRC)remove_list.c		\

OBJ	=	$(SRCS:.c=.o)

LIB	=	list.a

$(LIB):		$(OBJ)
		ar -rcs $(LIB) $(OBJ)
		ranlib $(LIB)

all:		$(LIB)

clean:
		rm -fv $(OBJ)

fclean:		clean
		rm -fv $(LIB)

re:		fclean all
