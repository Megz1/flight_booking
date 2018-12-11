CC		:= g++
C_FLAGS := -g -Wall -Wextra -std=c++11

LIBRARIES	:=

EXECUTABLE	:= main.out

all: $(EXECUTABLE)

clean:
	-$(RM) $(EXECUTABLE)

run: all
	./$(EXECUTABLE)

$(EXECUTABLE): *.cpp
	$(CC) $(C_FLAGS) -I*.h $^ -o $@ $(LIBRARIES)
