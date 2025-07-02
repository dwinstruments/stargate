#include "StringManager.h"

#include <unordered_map>
#include <memory>

#include "SharedString.h"

using namespace sgc;

class sgc::StringManagerImpl {
public:
    StringRef getString(const std::string& str) {
        const auto it = _strings.find(str);
        if (it != _strings.end()) {
            return StringRef(it->second.get());
        }

        const auto strID = _nextStringID++;
        auto sharedString = std::make_unique<SharedString>(strID, str);
        const auto stringRef = StringRef(sharedString.get());
        _strings.emplace(str, std::move(sharedString));
        return stringRef;
    }

private:
    std::unordered_map<std::string, std::unique_ptr<SharedString>> _strings;
    SharedString::SharedStringID _nextStringID {0};
};

StringManager::StringManager()
    : _impl(new StringManagerImpl())
{
}

StringManager::~StringManager() {
    if (_impl) {
        delete _impl;
    }
}

StringRef StringManager::getString(const std::string& str) {
    return _impl->getString(str);
}