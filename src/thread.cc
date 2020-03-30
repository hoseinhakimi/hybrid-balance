//Author: Mohammad Hossein Hakimi Siboni
//Center For Complex Networks and Social Data Science, Shahid Beheshti University, Physics Dpt.

#include "headers/matrix.cc"
#include "headers/dynamics.cc"
#include <fstream>
#include <iostream> // std::cout
#include <pthread.h>
#include <chrono>
#include <ctime>

using namespace std;
#define NUM_THREADS 4

ofstream outfile;
struct thread_data
{
  int thread_id, size;
  double thread_temperature_step, start_temp;
  float randomness, participation;
};
void *doTheJob(void *args)
{
  struct thread_data *data;
  data = (struct thread_data *)args;
  Matrix mat(data->size, data->randomness, data->participation);
  for (int t = data->start_temp; t < data->thread_temperature_step + data->start_temp; t++)
  {
    dynamics dyn(&mat, t);
    dyn.mixedDynamics();
    outfile << data->participation
            << "\t"
            << t
            << "\t"
            << float(mat.squareEnergy) / (mat.squarCount * 3)
            << "\t"
            << float(mat.openSquares) / (mat.squarCount * 12)
            << "\t"
            << float(mat.triadEnergy) / mat.triadCount
            << "\t"
            << mat.twoStars / (mat.triadCount * 3)
            << "\t"
            << float(mat.signsSum) / ((mat.size * mat.size - mat.size) / 2)
            << "\n";
    mat.resetMatrix();
  }

  pthread_exit(NULL);
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

void simulate(int size, float randomness, float participation)
{
  int thread_temp_step = 100 / NUM_THREADS;
  const char *path = "../outputs/data/mixed_dynamics_";
  outfile.open(path + to_string(size) + '_' + to_string(randomness), ios_base::app);

  pthread_t threads[NUM_THREADS];
  struct thread_data td[NUM_THREADS];
  int rc;
  int i;
  for (i = 0; i < NUM_THREADS; i++)
  {
    td[i].thread_id = i;
    td[i].thread_temperature_step = thread_temp_step;
    td[i].start_temp = thread_temp_step * i;
    td[i].participation = participation;
    td[i].randomness = randomness;
    td[i].size = size;
    rc = pthread_create(&threads[i], NULL, doTheJob, (void *)&td[i]);

    if (rc)
    {
      cout << "Error:unable to create thread," << rc << endl;
      exit(-1);
    }
    // cout << pthread_join(threads[i], NULL) << "\n";
  }
  pthread_exit(NULL);
}