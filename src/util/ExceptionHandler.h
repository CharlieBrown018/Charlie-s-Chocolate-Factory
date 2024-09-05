// ExceptionHandler.h
#pragma once
#include <stdexcept>
#include <string>

// Custom exception for input-related errors
class InputException : public std::runtime_error {
public:
    InputException(const std::string& message) : std::runtime_error(message) {}
};

// Custom exception for file-related errors
class FileException : public std::runtime_error {
public:
    FileException(const std::string& message) : std::runtime_error(message) {}
};