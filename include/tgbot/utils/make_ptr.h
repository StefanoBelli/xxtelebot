#ifndef TGBOT_UTILS_MAKE_PTR_H
#define TGBOT_UTILS_MAKE_PTR_H

#include "../types.h"
#include <utility>

namespace tgbot {
namespace utils {

/*!
 * @brief Make a new tgbot::types::Ptr
 * @tparam PtrType
 * @tparam TypeArgs
 * @param args_fwd : argument to be forwarded to constructor
 * @return a new tgbot::types::Ptr holding your pointer
 */
template <typename PtrType, typename... TypeArgs>
inline types::Ptr<PtrType> makePtr(TypeArgs &&... args_fwd) {
  return types::Ptr<PtrType>(new PtrType(std::forward<TypeArgs>(args_fwd)...));
}

} // namespace utils

} // namespace tgbot

#endif // TGBOT_UTILS_MAKE_PTR_H
