//Author: Mohammad Hossein Hakimi Siboni
//Affiliation: Center For Cognitive and Data Science, Shahid Beheshti University, Physics Dpt.

#include "headers/matrix.cc"
#include <iostream> // std::cout

using namespace std;

int main()
{

    Matrix mat(50, 0, 0.5);
    cout << mat.totalEnergy << "\t" << mat.squareEnergy << "\t" << mat.triadEnergy << "\n";
}