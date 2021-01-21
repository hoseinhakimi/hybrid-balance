//Author: Mohammad Hossein Hakimi Siboni
//Center For Complex Networks and Social Data Science, Shahid Beheshti University, Physics Dpt.

#include "thread.cc"
#include <memory>

int main()
{
  int size, ensemblesCount;
  float temperature, theta, randomness;
  cin >> size >> temperature >> theta >> randomness >> ensemblesCount;
  // alpha /= 1000;

  cout << temperature << '\t' << theta << '\t' << size << '\t' << randomness << '\n';

  simulate(size, randomness, 1, theta, temperature, ensemblesCount);
}