#include "rating_dataset.h"

#include <algorithm>
#include <cmath>
#include <fstream>
#include <limits>
#include <stdexcept>
#include <string>

namespace movielens {

rating_dataset::rating_dataset(const char* file_path) {
  using namespace std;

  fstream file(file_path, ios::in);
  if (!file.is_open())
    throw runtime_error(string("The file '") + file_path +
                        "' could not be opened!\n");

  // local helper functions
  const auto ignore_line = [&file]() {
    file.ignore(numeric_limits<streamsize>::max(), '\n');
  };
  const auto match = [&file](char c) {
    if (c != file.get()) throw runtime_error("Format does not match!");
  };

  std::vector<Eigen::Triplet<float>> rating_list;

  // ignore header
  ignore_line();
  int user_id;
  while (file >> user_id) {  // get user_id in place
    const auto user_emplace = user_index_.try_emplace(user_id, user_id_.size());
    const auto new_user_emplaced = user_emplace.second;
    const auto user_index = user_emplace.first->second;
    if (new_user_emplaced) {
      user_id_.push_back(user_id);
      user_rating_count_.push_back(0);
    }

    match(',');

    int movie_id;
    file >> movie_id;
    const auto movie_emplace =
        movie_index_.try_emplace(movie_id, movie_id_.size());
    const auto new_movie_emplaced = movie_emplace.second;
    const auto movie_index = movie_emplace.first->second;
    if (new_movie_emplaced) {
      movie_id_.push_back(user_id);
      movie_rating_count_.push_back(0);
    }

    match(',');

    float rating;
    file >> rating;
    rating_list.push_back({user_index, movie_index, rating});

    ++user_rating_count_[user_index];
    ++movie_rating_count_[movie_index];

    ignore_line();
  }

  // for (auto i = 0; i < user_id_.size(); ++i) {
  //   if (i != user_index_[user_id_[i]])
  //     throw runtime_error("Something went wrong!");
  // }

  ratings_ = Matrix(user_id_.size(), movie_id_.size());
  ratings_.setFromTriplets(rating_list.begin(), rating_list.end());
}

}  // namespace movielens