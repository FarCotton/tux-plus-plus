#include "ping.hpp"

void ping(dpp::cluster& bot, const dpp::slashcommand_t& event) {
  event.reply("Pong!");
}