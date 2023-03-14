FLAGS= -Wall -pedantic -std=c++17 -iquote inc

__start__: ./test_arytm_zesp
	./test_arytm_zesp test-arytmetyka.txt 

./test_arytm_zesp: obj obj/main.o obj/LZespolona.o\
                     
	g++ -o ./test_arytm_zesp obj/main.o obj/LZespolona.o\
                    
					 
					 

obj:
	mkdir obj

obj/main.o: app/main.cpp inc/LZespolona.hh inc/vector.hh inc/size.hh inc/matrix.hh inc/equations.hh
	g++ -c ${FLAGS} -o obj/main.o app/main.cpp

obj/LZespolona.o: src/LZespolona.cpp inc/LZespolona.hh
	g++ -c ${FLAGS} -o obj/LZespolona.o src/LZespolona.cpp


clean:
	rm -f ./test_arytm_zesp obj/*
