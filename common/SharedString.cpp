#include "SharedString.h"

using namespace sgc;

SharedString::SharedString(SharedStringID id, const std::string& str)
    : _id(id),
    _str(str)
{
}

SharedString::~SharedString()
{
}