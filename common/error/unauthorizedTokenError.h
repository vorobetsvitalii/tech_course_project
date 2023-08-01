#ifndef UNAUTHORIZED_TOKEN_ERROR_H
#define UNAUTHORIZED_TOKEN_ERROR_H

#include <exception>
#include <string>

class UnauthorizedTokenError : public std::exception {
public:
    UnauthorizedTokenError();

    const char* what() const noexcept override;

private:
    std::string errorMessage;
};

#endif // UNAUTHORIZED_TOKEN_ERROR_H
