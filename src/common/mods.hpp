#pragma once

#include <filesystem>
#include <map>
#include <string>
#include <vector>

namespace mods {
enum class mod_option_type { multiple, custom, key, checkbox };

struct mod_option {
    std::string name;
    mod_option_type type;
    std::string choice_default;
    std::vector<std::string> choice_multiple;
};

struct mod_state {
    bool enabled = false;
    std::map<std::string, std::string> options;
};

struct mod_info {
    std::string id;
    std::string name;
    std::string author;
    std::string description;
    std::string version;
    std::vector<mod_option> options;
    std::string path;
};

class manager {
  public:
    static manager& get() {
        static manager instance;
        return instance;
    }

    void initialize(const std::filesystem::path& mods_directory);
    std::vector<mod_info> scan_mods_directory(const std::filesystem::path& mods_directory);
    std::optional<mod_info> parse_mod_config(const std::filesystem::path& mod_config_path);

    std::vector<mod_info> get_enabled_mods();
    const std::vector<mod_info>& get_discovered_mods();

  private:
    std::vector<mod_info> m_discovered_mods;
    void sync_states_with_discovered();
};

} // namespace mods
