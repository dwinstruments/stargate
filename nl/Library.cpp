#include "Library.h"

#include "Design.h"
#include "SGCDB.h"

using namespace sgc;

Library::Library(SGCDB* db, LibraryID id, StringRef name)
    : _db(db),
    _id(id),
    _name(name)
{
}

Library::~Library() {
    for (const auto& [id, design] : _designs) {
        delete design;
    }
}

Library* Library::create(SGCDB* db, StringRef name) {
    return db->createLibrary(name);
}

Design* Library::getDesign(StringRef name) const {
    const auto it = _designNameMap.find(name);
    if (it != _designNameMap.end()) {
        return it->second;
    }
    return nullptr;
}

Design* Library::createDesign(StringRef name) {
    if (getDesign(name)) {
        return nullptr;
    }

    const auto designID = _nextDesignID++;

    auto design = new Design(designID, this, name);
    _designs.emplace(designID, design);
    _designNameMap.emplace(name, design);

    return design;
}