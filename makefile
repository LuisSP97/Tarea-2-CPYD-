CXX=g++
CXXFLAGS=-Wall -g3
LDFLAGS=-lm
OBJECTS=funciones.o registro.o ventas.o

main: main.cpp $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o main main.cpp $(OBJECTS) $(LDFLAGS)

registro.o: registro.h registro.cpp
	$(CXX) $(CXXFLAGS) -c registro.cpp

funciones.o: funciones.h funciones.cpp
	$(CXX) $(CXXFLAGS) -c funciones.cpp

ventas.o: ventas.h ventas.cpp
	$(CXX) $(CXXFLAGS) -c ventas.cpp
	
.PHONY: clean
clean:
	rm -fr *.o main
	rm -fr *0 main
