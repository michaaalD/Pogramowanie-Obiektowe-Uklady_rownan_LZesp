// Executables must have the following defined if the library contains
// doctest definitions. For builds with this disabled, e.g. code shipped to
// users, this can be left out.
#ifdef ENABLE_DOCTEST_IN_LIBRARY
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest.h"
#endif

#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>

#include "vector.hh"
#include "size.hh"
#include "LZespolona.hh"
#include "matrix.hh"
#include "equations.hh"


int main(int argc, char **argv) {
  
/*                                                              //testy poszczegolnych funkcji programu
TVector<double, SIZE> Temp,Temp2;

for(int i = 0; i < SIZE; ++i){
    Temp[i] = i;
}
for(int i = 0; i < SIZE; ++i){
    std::cin >> Temp2[i];
}
Temp = Temp + Temp2;
std::cout << Temp;
std::cout << "Dlugosc Wektora "<< vector_lenghth(Temp) << std::endl;

std::cout << Temp2 * Temp << std::endl;

TVector<LZespolona,2>    W, W_wynik;
  
  for (unsigned int Ind = 0; Ind < 2; ++Ind) {
    W[Ind].re = Ind;      W[Ind].im = Ind;
  }

  std::cout << "  Wyswietlenie wspolrzednych wektora: W" << std::endl
       << "        " << W << std::endl
       << std::endl;

  W_wynik = W*2;
  std::cout << "  Wyswietlenie wyniku: W*2" << std::endl
       << "        " << W_wynik << std::endl
       << std::endl;
  
  W_wynik = W*2-W;
  std::cout << "  Wyswietlenie wyniku: W-W*0.5" << std::endl
       << "        " << W_wynik << std::endl
       << std::endl;


TMatrix<LZespolona,2> Macierz;
LZespolona complex,complex2,complex3,complex4;
complex.re = 5;
complex.im = 4;
complex4.re = 1;
complex4.im = 4;
complex2.re = 7;
complex2.im = 4;
complex3.re = 8;
complex3.im = 4;
Macierz(0,0) = complex;
Macierz(0,1) = complex3;
Macierz(1,0) = complex2;
Macierz(1,1) = complex4;


std::cout <<Macierz <<std::endl;

Macierz.transpose();
std::cout <<Macierz<<std::endl;

Macierz.column_swap(0,W);
std::cout << Macierz << std::endl;

*/
/*
std::ifstream File;
TlinearEquation<LZespolona,SIZE> Rownanie;   
File.open("macierz_zesp.txt", std::ios::in);   
File >> Rownanie;
File.close();
std::cout << Rownanie << std::endl;
Rownanie.Solve();
Rownanie.Display();
*/
/*
std::ifstream File2;
TlinearEquation<double,SIZE> Rownanie2;   
File2.open("macierz_rzecz.txt", std::ios::in);   
File2 >> Rownanie2;
File2.close();
std::cout << Rownanie2 << std::endl;
Rownanie2.Solve();
Rownanie2.Display();
*/



std::ifstream File;
    if(argc <= 1)
    {
        std::cout<<"Nie podano opcji wywolania programu"<< std::endl;
       std::cout <<"r dla rzeczywistych, c dla zespolonych"<<std::endl;
        return 1;
    }

    if(*argv[1] == 'c'){

        TlinearEquation<LZespolona, SIZE> Rownanie;
        File.open("macierz_zesp.txt", std::ios::in);

        if (!File.good())
        { 
            std::cout << "Error, nie mozna otworzyc pliku" << std::endl;
            return 1;
        }
        
        File >> Rownanie;
        File.close();
        
        Rownanie.Solve();
        Rownanie.Display();
        return 0;
    }
    else if(*argv[1] == 'r'){

        TlinearEquation<double, SIZE> Rownanie;
   
        File.open("macierz_rzecz.txt", std::ios::in);
        if (!File.good())
        { 
             std::cout << "Error, nie mozna otworzyc pliku" << std::endl;
             return 1;
        }
        
        File >> Rownanie;
        File.close();
        
        Rownanie.Solve();
        Rownanie.Display();
        return 0;
    }
    else {
        std::cout << "Bledny argument wywolania programu" << std::endl;
        return 1;
    }
   

   

}

