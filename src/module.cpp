// Counter-Strike: Source as a game module. The game's weapon scripts are encrypted, so this
// module ships readable ones (content/scripts/weapon_*.txt) that use the game's own models
// and soundscripts, and gives each team a loadout.
#include "core/cvar.h"
#include "game/world.h"

namespace {

// The teams are the engine's built-in "ct" and "t". The last weapon listed is drawn first.
ose::CVar loadout_ct("loadout_ct", "weapon_knife weapon_usp weapon_m4a1", ose::CVar::None, "Weapons counter-terrorists spawn with");
ose::CVar loadout_t("loadout_t", "weapon_knife weapon_glock weapon_ak47", ose::CVar::None, "Weapons terrorists spawn with");

const bool kRegistered = (ose::game::addGameContent(OSE_CSTRIKE_CONTENT), true);

}  // namespace
