#include "Design.h"

#include "Library.h"

using namespace sgc;

Design::Design(DesignID id, Library* lib, StringRef name)
    : _id(id),
    _lib(lib),
    _name(name)
{
}

Design::~Design() {
}

Design* Design::create(Library* lib, StringRef name) {
    return lib->createDesign(name);
}