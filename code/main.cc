#include <cmath>
#include <iostream>

#include <movielens/movie_dataset.h>
#include <movielens/rating_dataset.h>
#include <movielens/rbm.h>

int main(int argc, char** argv) {
  using namespace std;

  if (3 != argc) {
    cout << "usage:\n" << argv[0] << " <movie dataset> <rating dataset>\n";
    return -1;
  }

  movielens::movie_dataset movies{argv[1]};
  movielens::rating_dataset ratings{argv[2]};
  movielens::rbm{ratings, 100};
}