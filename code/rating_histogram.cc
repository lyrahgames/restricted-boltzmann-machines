#include <cmath>
#include <iostream>

#include <movielens/histogram.h>
#include <movielens/rating_dataset.h>

int main(int argc, char** argv) {
  using namespace std;

  if (2 > argc || argc > 3) {
    cout << "usage:\n"
         << argv[0] << " <rating dataset> [options]\n"
         << "options: movie, user\n";
    return -1;
  }

  movielens::rating_dataset ratings{argv[1]};

  if (3 == argc) {
    string option = argv[2];
    if (option == "user") {
      movielens::histogram histogram{ratings.user_rating_count()};
      for (auto i = 0; i < histogram.size(); ++i) {
        const float box_position =
            0.5 * (histogram.bin(i) + histogram.bin(i + 1));
        const float box_width = histogram.bin(i + 1) - histogram.bin(i);
        cout << box_position << "\t" << histogram[i] << "\t" << box_width
             << endl;
      }
      cout << endl;
    } else if (option == "movie") {
      movielens::histogram histogram{ratings.movie_rating_count()};
      for (auto i = 0; i < histogram.size(); ++i) {
        const float box_position =
            0.5 * (histogram.bin(i) + histogram.bin(i + 1));
        const float box_width = histogram.bin(i + 1) - histogram.bin(i);
        cout << box_position << "\t" << histogram[i] << "\t" << box_width
             << endl;
      }
      cout << endl;
    } else {
      cout << "usage:\n"
           << argv[0] << " <rating dataset> [options]\n"
           << "options: movie, user\n";
      return -1;
    }
  } else {
    cout << "rating count = " << ratings.size() << endl
         << "movie count = " << ratings.movie_count() << endl
         << "user count = " << ratings.user_count() << endl
         << endl;

    cout << "user rating histogram:" << endl
         << movielens::histogram{ratings.user_rating_count()} << endl
         << endl;

    cout << "movie rating histogram:" << endl
         << movielens::histogram{ratings.movie_rating_count()} << endl
         << endl;
  }
}