#include "../command.hpp"

class PingCommand : public Command {
public:
  void execute(dpp::cluster &bot, const dpp::slashcommand_t &event) override {
    event.reply("Pong!");
  }

  void execute(dpp::cluster &bot, const dpp::message_create_t &event) override {}

  std::string get_name() const override { return "ping"; }

  std::string get_description() const override { return "Ping Pong!"; }

  std::string get_prefix() const override { return ""; }

  std::vector<dpp::command_option> get_options() const override { return {}; }
};

// Export the function
extern "C" {
  Command *create_ping_command() { return new PingCommand(); }
}