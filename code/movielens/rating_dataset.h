#ifndef RBM_MOVIELENS_RATING_DATASET_H_
#define RBM_MOVIELENS_RATING_DATASET_H_

#include <unordered_map>
#include <vector>

#include <Eigen/Sparse>

namespace movielens {

class rating_dataset {
  using Matrix = Eigen::SparseMatrix<float, Eigen::RowMajor>;

 public:
  rating_dataset(const char* file_path);

  auto size() const noexcept { return ratings_.nonZeros(); }

  auto user_count() const noexcept { return user_id_.size(); }
  auto movie_count() const noexcept { return movie_id_.size(); }

  const auto& user_indices() const noexcept { return user_index_; }
  const auto& user_ids() const noexcept { return user_id_; }
  const auto& movie_indices() const noexcept { return movie_index_; }
  const auto& movie_ids() const noexcept { return movie_id_; }

  decltype(auto) user_index(int id) const noexcept {
    return user_index_.at(id);
  }
  decltype(auto) movie_index(int id) const noexcept {
    return movie_index_.at(id);
  }
  decltype(auto) user_id(int index) const noexcept { return user_id_[index]; }
  decltype(auto) movie_id(int index) const noexcept { return movie_id_[index]; }

  const auto& user_rating_count() const noexcept { return user_rating_count_; }
  const auto& movie_rating_count() const noexcept {
    return movie_rating_count_;
  }

  const auto& ratings() const noexcept { return ratings_; }

 private:
  std::unordered_map<int, int> user_index_;
  std::vector<int> user_id_;

  std::unordered_map<int, int> movie_index_;
  std::vector<int> movie_id_;

  std::vector<int> user_rating_count_;
  std::vector<int> movie_rating_count_;

  Matrix ratings_;
};

}  // namespace movielens

#endif  // RBM_MOVIELENS_RATING_DATASET_H_