#pragma once

#include "size.hh"
#include "vector.hh"
#include "LZespolona.hh"
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <vector>
#include "cassert"


template<typename T, int SIZE>
class TMatrix 
{
    private:
        TVector<T,SIZE> value[SIZE];                                // Wartosci macierzy
        T determinant;                                              // Wartosc wyznacznika
    public:
        TMatrix(T [SIZE][SIZE]);            // Konstruktor klasy

        TMatrix(); 

        TVector<T,SIZE> operator * (TVector<T,SIZE> tmp);           // Operator mnożenia przez wektor

        TMatrix<T,SIZE> operator + (TMatrix<T, SIZE> tmp);          //Operator dodawania dwoch macierzy

        T  &operator ()  (int row, int column)                      //indeksowanie maceirzy
        {
            assert(row >= 0 && row < SIZE && column >= 0 && column < SIZE);
            return value[column][row];
        }
        
        const T &operator () (int row, int column) const;

        T get_det()const {return determinant;};                     //funkcje dostepowe dla wyznacznika

        T set_det() {return determinant;};

        void transpose();                                           //transponowanie macierzy

        T detGauss()const;                                          //funkcja obliczajaca wyznacznik metoda gaussa

        void column_swap(int which_clmn, TVector<T, SIZE> clmn);    


        void rotate(double angle)
        {
            this->operator()(0,0) = cos(angle);
            this->operator()(0,1) = -sin(angle);
            this->operator()(0,2) = 0;
            this->operator()(1,0) = sin(angle);
            this->operator()(1,1) = cos(angle);
            this->operator()(1,2) = 0;
            this->operator()(2,0) = 0;
            this->operator()(2,1) = 0;
            this->operator()(2,2) = 1;
        }
            
           
};

template<typename T, int SIZE>
TMatrix<T,SIZE>::TMatrix() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            value[i][j] = 0;
        }
    }
}




template<typename T, int SIZE>
TMatrix<T,SIZE>::TMatrix(T tmp[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            value[i][j] = tmp[i][j];
        }
    }
}

template<typename T, int SIZE>
TVector<T,SIZE> TMatrix<T,SIZE>::operator * (TVector<T,SIZE> tmp)
{
    TVector<T,SIZE> result;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            result[i] = result[i] +( value[i][j] * tmp[j] );
        }
    }
    return result;
}

template<typename T, int SIZE>
TMatrix<T,SIZE> TMatrix<T,SIZE>::operator + (TMatrix<T, SIZE> tmp)
{
    TMatrix<T,SIZE> result;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            result(i, j) = this->value[i][j] + tmp(i, j);
        }
    }
    return result;
}

template<typename T, int SIZE>
const T  &TMatrix<T,SIZE>::operator () (int row, int column) const
{
    assert(row >= 0 && row < SIZE && column >= 0 && column < SIZE);
    return value[column][row];
}

template<typename T, int SIZE>
void TMatrix<T,SIZE>::transpose()
{
    T temp[SIZE][SIZE];

    for(int i=0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            temp[i][j]= this->value[i][j];
        }
    }
    for(int i=0; i< SIZE; i++){
        for(int j=0; j < SIZE; j++){
            std::swap(this->value[j][i], temp[i][j]);
        }
    }
}

template <typename T, int SIZE>
T TMatrix<T, SIZE>::detGauss()const
{
    
    T det;
    det = 1;                                   //zmienna pomocnicza do sprawzdenie parzystosci operacji
    T temp[SIZE][SIZE];                          // pomocnicza tablica to macierzy tymczasowej
    
    for(int i=0; i < SIZE; i++){                     //kopiowanie macierzy do maceirzy tymczasowej
        for(int j = 0; j < SIZE; j++){
            temp[i][j] = this->operator()(i,j);      
        }
    }
    
   
   //0.000000001 std::numeric_limits<double>::epsilon()
    if(SIZE != 3){
        for(int i = 0; i < SIZE; i++){
        
            if(abs(temp[i][i]) < 0.000000001){       //sprawdzenie czy element [0][0] == 0
                
                for(int j = i+1; j < SIZE; j++){                               
                    
                    if(abs(temp[j][i]) > 0.000000001){    //sprawdzamy czy element [1][0] > 0
                        
                        for(int l=j; l < SIZE; l++){                                // jezeli tak zamianiemy elementy z kolumny 0 i 1 miejscami
                            
                            T x = temp[i][l];
                            temp[i][l]=temp[j][l];
                            temp[j][l] = x;
                                }
                            det = det * (-1);                                       // sprawdzanie parzystosci operacji
                            break;
                            }
                        
                            if(j==SIZE){                                            //jak doszlismy do konca to determinant = 0
                                det = 0;
                            }
                }
            }

            
                
            for(int j= i+1; j < SIZE ; j++){                                        //jak [0][0] != 0
                    
                if(abs(temp[j][i]) < 0.000000001) continue;
                        
                T D = temp[j][i] / temp[i][i];
                        
                for(int m = i+1; m < SIZE; m++){
                    temp[j][m] = temp[j][m] - (D * temp[i][m]);
                    }
                        
                }
                
        }
            for(int i=0; i < SIZE; i++){
                        det = det * temp[i][i];                                           //uwzglednienie parzystosci przez pomnozenie
                    }
        
        return det;
    }


    else if(SIZE == 3){
        T w1,w2,w3,det;
        w1 = ( (temp[1][1] * temp[2][2]) - (temp[2][1] * temp[1][2]));
        w2 = ( (temp[1][0] * temp[2][2]) - (temp[2][0] * temp[1][2]) );
        w3 = ( (temp[1][0] * temp[2][1]) - (temp[2][0] * temp[1][1]) );
        det = (temp[0][0] * w1) - (temp[0][1] * w2) + (temp[0][2] * w3);
        return det;
    }
     
}

template<typename T, int SIZE>
void TMatrix<T,SIZE>::column_swap(int which_clmn, TVector<T,SIZE> clmn)
{
    if(which_clmn >=0 && which_clmn < SIZE)               //zamiana wiersza(po transponowaniu) na wektor wyrazow wolnych
    std::swap(this->value[which_clmn], clmn);
}

template<typename T, int SIZE>
std::istream &operator>>(std::istream &in, TMatrix<T, SIZE> &mat)        //przeciazenie pobrania do macierzy
{
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            in >> mat(i, j);
        }
    }
    return in;
}

template<typename T, int SIZE>
std::ostream &operator<<(std::ostream &out, TMatrix<T, SIZE> const &mat) //przeciazenie wyswietlenia macierzy
{
    for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                out << "| " << mat(i, j) << " | "; //warto ustalic szerokosc wyswietlania dokladnosci liczb
            }
            std::cout << std::endl;
        }
        return out;
} 











