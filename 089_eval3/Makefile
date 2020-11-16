CCFLAGS=--std=gnu++98 -pedantic -Wall -Werror -ggdb3
all: step1 step2 step3 step4
step1: cyoa-step1.cpp rand_story.o page.o choice.o
	g++ -o cyoa-step1 $(CCFLAGS) cyoa-step1.cpp rand_story.o page.o choice.o
step2: cyoa-step2.cpp rand_story.o page.o choice.o
	g++ -o cyoa-step2 $(CCFLAGS) cyoa-step2.cpp rand_story.o page.o choice.o
step3: cyoa-step3.cpp rand_story.o page.o choice.o
	g++ -o cyoa-step3 $(CCFLAGS) cyoa-step3.cpp rand_story.o page.o choice.o
step4: cyoa-step4.cpp rand_story.o page.o choice.o
	g++ -o cyoa-step4 $(CCFLAGS) cyoa-step4.cpp rand_story.o page.o choice.o
.PHONY: clean depend
clean:
	rm -f *.o *~
depend:
	makedepend rand_story.cpp page.cpp choice.cpp

rand_story.o: rand_story.hpp page.hpp choice.hpp headers.hpp
page.o: page.hpp choice.hpp headers.hpp
choice.o: choice.hpp headers.hpp

