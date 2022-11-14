NAME			=	main
SRC				=	main.cc
OBJ				=	$(SRC:%.cc=%.o)
H				=	-I.
CXXFLAGS		+=	-Wall -Wextra -Werror $(H) -pedantic -std=c++98

all:		$(NAME)

$(NAME):	$(OBJ)
			$(CXX) $(CXXFLAGS) $^ -o $@

nomain:		$(OBJ)
			$(CXX) nomain.cc -c
			$(CXX) $(CXXFLAGS) $^ nomain.o -o $(NAME)

clean:
			rm -rf $(OBJ)

fclean:		clean
			rm -rf $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
