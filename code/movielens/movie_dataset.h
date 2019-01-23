#ifndef RBM_MOVIELENS_MOVIE_DATASET_H_
#define RBM_MOVIELENS_MOVIE_DATASET_H_

#include <string>
#include <unordered_map>
#include <vector>

namespace movielens {

class movie_dataset {
 public:
  movie_dataset(const char* file_path);

  auto size() const noexcept { return movie_id_.size(); }

  const auto& indices() const noexcept { return index_; }
  const auto& movie_ids() const noexcept { return movie_id_; }
  const auto& movie_titles() const noexcept { return movie_title_; }

  decltype(auto) index(int id) const noexcept { return index_.at(id); }
  decltype(auto) movie_id(int index) const noexcept { return movie_id_[index]; }
  decltype(auto) movie_title(int index) const noexcept {
    return movie_title_[index];
  }

 private:
  std::unordered_map<int, int> index_;
  std::vector<int> movie_id_;
  std::vector<std::string> movie_title_;
};

}  // namespace movielens

#endif  // RBM_MOVIELENS_MOVIE_DATASET_H_