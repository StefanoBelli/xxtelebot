#ifndef TGBOT_UTILS_ENCODER_H
#define TGBOT_UTILS_ENCODER_H

#include <sstream>
#include <string>

namespace tgbot {
namespace utils {
/*!
 * @brief Encode URL paramter using a stringstream
 * @param stream
 * @param target
 */
void encode(std::stringstream &stream, const std::string &target);

/*!
 * @brief Encode URL paramter and return a new std::string object
 * @param target
 * @return encoded std::string
 */
std::string encode(const std::string &target);

} // namespace utils

} // namespace tgbot

#endif
