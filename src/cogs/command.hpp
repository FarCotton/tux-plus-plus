#include <dpp/dpp.h>

class Command {
public:
  virtual ~Command() {}
  virtual void execute(dpp::cluster &bot, const dpp::slashcommand_t &event) = 0;
  virtual std::string get_name() const = 0;
  virtual std::string get_description() const = 0;
};