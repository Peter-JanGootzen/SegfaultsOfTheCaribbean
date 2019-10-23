#ifndef FILE_BATTLE_CONTROLLER_HPP
#define FILE_BATTLE_CONTROLLER_HPP

#include "models/ship.hpp"
#include "view_controllers/cli_view_controller.hpp"
#include "models/world.hpp"
#include "std/unique_ptr.hpp"

class BattleController {
public:
	BattleController(World& w, CliViewController& cliViewController);
	void battle(Ship* s);
private:
	unique_ptr<Ship> spawnPirateShip();
	String presentOptions(); 
	void shoot(Ship& s, Ship& priateShip);
	bool flee(Ship& s, Ship& pirateShip);
	void surrender(Ship& s, Ship& pirateShip);
	int calculateDamage(Ship& s);
	World& world;
	CliViewController& cliViewController;
};

#endif