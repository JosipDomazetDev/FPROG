all: computeSalaries strategy dependencyinjection autoincrement state maybe 

.outputFolder:
	mkdir -p out

computeSalaries: .outputFolder
	clang -std=c++17 -lstdc++ -lm computeSalaries.cpp -Wall -Wextra -Werror -o out/computeSalaries
	./out/computeSalaries

strategy : .outputFolder
	clang -std=c++17 -lstdc++ -lm strategy.cpp -Wall -Wextra -Werror -o out/strategy
	./out/strategy

dependencyinjection : .outputFolder
	clang -std=c++17 -lstdc++ -lm dependencyinjection.cpp -Wall -Wextra -Werror -o out/dependencyinjection
	./out/dependencyinjection

autoincrement: .outputFolder
	clang -std=c++17 -lstdc++ -lm autoincrement.cpp -Wall -Wextra -Werror -o out/autoincrement
	./out/autoincrement

state: .outputFolder
	clang -std=c++17 -lstdc++ -lm state.cpp -Wall -Wextra -Werror -o out/state
	./out/state

maybe: .outputFolder
	clang -std=c++17 -lstdc++ -lm maybe.cpp -Wall -Wextra -Werror -o out/maybe
	./out/maybe
