g++ -Wall -Wextra -fsanitize=address -fsanitize=undefined -std=c++11 -o check src/Checker.hpp src/Checker.cpp src/File.hpp src/File.cpp src/Settings.hpp src/Settings.cpp src/Time.hpp src/Time.cpp src/main.cpp
g++ -Wall -Wextra -fsanitize=address -fsanitize=undefined -std=c++11 -o cmp/default cmp/default.cpp
g++ -Wall -Wextra -fsanitize=address -fsanitize=undefined -std=c++11 -o example tasks/example/pattern.cpp
