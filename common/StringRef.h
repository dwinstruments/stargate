#pragma once

#include <functional>

#include "SharedString.h"

namespace sgc {

class StringRef {
public:
    StringRef()
        : _sharedString(nullptr)
    {}

    StringRef(const SharedString* sharedString)
        : _sharedString(sharedString)
    {}

    const SharedString* getSharedString() const { return _sharedString; }

    bool operator==(const StringRef& other) const { return _sharedString == other._sharedString; }
    bool operator!=(const StringRef& other) const { return _sharedString != other._sharedString; }
    bool operator<(const StringRef& other) const { return *_sharedString < *other._sharedString; }

private:
    const SharedString* _sharedString {nullptr};
};

}

namespace std {

template<>
struct hash<sgc::StringRef> {
    size_t operator()(const sgc::StringRef& stringRef) const {
        return hash<const sgc::SharedString*>{}(stringRef.getSharedString());
    }
};

}