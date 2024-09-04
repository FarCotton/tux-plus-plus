#include <dpp/dpp.h>
#include <string>

class Command {
public:
  virtual void execute(dpp::cluster &bot, const dpp::slashcommand_t &event) = 0;
  virtual void execute(dpp::cluster &bot, const dpp::message_create_t &event) = 0;
  virtual std::string get_name() const = 0;
  virtual std::string get_description() const = 0;
  virtual std::string get_prefix() const = 0;
  virtual std::vector<dpp::command_option> get_options() const = 0;
};