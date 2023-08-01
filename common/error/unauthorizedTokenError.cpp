#include "unauthorizedTokenError.h"

UnauthorizedTokenError::UnauthorizedTokenError() : errorMessage("Unauthorized: Invalid token") {}

const char* UnauthorizedTokenError::what() const noexcept {
    return errorMessage.c_str();
}
