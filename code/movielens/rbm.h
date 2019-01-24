#ifndef RBM_MOVIELENS_RBM_H_
#define RBM_MOVIELENS_RBM_H_

#include <Eigen/Sparse>

#include "movie_dataset.h"
#include "rating_dataset.h"

namespace movielens {

class rbm {
 public:
  rbm(const movie_dataset& movie_data, const rating_dataset& ratings);

 private:
  Eigen::SparseMatrix<float, Eigen::RowMajor> ratings_;
};

}  // namespace movielens

#endif  // RBM_MOVIELENS_RBM_H_