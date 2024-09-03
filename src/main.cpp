#include <dpp/dpp.h>
#include <fstream>
#include <string>
 
std::string get_token_from_env() {
    std::ifstream file("../.env");
    std::string line;
    while (std::getline(file, line)) {
        size_t pos = line.find("TOKEN=");
        if (pos != std::string::npos) {
            return line.substr(pos + 6);
        }
    }
    file.close();
    throw std::runtime_error("No token found in .env");
}
const std::string BOT_TOKEN = get_token_from_env();
 
int main() {
    dpp::cluster bot(BOT_TOKEN);
 
    bot.on_log(dpp::utility::cout_logger());
 
    bot.on_slashcommand([](const dpp::slashcommand_t& event) {
        if (event.command.get_command_name() == "ping") {
            event.reply("Pong!");
        }
    });
 
    bot.on_ready([&bot](const dpp::ready_t& event) {
        if (dpp::run_once<struct register_bot_commands>()) {
            bot.global_command_create(dpp::slashcommand("ping", "Ping pong!", bot.me.id));
        }
    });
 
    bot.start(dpp::st_wait);
}
