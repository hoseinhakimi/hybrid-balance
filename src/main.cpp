//Author: Mohammad Hossein Hakimi Siboni
//Center For Complex Networks and Social Data Science, Shahid Beheshti University, Physics Dpt.

#include "thread.cc"

int main()
{
  int size;
  float participation, randomness;
  randomness = 0.5;
  cin >> size >> participation;
  cout << participation / 20 << '\t' << size << '\n';
  
  const char *path = "../outputs/data/mixed_dynamics_";
  if (!(ifstream(path + to_string(size) + '_' + to_string(randomness))))
  {
    ofstream outfile;
    outfile.open(path + to_string(size) + '_' + to_string(randomness));
    outfile << "Participation"
            << "\t"
            << "Temperature"
            << "\t"
            << "SquareEnergy"
            << "\t"
            << "OpenSquares"
            << "\t"
            << "TriadEnergy"
            << "\t"
            << "TwoStars"
            << "\t"
            << "Mean"
            << "\n";
  }
  simulate(size, 0.5, participation / 20);
}