CC=g++
CXXFLAGS += -march=native -frename-registers -funroll-loops -Ofast -ansi -DNDEBUG -Wall $(PROF_GEN_USE)

default:
	rm -f *.o jawpc
	make PROF_GEN_USE=-fprofile-use jawpc
   
profgen:
	make PROF_GEN_USE=-fprofile-generate jawpc
	./jawpc 65536 1677721 -d

install: jawpc
	cp jawpc /usr/bin

clean:
	rm jawpc.gcda
	rm jawpc
