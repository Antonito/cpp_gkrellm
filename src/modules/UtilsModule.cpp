#include "UtilsModule.hpp"

namespace Module
{
  void split(const std::string &s, char delim, std::vector<std::string> &elems)
  {
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim))
      {
	elems.push_back(item);
      }
  }

  std::vector<std::string> split(const std::string &s, char delim)
  {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
  }
  static inline std::string &ltrim(std::string &s)
  {
    s.erase(s.begin(),
            std::find_if(s.begin(), s.end(),
                         std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
  }
}
