#include <cmath>
#include <iostream>

#include <movielens/rating_dataset.h>

int main(int argc, char** argv) {
  using namespace std;

  if (2 > argc || argc > 3) {
    cout << "usage:\n"
         << argv[0] << " <rating dataset> [options]\n"
         << "options: log, gnuplot\n"
         << "default: log\n";
    return -1;
  }

  string option{"log"};
  if (3 == argc) option = argv[2];

  movielens::rating_dataset ratings{argv[1]};

  if (option == "log") {
    const auto& histogram = ratings.rating_histogram();
    cout << "bin\tmin ratings\tuser count\n";
    for (auto i = 0; i < histogram.size(); ++i) {
      cout << i << "\t"
           << static_cast<int>(ceil(exp(i / ratings.rating_histogram_factor())))
           << "\t\t" << histogram[i] << endl;
    }
    cout << endl;
    cout << "user count = " << ratings.size() << endl
         << "max rating count = " << ratings.max_rating_count() << endl
         << "mean rating count = " << ratings.mean_rating_count() << endl
         << "std dev rating count = " << sqrt(ratings.var_rating_count())
         << endl;

  } else if (option == "gnuplot") {
    const auto& histogram = ratings.rating_histogram();
    float min_ratings = 1;
    for (auto i = 0; i < histogram.size(); ++i) {
      const float new_min_ratings =
          ceil(exp((i + 1) / ratings.rating_histogram_factor()));
      const float box_position = 0.5 * (min_ratings + new_min_ratings);
      const float box_width = new_min_ratings - min_ratings;
      cout << box_position << "\t" << histogram[i] << "\t" << box_width << endl;
      min_ratings = new_min_ratings;
    }
    cout << endl;
  }
}