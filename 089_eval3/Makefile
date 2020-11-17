CCFLAGS=--std=gnu++98 -pedantic -Wall -Werror -ggdb3
all: cyoa-step1 cyoa-step2 cyoa-step3 cyoa-step4
cyoa-step1: cyoa-step1.cpp rand_story.hpp rand_story.cpp
	g++ -o cyoa-step1 $(CCFLAGS) cyoa-step1.cpp
cyoa-step2: cyoa-step2.cpp rand_story.hpp rand_story.cpp
	g++ -o cyoa-step2 $(CCFLAGS) cyoa-step2.cpp
cyoa-step3: cyoa-step3.cpp rand_story.hpp rand_story.cpp
	g++ -o cyoa-step3 $(CCFLAGS) cyoa-step3.cpp
cyoa-step4: cyoa-step4.cpp rand_story.hpp rand_story.cpp
	g++ -o cyoa-step4 $(CCFLAGS) cyoa-step4.cpp

clean:
	rm -f *.o *~
