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
}
void dynamics::mixedDynamics()
{
  float eng;
  int montCarloSteps = pow(mat->size, 4);
  for (int i = 0; i < montCarloSteps; i++)
  {
    this->randomTwinsGenerator();

    this->oneSquareLink();
    this->oneTraidLink();
    eng = (1 - mat->participation) * this->tEng + mat->participation * this->sEng; //!!!!????

    /*
    Energy Change on Flip (dE) = - eng - eng = -2eng, 
    Boltzman Factor = exp(-dE/T) = exp(2eng/T) 
    */

    if (float(rand()) / RAND_MAX < exp(2 * eng / this->temperature))
    {
      mat->adjacency[this->randomTwins[0]][this->randomTwins[1]] *= -1;
      mat->adjacency[this->randomTwins[1]][this->randomTwins[0]] *= -1;
      mat->triadEnergy -= 2 * this->tEng;
      mat->squareEnergy -= 2 * this->sEng;
      mat->twoStars += this->tsc;
      mat->openSquares += mat->ssc;
      mat->signsSum += 2 * mat->adjacency[this->randomTwins[0]][this->randomTwins[1]];
    }
  }
}
void dynamics::triadDynamics()
{
  int montCarloSteps = pow(mat->size, 3);
  for (int i = 0; i < montCarloSteps; i++)
  {
    this->randomTwinsGenerator();
    this->oneTraidLink();
    /*
    Energy Change on Flip (dE) = - eng - eng = -2eng, 
    Boltzman Factor = exp(-dE/T) = exp(2eng/T) 
    */
    if (float(rand()) / RAND_MAX < exp(2 * this->tEng / this->temperature))
    {
      mat->adjacency[this->randomTwins[0]][this->randomTwins[1]] *= -1;
      mat->adjacency[this->randomTwins[1]][this->randomTwins[0]] *= -1;
      mat->triadEnergy -= 2 * this->tEng / mat->triadCount;
      mat->twoStars += this->tsc;
    }
  }
}

void dynamics::oneTraidLink()
{
  this->row = mat->adjacency[this->randomTwins[0]];
  this->column = mat->adjacency[this->randomTwins[1]];
  short linkSign = this->row[this->randomTwins[1]];
  int sum = std::accumulate(this->row, this->row + mat->size, 0) +
            std::accumulate(this->column, this->column + mat->size, 0);
  this->tEng = -std::inner_product(this->row, this->row + mat->size, this->column, 0) * linkSign;
  this->tsc = -2 * linkSign * (sum - 2 * linkSign);
}

void dynamics::squarDynamics()
{
  int montCarloSteps = pow(mat->size, 4) * 3;

  for (int i = 0; i < montCarloSteps; i++)
  {
    this->randomTwinsGenerator();
    this->oneSquareLink();
    if (float(rand()) / RAND_MAX < exp(2 * this->sEng / this->temperature))
    {
      mat->adjacency[this->randomTwins[0]][this->randomTwins[1]] *= -1;
      mat->adjacency[this->randomTwins[1]][this->randomTwins[0]] *= -1;
      mat->squareEnergy -= 2 * this->sEng / (3 * mat->squarCount);
      mat->openSquares += mat->ssc;
    }
  }
}

void dynamics::oneSquareLink()
{
  this->sEng = 0;
  mat->ssc = 0;
  if (this->randomTwins[0] > this->randomTwins[1])
  {
    this->bigger = this->randomTwins[0];
    this->smaller = this->randomTwins[1];
  }
  else
  {
    this->bigger = this->randomTwins[1];
    this->smaller = this->randomTwins[0];
  }

  this->oneSquare[0] = smaller;
  this->oneSquare[1] = bigger;

  short counter = 0;
  for (counter = 0; counter < smaller; counter++)
    this->nodes[counter] = counter;
  for (counter = smaller + 1; counter < bigger; counter++)
    this->nodes[counter - 1] = counter;
  for (counter = bigger + 1; counter < mat->size; counter++)
    this->nodes[counter - 2] = counter;

  for (int c = 0; c < mat->size - 2; c++)
  {
    this->oneSquare[2] = this->nodes[c];
    for (int j = c + 1; j < mat->size - 2; j++)
    {
      this->oneSquare[3] = this->nodes[j];
      this->sEng += mat->oneSquareEnergyPrime(oneSquare);
    }
  }
}
void dynamics::randomTwinsGenerator()
{
  this->randomTwins[0] = rand() % this->mat->size;
  this->randomTwins[1] = (this->randomTwins[0] + (rand() % (this->mat->size - 1)) + 1) % this->mat->size;
}