NAME			=	main
SRC				=	main.cc
OBJ				=	main.o
H				=	-I.
HF				=	*hpp
CXXFLAGS		+=	-Wall -Wextra -Werror $(H) -pedantic -std=c++98
D				=	-Dnoasan=42

all:		$(NAME) $(HF)

-include $(OBJ:.o=.d)

%.o:		%.cc *.hpp
			$(CXX) $(CXXFLAGS) -o $@ -c $<

$(NAME):	$(OBJ)
			$(CXX) $(CXXFLAGS) $^ -o $@ -fsanitize=address

noasan:		vector.hpp map.hpp
			$(CXX) $(CXXFLAGS) -c $(SRC) $(D)
			$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

vector:		vector.hpp
			$(CXX) $(CXXFLAGS) -c testvector.cc
			$(CXX) $(CXXFLAGS) testvector.o -o $(NAME) -fsanitize=address

vectornoasan:		vector.hpp
			$(CXX) $(CXXFLAGS) -c testvector.cc $(D)
			$(CXX) $(CXXFLAGS) testvector.o -o $(NAME)

map:		map.hpp
			$(CXX) $(CXXFLAGS) -c testmap.cc
			$(CXX) $(CXXFLAGS) testmap.o -o $(NAME) -fsanitize=address

mapnoasan:		map.hpp
			$(CXX) $(CXXFLAGS) -c testmap.cc $(D)
			$(CXX) $(CXXFLAGS) testmap.o -o $(NAME)

test:		map.hpp
			$(CXX) $(CXXFLAGS) -c test.cc
			$(CXX) $(CXXFLAGS) test.o -o $(NAME) -fsanitize=address
		

clean:
			rm -rf $(OBJ) *.o

fclean:		clean
			rm -rf $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
