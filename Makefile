COMP =	g++ -std=c++11 -c -O3

LINK =	g++ -std=c++11

OBJS =		main.o

LIBS =

TARGET =	OptimalTransport

all:	$(TARGET)

$(TARGET):	main.o RenderWindow.o PointCloud.o Point.o Correspondence.o SimpleTransport.o Matrix.o
	$(LINK) main.o RenderWindow.o PointCloud.o Point.o Correspondence.o SimpleTransport.o Matrix.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system -o $(TARGET) $(LIBS)


main.o: main.cpp RenderWindow.h PointCloud.h SimpleTransport.h
	$(COMP) main.cpp

RenderWindow.o: RenderWindow.cpp RenderWindow.h PointCloud.h Point.h
	$(COMP) RenderWindow.cpp 
	
Point.o: Point.cpp Point.h
	$(COMP) Point.cpp
	
PointCloud.o: PointCloud.cpp PointCloud.h Point.h
	$(COMP) PointCloud.cpp

Correspondence.o: Correspondence.cpp Correspondence.h PointCloud.h Point.h
	$(COMP) Correspondence.cpp

SimpleTransport.o: SimpleTransport.cpp SimpleTransport.h PointCloud.h Point.h
	$(COMP) SimpleTransport.cpp

Matrix.o: Matrix.cpp Matrix.h
	$(COMP) Matrix.cpp

clean:
	rm -f $(BUILD)*.o OptimalTransport rm -f
