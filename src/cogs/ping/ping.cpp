#include "../command.hpp"

class PingCommand : public Command {
public:
  void execute(dpp::cluster &bot, const dpp::slashcommand_t &event) override {
    event.reply("Pong!");
  }

  std::string get_name() const override { return "ping"; }

  std::string get_description() const override { return "Ping Pong!"; }
};

// Export the function
extern "C" {
Command *create_ping_command() { return new PingCommand(); }
}