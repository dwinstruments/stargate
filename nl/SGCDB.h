#pragma once

#include <map>
#include <unordered_map>

#include "ObjectID.h"
#include "StringRef.h"

namespace sgc {

class SGCDB;
class Library;

class SGCDB {
public:
    friend Library;

    SGCDB();
    ~SGCDB();

    Library* getLibrary(StringRef libName) const;

private:
    std::map<LibraryID, Library*> _libraries;
    std::unordered_map<StringRef, Library*> _libNameMap;

    LibraryID _nextLibraryID {0};

    Library* createLibrary(StringRef name);
};

}
