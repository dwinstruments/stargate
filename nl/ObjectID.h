#pragma once

#include <stdint.h>
#include <tuple>

namespace sgc {

using DBID = uint8_t;
using LibraryID = uint8_t;
using DesignID = uint32_t;
using InstanceID = uint32_t;
using TermID = uint32_t;
using NetID = uint32_t;

class ObjectID {
public:
    struct NLID {
        DBID _dbID {0};
        LibraryID _libID {0};
        DesignID _designID {0};
        InstanceID _instID {0};
        TermID _termID {0};
        NetID _netID {0};

        bool operator<(const NLID& other) const noexcept {
            return std::tie(_dbID, _libID, _designID, _instID, _termID, _netID)
                < std::tie(other._dbID, other._libID, other._designID, other._instID, other._termID, other._netID);
        }

        bool operator==(const NLID& other) const noexcept {
            return std::tie(_dbID, _libID, _designID, _instID, _termID, _netID)
                == std::tie(other._dbID, other._libID, other._designID, other._instID, other._termID, other._netID);
        }
    };

    struct NLIDCompare {
        bool operator()(const NLID& lhs, const NLID& rhs) const noexcept {
            return lhs < rhs;
        }
    };
};

}
