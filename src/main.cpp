//Author: Mohammad Hossein Hakimi Siboni
//Center For Complex Networks and Social Data Science, Shahid Beheshti University, Physics Dpt.

#include "thread.cc"
#include <memory>

int main()
{
  int size, ensemblesCount;
  float temperature, alpha, randomness;
  cin >> size >> temperature >> alpha >> randomness >> ensemblesCount;
  // alpha /= 1000;

  cout << temperature << '\t' << alpha << '\t' << size << '\t' << randomness << '\n';

  simulate(size, randomness, alpha, 1, temperature, ensemblesCount);
}