TARGET = s21_tetris
CC = gcc
CFLAGS = -std=c99 -std=gnu99 -Wall #-Wextra -Werror
TETRIS_BACKEND_SRC =  brickgame/tetris/tetris.c brickgame/tetris/tetris_backend.c brickgame/tetris/fsm.c
TETRIS_BACKEND_LIBS = brickgame/tetris/tetris_backend.h brickgame/tetris/tetris.h brickgame/tetris/fsm.h
TETRIS_FRONTEND_SRC = gui/cli/frontend.c
TETRIS_FRONTEND_LIBS = gui/cli/frontend.h
VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes
MAIN = brickgame/tetris/main.c
OS=$(shell uname -s)
test_flags=-fprofile-arcs -ftest-coverage --coverage

ifeq ($(OS),Linux)
	test_libs=-lcheck -lm -lsubunit
	open=xdg-open
else
	test_libs=-lcheck
	open=open
endif



all: clean install

install: tetris_backend tetris_frontend
	$(CC) $(CFLAGS) -o $(TARGET) *.o $(MAIN) -lncurses 
	rm -rf *.o *.a

uninstall: clean

tetris_backend: tetris_backend.o
	ar rcs $(TARGET).a *.o
	ranlib $(TARGET).a

tetris_backend.o: 
	$(CC) $(CFLAGS) -c $(TETRIS_BACKEND_SRC)

tetris_frontend:
	$(CC) $(CFLAGS) -c $(TETRIS_FRONTEND_SRC)

test: clean 
	$(CC) $(CFLAGS) $(test_flags) $(TARGET)_test.c $(TETRIS_BACKEND_SRC)  -o test $(test_libs) 
	./test

gcov_report: test
	lcov -t "test" -o $(tests_info)test.info -c -d .
	genhtml -o report $(tests_info)test.info
	$(open) report/index.html

dvi: 
	open doxygen_files/doxygen/html/index.html

dist:
	tar -czf s21_tetris.tar.gz ./* 

style_check:
	cp ../materials/linters/.clang-format ./
	clang-format -n $(TETRIS_BACKEND_SRC) $(TETRIS_FRONTEND_SRC) $(TETRIS_BACKEND_LIBS) $(TETRIS_FRONTEND_LIBS) 
	rm -rf .clang-format

style_make:
	cp ../materials/linters/.clang-format ./
	clang-format -i $(TETRIS_BACKEND_SRC) $(TETRIS_FRONTEND_SRC) $(TETRIS_BACKEND_LIBS) $(TETRIS_FRONTEND_LIBS) 
	rm -rf .clang-format

leaks: install
	leaks -atExit -- ./$(TARGET)
	
clean:
	rm -f $(TARGET) *.o a.out
	rm -f *.gcno *.info *.gcda 
	rm -rf report
	rm -f test 
	rm -rf test.dSYM 
	rm -rf *.tar.gz