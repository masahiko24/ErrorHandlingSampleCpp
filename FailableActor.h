/// @file   FailableActor.h
/// @author Masahiko TSUJITA
/// @note   Copyright(c) 2015 Masahiko TSUJITA. All rights reserved.

#ifndef ERRORHANDLINGSAMPLECPP_FAILABLEACTOR_H
#define ERRORHANDLINGSAMPLECPP_FAILABLEACTOR_H

namespace mst {

/**
@class      FailableActor
@brief      An object which performs failable action.
*/
class FailableActor {
public:

    static const char *ErrorDomainName;

    enum ErrorCode {
        Internal
    };

    FailableActor();

    FailableActor(const FailableActor &actor);

    FailableActor(FailableActor &&actor);

    virtual ~FailableActor();

    bool performFailableAction();

};

}

#endif //ERRORHANDLINGSAMPLECPP_FAILABLEACTOR_H
