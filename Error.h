/// @file   Error.h
/// @author Masahiko TSUJITA
/// @note   Copyright(c) 2015 Masahiko TSUJITA. All rights reserved.

#ifndef ERRORHANDLINGSAMPLECPP_ERROR_H
#define ERRORHANDLINGSAMPLECPP_ERROR_H

namespace mst {

/**
@class      Error
@brief      An `Error` object represents an error occurred while application is running.
            To get the latest or set an error on your code, use static method `getSharedContext` of `ErrorContext`.
*/
class Error final {
public:

    /// String representing the error is related to this class itself.
    static const char *DomainName;

    /**
    @enum       Code
    @brief      Constants defining type of the error whose domain is this class.
    */
    enum Code : int {
        Empty,      ///<    The error describes empty error.
        Internal    ///<    The error describes internal error in constructing error, such as failure on memory allocation for copying description.
    };

    /// The shared error instance representing empty error.
    static const Error empty;

    /// Default Constructor. Constructs an error.
    Error();

    /**
    Copy Constructor. Constructs an error as a copy of the given error.
    @param[in]  error   The error to be copied.
    */
    Error(const Error &error);

    /**
    Move Constructor. Constructs an error moving contents from the given error.
    @param[in]  error   The error to be moved.
    */
    Error(Error &&error);

    /**
    Constructs an error with given domain, code, and description.
    @param[in]  domain                  A string representing the domain of the error.
    @param[in]  code                    An error code.
    @param[in]  description             A string describing detail of the error.
    @param[in]  descriptionNeedsCopy    A bool value describing whether description is needs to be copied or not.
    */
    Error(const char *domain, int code, const char *description, bool descriptionNeedsCopy = false);

    /**
    @enum       FormatStyle
    @brief      Constants defining style of formatted string.
    */
    enum FormatStyle : int {
        CString
    };

    /**
    Constructs an error with given domain, code, and formatted description.
    @param[in]  domain                  A string representing the domain of the error.
    @param[in]  code                    An error code.
    @param[in]  style                   A value indincating style of format of description.
    @param[in]  descriptionFormat       A format string describing detail of the error.
    @note       You must `CString` value to the style parameter currently.
    */
    Error(const char *domain, int code, FormatStyle style, const char *descriptionFormat, ...);

    /// Destructor.
    ~Error();

    /**
    Assignment Operator. Assigns an error as a copy of the given error.
    @param[in]  error   The error to be copied.
    @return     Reference of this object.
    */
    Error &operator=(const Error &error);

    /**
    Move Assignment Operator. Assigns an error moving contents from the given error.
    @param[in]  error   The error to be moved.
    @return     Reference of this object.
    */
    Error &operator=(Error &&error);

    /**
    Returns the domain of the error.
    @return The domain of the error.
    */
    const char * getDomain() const;

    /**
    Assigns a domain to the error.
    @param[in]  domain  A domain string.
    */
    void setDomain(const char *domain);

    /**
    Returns the error code of the error.
    @return The error code of the error.
    */
    int getCode() const;

    /**
    Assigns an error code to the error.
    @param[in]  code An error code.
    */
    void setCode(int code);

    /**
    Returns the description of the error.
    @return The description of the error.
    */
    const char * getDescription() const;

    /**
    Assigns a description string to the error.
    @param[in]  description A description string.
    @param[in]  needsCopy   A bool value indicating whether the given description string needs to be copied or not.
    @return     `true` if assignment completed successfully, otherwise `false`.
    @note       This method always succeeds if `false` is specified to the `needsCopy` parameter.
    */
    bool setDescription(const char *description, bool needsCopy = false);

private:

    /// The shared error instance representing failure of memory allocation.
    static const Error failureOfMemoryAllocation;

    /// A string representing domain of the error.
    const char *domain;

    /// An int value representing error code.
    int code;

    /// A string describing detail of the error.
    const char *description;

    /// A allocated memory to contain description string.
    char *descriptionMemory;

};

}

#endif //ERRORHANDLINGSAMPLECPP_ERROR_H
