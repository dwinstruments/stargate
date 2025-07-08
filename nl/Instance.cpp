#include "Instance.h"

#include "Design.h"

using namespace sgc;

Instance::Instance(InstanceID id,
                   Design* parent,
                   Design* model,
                   StringRef name)
    : _id(id),
    _parent(parent),
    _model(model),
    _name(name)
{
}

Instance::~Instance() {
}

Instance* Instance::create(Design* parent,
                           Design* model,
                           StringRef name) {
    return parent->createChildInstance(model, name);
}
