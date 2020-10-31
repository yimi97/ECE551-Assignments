CCFLAGS=--std=gnu++98 -pedantic -Wall -Werror -ggdb3
all: step1 step2
step1: cyoa-step1.cpp rand_story.hpp
	g++ -o step1 $(CCFLAGS) cyoa-step1.cpp
step2: cyoa-step2.cpp rand_story.hpp
	g++ -o step2 $(CCFLAGS) cyoa-step2.cpp
