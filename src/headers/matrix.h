//Author: Mohammad Hossein Hakimi Siboni
//Center For Complex Networks and Social Data Science, Shahid Beheshti University, Physics Dpt.

#ifndef HYBRIDDYNAMICS_HEADERS_MATRIX_H_
#define HYBRIDDYNAMICS_HEADERS_MATRIX_H_

class Matrix
{
public:
  short threadId;
  short size;
  double randomness;
  double participation;
  double alpha;
  double theta;
  double omega;
  double erdosProbability;
  int triadCount;
  int squarCount;
  int pentagonCount;

  int signsSum = 0;

  int twoStars;
  int openSquares;
  int ssc;

  int triadEnergy;
  int squareEnergy;
  int pentagonEnergy;

  float totalEnergy;
  int **adjacency;

  Matrix(short size, double randomness,double omega, double alpha, double theta, double erdosProbability,short threadId);
  void count();
  void makeMatrix();
  void resetMatrix();
  void erdosAdjacency();
  void initializeAdjacency();
  void calculateTriadEnergy();
  void calculateSquarEnergy();
  void calculatePentagonEnergy();
  void calculateTotalEnergy();
  void openSquaresChange(int *link);
  void oneSquareEnergy(unsigned *row);
  void onePentagonEnergy(unsigned *row);
  int oneSquareEnergyPrime(unsigned *row);
  int onePentagonEnergyPrime(unsigned *row);
  int specificPentagonEnergyOneLinkFixed(unsigned *row);
};

#endif // HYBRIDDYNAMICS_HEADERS_MATRIX_H_