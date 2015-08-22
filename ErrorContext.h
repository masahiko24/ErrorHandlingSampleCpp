/// @file   ErrorContext.h
/// @author Masahiko TSUJITA
/// @note   Copyright(c) 2015 Masahiko TSUJITA. All rights reserved.

#ifndef ERRORHANDLINGSAMPLECPP_ERRORCONTEXT_H
#define ERRORHANDLINGSAMPLECPP_ERRORCONTEXT_H

#include "Error.h"

namespace mst {

/**
@class  ErrorContext
@brief  An `ErrorContext` object represents a context of error handling.
        You can get the latest or set an error over function calls, by the shared `ErrorContext` object.
*/
class ErrorContext {
private:

    /**
    Default Constructor.
    */
    ErrorContext();

    /**
    Destructor.
    */
    virtual ~ErrorContext();

public:

    /**
    Returns current error context.
    @return Current error context.
    */
    static ErrorContext &getCurrentContext();

private:

    /// The error assigned to the error context.
    Error error;

public:

    /**
    Returns the latest error.
    @return The latest error.
    */
    const Error & getError() const;

    /**
    Assigns an error to the error context.
    @param[in]  An error.
    */
    void setError(const Error &error);

    /**
    Moves an error to the error context.
    @param[in]  An error.
    */
    void setError(Error &&error);

};

}

#endif //ERRORHANDLINGSAMPLECPP_ERRORCONTEXT_H
