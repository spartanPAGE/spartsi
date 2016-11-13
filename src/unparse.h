#pragma once
#include <string>
#include "elementary_types.h"

namespace spartsi {
    namespace unparsed {
        using declaration = std::string;
        using definition = std::stirng;
    }

    std::string unparse(spartsi::tree const &tree);
}