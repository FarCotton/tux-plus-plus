#include <dpp/dpp.h>
#include <string>

class Command {
public:
  virtual void execute(dpp::cluster &bot, const dpp::slashcommand_t &event) = 0;
  virtual std::string get_name() const = 0;
  virtual std::string get_description() const = 0;
};