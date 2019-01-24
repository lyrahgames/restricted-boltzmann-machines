#include "rbm.h"

namespace movielens {

rbm::rbm(const rating_dataset& ratings, int hidden_units)
    : ratings_{ratings},
      weight_(ratings.movie_count(), hidden_units),
      visible_bias_(ratings.movie_count()),
      hidden_bias_(hidden_units) {
  std::normal_distribution<float> distribution{0, 0.01};

  // initialize weights
  for (int i = 0; i < weight_.rows(); ++i) {
    for (int j = 0; j < weight_.cols(); ++j) {
      weight_(i, j) = distribution(rng_);
    }
  }

  // initialize visible bias
  for (int i = 0; i < visible_bias_.size(); ++i) {
    visible_bias_(i) = distribution(rng_);
  }

  // initialize hidden bias
  for (int i = 0; i < hidden_bias_.size(); ++i) {
    hidden_bias_(i) = distribution(rng_);
  }
}

float rbm::inference(int user_id, int movie_id) const {
  std::uniform_real_distribution<float> distribution(0, 1);
  return (distribution(rng_) < 0.5) ? 0 : 1;
}

// float rbm::test() const {
//   int correct = 0;
//   for (int i = 0; i < ratings_.user_count(); ++i) {
//   }
// }

}  // namespace movielens