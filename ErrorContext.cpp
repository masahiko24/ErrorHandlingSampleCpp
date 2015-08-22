/// @file   ErrorContext.cpp
/// @author Masahiko TSUJITA
/// @note   Copyright(c) 2015 Masahiko TSUJITA. All rights reserved.

#include <algorithm>
#include "ErrorContext.h"

namespace mst {

    ErrorContext::ErrorContext() : error() {
        //  Nothing to do.
    }

    ErrorContext::~ErrorContext() {
        //  Nothing to do.
    }

    ErrorContext &ErrorContext::getCurrentContext() {
        static ErrorContext sharedContext;
        return sharedContext;
    }

    const Error &ErrorContext::getError() const {
        return error;
    }

    void ErrorContext::setError(const Error &error) {
        this->error = error;
    }

    void ErrorContext::setError(Error &&error) {
        this->error = std::move(error);
    }

}
