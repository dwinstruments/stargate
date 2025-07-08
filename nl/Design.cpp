#include "Design.h"

#include "Library.h"
#include "Instance.h"

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

Instance* Design::getChildInstance(StringRef name) const {
    const auto it = _childInstancesNameMap.find(name);
    if (it == _childInstancesNameMap.end()) {
        return nullptr;
    }

    return it->second;
}

Instance* Design::createChildInstance(Design* model, StringRef name) {
    if (!getChildInstance(name)) {
        return nullptr;
    }

    const auto instanceID = _nextInstanceID++;
    Instance* inst = new Instance(instanceID, this, model, name);
    _childInstances[instanceID] = inst;
    _childInstancesNameMap[name] = inst;

    return inst;
}
