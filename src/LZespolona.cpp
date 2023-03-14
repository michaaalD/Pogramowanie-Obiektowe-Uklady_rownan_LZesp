
#include "LZespolona.hh"
#include <cmath>
#include <iostream>
#include <stdexcept>



LZespolona  operator + (LZespolona  Skl1,  LZespolona  Skl2) //przeciazenie operatora dla dodawania lzesp
{
  LZespolona  Wynik;

  Wynik.re = Skl1.re + Skl2.re;
  Wynik.im = Skl1.im + Skl2.im;
  return Wynik;
}

LZespolona operator - (LZespolona Skl1, LZespolona Skl2) //przeciazenie operatora dla odejmowania lzesp
{
  LZespolona Wynik;
  Wynik.re = Skl1.re - Skl2.re; 
  Wynik.im = Skl1.im - Skl2.im;
  return Wynik;
}

LZespolona operator / (LZespolona Skl1, LZespolona Skl2) //przeciazenie operatora dla dzielenia lzesp
{
  LZespolona Wynik;
  double modul_zespolonej= modul2(LZespolona (Skl2));

  // ze wzoru na dizelenie z materialow do zadania (a+bi):(c+di)= [ac + bd)/ c^2+d^2 ] + [i(bc-ad)/c^2+b^2]

  if(Skl2.re != 0 && Skl2.im != 0){
    Wynik.re = ((Skl1.re*Skl2.re) + (Skl1.im*Skl2.im))/modul_zespolonej;
    Wynik.im = ((Skl1.im*Skl2.re) - (Skl1.re*Skl2.im))/modul_zespolonej;
  }
  else{
    throw std::runtime_error("Niepoprawne dzialanie. Nie mozna wykonac dzielenia przez 0");
  }

  return Wynik;
}

LZespolona operator * (LZespolona Skl1, LZespolona Skl2) //przeciazenie operatora dla mnozenia lzesp
{
  LZespolona Wynik;
  Wynik.re = (Skl1.re * Skl2.re) - (Skl1.im * Skl2.im);
  Wynik.im = (Skl1.re * Skl2.im) + (Skl1.im * Skl2.re);
  return Wynik;
}

bool operator == (LZespolona Skl1, LZespolona Skl2) //przeciazenie operatora dla porownania lzesp
{
  return (Skl1.re==Skl2.re) && (Skl1.im==Skl2.im);
}

LZespolona sprzezenie (LZespolona Skl1) //sprzezenie lzesp
{
  Skl1.im = -Skl1.im;
  return Skl1;
}

double modul2 (LZespolona Skl1)  // funckja zwracajaca modul ^2 l zespolonej
{ 
  return (Skl1.re*Skl1.re) + (Skl1.im * Skl1.im);
}


std::ostream& operator << (std::ostream& str_wyj, LZespolona Skl1)    //przeciazenie do wypisania l zesp
{
  str_wyj.precision(3); // wyswietlanie 3 miejsc po przecinku
  str_wyj << std::noshowpos << '(' << Skl1.re << std::showpos << Skl1.im << "i)";
  return str_wyj;
}

std::istream& operator >> (std::istream  &str_wej, LZespolona &Skl1)   //przeciazenie do pobrania l zesp
{
  char znak;     

  str_wej >> std::skipws >> znak;   //pobranie nawiasu '(' i sprawdzenie
  if(str_wej.fail()) return str_wej;
  if(znak != '('){
    str_wej.fail();
    return str_wej;
  }

  str_wej >> Skl1.re;                 //pobranie czesci re i sprawdzenie
  if(str_wej.fail()) return str_wej;

  str_wej >> Skl1.im;                 //pobranie czesci  im i sprawdzenie
  if(str_wej.fail()) return str_wej;

  str_wej >> znak;               // pobranie znaku 'i' i sprawdzenie
  if(str_wej.fail() || znak != 'i') return str_wej; 
 
  str_wej >> std::skipws >> znak;   // sprawdzenie nawiasu ')' i sprawdzenie
  if(str_wej.fail()) return str_wej;
  if(znak != ')'){
    str_wej.fail();
    return str_wej;
  }
  return str_wej;
}  

LZespolona &LZespolona::operator = (double  Liczba)
{
  this->re = Liczba;
  this->im = 0;
  return *this;
}

LZespolona operator *(LZespolona Skl1, double arg)
{
  LZespolona Wynik;
  Wynik.re = Skl1.re * arg;
  Wynik.im = Skl1.im * arg;
  return Wynik;
}


double abs(LZespolona Skl1)
{
    return sqrt(Skl1.re * Skl1.im);
}

LZespolona operator +=(LZespolona &Skl1, LZespolona Skl2)
{
  Skl1 = Skl1 + Skl2;
  return Skl1;
}

LZespolona operator *=(LZespolona Skl1, LZespolona Skl2)
{
  Skl1 = Skl1*Skl2;
  return Skl1;
}