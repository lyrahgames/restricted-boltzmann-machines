#include <cmath>
#include <iostream>

#include <movielens/movie_dataset.h>
#include <movielens/rating_dataset.h>

int main(int argc, char** argv) {
  using namespace std;

  if (3 != argc) {
    cout << "usage:\n" << argv[0] << " <movie dataset> <rating dataset>\n";
    return -1;
  }

  movielens::movie_dataset movies{argv[1]};

  // cout << "#\tid\ttitle\n";
  // for (auto i = 0; i < movies.size(); ++i) {
  //   cout << i << "\t" << movies.movie_id(i) << "\t" << movies.movie_title(i)
  //        << endl;
  // }
  // cout << "movie count = " << movies.size() << endl;

  movielens::rating_dataset ratings{argv[2]};

  // for (auto i = 0; i < ratings.size(); ++i) {
  //   cout << i << "\t" << ratings.user_id(i) << "\t" <<
  //   ratings.rating_count(i)
  //        << endl;
  // }
  // cout << endl;

  // const auto& histogram = ratings.rating_histogram();
  // for (auto i = 0; i < histogram.size(); ++i) {
  //   cout << i << "\t"
  //        << static_cast<int>(ceil(exp(i /
  //        ratings.rating_histogram_factor())))
  //        << "\t" << histogram[i] << endl;
  // }
  // cout << endl;

  // cout << "movie count = " << movies.size() << endl
  //      << "user count = " << ratings.size() << endl
  //      << "max rating count = " << ratings.max_rating_count() << endl
  //      << "mean rating count = " << ratings.mean_rating_count() << endl
  //      << "std dev rating count = " << sqrt(ratings.var_rating_count()) <<
  //      endl;

  // const auto& histogram = ratings.rating_histogram();
  // for (auto i = 0; i < histogram.size(); ++i) {
  //   const float position =
  //       0.5 * (ceil(exp(i / ratings.rating_histogram_factor())) +
  //              ceil(exp((i + 1) / ratings.rating_histogram_factor())));
  //   const float width = ceil(exp((i + 1) /
  //   ratings.rating_histogram_factor())) -
  //                       ceil(exp(i / ratings.rating_histogram_factor()));
  //   cout << position << "\t" << histogram[i] << "\t" << width << endl;
  // }
  // cout << endl;
}