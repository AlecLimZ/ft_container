NAME			=	main
SRC				=	main.cc
OBJ				=	$(SRC:%.cc=%.o)
H				=	-I.
CXXFLAGS		+=	-Wall -Wextra -Werror $(H) -pedantic -std=c++11

all:		$(NAME)

$(NAME):	$(OBJ)
			$(CXX) $(CXXFLAGS) $^ -o $@ -fsanitize=address

clean:
			rm -rf $(OBJ)

fclean:		clean
			rm -rf $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
