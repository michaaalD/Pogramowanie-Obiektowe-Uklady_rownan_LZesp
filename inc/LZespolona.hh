#ifndef LZESPOLONA_HH
#define LZESPOLONA_HH
#include <iostream>

/*!
 *  Plik zawiera definicje struktury LZesplona oraz zapowiedzi
 *  przeciazen operatorow arytmetycznych dzialajacych na tej 
 *  strukturze.
 */


/*!
 * Modeluje pojecie liczby zespolonej
 */
struct  LZespolona {
  double   re;    /*! Pole repezentuje czesc rzeczywista. */
  double   im;    /*! Pole repezentuje czesc urojona. */
  LZespolona &operator = (double  Liczba);
};

/*
 * Dalej powinny pojawic sie zapowiedzi definicji przeciazen operatorow
 */

LZespolona operator + (LZespolona  Skl1,  LZespolona  Skl2);
LZespolona operator - (LZespolona Skl1, LZespolona Skl2);
LZespolona operator / (LZespolona Skl1, LZespolona Skl2);
LZespolona operator * (LZespolona Skl1, LZespolona Skl2);
bool operator == (LZespolona Skl1, LZespolona Skl2);
LZespolona operator * (LZespolona Skl1, double arg);
LZespolona operator +=(LZespolona &Skl1, LZespolona Skl2);
LZespolona operator *=(LZespolona &Skl1, LZespolona Skl2);


double modul2 (LZespolona Skl1); // zwraca kwadrat modulu
LZespolona sprzezenie (LZespolona Skl1); 
double abs(LZespolona SKl1);


std::ostream& operator << (std::ostream& str_wyj, LZespolona Skl1);
std::istream& operator >> (std::istream  &str_wej, LZespolona &Skl1);

#endif
