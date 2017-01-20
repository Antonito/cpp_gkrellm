CXX = g++

CXXFLAGS = -W -Wall -Werror -g -I..

LDFLAGS = -lncurses

NAME = test_bin

GRAPHIC_DIR= ./

GRAPHIC_FILES= AGraphicFrame.cpp

GRAPHIC_SRC= $(addprefix $(GRAPHIC_DIR),$(GRAPHIC_FILES))

NCURSES_DIR= ncurses/

NCURSES_FILES= AFrame.cpp	\
		Window.cpp	\
		NCursesUnit.cpp

NCURSES_SRC= $(addprefix $(NCURSES_DIR), $(NCURSES_FILES))

SRC+= $(GRAPHIC_SRC)

SRC+= $(NCURSES_SRC)

OBJ = $(SRC:.cpp=.o)

$(NAME): $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(LDFLAGS)

all: $(NAME)

clean:
	rm $(OBJ)

fclean: clean
	rm $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re