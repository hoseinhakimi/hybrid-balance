// Author: Mohammad Hossein Hakimi Siboni
// Center For Complex Networks and Social Data Science, Shahid Beheshti University, Physics Dpt.

#include <stdlib.h> /* srand, rand */
#include <time.h>   /* time */
#include <chrono>
#include <thread>
#include <numeric> /* std::inner_product */
#include "matrix.h"
#include "../mathematics/iter.cc"

using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
using std::chrono::system_clock;

Matrix::Matrix(short size, double randomness, double omega, double alpha, double theta, double erdosProbability = 1, short threadId = 0)
{
  this->threadId = threadId;
  this->size = size;
  this->randomness = randomness;
  this->alpha = alpha;
  this->theta = theta;
  this->omega = omega;
  this->erdosProbability = erdosProbability;
  this->count();
  this->makeMatrix();
  this->resetMatrix();
}

void Matrix::resetMatrix()
{
  this->erdosProbability == 1 ? this->initializeAdjacency() : this->erdosAdjacency();
  this->calculateTriadEnergy();
  this->calculateSquarEnergy();
  this->calculatePentagonEnergy();
}

void Matrix::count()
{
  this->triadCount = nChoosek(this->size, 3);
  this->squarCount = nChoosek(this->size, 4);
  this->pentagonCount = nChoosek(this->size, 5) * 12;
}

void Matrix::makeMatrix()
{
  this->adjacency = new int *[this->size];
  for (short i = 0; i < this->size; i++)
  {
    this->adjacency[i] = new int[this->size];
    this->adjacency[i][i] = 0;
  }
}

void Matrix::erdosAdjacency()
{
  this->signsSum = 0;
  srand(time(0));
  for (short i = 0; i < this->size; i++)
  {
    for (short j = i + 1; j < this->size; j++)
    {
      if (rand() / RAND_MAX > this->erdosProbability)
      {
        short sign = int(float(rand()) / RAND_MAX + this->randomness) * 2 - 1;
        this->adjacency[i][j] = sign;
        this->adjacency[j][i] = sign;
        this->signsSum += sign;
      }
    }
  }
}

void Matrix::initializeAdjacency()
{
  this->signsSum = 0;
  srand(this->threadId);
  for (short i = 0; i < this->size; i++)
  {
    for (short j = i + 1; j < this->size; j++)
    {
      short sign = int(float(rand()) / RAND_MAX + this->randomness) * 2 - 1;
      this->adjacency[i][j] = sign;
      this->adjacency[j][i] = sign;
      this->signsSum += sign;
    }
  }
}

void Matrix::calculateTriadEnergy()
{
  int eng = 0;
  int stars = 0;
  this->twoStars = 0;
  for (short i = 0; i < this->size; i++)
  {
    int *row = this->adjacency[i];
    for (short j = i + 1; j < this->size; j++)
    {
      int *column = this->adjacency[j];
      stars = std::inner_product(row, row + this->size, column, 0);
      eng -= stars * this->adjacency[i][j];
      this->twoStars += stars;
    };
  };
  this->triadEnergy = eng / 3; // every triad is counted 3 times
}

void Matrix::calculateSquarEnergy()
{
  this->squareEnergy = 0;
  this->openSquares = 0;
  // squares(4, this);
}

void Matrix::calculatePentagonEnergy()
{
  this->pentagonEnergy = 0;
  // pentagons(5, this);
}

void Matrix::calculateTotalEnergy()
{
  this->totalEnergy = this->alpha * float(this->squareEnergy) / (this->squarCount * 3) +
                      this->theta * float(this->triadEnergy) / this->triadCount +
                      this->omega * float(this->pentagonEnergy) / this->pentagonCount;
}

void Matrix::oneSquareEnergy(unsigned *row)
{
  int sqrEnergy = 0;
  int openSquare = 0;
  unsigned idx[3][3] = {{1, 2, 3}, {1, 3, 2}, {2, 1, 3}};
  for (unsigned i = 0; i < 3; i++)
  {
    sqrEnergy -= this->adjacency[row[0]][row[idx[i][0]]] *
                 this->adjacency[row[idx[i][0]]][row[idx[i][1]]] *
                 this->adjacency[row[idx[i][1]]][row[idx[i][2]]] *
                 this->adjacency[row[idx[i][2]]][row[0]];
    openSquare += this->adjacency[row[0]][row[idx[i][0]]] *
                      this->adjacency[row[idx[i][0]]][row[idx[i][1]]] *
                      this->adjacency[row[idx[i][1]]][row[idx[i][2]]] +
                  this->adjacency[row[0]][row[idx[i][0]]] *
                      this->adjacency[row[idx[i][0]]][row[idx[i][1]]] *
                      this->adjacency[row[idx[i][2]]][row[0]] +
                  this->adjacency[row[0]][row[idx[i][0]]] *
                      this->adjacency[row[idx[i][1]]][row[idx[i][2]]] *
                      this->adjacency[row[idx[i][2]]][row[0]] +
                  this->adjacency[row[idx[i][0]]][row[idx[i][1]]] *
                      this->adjacency[row[idx[i][1]]][row[idx[i][2]]] *
                      this->adjacency[row[idx[i][2]]][row[0]];
  }
  this->squareEnergy += sqrEnergy;
  this->openSquares += openSquare;
}

void Matrix::onePentagonEnergy(unsigned *row)
{
  int pentagonEnergy = 0;
  unsigned idx[12][4] = {{1, 2, 3, 4}, {1, 2, 4, 3}, {1, 4, 2, 3}, {1, 3, 2, 4}, {1, 4, 3, 2}, {1, 3, 4, 2}, {2, 1, 3, 4}, {2, 1, 4, 3}, {2, 3, 1, 4}, {2, 4, 1, 3}, {3, 1, 2, 4}, {3, 2, 1, 4}};
  for (unsigned i = 0; i < 12; i++)
  {
    pentagonEnergy -= this->adjacency[row[0]][row[idx[i][0]]] *
                      this->adjacency[row[idx[i][0]]][row[idx[i][1]]] *
                      this->adjacency[row[idx[i][1]]][row[idx[i][2]]] *
                      this->adjacency[row[idx[i][2]]][row[idx[i][3]]] *
                      this->adjacency[row[idx[i][3]]][row[0]];
  }
  this->pentagonEnergy += pentagonEnergy;
}

int Matrix::oneSquareEnergyPrime(unsigned *row)
{
  int sqrEnergy = 0;
  int openSquare = 0;
  unsigned idx[2][3] = {{1, 2, 3}, {1, 3, 2}};
  short linkSign = this->adjacency[row[0]][row[1]];
  for (unsigned i = 0; i < 2; i++)
  {
    sqrEnergy +=
        this->adjacency[row[idx[i][0]]][row[idx[i][1]]] *
        this->adjacency[row[idx[i][1]]][row[idx[i][2]]] *
        this->adjacency[row[idx[i][2]]][row[0]];
    openSquare +=
        this->adjacency[row[idx[i][0]]][row[idx[i][1]]] *
            this->adjacency[row[idx[i][1]]][row[idx[i][2]]] +
        this->adjacency[row[idx[i][0]]][row[idx[i][1]]] *
            this->adjacency[row[idx[i][2]]][row[0]] +
        this->adjacency[row[idx[i][1]]][row[idx[i][2]]] *
            this->adjacency[row[idx[i][2]]][row[0]];
  }
  this->ssc += openSquare;
  return sqrEnergy;
}

int Matrix::onePentagonEnergyPrime(unsigned *row)
{
  int pentagonEnergy = 0;
  unsigned idx[6][4] = {{1, 2, 3, 4}, {1, 2, 4, 3}, {1, 4, 2, 3}, {1, 3, 2, 4}, {1, 4, 3, 2}, {1, 3, 4, 2}};
  for (unsigned i = 0; i < 6; i++)
  {
    pentagonEnergy += this->adjacency[row[idx[i][0]]][row[idx[i][1]]] *
                      this->adjacency[row[idx[i][1]]][row[idx[i][2]]] *
                      this->adjacency[row[idx[i][2]]][row[idx[i][3]]] *
                      this->adjacency[row[idx[i][3]]][row[0]];
  }
  return pentagonEnergy;
}

int Matrix::specificPentagonEnergyOneLinkFixed(unsigned *row)
{
  int pentagonEnergy = 0;
  unsigned nodeIterations[6][3] = {{4, 2, 3}, {4, 3, 2}, {2, 4, 3}, {2, 3, 4}, {3, 4, 2}, {3, 2, 4}};
  for (unsigned i = 0; i < 3; i++)
  {
    pentagonEnergy += this->adjacency[row[0]][row[nodeIterations[i][0]]] *
                      this->adjacency[row[nodeIterations[i][0]]][row[nodeIterations[i][1]]] *
                      this->adjacency[row[nodeIterations[i][1]]][row[nodeIterations[i][2]]] *
                      this->adjacency[row[nodeIterations[i][2]]][row[1]];
  }
  return pentagonEnergy;
}

void Matrix::openSquaresChange(int *link)
{
}