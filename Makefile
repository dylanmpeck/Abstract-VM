NAME = avm
SOURCE = main.cpp \
		 AVM.cpp \
		 Exceptions.cpp \
		 Operand.cpp 
OBJ = main.o \
	  AVM.o \
	  Exceptions.o \
	  Operand.o

all: $(NAME)

$(NAME):
	g++ -c -Wall -Wextra -Werror -std=c++11 $(SOURCE)
	g++ -o $(NAME) -Wall -Wextra -Werror -std=c++11 $(OBJ)

clean:
	/bin/rm -f *.o

fclean: clean
	/bin/rm $(NAME)

re: fclean all
