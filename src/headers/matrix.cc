//Author: Mohammad Hossein Hakimi Siboni
//Center For Complex Networks and Social Data Science, Shahid Beheshti University, Physics Dpt.

#include <stdlib.h> /* srand, rand */
#include <time.h>   /* time */
#include <numeric>  // std::inner_product
#include <iostream>
#include "matrix.h"
#include "../mathematics/iter.cc"

Matrix::Matrix(short size, double randomness, double participation)
{
    this->size = size;
    this->randomness = randomness;
    this->participation = participation;
    this->count();
    this->makeMatrix();
    this->calculateTriadEnergy();
    this->calculateSquarEnergy();
    this->calculateTotalEnergy();
}

void Matrix::count()
{
    this->triadCount = nChoosek(this->size, 3);
    this->squarCount = nChoosek(this->size, 4);
}

void Matrix::makeMatrix()
{
    this->adjacency = new int *[this->size];
    for (short i = 0; i < this->size; i++)
    {
        this->adjacency[i] = new int[this->size];
        this->adjacency[i][i] = 0;
    }
    this->initializeAdjacency();
}

void Matrix::initializeAdjacency()
{
    srand(time(NULL));
    for (short i = 0; i < this->size; i++)
    {
        for (short j = i + 1; j < this->size; j++)
        {
            short sign = int(float(rand()) / RAND_MAX + this->randomness) * 2 - 1;
            this->adjacency[i][j] = sign;
            this->adjacency[j][i] = sign;
        }
    }
}

void Matrix::calculateTriadEnergy()
{
    int eng = 0;
    for (short i = 0; i < this->size; i++)
    {
        int *row = this->adjacency[i];
        for (short j = i + 1; j < this->size; j++)
        {
            int *column = this->adjacency[j];
            eng -= std::inner_product(row, row + this->size, column, 0) * this->adjacency[i][j];
        };
    };
    this->triadEnergy = float(eng) / (3 * this->triadCount);
}

void Matrix::calculateSquarEnergy()
{
    this->squareEnergy = 0;
    squares(4, this);
    this->squareEnergy = -float(this->squareEnergy) / (this->squarCount * 3);
}

void Matrix::calculateTotalEnergy()
{
    this->totalEnergy = this->participation * this->squareEnergy +
                        (1 - this->participation) * this->triadEnergy;
}

void Matrix::oneSquareEnergy(unsigned *row)
{
    short sqrEnergy = 0;
    unsigned idx[3][3] = {{1, 2, 3}, {1, 3, 2}, {2, 1, 3}};
    for (unsigned i = 0; i < 3; i++)
    {
        sqrEnergy += this->adjacency[row[0]][row[idx[i][0]]] *
                     this->adjacency[row[idx[i][0]]][row[idx[i][1]]] *
                     this->adjacency[row[idx[i][1]]][row[idx[i][2]]] *
                     this->adjacency[row[idx[i][2]]][row[0]];
    }
    this->squareEnergy += sqrEnergy;
}