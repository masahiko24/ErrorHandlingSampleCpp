/// @file   main.cpp
/// @author Masahiko TSUJITA
/// @note   Copyright(c) 2015 Masahiko TSUJITA. All rights reserved.

#include <iostream>
#include "FailableActor.h"
#include "Error.h"
#include "ErrorContext.h"

using namespace std;

int main() {
    mst::FailableActor actor;
    for (int i = 0; i < 100; ++i) {
        if (!actor.performFailableAction()) {
            const mst::Error &error = mst::ErrorContext::getCurrentContext().getError();
            std::cout << "[" << i << "] Domain: " << error.getDomain() << ", Error Code: " << error.getCode() << ", Description: " << error.getDescription() << std::endl;
        }
    }
    return 0;
}
