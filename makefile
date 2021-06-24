CXX=g++
CXXFLAGS=-Wall -g3
LDFLAGS=-lm
OBJECTS=funciones.o registro.o

main: main.cpp $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o main main.cpp $(OBJECTS) $(LDFLAGS)

registro.o: registro.h registro.cpp
	$(CXX) $(CXXFLAGS) -c registro.cpp

funciones.o: funciones.h funciones.cpp
	$(CXX) $(CXXFLAGS) -c funciones.cpp

.PHONY: clean
clean:
	rm -fr *.0 main
