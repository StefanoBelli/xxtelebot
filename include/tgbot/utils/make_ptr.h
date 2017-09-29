#ifndef TGBOT_UTILS_MAKE_PTR_H
#define TGBOT_UTILS_MAKE_PTR_H

#include <utility>
#include "../types.h"

namespace tgbot {
	namespace utils {

		template<typename PtrType, typename ... TypeArgs>
			inline types::Ptr<PtrType> makePtr(TypeArgs &&... args_fwd) {
				return types::Ptr<PtrType>(new PtrType(std::forward<TypeArgs>(args_fwd)...));
			}

	}
}

#endif //TGBOT_UTILS_MAKE_PTR_H
