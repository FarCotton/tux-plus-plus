#include "../command.hpp"

class HelpCommand : public Command {
public:
    void execute(dpp::cluster &bot, const dpp::slashcommand_t &event) override {

        event.reply("message");
    }

    void execute(dpp::cluster &bot, const dpp::message_create_t &event) override {}

    std::string get_name() const override { return "help"; }

    std::string get_description() const override { return "Lists all commands"; }

    std::string get_prefix() const override { return ""; }

    std::vector<dpp::command_option> get_options() const override { return {}; }
};

// Export the function
extern "C" {
    Command *create_tux_help_command() { return new HelpCommand(); }
}