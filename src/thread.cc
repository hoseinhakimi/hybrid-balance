// Author: Mohammad Hossein Hakimi Siboni
// Center For Complex Networks and Social Data Science, Shahid Beheshti University, Physics Dpt.

#include "headers/matrix.cc"
#include "headers/dynamics.cc"
#include <fstream>
#include <iostream> // std::cout
#include <pthread.h>
#include <chrono>
#include <ctime>

using namespace std;
#define NUM_THREADS 3

ofstream outfile;
struct thread_data
{
  int thread_id, size, ensemblesCount;
  float randomness, omega, alpha, theta, temperature;
};
void *doTheJobFixedTheta(void *args)
{
  const char *path = "../outputs/data/r_";
  struct thread_data *data;
  data = (struct thread_data *)args;
  ofstream outfile;
  outfile.open(path + to_string(data->size) + '_' + to_string(data->thread_id) + ".csv", ios_base::app);
  // for (int ensemble = 0; ensemble < data->ensemblesCount; ensemble++)
  // {
  Matrix mat(data->size, data->randomness, data->omega, data->alpha, data->theta);
  mat.calculateTotalEnergy();
  dynamics dyn(&mat, data->temperature);
  dyn.mixedDynamics();
  for (int e = 0; e < data->ensemblesCount * 1000 + 1; e++)
  {
    dyn.mixedMonteCarloStep();
    if (e % 1000 == 0)
      outfile << data->temperature
              << ","
              << data->alpha
              << ","
              << data->randomness
              << ","
              << float(mat.squareEnergy) / (mat.squarCount * 3) // four nodes create 3 squares
              << ","
              << float(mat.openSquares) / (mat.squarCount * 12)
              << ","
              << float(mat.triadEnergy) / mat.triadCount
              << ","
              << float(mat.twoStars) / (mat.triadCount * 3)
              << ","
              << float(mat.signsSum) / ((mat.size * mat.size - mat.size) / 2)
              << ","
              << float(mat.pentagonEnergy) / mat.pentagonCount
              << "\n";
  }
  // }
  pthread_exit(NULL);
}

void simulate(int size,
              float randomness,
              float omega,
              float alpha,
              float theta,
              float temperature,
              int ensemblesCount)
{
  pthread_t threads[NUM_THREADS];
  struct thread_data td[NUM_THREADS];
  int rc;
  int i;
  if (theta < 0)
  {
    cout << "wrong input"
         << "\n";
  }
  else
  {
    int ensembles = floor(ensemblesCount / NUM_THREADS);
    for (i = 0; i < NUM_THREADS; i++)
    {
      td[i].thread_id = i;
      td[i].ensemblesCount = ensembles;
      td[i].theta = theta;
      td[i].alpha = alpha;
      td[i].temperature = temperature;
      td[i].randomness = randomness;
      td[i].size = size;
      rc = pthread_create(&threads[i],
                          NULL,
                          doTheJobFixedTheta,
                          (void *)&td[i]);

      if (rc)
      {
        cout << "Error:unable to create thread," << rc << endl;
        exit(-1);
      }
    }
    pthread_exit(NULL);
  }
}

std::string datetime()
{
  time_t rawtime;
  struct tm *timeinfo;
  char buffer[80];

  time(&rawtime);
  timeinfo = localtime(&rawtime);

  strftime(buffer, 80, "%d-%m-%Y %H:%M:%S", timeinfo);
  return string(buffer);
}
