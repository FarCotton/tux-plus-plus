#include "../command.hpp"

class SnippetsCommand : public Command {
public:
  void execute(dpp::cluster &bot, const dpp::slashcommand_t &event) override {
    std::string snippetIdentifier = std::get<std::string>(event.get_parameter("snippet"));

    event.reply(get_snippet(bot, snippetIdentifier));
  }

  void execute(dpp::cluster &bot, const dpp::message_create_t &event) override {
    std::string messageContent = event.msg.content;
    std::size_t pos = messageContent.find(" ");

    if (pos != std::string::npos) {
      std::string snippetIdentifier = messageContent.substr(0, pos);
      std::string snippet = get_snippet(bot, snippetIdentifier);
      event.send(snippet);
    }
  }

  std::string get_name() const override { return "snippet"; }

  std::string get_description() const override { return "Snippets"; }

  std::string get_prefix() const override { return "$s"; }

  std::vector<dpp::command_option> get_options() const override { return {
    dpp::command_option(dpp::co_string, "snippet", "the snippet to fetch", true)
  }; }

protected:
  std::string get_snippet(dpp::cluster &bot, std::string snippetIdentifier) {
    return "test";
  }
};

// Export the function
extern "C" {
  Command *create_snippets_command() { return new SnippetsCommand(); }
}
