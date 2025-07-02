#include "SGCDB.h"

#include "Library.h"

using namespace sgc;

SGCDB::SGCDB() {
}

SGCDB::~SGCDB() {
    for (const auto& [id, lib] : _libraries) {
        delete lib;
    }
}

Library* SGCDB::getLibrary(StringRef libName) const {
    const auto it = _libNameMap.find(libName);
    if (it != _libNameMap.end()) {
        return it->second;
    }
    return nullptr;
}

Library* SGCDB::createLibrary(StringRef name) {
    if (getLibrary(name)) {
        return nullptr;
    }

    const auto libID = _nextLibraryID++;
    auto lib = new Library(this, libID, name);
    _libraries.emplace(libID, lib);
    _libNameMap.emplace(name, lib);
    return lib;
}