all: sorts

.outputFolder:
	mkdir -p out
	
sorts: .outputFolder
	clang -std=c++17 -lstdc++ -lm sorts.cpp -Wall -Wextra -Werror -o out/sorts
	./out/sorts
