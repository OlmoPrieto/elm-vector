ifndef config
  config=release
endif

test: main.cpp
	g++ -std=c++11 -o test main.cpp -I.