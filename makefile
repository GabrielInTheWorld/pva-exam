CC = g++
CXXFLAGS = -Wall -Werror -Wextra -pedantic -std=c++17 -g -fsanitize=address
LDFLAGS =  -fsanitize=address
LDLIBSS = -ltbb

SRC := ./*.cpp
# OBJ = $(SRC:.cpp=.o)
OBJ := $(addsuffix .o,$(basename $(SRC)))
DEPS := $(OBJS:.o=.d)
TARGET ?= pva.out

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $(OBJ) $(CXXFLAGS) $(LBLIBS)

clean:
	rm -rf $(OBJ) $(TARGET) $(DEPS)

# pva: ./*.cpp
#     g++ -o pva *.cpp -ltbb -Wall -Werror -Wextra