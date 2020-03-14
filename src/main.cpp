//Author: Mohammad Hossein Hakimi Siboni
//Affiliation: Center For Cognitive and Data Science, Shahid Beheshti University, Physics Dpt.

#include "headers/matrix.cc"
#include <iostream> // std::cout

using namespace std;

int main()
{
    Matrix mat(10, 1, 3);
    mat.count();
    mat.makeMatrix();
    mat.calculateSquarEnergy();
    mat.calculateTriadEnergy();
    mat.calculateTotalEnergy();
    cout << mat.totalEnergy << "\n";
}