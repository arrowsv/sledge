#include "xml.hpp"

#include <pugixml.hpp>
#include <sol/sol.hpp>

namespace lua::bindings::sledge {
void bind_xml(sol::state_view& lua) {
    auto types_table = lua["types"].get_or_create<sol::table>();

    auto xml_node = types_table.new_usertype<pugi::xml_node>("xml_node");
    xml_node["get"] = [](pugi::xml_node& node,
                         const std::string& name) -> sol::optional<pugi::xml_node> {
        auto child = node.child(name.c_str());

        if (child.empty())
            return sol::nullopt;

        return child;
    };
    xml_node["get_from_path"] = [](pugi::xml_node& node,
                                   const std::string& query) -> sol::optional<pugi::xml_node> {
        pugi::xpath_node found_node = node.select_node(query.c_str());

        if (!found_node)
            return sol::nullopt;

        return found_node.node();
    };
    xml_node["get_multiple_from_path"] = [&lua](pugi::xml_node& node,
                                                const std::string& query) -> sol::table {
        pugi::xpath_node_set found_nodes = node.select_nodes(query.c_str());

        sol::table list = lua.create_table();

        int index = 1;
        for (pugi::xpath_node_set::const_iterator it = found_nodes.begin(); it != found_nodes.end();
             ++it) {
            pugi::xpath_node found_node = *it;
            list[index++] = found_node.node();
        }

        return list;
    };
    xml_node["value"] = [](pugi::xml_node& node) { return std::string(node.text().as_string()); };
    xml_node["set"] = [](pugi::xml_node& node, const std::string& value) {
        node.text().set(value);
    };
    xml_node["add"] = [](pugi::xml_node& node, const std::string& name,
                         sol::optional<std::string> value) {
        pugi::xml_node child = node.append_child(name.c_str());
        if (value.has_value()) {
            child.text().set(value.value());
        }
        return child;
    };
    xml_node["delete"] = [](pugi::xml_node& node) {
        if (node.parent()) {
            node.parent().remove_child(node);
        }
    };
    xml_node["children"] = [&lua](pugi::xml_node& node) -> sol::table {
        sol::table list = lua.create_table();

        int index = 1;
        for (pugi::xml_node child : node.children()) {
            list[index++] = child;
        }
        return list;
    };

    auto xml_document = types_table.new_usertype<pugi::xml_document>("xml_document");
    xml_document[sol::base_classes] = sol::bases<pugi::xml_node>();
}

} // namespace lua::bindings::sledge
