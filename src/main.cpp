//Author: Mohammad Hossein Hakimi Siboni
//Center For Complex Networks and Social Data Science, Shahid Beheshti University, Physics Dpt.

#include "thread.cc"
#include <memory>

int main()
{
  int size, ensemblesCount;
  float temperature, alpha, randomness, temperature_steps;

  cin >> size >> temperature >> temperature_steps >> alpha >> randomness >> ensemblesCount;

  cout << temperature * temperature_steps << '\t' << alpha << '\t' << size << '\t' << randomness / 2 << '\n';

  simulate(size, randomness / 2, alpha, 1, temperature * temperature_steps, ensemblesCount);
}