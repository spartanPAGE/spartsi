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

        indent(std::begin(value_lines)+1, std::end(value_lines), generic_attr_declaration.size());

        result.reserve(comment_lines.size() + value_lines.size() + 1);
        result.insert(std::end(result), std::begin(comment_lines), std::end(comment_lines));
        result.push_back(generic_attr_declaration + value_lines[0]);
        result.insert(std::end(result), std::begin(value_lines) + 1, std::end(value_lines));

        return result;
    }

    unparsed::declaration unparse_ref_attr_declaration(std::string const &name, spartsi::ref_attribute const &attribute) {
        unparsed::declaration declaration;
        auto ref_attr_declaration = "ref attr " + name;
        auto declaration_comments = unparse_comment(attribute.comment);
        declaration.reserve(declaration_comments.size() + 1);
        declaration.insert(std::end(declaration), std::begin(declaration_comments), std::end(declaration_comments));
        declaration.push_back(ref_attr_declaration);
        return declaration;
    }

    //TODO: extract common function of unparse(attr) and unparse(ref_attr)
    unparsed::definition unparse_ref_attr_definition(std::string const &name, spartsi::ref_attribute const &attribute) {
        unparsed::definition definition;
        auto generic_ref_attr_definition = "ref attr " + name + " ";
        auto definition_comments = unparse_comment(attribute.ref_comment);
        auto value_lines = unparse_attribute_value(attribute.value);
        indent(std::begin(value_lines)+1, std::end(value_lines), generic_ref_attr_definition.size());
        definition.reserve(definition_comments.size() + value_lines.size() + 1);
        definition.insert(std::end(definition), std::begin(definition_comments), std::end(definition_comments));
        definition.push_back(generic_ref_attr_definition + value_lines[0]);
        definition.insert(std::end(definition), std::begin(value_lines) + 1, std::end(value_lines));
        return definition;
    }

    unparsed::pair unparse(std::string const &name, spartsi::ref_attribute const &attribute) {
        assert(!name.empty());
        return std::make_pair(
            unparse_ref_attr_declaration(name, attribute),
            unparse_ref_attr_definition(name, attribute)
        );
    }

    unparsed::pair unparse(std::string const &name, spartsi::attribute_variant const &variant) {
        switch(variant.which()) {
            case VA_ATTR:
                return {unparse(name, boost::get<spartsi::attribute>(variant)), {}};
            case VA_REF_ATTR:
                return unparse(name, boost::get<spartsi::ref_attribute>(variant));
            default:
                assert(false); //impossible
                return {};
        }
        return {};
    }

    unparsed::pair unparse(spartsi::attributes_map const &attrs) {
        unparsed::declaration decl;
        unparsed::definition def;

        auto const &history = attrs.history();
        for(auto const &key: history) {
            auto const &variant = attrs.at(key);
            auto subresult = unparse(key, variant);
            decl.insert(std::end(decl), std::begin(subresult.first), std::end(subresult.first));
            def.insert(std::end(def), std::begin(subresult.second), std::end(subresult.second));
        }

        return { decl, def };
    }

    lines unparse(spartsi::tree const &tree) {
        return {};
    }
}