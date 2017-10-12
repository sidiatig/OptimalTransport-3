COMP =	g++ -std=c++11 -c -O3

LINK =	g++ -std=c++11

OBJS =		main.o

LIBS =

TARGET =	OptimalTransport

all:	$(TARGET)

$(TARGET):	main.o RenderWindow.o PointCloud.o Point.o
	$(LINK) main.o RenderWindow.o PointCloud.o Point.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system -o $(TARGET) $(LIBS)


main.o: main.cpp RenderWindow.h PointCloud.h
	$(COMP) main.cpp

RenderWindow.o: RenderWindow.cpp RenderWindow.h PointCloud.h Point.h
	$(COMP) RenderWindow.cpp 
	
Point.o: Point.cpp Point.h
	$(COMP) Point.cpp
	
PointCloud.o: PointCloud.cpp PointCloud.h Point.h
	$(COMP) PointCloud.cpp

clean:
	rm -f $(BUILD)*.o OptimalTransport rm -f
