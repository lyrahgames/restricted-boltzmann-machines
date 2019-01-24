#include "rbm.h"

#include <iostream>

namespace movielens {

rbm::rbm(const movie_dataset& movie_data, const rating_dataset& ratings)
    : ratings_(ratings.user_count(), movie_data.size()) {}

}  // namespace movielens