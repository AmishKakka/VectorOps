#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <omp.h>
#include "main.hpp"

using namespace std;

// Function to add two vectors
vector<float> add(vector<float> &v1, vector<float> &v2) {
  vector<float> result(v1.size());
  # pragma omp parallel
  transform(v1.begin(), v1.end(), v2.begin(), result.begin(), plus<float>());
  return result;
}

// Function to subtract two vectors
vector<float> subtract(vector<float> &v1, vector<float> &v2) {
  vector<float> result(v1.size());
  # pragma omp parallel
  transform(v1.begin(), v1.end(), v2.begin(), result.begin(), minus<float>());
  return result;
}

// Function to multiply two vectors
vector<float> multiply(vector<float> &v1, vector<float> &v2) {
  vector<float> result(v1.size());
  transform(v1.begin(), v1.end(), v2.begin(), result.begin(), multiplies<float>());
  return result;
}

int main() {
  vector<float> v1(200000000);
  vector<float> v2(200000000);
  vector<float> v3(200000000);

  default_random_engine generator;
  uniform_real_distribution<float> distribution(0.0, 1.0);
  
  auto st = chrono::high_resolution_clock::now();
  #pragma omp parallel for
  for (int i = 0; i < v1.size(); ++i) {
    v1[i] = distribution(generator);
    v2[i] = distribution(generator);
  }
  
  v3 = add(v1, v2);
  v3 = subtract(v1, v2);
  auto et = chrono::high_resolution_clock::now();

  std::chrono::duration<double, std::milli> elapsed_ms = et - st;
  
  cout << "Time taken: " << elapsed_ms.count() << " ms" << endl;

  return 0;
}