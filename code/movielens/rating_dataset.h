#ifndef RBM_MOVIELENS_RATING_DATASET_H_
#define RBM_MOVIELENS_RATING_DATASET_H_

#include <cmath>
#include <string>
#include <unordered_map>
#include <vector>

namespace movielens {

class rating_dataset {
 public:
  rating_dataset(const char* file_path);

  auto size() const noexcept { return user_id_.size(); }

  const auto& user_indices() const noexcept { return user_index_; }
  const auto& user_ids() const noexcept { return user_id_; }
  decltype(auto) user_index(int id) const noexcept {
    return user_index_.at(id);
  }
  decltype(auto) user_id(int index) const noexcept { return user_id_[index]; }
  decltype(auto) rating_count(int index) const noexcept {
    return rating_count_[index];
  }

  const auto& rating_histogram() const noexcept { return rating_histogram_; }

  auto max_rating_count() const noexcept { return max_rating_count_; }
  auto mean_rating_count() const noexcept { return mean_rating_count_; }
  auto var_rating_count() const noexcept { return var_rating_count_; }

  auto rating_histogram_factor() const noexcept {
    return rating_histogram_factor_;
  }

 private:
  std::unordered_map<int, int> user_index_;
  std::vector<int> user_id_;
  std::vector<int> rating_count_;
  int max_rating_count_;
  float mean_rating_count_;
  float var_rating_count_;
  std::vector<int> rating_histogram_;
  int rating_histogram_bin_size_ = 1000;
  float rating_histogram_factor_ = 2 / log(3);
};

}  // namespace movielens

#endif  // RBM_MOVIELENS_RATING_DATASET_H_