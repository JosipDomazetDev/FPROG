all: monads

.outputFolder:
	mkdir -p out
	
monads: .outputFolder
	clang -std=c++17 -lstdc++ -lm monads.cpp -Wall -Wextra -Werror -o out/sorts
	./out/sorts
