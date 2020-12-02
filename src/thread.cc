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
  float theta_step, start_theta;
  float randomness, alpha;
};
void *doTheJob(void *args)
{
  const char *path = "../outputs/data/r_";
  struct thread_data *data;
  data = (struct thread_data *)args;
  ofstream outfile;
  outfile.open(path + to_string(data->size) + '_' +to_string(data->thread_id) + ".csv", ios_base::app);
  for (int t = data->start_theta; t < data->theta_step + data->start_theta; t++)
  {
    Matrix mat(data->size, data->randomness, data->alpha, float(t) / 1000);
    mat.calculateTotalEnergy();
    dynamics dyn(&mat, 1);
    dyn.mixedDynamics();
    outfile << data->alpha
            << ","
            << float(t) / 1000
            << ","
            << mat.totalEnergy
            << ","
            << float(mat.squareEnergy) / (mat.squarCount * 3)
            << ","
            << float(mat.openSquares) / (mat.squarCount * 12)
            << ","
            << float(mat.triadEnergy) / mat.triadCount
            << ","
            << float(mat.twoStars) / (mat.triadCount * 3)
            << ","
            << float(mat.signsSum) / ((mat.size * mat.size - mat.size) / 2)
            << "\n";
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

void simulate(int size, float randomness, float alpha)
{
  int thread_temp_step = 500 / NUM_THREADS;
  pthread_t threads[NUM_THREADS];
  struct thread_data td[NUM_THREADS];
  int rc;
  int i;
  for (i = 0; i < NUM_THREADS; i++)
  {
    td[i].thread_id = i;
    td[i].theta_step = thread_temp_step;
    td[i].start_theta = thread_temp_step * i;
    td[i].alpha = alpha;
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