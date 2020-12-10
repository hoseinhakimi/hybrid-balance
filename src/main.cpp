//Author: Mohammad Hossein Hakimi Siboni
//Center For Complex Networks and Social Data Science, Shahid Beheshti University, Physics Dpt.

#include "thread.cc"
#include <memory>

int main()
{
  int size, ensemblesCount;
  float alpha, theta, randomness;
  cin >> size >> alpha >> theta >> randomness >> ensemblesCount;
  alpha /= 1000;

  cout << alpha << '\t'<< theta <<'\t' <<size << '\t' << randomness << '\n';

  simulate(size, randomness, alpha, theta, ensemblesCount);
}