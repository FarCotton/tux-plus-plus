#include "../command.hpp"

class HelpCommand : public Command {
public:
    void execute(dpp::cluster &bot, const dpp::slashcommand_t &event) override {

        event.reply("message");
    }

    std::string get_name() const override { return "help"; }

    std::string get_description() const override { return "Lists all commands"; }
};

// Export the function
extern "C" {
    Command *create_tux_help_command() { return new HelpCommand(); }
}