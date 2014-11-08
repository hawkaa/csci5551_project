CXX=g++
CXXINCLUDE = -I /usr/local/Aria/include
CXXLIBS = -L/usr/local/Aria/lib -lAria -lArNetworking -lpthread -ldl
BINDIR = bin/


direct: bin
	$(CXX) $(CXXINCLUDE) $(CXXLIBS) -o $(BINDIR)direct direct.cpp

wander: bin
	$(CXX) $(CXXINCLUDE) $(CXXLIBS) -o $(BINDIR)wander wander.cpp

bin:
	mkdir -p $(BINDIR)

clean:
	rm -rf wander
