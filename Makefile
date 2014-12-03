CC=g++
CFLAGS=-std=c++11 -ggdb3 -Wpedantic -Wall -Wextra -Winit-self -Winline -Wconversion -Weffc++ -Wstrict-null-sentinel -Wold-style-cast -Wnoexcept -Wctor-dtor-privacy -Woverloaded-virtual -Wconversion -Wsign-promo -Wzero-as-null-pointer-constant
LDFLAGS=
EXEC=main
SRC= $(wildcard *.cpp)
OBJ= $(SRC:.cpp=.o)

run: all
	@echo -e "\e[0;31m================= Run ================\e[0m"
	./$(EXEC)

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: clean mrproper

clean:
	@echo Removed $(EXEC) and $(OBJ)
	@rm -rf *.o
	@rm -rf $(EXEC)
