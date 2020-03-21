//Author: Mohammad Hossein Hakimi Siboni
//Center For Complex Networks and Social Data Science, Shahid Beheshti University, Physics Dpt.

#ifndef HYBRIDDYNAMICS_HEADERS_DYNAMICS_H_
#define HYBRIDDYNAMICS_HEADERS_DYNAMICS_H_

#include "matrix.h"

class dynamics
{
public:
  Matrix *mat;
  int randomTwins[2];
  float temperature;

  int *row;
  int *column;
  int tsc;
  float tEng, sEng;
  unsigned oneSquare[4];
  unsigned smaller, bigger;
  unsigned *nodes;

  dynamics(Matrix *, float);
  void randomTwinsGenerator();
  void mixedDynamics();
  void triadDynamics();
  void squarDynamics();
  void oneSquareLink();
  void oneTraidLink();
};

#endif // HYBRIDDYNAMICS_DYNAMICS_MATRIX_H_