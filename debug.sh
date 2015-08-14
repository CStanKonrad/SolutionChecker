g++ -Wall -Wextra -fsanitize=address -fsanitize=undefined -std=c++11 -o check src/Checker.hpp src/Checker.cpp src/File.hpp src/File.cpp src/Limit.hpp src/Limit.cpp src/Settings.hpp src/Settings.cpp src/Time.hpp src/Time.cpp src/main.cpp
g++ -Wall -Wextra -fsanitize=address -fsanitize=undefined -std=c++11 -o cmp/default cmp/default.cpp
g++ -Wall -Wextra -fsanitize=address -fsanitize=undefined -std=c++11 -o tasks/example/example tasks/example/pattern.cpp
g++ -Wall -Wextra -fsanitize=address -fsanitize=undefined -std=c++11 -o tasks/example/generator tasks/example/generator.cpp