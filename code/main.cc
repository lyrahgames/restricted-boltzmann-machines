#include <iostream>

#include <movielens/movie_dataset.h>

int main(int argc, char** argv) {
  using namespace std;

  if (2 != argc) {
    cout << "usage:\n" << argv[0] << " <movie dataset>\n";
    return -1;
  }

  movielens::movie_dataset movies{argv[1]};

  cout << "#\tid\ttitle\n";
  for (auto i = 0; i < movies.size(); ++i) {
    cout << i << "\t" << movies.movie_id(i) << "\t" << movies.movie_title(i)
         << endl;
  }
  cout << "movie count = " << movies.size() << endl;
}