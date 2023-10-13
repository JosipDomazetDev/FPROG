all: computeSalariesTest 

.outputFolder:
	mkdir -p out


computeSalariesTest: .outputFolder
	g++ -std=c++17 computeSalariesTest.cpp computeSalaries.h -Wall -Wextra -Werror -o out/computeSalariesTest
	./out/computeSalariesTest
