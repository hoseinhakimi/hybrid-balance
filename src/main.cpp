//Author: Mohammad Hossein Hakimi Siboni
//Center For Complex Networks and Social Data Science, Shahid Beheshti University, Physics Dpt.

#include "headers/matrix.cc"
#include "headers/dynamics.cc"
#include <iostream> // std::cout

using namespace std;

int main()
{
  Matrix mat(50, 0.5, 0.5);
  cout << mat.squareEnergy << "\t" << mat.openSquares << "\t"
       << mat.triadEnergy << "\t" << mat.twoStars << "\t"
       << mat.signsSum << "\n";
  dynamics dyn(&mat, 70);
  dyn.mixedDynamics();
  cout << mat.squareEnergy << "\t" << mat.openSquares << "\t"
       << mat.triadEnergy << "\t" << mat.twoStars << "\t"
       << mat.signsSum << "\n";
  
}