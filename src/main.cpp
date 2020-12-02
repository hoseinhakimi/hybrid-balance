//Author: Mohammad Hossein Hakimi Siboni
//Center For Complex Networks and Social Data Science, Shahid Beheshti University, Physics Dpt.

#include "thread.cc"
#include <memory>

int main()
{
  int size;
  float alpha, randomness;
  cin >> size >> alpha >> randomness;
  alpha /= 1000;

  cout << alpha << '\t' << size << '\t' << randomness << '\n';

  simulate(size, randomness, alpha);
}