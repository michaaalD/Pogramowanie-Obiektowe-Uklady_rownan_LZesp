#pragma once

#include <iostream>
#include <cassert>
#include <cmath>
#include "size.hh"
#include "LZespolona.hh"

template <typename T, int SIZE>
class TVector {
    private:

        T coord[SIZE];     //Tablica wektora
        float lenghth;

    public:

        TVector() {for (int i = 0; i < SIZE; ++i) coord[i] = 0;};

        TVector<T,SIZE> operator + (const TVector<T,SIZE> &v);          //operator dodawania wektorow

        TVector<T,SIZE> operator - (const TVector<T, SIZE> &v);         //operator odejmowania wektorow

        T operator * (const TVector<T, SIZE> &v);                   //operator mnozenia wektorow przez wektor

        TVector<T,SIZE> operator * (const double &tmp);                 //operator mnozenia wektorow przez liczbe
    
        TVector<T,SIZE> operator / (const double &tmp);                 //operator dzielenia wektorow

        const T &operator [] (unsigned int index) const;                //indeksowanie wektorow

        T &operator [] (unsigned int index);

};


template<typename T, int SIZE>
TVector<T,SIZE> TVector<T,SIZE>::operator +(const TVector<T, SIZE> &v)
{
    TVector<T,SIZE> result;

    for(int i=0; i < SIZE; ++i)
    {
        result[i] = (*this)[i] + v[i];
    }
    return result;
}

template<typename T, int SIZE>
TVector<T,SIZE> TVector<T,SIZE>::operator -(const TVector<T, SIZE> &v)
{
    TVector<T,SIZE> result;

    for(int i=0; i < SIZE; ++i)
    {
        result[i] = (*this)[i] - v[i];
    }
    return result;
}


template<typename T, int SIZE>
T TVector<T,SIZE>::operator *(const TVector<T, SIZE> &v)
{
    T temp;

    for(int i = 0; i < SIZE; i++)
    {
        temp += this->coord[i] * v[i];
    }
    return temp;
}


template<typename T, int SIZE>
TVector<T,SIZE> TVector<T,SIZE>::operator *(const double &tmp)
{
    TVector<T,SIZE> result;

    for(int i=0; i < SIZE; ++i)
    {
        result[i] = this->coord[i] * tmp;
    }
    return result;
}


template<typename T, int SIZE>
TVector<T,SIZE> TVector<T,SIZE>::operator /(const double &tmp)
{
    TVector<T,SIZE> result;

    for(int i=0; i < SIZE; ++i)
    {
        result[i] = (*this)[i] / tmp;
    }
    return result;
}


template<typename T, int SIZE>
const T &TVector<T,SIZE>::operator [] (unsigned int index) const
{
    assert(index >= 0 && index < SIZE);
    return coord[index];
}


template<typename T, int SIZE>
T &TVector<T,SIZE>::operator [] (unsigned int index) 
{
    assert(index >= 0 && index < SIZE);
    return coord[index];
}


template<typename T, int SIZE>
std::ostream &operator << (std::ostream &out, TVector<T,SIZE> tmp){
    for(int i = 0; i < SIZE; ++i)
    {
        out << "[" << tmp[i] << "]" << std::endl;
    }
    return out;
}


template<typename T, int SIZE>
std::istream &operator >> (std::istream &in, TVector<T,SIZE> &tmp)
{
    for(int i = 0; i < SIZE; ++i)
    {
        in >> tmp[i];
    }
    std::cout << std::endl;
    return in;
}

/*
template<typename T, int SIZE>
double vector_lenghth(TVector<T,SIZE> tmp)
{
    return sqrt(tmp * tmp);
}
*/