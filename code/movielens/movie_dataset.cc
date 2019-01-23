#include "movie_dataset.h"

#include <fstream>
#include <limits>
#include <stdexcept>

namespace movielens {

movie_dataset::movie_dataset(const char* file_path) {
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

  if ((index_.size() != movie_id_.size()) ||
      (index_.size() != movie_title_.size()))
    throw runtime_error("File may contain doubled entries!");
}

}  // namespace movielens