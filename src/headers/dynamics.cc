//Author: Mohammad Hossein Hakimi Siboni
//Center For Complex Networks and Social Data Science, Shahid Beheshti University, Physics Dpt.

#include "dynamics.h"
#include <iostream>
#include <numeric> // std::inner_product
#include <math.h>  /* exp pow */

dynamics::dynamics(Matrix *mat, double temperature)
{
  this->mat = mat;
  this->temperature = temperature;
  this->nodes = new unsigned[mat->size];
  this->dum_1 = this->dum_2 = this->dum_3 = this->delta_o = this->extraTerms = 0;
}
void dynamics::mixedDynamics()
{
  float eng;
  int montCarloSteps = pow(mat->size, 3);
  for (int i = 0; i < montCarloSteps; i++)
  {
    this->randomTwinsGenerator();
    this->oneSquareLink();
    this->oneTraidLink();
    eng = mat->theta * this->tEng + mat->alpha * this->sEng;
    /*
    Boltzman Factor = exp(-dE/T)
    */

    if (float(rand()) / RAND_MAX < exp(- eng / this->temperature))
    // if (eng<0)
    {
      mat->adjacency[this->randomTwins[0]][this->randomTwins[1]] *= -1;
      mat->adjacency[this->randomTwins[1]][this->randomTwins[0]] *= -1;
      mat->triadEnergy += this->tEng;
      mat->squareEnergy += this->sEng;
      mat->twoStars += this->tsc;
      mat->openSquares += this->delta_o;
      mat->signsSum += 2 * mat->adjacency[this->randomTwins[0]][this->randomTwins[1]];
    }
  }
}
void dynamics::triadDynamics()
{
  int montCarloSteps = pow(mat->size, 4);
  for (int i = 0; i < montCarloSteps; i++)
  {
    this->randomTwinsGenerator();
    this->oneTraidLink();
    /*
    Boltzman Factor = exp(-dE/T)
    */

    if (float(rand()) / RAND_MAX < exp(- this->tEng / this->temperature))
    {
      // std::cout << exp(2 * this->tEng / this->temperature);
      mat->adjacency[this->randomTwins[0]][this->randomTwins[1]] *= -1;
      mat->adjacency[this->randomTwins[1]][this->randomTwins[0]] *= -1;
      mat->triadEnergy += this->tEng;
      mat->twoStars += this->tsc;
      mat->signsSum += 2 * mat->adjacency[this->randomTwins[0]][this->randomTwins[1]];
    }
  }
}

void dynamics::oneTraidLink()
{
  int dummy;
  this->row = mat->adjacency[this->randomTwins[0]];
  this->column = mat->adjacency[this->randomTwins[1]];
  short linkSign = this->row[this->randomTwins[1]];
  int sum = std::accumulate(this->row, this->row + mat->size, 0) +
            std::accumulate(this->column, this->column + mat->size, 0);
  this->tEng = std::inner_product(this->row, this->row + mat->size, this->column, 0) * linkSign * 2;
  this->tsc = -2 * linkSign * (sum - 2 * linkSign);
  // std::cout << this->tEng << "\n";
  // std::cin >> dummy;
}

void dynamics::squarDynamics()
{
  int montCarloSteps = pow(mat->size, 3);

  for (int i = 0; i < montCarloSteps; i++)
  {
    this->randomTwinsGenerator();
    this->oneSquareLink();
    if (float(rand()) / RAND_MAX < exp(- this->sEng / this->temperature))
    {
      mat->adjacency[this->randomTwins[0]][this->randomTwins[1]] *= -1;
      mat->adjacency[this->randomTwins[1]][this->randomTwins[0]] *= -1;
      mat->squareEnergy += this->sEng;
      mat->openSquares += this->delta_o;
      mat->signsSum += 2 * mat->adjacency[this->randomTwins[0]][this->randomTwins[1]];
    }
  }
}

void dynamics::oneSquareLink()
{
  this->sEng = 0;
  mat->ssc = 0;
  this->dum_1 = this->dum_2 = this->dum_3 = this->delta_o = this->extraTerms = 0;
  short linkSign = mat->adjacency[this->oneSquare[0]][this->oneSquare[1]];
  for (int c = 0; c < mat->size; c++)
  {
    this->dum_1 += mat->adjacency[this->oneSquare[0]][c];
    this->dum_2 += mat->adjacency[this->oneSquare[1]][c];
    this->dum_3 += mat->adjacency[this->oneSquare[0]][c] *
                   mat->adjacency[this->oneSquare[1]][c];
    this->oneSquare[2] = c;
    for (int j = 0; j < c; j++)
    {
      this->oneSquare[3] = j;
      this->sEng += mat->oneSquareEnergyPrime(oneSquare);
    }
  }
  this->extraTerms = (this->dum_1 + this->dum_2) * 2 * linkSign +
                     2 * dum_3 + 2 * (mat->size - 1) - 3;
  this->sEng = 2 * linkSign * (this->sEng + (3 - 2 * mat->size) * linkSign);
  // std::cout << this->sEng << "\n";
  this->delta_o = -2 * linkSign * (mat->ssc - this->extraTerms);
}
void dynamics::randomTwinsGenerator()
{
  this->randomTwins[0] = rand() % this->mat->size;
  this->randomTwins[1] = (this->randomTwins[0] + (rand() % (this->mat->size - 1)) + 1) % this->mat->size;
  this->oneSquare[0] = this->randomTwins[0];
  this->oneSquare[1] = this->randomTwins[1];
}