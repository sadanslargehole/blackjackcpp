HEADERS = $(wildcard **.hpp)
source = $(wildcard **.cpp)
objs = $(source:.cpp=.o)
OUTNAME = "build/bj"
OUTDIR = "build"
COMMONARGS = "--std=c++20"
test:
	$(info $(HEADERS))
	$(info $(OUTNAME))
	$(info $(objs))

%.o:
	g++ $(COMMONARGS) -c -o $@ $*.cpp -g3
all: $(objs)
	mkdir $(OUTDIR)
	g++ $(COMMONARGS) -o $(OUTNAME) $^ -g3

clean:
	-rm -rf build/
	-rm *.o
build: clean all
	rm -rf *.o
run: build
	$(OUTNAME)
.PHONY: clean build run

