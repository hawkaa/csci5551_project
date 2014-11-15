CXX=g++
CXXINCLUDE = -I /usr/local/Aria/include
CXXLIBS = -L/usr/local/Aria/lib -lAria -lArNetworking -lpthread -ldl

testinput: robolib.o geometry.o testinput.cpp
	$(CXX) $(CXXINCLUDE) $(CXXLIBS) -o testinput testinput.cpp robolib.o geometry.o

dump: robolib.o geometry.o dump.cpp
	$(CXX) $(CXXINCLUDE) $(CXXLIBS) -o dump dump.cpp robolib.o geometry.o

robolib.o: robolib.cpp
	$(CXX) $(CXXINCLUDE) $(CXXLIBS) -c robolib.cpp

geometry.o: geometry.cpp
	$(CXX) $(CXXINCLUDE) $(CXXLIBS) -c geometry.cpp


clean:
	rm -f *.o
