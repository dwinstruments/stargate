#pragma once

#include <map>
#include <unordered_map>

#include "ObjectID.h"
#include "StringRef.h"

namespace sgc {

class SGCDB;
class Design;

class Library {
public:
    friend SGCDB;
    friend Design;

    SGCDB* getDB() const { return _db; }

    LibraryID getID() const { return _id; }

    StringRef getName() const { return _name; }

    Design* getDesign(StringRef name) const;

    static Library* create(SGCDB* db, StringRef name);

private:
    SGCDB* _db {nullptr};
    LibraryID _id;
    StringRef _name;

    DesignID _nextDesignID {0};
    std::map<DesignID, Design*> _designs;
    std::unordered_map<StringRef, Design*> _designNameMap;

    Library(SGCDB* db, LibraryID id, StringRef name);
    ~Library();

    Design* createDesign(StringRef name);
};

}
