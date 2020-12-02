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
  double temperature;
  float theta;

  int *row;
  int *column;
  int tsc, dum_1, dum_2, dum_3, extraTerms, delta_o;
  float tEng, sEng;
  unsigned oneSquare[4];
  unsigned smaller, bigger;
  unsigned *nodes;

  dynamics(Matrix *, double);
  void randomTwinsGenerator();
  void mixedDynamics();
  void triadDynamics();
  void squarDynamics();
  void oneSquareLink();
  void oneTraidLink();
};

#endif // HYBRIDDYNAMICS_DYNAMICS_MATRIX_H_