#pragma once

#include <string>

#include "StringRef.h"

namespace sgc {

class StringManagerImpl;

class StringManager {
public:
    StringManager();
    ~StringManager();

    StringRef getString(const std::string& str);

private:
    StringManagerImpl* _impl {nullptr};
};

}