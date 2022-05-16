main.ex : main.o Graphe.o Element.o
	g++ main.o Graphe.o Element.o -omain.exe

Element.o : Element.cpp Element.hpp
	g++ -Wall -c Element.cpp

Graphe.o : Graphe.cpp Graphe.hpp Element.hpp
	g++ -Wall -c Graphe.cpp 

main.o : main.cpp Graphe.hpp Element.hpp
	g++  -Wall -ansi -c main.cpp

clean :
	-rm *.o *~

veryclean : clean 
	-rm *.ex
