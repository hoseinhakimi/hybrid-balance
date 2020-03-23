//Author: Mohammad Hossein Hakimi Siboni
//Center For Complex Networks and Social Data Science, Shahid Beheshti University, Physics Dpt.

#include "thread.cc"

int main()
{
  int size;
  float participation;
  cin >> size >> participation;
  cout << participation / 20 << '\t' << size << '\t';
  simulate(size, 0.5, participation/20);
}