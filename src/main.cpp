#include "cogs/command.hpp"
#include <dlfcn.h>
#include <dpp/dpp.h>
#include <filesystem>
#include <fstream>
#include <memory>
#include <string>
#include <vector>

namespace fs = std::filesystem;

std::string get_token_from_env() {
  std::ifstream file("../.env");
  std::string line;
  while (std::getline(file, line)) {
    size_t pos = line.find("TOKEN=");
    if (pos != std::string::npos) {
      return line.substr(pos + 6);
    }
  }
  file.close();
  throw std::runtime_error("No token found in .env, exiting...");
}
const std::string BOT_TOKEN = get_token_from_env();

void logCallback(const dpp::confirmation_callback_t callback) {
  if (callback.is_error()) {
    std::cerr << "Error: " << callback.get_error().human_readable << std::endl;
  }
}

int main() {
  dpp::cluster bot(BOT_TOKEN);

  // Log all events to stdout
  bot.on_log(dpp::utility::cout_logger());

  // Load all commands
  std::vector<std::unique_ptr<Command>> commands;

  // Iterate over all subdirectories in build/cogs/
  for (const auto &entry : fs::directory_iterator("./cogs/")) {
    if (entry.is_directory()) {
      // Iterate over .so files within each subdirectory
      for (const auto &file : fs::directory_iterator(entry.path())) {
        if (file.is_regular_file() && file.path().extension() == ".so") {
          // Load the .so file
          void *lib_handle = dlopen(file.path().c_str(), RTLD_LAZY);
          if (lib_handle) {
            typedef Command *(*create_command_func)();
            // Assume the function name is "create_<cog_name>_command"
            std::string cog_name = entry.path().filename().string();
            std::string func_name = "create_" + cog_name + "_command";
            create_command_func create_command =
                (create_command_func)dlsym(lib_handle, func_name.c_str());
            if (create_command) {
              commands.push_back(std::unique_ptr<Command>(create_command()));
            } else {
              std::cerr << "Error loading command from library: " << dlerror()
                        << std::endl;
            }
          } else {
            std::cerr << "Error opening library: " << dlerror() << std::endl;
          }
        }
      }
    }
  }

  // ... (register commands)
  bot.on_ready([&bot, &commands](const dpp::ready_t &event) {
    for (const auto &command : commands) {
      bot.guild_command_create(dpp::slashcommand(
        command->get_name(), command->get_description(), bot.me.id), 1280574980345565184); // Testing guild
    }
  });

  // ... (register events)
  bot.on_slashcommand([&bot, &commands](const dpp::slashcommand_t &event) {
    for (const auto &command : commands) {
      if (event.command.get_command_name() == command->get_name()) {
        command->execute(bot, event);
        break;
      }
    }
  });

  // Start the bot
  bot.start(dpp::st_wait);
}
