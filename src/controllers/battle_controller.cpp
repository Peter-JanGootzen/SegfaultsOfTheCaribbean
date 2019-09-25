#include "controllers/battle_controller.hpp"
#include "models/ship.hpp"
#include "view_controllers/cli_view_controller.hpp"

BattleController::BattleController(World& w, CliViewController& cliViewController) : world(w), cliViewController(cliViewController) {
}

void BattleController::battle(Ship* s) {

};