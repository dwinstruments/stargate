#pragma once

#include "ObjectID.h"
#include "StringRef.h"

namespace sgc {

class Design;

class Instance {
public:
    friend Design;

    Design* getParent() const { return _parent; }

    Design* getModel() const { return _model; }

    InstanceID getID() const { return _id; }

    StringRef getName() const { return _name; }

    static Instance* create(Design* parent,
                            Design* model,
                            StringRef name);
private:
    InstanceID _id;
    Design* _parent {nullptr};
    Design* _model {nullptr};
    StringRef _name;

    Instance(InstanceID id,
             Design* parent,
             Design* model,
             StringRef name);
    ~Instance();
};

}
