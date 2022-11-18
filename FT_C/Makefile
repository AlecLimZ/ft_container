NAME			=	main
SRC				=	main.cc
OBJ				=	main.o
H				=	-I.
CXXFLAGS		+=	-Wall -Wextra -Werror $(H) -pedantic -std=c++98

all:		$(NAME)

-include $(OBJ:.o=.d)

%.o:		%.cc vector.hpp
			$(CXX) $(CXXFLAGS) -o $@ -c $<

$(NAME):	$(OBJ)
			$(CXX) $(CXXFLAGS) $^ -o $@ -fsanitize=address

clean:
			rm -rf $(OBJ)

fclean:		clean
			rm -rf $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
