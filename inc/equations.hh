#include <iostream>
#include "matrix.hh"
#include "vector.hh"
#include "LZespolona.hh"

template<typename T, int SIZE>
class TlinearEquation{    //klasa definiujaca uklad rownan

    TMatrix<T,SIZE> equation_matrix;    //macierz wspolczynnikow
    T main_det;                         //wyznacznik glowny macierzy
    TVector<T,SIZE> mistake_vector;     //wektor bledu
    TVector<T,SIZE> free_vector;        //wektor wyrazow wolnych
    TVector<T,SIZE> det;                //wektor wyznacznikow 
    TVector<T,SIZE> solved;             //wektor rozwiazan

    public:
    
    void Cramer();   //funkcja obliczajaca wyznacnziki macierzy
    void Solve();    //funkcja obliczajaca rozwiazania ukladu rownan
        
    void Display();  //funkcja wyswietlajaca macierz,wyznaczniki, rozwiazanie itp.   
    void mistake();  // funkcja obliczajaca wektor bledow

    friend std::istream &operator >>(std::istream &str_in, TlinearEquation<T,SIZE> &equation)         //przeciazenie wczytania wyrazenia
    {
        TMatrix<T,SIZE> temp;

        for(int i = 0; i < SIZE; i++){                   //wczytanie macierzy
            for(int j = 0 ; j < SIZE; j++){
                str_in >> temp(i,j);
            }
        }

        std::cout << "Macierz wczytana " << std::endl;

       // temp.transpose();                                //transpozycja macierzy glownej, zeby pozniej zmaienic kolumne z wektorem wyrazow wolnych

        for(int  i = 0; i < SIZE; i++){                  //wczytanie wektora wyrazow wolnych
            str_in >> equation.free_vector[i];
        }
        equation.equation_matrix = temp;
        
        return str_in;
    }
    friend std::ostream &operator <<(std::ostream &str_out, const TlinearEquation<T,SIZE> &equation)  //przeciazenie wypisania wyrazenia
    {
        TMatrix<T,SIZE> temp;

        temp = equation.equation_matrix;
        str_out << "Macierz pobrana " << std::endl;
        str_out << temp;
        str_out << "Wektor wyrazow wolnych" <<std::endl;
        str_out << equation.free_vector;

        return str_out;
    }
};  



template<typename T, int SIZE>
void TlinearEquation<T,SIZE>::Cramer()
{
    for(int i = 0; i < SIZE; i++){

        TMatrix<T,SIZE> temp = equation_matrix;           //pomocnicza macierz tymczasowa
        temp.column_swap(i,free_vector);                  //zamiana poszczegolnych w wektorem wyrazow wolnych
        std::cout << temp << std::endl;                   

        det[i] = temp.detGauss();                //wpisanie wyznacznikow macierzy do wektora z wyznacznikami
    }
}

template<typename T, int SIZE>
void TlinearEquation<T,SIZE>::Solve()
{

this->Cramer();                              //rozwiazanie metoda cramera

    this->main_det = equation_matrix.detGauss(); 

    if(abs(main_det) > 0){
        for(int i = 0; i < SIZE; i++){
           
            solved[i]=det[i]/main_det;
        }
    }
    else{                                        //sprawdzenie czy wyznacznik != 0
        std::cout << "Glowny wyznacznik = 0, brak rozwiazan" << std::endl;
        exit(1);
    }
    
    this->mistake();                             //oblcizenie wektora bledow
}

template<typename T, int SIZE>
void TlinearEquation<T,SIZE>::mistake()
{
    TVector<T,SIZE> temp1 = equation_matrix*solved;
    TVector<T,SIZE> temp2 = temp1 - free_vector;

    mistake_vector = temp2;
}


template<typename T, int SIZE>
void TlinearEquation<T,SIZE>::Display()
{
    std::cout<<std::endl;
    std::cout << "..................................." << std::endl;
    std::cout << "Wyznacznik glowny" << std::endl;
    std::cout << this->main_det << std::endl;

    std::cout << "Wektor wyznacznikow " << std::endl;
    std::cout << this->det << std::endl;

    std::cout << "Wektor bledu" << std::endl;
    std::cout << this->mistake_vector << std::endl;

    std::cout << "Wektor rozwiazan" << std::endl;
    std::cout << this->solved << std::endl;

}