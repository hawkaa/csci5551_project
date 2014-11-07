CXX=g++
CXXINCLUDE = -I /usr/local/Aria/include
CXXLIBS = -L/usr/local/Aria/lib -lAria -lArNetworking -lpthread -ldl

wander:
	$(CXX) $(CXXINCLUDE) $(CXXLIBS) -o wander wander.cpp

clean:
	rm -rf wander
