#ifndef TGBOT_STR_MATCH_H
#define TGBOT_STR_MATCH_H

#include <cstring>
#include <string>

namespace tgbot {
namespace utils {

/*!
 * @brief whenStarts (see RegisterCallback::callback() )
 * @param target
 * @param what
 * @return true if 'target' starts with 'what'
 */
inline bool whenStarts(const std::string &target, const char *what) {
  return target.compare(0, strlen(what), what) == 0;
}

/*!
 * @brief whenContains (see RegisterCallback::callback() )
 * @param target
 * @param what
 * @return true if 'target' contains 'what'
 */
inline bool whenContains(const std::string &target, const char *what) {
  return target.find(what) != std::string::npos;
}

} // namespace utils
} // namespace tgbot

#endif // TGBOT_STR_MATCH_H
