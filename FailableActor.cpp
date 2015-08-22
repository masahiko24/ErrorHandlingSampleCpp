/// @file   FailableActor.cpp
/// @author Masahiko TSUJITA
/// @note   Copyright(c) 2015 Masahiko TSUJITA. All rights reserved.

#include <random>
#include <iostream>
#include "FailableActor.h"
#include "ErrorContext.h"

namespace mst {

const char *FailableActor::ErrorDomainName = "jp.masahikot.mst.FailableActorErrorDomain";

FailableActor::FailableActor() {

}

FailableActor::~FailableActor() {

}

FailableActor::FailableActor(const FailableActor &actor) {

}

FailableActor::FailableActor(FailableActor &&actor) {

}

bool FailableActor::performFailableAction() {
    static std::mt19937 engine;
    static std::uniform_int_distribution<int> distribution(1, 6) ;
    int dice = distribution(engine);
    if (dice >= 4) {
        auto &context = ErrorContext::getCurrentContext();
        context.setError(Error(ErrorDomainName, ErrorCode::Internal, "Some error occurred..."));
        return false;
    }
    return true;
}

}
