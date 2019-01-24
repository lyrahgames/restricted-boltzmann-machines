#ifndef RBM_MOVIELENS_RBM_H_
#define RBM_MOVIELENS_RBM_H_

#include <random>

#include <Eigen/Dense>

#include "rating_dataset.h"

namespace movielens {

class rbm {
  using Matrix =
      Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>;
  using Vector = Eigen::VectorXf;

 public:
  rbm(const rating_dataset& ratings, int hidden_units);

  float inference(int user_id, int movie_id) const;
  float test() const;

 private:
  const rating_dataset& ratings_;

  mutable std::mt19937 rng_{std::random_device{}()};

  Matrix weight_;
  Vector visible_bias_;
  Vector hidden_bias_;

  float training_test_separation_ = 0.5;
};

}  // namespace movielens

#endif  // RBM_MOVIELENS_RBM_H_