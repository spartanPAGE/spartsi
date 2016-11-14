#include "unparse.h"
#include "boost/algorithm/string.hpp"

//TODO: customizable whitespace length & type
namespace spartsi {

    template<typename F>
    lines split_to_lines_and_transform(std::string const &val, std::string const &splitters, F f) {
        lines result;
        boost::split(result, val, boost::is_any_of(splitters));
        for(auto &line: result) {
            f(line);
        }
        return result;
    }

    lines unparse_attribute_value(std::string const &val) {
        return split_to_lines_and_transform(val, "\n", [](std::string &line) {
            line = "\"" + line + "\"";
        });
    }

    lines unparse_comment(std::string const &val) {
        if(boost::algorithm::trim_copy(val) == "") {
            return {};
        }

        return split_to_lines_and_transform(val, "\n", [](std::string &line) {
            auto trimmed = boost::algorithm::trim_copy(line);
            line = trimmed.empty()? "::" : ":: " + trimmed;
        });
    }

    lines unparse(std::string const &name, spartsi::attribute const &attribute) {
        assert(!name.empty());
        lines result;

        auto generic_attr_declaration = "attr " + name + " ";
        auto comment_lines = unparse_comment(attribute.comment);
        auto value_lines = unparse_attribute_value(attribute.value);

        std::for_each(std::begin(value_lines) + 1, std::end(value_lines), [&generic_attr_declaration](std::string &line) {
            line = std::string(generic_attr_declaration.size(), ' ') + line;
        });

        result.reserve(comment_lines.size() + value_lines.size() + 1);
        result.insert(std::end(result), std::begin(comment_lines), std::end(comment_lines));
        result.push_back(generic_attr_declaration + value_lines[0]);
        result.insert(std::end(result), std::begin(value_lines) + 1, std::end(value_lines));

        return result;
    }

    lines unparse(spartsi::tree const &tree) {
        return {};
    }
}