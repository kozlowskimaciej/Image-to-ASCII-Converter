CC = clang++ -Wall -Wextra -pedantic -Werror -fsanitize=undefined -std=c++20

all:
	$(CC) src/*.cpp *.cpp -o main.out && ./main.out

test:
	$(CC) tests/*.cpp src/classes/*.cpp -o test.out && ./test.out

clean:
	rm *.o *.out