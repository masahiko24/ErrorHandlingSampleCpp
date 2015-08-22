/// @file   Error.cpp
/// @author Masahiko TSUJITA
/// @note   Copyright(c) 2015 Masahiko TSUJITA. All rights reserved.

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <new>
#include "ErrorContext.h"
#include "Error.h"

namespace mst {

const char *Error::DomainName = "jp.masahikot.mst.ErrorDomain";
const Error Error::empty;
const Error Error::failureOfMemoryAllocation(Error::DomainName, Error::Code::Internal, "Failed to allocate memory.", false);

Error::Error() : domain(Error::DomainName), code(Error::Code::Empty), description(""), descriptionMemory(nullptr) {
    //  Nothing to do.
}

Error::Error(const Error &error) : domain(error.domain), code(error.code), description(nullptr), descriptionMemory(nullptr) {
    this->setDescription(error.description, error.descriptionMemory != nullptr);
}

Error::Error(Error &&error) : domain(error.domain), code(error.code), description(error.description), descriptionMemory(error.descriptionMemory) {
    error.descriptionMemory = nullptr;
    error = empty;
}

Error::Error(const char *domain, int code, const char *description, bool descriptionNeedsCopy) : domain(domain), code(code), description(nullptr), descriptionMemory(nullptr) {
    this->setDescription(description, descriptionNeedsCopy);
}

Error::Error(const char *domain, int code, FormatStyle, const char *descriptionFormat, ...) : domain(domain), code(code), description(nullptr), descriptionMemory(nullptr) {
    va_list ap;
    va_start(ap, descriptionFormat);
    char *buffer;
    vasprintf(&buffer, descriptionFormat, ap);
    va_end(ap);
    this->setDescription(buffer, true);
    free(buffer);
}

Error::~Error() {
    if (this->descriptionMemory != nullptr) {
        delete[] this->descriptionMemory;
    }
}

Error &Error::operator=(const Error &error) {
    if (this == &error) {
        return *this;
    }
    this->domain = error.domain;
    this->code = error.code;
    this->setDescription(error.description, error.descriptionMemory != nullptr);
    return *this;
}

Error &Error::operator=(Error &&error) {
    if (this == &error) {
        return *this;
    }
    if (this->descriptionMemory != nullptr) {
        delete[] this->descriptionMemory;
        this->descriptionMemory = nullptr;
    }
    this->domain = error.domain;
    this->code = error.code;
    this->description = error.description;
    this->descriptionMemory = error.descriptionMemory;
    error.descriptionMemory = nullptr;
    error = empty;
    return *this;
}

const char *Error::getDomain() const {
    return domain;
}

void Error::setDomain(const char *domain) {
    this->domain = domain;
}

int Error::getCode() const {
    return code;
}

void Error::setCode(int code) {
    this->code = code;
}

const char *Error::getDescription() const {
    return description;
}

bool Error::setDescription(const char *description, bool needsCopy) {
    if (this->description == description) {
        return true;
    }
    if (this->descriptionMemory != nullptr) {
        delete[] this->descriptionMemory;
        this->descriptionMemory = nullptr;
    }
    if (needsCopy) {
        size_t size = strlen(description) + 1;
        this->descriptionMemory = new(std::nothrow) char[size];
        if (this->descriptionMemory == nullptr) {
            *this = empty;
            auto &context = ErrorContext::getCurrentContext();
            context.setError(failureOfMemoryAllocation);
            return false;
        }
        bool succeededToCopy = nullptr != strcpy(this->descriptionMemory, description);
        if (!succeededToCopy) {
            *this = empty;
            auto &context = ErrorContext::getCurrentContext();
            context.setError(failureOfMemoryAllocation);
            return false;
        }
    } else {
        this->description = description;
    }
    return true;
}

}
