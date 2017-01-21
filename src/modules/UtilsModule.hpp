#ifndef UTILSMODULE_HPP_
#define UTILSMODULE_HPP_

#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

namespace Module
{
  void split(const std::string &s, char delim,
             std::vector<std::string> &elems);
  std::vector<std::string> split(const std::string &s, char delim);
  static inline std::string &ltrim(std::string &s);
}
#endif
