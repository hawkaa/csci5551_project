CXX=g++
CXXINCLUDE = -I /usr/local/Aria/include
CXXLIBS = -L/usr/local/Aria/lib -lAria -lArNetworking -lpthread -ldl
BINDIR = bin/

bin:
	mkdir -p $(BINDIR)

wander: bin
	$(CXX) $(CXXINCLUDE) $(CXXLIBS) -o $(BINDIR)wander wander.cpp

clean:
	rm -rf wander
