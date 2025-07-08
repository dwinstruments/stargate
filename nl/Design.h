#pragma once

#include <map>
#include <unordered_map>

#include "ObjectID.h"
#include "StringRef.h"

namespace sgc {

class Library;
class Instance;

class Design {
public:
    friend Library;
    friend Instance;

    Library* getLibrary() const { return _lib; }

    DesignID getID() const { return _id; }

    StringRef getName() const { return _name; }

    Instance* getChildInstance(StringRef name) const;

    static Design* create(Library* lib, StringRef name);

    bool isPrimitive() const { return _isPrimitive; }
    void setPrimitive(bool isPrimitive) { _isPrimitive = isPrimitive; }

private:
    DesignID _id;
    Library* _lib {nullptr};
    StringRef _name;
    bool _isPrimitive {false};

    InstanceID _nextInstanceID {0};
    std::map<InstanceID, Instance*> _childInstances;
    std::unordered_map<StringRef, Instance*> _childInstancesNameMap;

    Design(DesignID id, Library* lib, StringRef name);
    ~Design();
    Instance* createChildInstance(Design* model, StringRef name);
};

}
