all: state_alpha state_beta state_gamma state_delta state_epsilon

.outputFolder:
	mkdir -p out

state_alpha: .outputFolder
	clang -std=c++17 -lstdc++ -lm state_alpha.cpp -Wall -Wextra -Werror -o ./out/state_alpha
	./out/state_alpha

state_beta: .outputFolder
	clang -std=c++17 -lstdc++ -lm state_beta.cpp -Wall -Wextra -Werror -o ./out/state_beta
	./out/state_beta

state_gamma: .outputFolder
	clang -std=c++17 -lstdc++ -lm state_gamma.cpp -Wall -Wextra -Werror -o ./out/state_gamma
	./out/state_gamma
	
state_delta: .outputFolder
	clang -std=c++17 -lstdc++ -lm state_delta.cpp -Wall -Wextra -Werror -o ./out/state_delta
	./out/state_delta

state_epsilon: .outputFolder
	clang -std=c++17 -lstdc++ -lm state_epsilon.cpp -Wall -Wextra -Werror -o ./out/state_epsilon
	./out/state_epsilon