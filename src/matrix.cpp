#include <tgbot/utils/matrix.h>

const char* tgbot::utils::MatrixException::what() const noexcept {
    return "exceeding matrix limits";
}
