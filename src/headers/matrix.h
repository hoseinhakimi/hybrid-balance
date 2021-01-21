//Author: Mohammad Hossein Hakimi Siboni
//Center For Complex Networks and Social Data Science, Shahid Beheshti University, Physics Dpt.

#ifndef HYBRIDDYNAMICS_HEADERS_MATRIX_H_
#define HYBRIDDYNAMICS_HEADERS_MATRIX_H_

class Matrix
{
public:
  short size;
  double randomness;
  double participation;
  double alpha;
  double theta;
  double erdosProbability;
  int triadCount;
  int squarCount;

  int signsSum = 0;

  int twoStars;
  int openSquares;
  int ssc;

  int triadEnergy;
  int squareEnergy;

  float totalEnergy;
  int **adjacency;

  Matrix(short size, double randomness, double alpha, double theta, double erdosProbability);
  void count();
  void makeMatrix();
  void resetMatrix();
  void erdosAdjacency();
  void initializeAdjacency();
  void calculateTriadEnergy();
  void calculateSquarEnergy();
  void calculateTotalEnergy();
  void openSquaresChange(int *link);
  void oneSquareEnergy(unsigned *row);
  int oneSquareEnergyPrime(unsigned *row);
};

#endif // HYBRIDDYNAMICS_HEADERS_MATRIX_H_