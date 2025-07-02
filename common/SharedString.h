#pragma once

#include <string>

namespace sgc {

class SharedString {
public:
    using SharedStringID = uint64_t;

    SharedString(SharedStringID id, const std::string& str);
    ~SharedString();

    SharedStringID getID() const { return _id; }

    const std::string& getString() const { return _str; }

    bool operator==(const SharedString& other) const { return _id == other._id; }
    bool operator!=(const SharedString& other) const { return _id != other._id; }
    bool operator<(const SharedString& other) const { return _id < other._id; }

private:
    SharedStringID _id {0};
    const std::string _str;
};

}