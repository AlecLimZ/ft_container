NAME			=	main
SRC				=	main.cc TestClass1.cc TestClass2.cc
OBJ				=	$(SRC:%.cc=%.o)
H				=	-I.
CXXFLAGS		+=	-Wall -Wextra -Werror $(H) -pedantic -std=c++98

all:		$(NAME)

$(NAME):	$(OBJ)
			$(CXX) $(CXXFLAGS) $^ -o $@

clean:
			rm -rf $(OBJ)

fclean:		clean
			rm -rf $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
