//Author: Mohammad Hossein Hakimi Siboni
//Affiliation: Center For Cognitive and Data Science, Shahid Beheshti University, Physics Dpt.

#ifndef HYBRIDDYNAMICS_HEADERS_MATRIX_H_
#define HYBRIDDYNAMICS_HEADERS_MATRIX_H_

class Matrix
{
public:
    short size;
    double randomness;
    double participation;
    int triadCount;
    int squarCount;
    int triadEnergy;
    int squareEnergy;
    int totalEnergy;
    int **adjacency;

    Matrix(short size, double randomness, double participation);
    void count();
    void makeMatrix();
    void initializeAdjacency();
    void calculateTriadEnergy();
    void calculateSquarEnergy();
    void calculateTotalEnergy();
    short oneSquareEnergy(unsigned *row);
};

#endif // HYBRIDDYNAMICS_HEADERS_MATRIX_H_