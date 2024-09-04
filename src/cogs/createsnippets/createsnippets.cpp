#include "../command.hpp"

class SnippetsCommand : public Command {
public:
  void execute(dpp::cluster &bot, const dpp::slashcommand_t &event) override {
    std::string snippetIdentifier = std::get<std::string>(event.get_parameter("snippet"));
    std::string content = std::get<std::string>(event.get_parameter("content"));

    if (!write_snippet(bot, snippetIdentifier, content))
      event.reply("Snippet `" + snippetIdentifier + ".txt` already exists.");
    else
      event.reply("Snippet `" + snippetIdentifier + ".txt` created");
  }

  void execute(dpp::cluster &bot, const dpp::message_create_t &event) override {
    std::string messageContent = event.msg.content.substr(4, event.msg.content.length() - 4);
    std::size_t pos = messageContent.find(" ");

    if (pos != std::string::npos) {
      std::string snippetIdentifier = messageContent.substr(0, pos);
      snippetIdentifier.erase(0, snippetIdentifier.find_first_not_of(" "));
      std::replace(snippetIdentifier.begin(), snippetIdentifier.end(), ' ', '_');
      std::string content = messageContent.substr(pos, messageContent.length() - pos);
      content.erase(0, content.find_first_not_of(" "));
      if (!write_snippet(bot, snippetIdentifier, content))
        event.reply("Snippet `" + snippetIdentifier + ".txt` already exists.");
      else
        event.reply("Snippet `" + snippetIdentifier + ".txt` created");
    }
  }

  std::string get_name() const override { return "snippet create"; }

  std::string get_description() const override { return "Create snippets"; }

  std::string get_prefix() const override { return "$sc"; }

  std::vector<dpp::command_option> get_options() const override { return {
    dpp::command_option(dpp::co_string, "snippet", "the snippet name", true),
    dpp::command_option(dpp::co_string, "content", "the content of the snippet", true)
  }; }

protected:
bool write_snippet(dpp::cluster &bot, std::string snippetIdentifier, std::string content) {
    std::string filePath = "../snippets/" + snippetIdentifier + ".txt";

    if (std::filesystem::exists(filePath)) {
      return false;
    }

    std::ofstream file(filePath);

    if (file.is_open()) {
        file << content;
        file.close();
        return true;
    } else {
        throw std::runtime_error("Error: Failed to write snippet to file");
    }
}
};

// Export the function
extern "C" {
  Command *create_createsnippets_command() { return new SnippetsCommand(); }
}
