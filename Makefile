CXX=g++
CXXINCLUDE = -I /usr/local/Aria/include
CXXLIBS = -L/usr/local/Aria/lib -lAria -lArNetworking -lpthread -ldl

follow: robolib.o geometry.o follow.cpp
	$(CXX) $(CXXINCLUDE) $(CXXLIBS) -o follow  follow.cpp robolib.o geometry.o

plotroom: robolib.o geometry.o plotroom.cpp
	$(CXX) $(CXXINCLUDE) $(CXXLIBS) -o plotroom plotroom.cpp robolib.o geometry.o

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
