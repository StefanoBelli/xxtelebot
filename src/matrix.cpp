#include <tgbot/utils/matrix.h>

using tgbot::utils::MatrixException;

const char* MatrixException::what() const noexcept {
    return "exceeding matrix limits";
}
