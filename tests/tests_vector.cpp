#include "doctest/doctest.h"
#include "vector.hh"
#include "matrix.hh"
#include "equations.hh"

// Tests that don't naturally fit in the headers/.cpp files directly
// can be placed in a tests/*.cpp file. Integration tests are a good example.


TEST_CASE("Matrix Constructor")
{
  double arg1[][SIZE] = {2,0,-2,-3,1,7,0,0,-2,0,-1,1,7,4,0,3,0,0,5,0,2,1,2,3,1};
  TMatrix<double,SIZE> temp = TMatrix<double,SIZE>(arg1);
  

  for(int i = 0; i < SIZE; i++){
    for(int j = 0; j < SIZE; j++){
      CHECK(temp(i,j) == arg1[j][i]);
    }
  }

}

TEST_CASE("test transpose")
{
  double arg1[][SIZE] = {2,0,-2,-3,1,7,0,0,-2,0,-1,1,7,4,0,3,0,0,5,0,2,1,2,3,1};
  TMatrix<double,SIZE> temp = TMatrix<double,SIZE>(arg1);

  temp.transpose();

  double arg2[][SIZE] = {2,7,-1,3,2,0,0,1,0,1,-2,0,7,0,2,-3,-2,4,5,3,1,0,0,0,1};
  TMatrix<double,SIZE> correct = TMatrix<double,SIZE>(arg2);

  for(int i = 0; i < SIZE; i++){
    for(int j = 0; j < SIZE; j++){
      CHECK(temp(i,j) == correct(i,j));
    }
  }
}


TEST_CASE("test swap rows 1st with Vector")
{
  double arg1[][SIZE] = {2,0,-2,-3,1,7,0,0,-2,0,-1,1,7,4,0,3,0,0,5,0,2,1,2,3,1};
  TMatrix<double,SIZE> temp = TMatrix<double,SIZE>(arg1);
  
  TVector<double,SIZE> tmp;
  tmp[0] = 2;
  tmp[1] = 0;
  tmp[2] = -2;
  tmp[3] =-3;
  tmp[4] = 1;

  temp.column_swap(2, tmp);

  double arg3[][SIZE] = {2,0,-2,-3,1,7,0,0,-2,0,2,0,-2,-3,1,3,0,0,5,0,2,1,2,3,1};
  TMatrix<double,SIZE> correct = TMatrix<double,SIZE>(arg3);

  for(int i = 0; i < SIZE; i++){
        CHECK(temp(0,i) == correct(0,i));
  }
}


TEST_CASE("Gauss det for Real")
{
  double arg1[][SIZE] = {2,3,3,5,2,1,-2,-1,-6,-3,2,7,-5,4,3,3,5,-3,2,1,2,-1,-2,-4,-2};
  TMatrix<double,SIZE> temp = TMatrix<double,SIZE>(arg1);
  
  CHECK((temp.detGauss())== (98));
}








