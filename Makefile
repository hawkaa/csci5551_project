CXX=g++
CXXINCLUDE = -I /usr/local/Aria/include
CXXLIBS = -L/usr/local/Aria/lib -lAria -lArNetworking -lpthread -ldl
BINDIR = bin/


wander: bin
	$(CXX) $(CXXINCLUDE) $(CXXLIBS) -o $(BINDIR)wander wander.cpp

bin:
	mkdir -p $(BINDIR)

clean:
	rm -rf wander
