CC = g++
CFLAGS = -Wall -std=c++1z
DEPS = list.h cursor_handle.h keyboard.h pathtrim.h
OBJ = list.o cursor_handle.o keyboard.o pathtrim.o aman.o 
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

amanProject: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

