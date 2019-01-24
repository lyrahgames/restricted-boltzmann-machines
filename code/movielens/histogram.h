#ifndef RBM_MOVIELENS_HISTOGRAM_H_
#define RBM_MOVIELENS_HISTOGRAM_H_

#include <cmath>
#include <iostream>
#include <limits>
#include <vector>

namespace movielens {

class histogram {
 public:
  histogram(const std::vector<int>& data) {
    using namespace std;

    // mean count
    for (auto x : data) {
      max_ = std::max(max_, x);
      min_ = std::min(min_, x);
      mean_ += x;
    }
    mean_ /= data.size();

    // variance count
    for (auto x : data) {
      const float tmp = x - mean_;
      variance_ += tmp * tmp;
    }
    variance_ /= (data.size() - 1);
    std_dev_ = sqrt(variance_);

    // local helper functions
    const auto count_to_bin = [](int count) {
      constexpr float factor = 2 / log(3);
      return static_cast<int>(floor(factor * log(count)));
    };
    const auto bin_to_count = [](int bin) {
      constexpr float factor = log(3) / 2;
      return static_cast<int>(ceil(exp(factor * bin)));
    };

    // compute histogram data
    counts_.resize(1 + count_to_bin(max_));
    for (auto x : data) ++counts_[count_to_bin(x)];

    bins_.resize(counts_.size() + 1);
    for (auto i = 0; i < bins_.size(); ++i) {
      bins_[i] = bin_to_count(i);
    }
  }

  auto size() const noexcept { return counts_.size(); }
  auto max() const noexcept { return max_; }
  auto min() const noexcept { return min_; }
  auto mean() const noexcept { return mean_; }
  auto variance() const noexcept { return variance_; }
  auto standard_deviation() const noexcept { return std_dev_; }

  const auto& counts() const noexcept { return counts_; }
  const auto& bins() const noexcept { return bins_; }
  const auto& operator[](int index) const noexcept { return counts_[index]; }
  const auto& bin(int index) const noexcept { return bins_[index]; }

 private:
  std::vector<int> counts_;
  std::vector<int> bins_;
  int max_ = 0;
  int min_ = std::numeric_limits<int>::max();
  float mean_ = 0;
  float variance_ = 0;
  float std_dev_ = 0;
};

}  // namespace movielens

std::ostream& operator<<(std::ostream& os, const movielens::histogram& h) {
  os << "index\tbin start\tcount\n";
  for (auto i = 0; i < h.size(); ++i)
    os << i << "\t" << h.bin(i) << "\t\t" << h[i] << "\n";
  os << "\n"
        "[min,max] = ["
     << h.min() << "," << h.max()
     << "]\n"
        "mean = "
     << h.mean()
     << "\n"
        "variance = "
     << h.variance()
     << "\n"
        "standard_deviation = "
     << h.standard_deviation() << "\n";
  return os;
}

#endif  // RBM_MOVIELENS_HISTOGRAM_H_