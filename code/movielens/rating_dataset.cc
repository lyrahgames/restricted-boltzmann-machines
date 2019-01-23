#include "rating_dataset.h"

#include <algorithm>
#include <cmath>
#include <fstream>
#include <limits>
#include <stdexcept>

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
  const auto match = [&file](char c) { return (c == file.get()); };

  // ignore header
  ignore_line();
  int user_id;
  while (file >> user_id) {  // get user_id in place
    if (user_index_.try_emplace(user_id, user_id_.size()).second) {
      user_id_.push_back(user_id);
      rating_count_.push_back(0);
    }

    ++rating_count_[user_index_[user_id]];

    // ignore genres
    ignore_line();
  }

  if (user_index_.size() != user_id_.size())
    throw runtime_error("File may contain doubled entries!");

  // rating count statistics
  max_rating_count_ = 0;
  mean_rating_count_ = 0;
  for (auto x : rating_count_) {
    max_rating_count_ = max(max_rating_count_, x);
    mean_rating_count_ += x;
  }

  mean_rating_count_ /= rating_count_.size();
  var_rating_count_ = 0;
  for (auto x : rating_count_) {
    const float tmp = x - mean_rating_count_;
    var_rating_count_ += tmp * tmp;
  }
  var_rating_count_ /= (rating_count_.size() - 1);

  // rating_histogram_.resize(1 +
  //                           max_rating_count_ / rating_histogram_bin_size_);
  // for (auto x : rating_count_) {
  //   ++rating_histogram_[x / rating_histogram_bin_size_];
  // }
  rating_histogram_.resize(
      1 + static_cast<int>(
              floor(log(max_rating_count_) * rating_histogram_factor_)));
  for (auto x : rating_count_) {
    ++rating_histogram_[static_cast<int>(
        floor(log(x) * rating_histogram_factor_))];
  }
}

}  // namespace movielens