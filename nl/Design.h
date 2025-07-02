#pragma once

#include "ObjectID.h"
#include "StringRef.h"

namespace sgc {

class Library;

class Design {
public:
    friend Library;

    Library* getLibrary() const { return _lib; }

    DesignID getID() const { return _id; }

    StringRef getName() const { return _name; }

    static Design* create(Library* lib, StringRef name);

private:
    DesignID _id;
    Library* _lib {nullptr};
    StringRef _name;

    Design(DesignID id, Library* lib, StringRef name);
    ~Design();
};

}