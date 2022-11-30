NAME			=	main
SRC				=	main.cc
OBJ				=	main.o
H				=	-I.
HF				=	*hpp
CXXFLAGS		+=	-Wall -Wextra -Werror $(H) -pedantic -std=c++98
D				=	-Dnoasan=42

all:		$(NAME) $(HF)

-include $(OBJ:.o=.d)

%.o:		%.cc vector.hpp
			$(CXX) $(CXXFLAGS) -o $@ -c $<

$(NAME):	$(OBJ)
			$(CXX) $(CXXFLAGS) $^ -o $@ -fsanitize=address

noasan:		vector.hpp
			$(CXX) $(CXXFLAGS) -c $(SRC) $(D)
			$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

clean:
			rm -rf $(OBJ)

fclean:		clean
			rm -rf $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
