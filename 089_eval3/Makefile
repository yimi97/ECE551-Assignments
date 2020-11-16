CCFLAGS=--std=gnu++98 -pedantic -Wall -Werror -ggdb3
all: step1 step2 step3 step4
step1: cyoa-step1.cpp rand_story.hpp
	g++ -o cyoa-step1 $(CCFLAGS) cyoa-step1.cpp
step2: cyoa-step2.cpp rand_story.hpp
	g++ -o cyoa-step2 $(CCFLAGS) cyoa-step2.cpp
step3: cyoa-step3.cpp rand_story.hpp
	g++ -o cyoa-step3 $(CCFLAGS) cyoa-step3.cpp
step4: cyoa-step4.cpp rand_story.hpp
	g++ -o cyoa-step4 $(CCFLAGS) cyoa-step4.cpp

clean:
	rm -f *.o *~
