#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

class movielens_dataset {
 public:
  movielens_dataset(const char* file_path) {
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
    int id;
    while (file >> id) {  // get id in place
      index_[id] = movie_id_.size();
      movie_id_.push_back(id);

      // match separator
      if (!match(',')) throw runtime_error("File is not correctly formatted!");

      // get title
      string tmp;
      getline(file, tmp, ',');
      movie_title_.push_back(tmp);

      // ignore genres
      ignore_line();
    }
  }

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

int main(int argc, char** argv) {
  using namespace std;

  if (2 != argc) {
    cout << "usage:\n" << argv[0] << " <movie dataset>\n";
    return -1;
  }

  movielens_dataset mv_data{argv[1]};

  cout << "#\tid\ttitle\n";
  for (auto i = 0; i < mv_data.size(); ++i) {
    cout << i << "\t" << mv_data.movie_id(i) << "\t" << mv_data.movie_title(i)
         << endl;
  }
  cout << "movie count = " << mv_data.size() << endl;
}