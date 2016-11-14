#pragma once
#include <string>
#include <vector>
#include "elementary_types.h"

namespace spartsi {
    using lines = std::vector<std::string>;

    namespace unparsed {
        using declaration = lines;
        using definition = lines;

        using pair = std::pair<declaration, definition>;
    }

    lines unparse_attribute_value(std::string const &val);

    lines unparse_comment(std::string const &val);

    lines unparse(std::string const &name, spartsi::attribute const &attribute);

    lines unparse(spartsi::tree const &tree);
}