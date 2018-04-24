#ifndef TGBOT_UTILS_GETFILENAME_H
#define TGBOT_UTILS_GETFILENAME_H

#include <string>

namespace tgbot {
namespace utils {

inline std::string getFileName(const std::string& s) {
  std::size_t size = s.size();
  std::size_t i = s.rfind('/', size);

  if (i != std::string::npos) return s.substr(i + 1, size - i);

  return "";
}

}  // namespace utils
}  // namespace tgbot

#endif
