ksolver: graph.o vertex.o ken.o
	g++ $(CFLAGS) -o ksolver graph.o vertex.o ken.o

graph.o: graph.cc vertex.h ken.h
	g++ $(CFLAGS) -c graph.cc

vertex.o: vertex.cc ken.h
	g++ $(CFLAGS) -c vertex.cc

ken.o: ken.cc common_consts.h
	g++ $(CFLAGS) -c ken.cc

clean:
	rm -f *.o ksolver