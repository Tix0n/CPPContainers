FLAGS = -Wall -Werror -Wextra  -g -pthread

SRC = s21_containers/general_structures/container.tpp \
			s21_containers/stack/stack.tpp s21_containers/queue/queue.tpp s21_containers/vector/vector.tpp s21_containers/list/list.tpp 
OBJ = $(SRC:.tpp =.o)

all: clean test

static_container.a:$(OBJ)
	ar rc static_container.a $(OBJ)
	ranlib static_container.a
	rm -rf *.o
	
test: 
	g++ -std=c++17 $(FLAGS) tests.cc -L.   -lgtest  --coverage -o test
	./test

gcov_report: test
	lcov -t "test" -o test.info -c -d .
	lcov --extract test.info "*/s21_containers/*" -o test_filtered.info
	genhtml -o report test_filtered.info
	google-chrome ./report/index.html

clean:    
	rm -rf *.o *.a *.gcno *.gcda test test.info *.out
	rm -rf report
	rm -rf .txt *.dSYM

style:
	clang-format -i --style=Google *.h \
	 s21_containers/set/*.h\
	 s21_containers/map/*.h \
	 s21_containers/general_structures/*.tpp s21_containers/general_structures/*.h \
	 s21_containers/stack/*.tpp s21_containers/stack/*.h \
	 s21_containers/queue/*.tpp s21_containers/queue/*.h \
	 s21_containers/list/*.tpp s21_containers/list/*.h \
	 s21_containers/vector/*.tpp s21_containers/vector/*.h \
	 tests.cc

	clang-format -n --style=Google *.h \
	s21_containers/set/*.h \
	s21_containers/map/*.h \
	s21_containers/general_structures/*.tpp s21_containers/general_structures/*.h \
	s21_containers/stack/*.tpp s21_containers/stack/*.h \
	s21_containers/queue/*.tpp s21_containers/queue/*.h \
	s21_containers/list/*.tpp s21_containers/list/*.h \
	s21_containers/vector/*.tpp s21_containers/vector/*.h

check:
	 cppcheck ./s21_containers/general_structures/*.tpp \
	./s21_containers/stack/*.tpp \
	./s21_containers/queue/*.tpp \
	./s21_containers/list/*.tpp \
	./s21_containers/vector/*.tpp
leaks:
	leaks -atExit -- ./test
