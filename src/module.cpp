// Counter-Strike: Source as a game module. The game's weapon scripts are encrypted, so this
// module ships readable ones (content/scripts/weapon_*.txt) that use the game's own models
// and soundscripts, and gives each team a loadout and its player models.
#include "core/cvar.h"
#include "game/launch.h"
#include "game/world.h"

namespace {

// The teams are the engine's built-in "ct" and "t". The last weapon listed is drawn first.
ose::CVar loadout_ct("loadout_ct", "weapon_knife weapon_usp weapon_m4a1", ose::CVar::None, "Weapons counter-terrorists spawn with");
ose::CVar loadout_t("loadout_t", "weapon_knife weapon_glock weapon_ak47", ose::CVar::None, "Weapons terrorists spawn with");
// Player models, handed out in turns.
ose::CVar playermodel_ct("playermodel_ct", "models/player/ct_urban.mdl models/player/ct_gsg9.mdl models/player/ct_sas.mdl models/player/ct_gign.mdl",
                         ose::CVar::None, "Models counter-terrorists are shown with");
ose::CVar playermodel_t("playermodel_t", "models/player/t_phoenix.mdl models/player/t_leet.mdl models/player/t_arctic.mdl models/player/t_guerilla.mdl",
                        ose::CVar::None, "Models terrorists are shown with");

// The launcher menu's entry for Counter-Strike: Source.
ose::game::LaunchMode launchMode() {
    ose::game::LaunchMode m;
    m.name = "Counter-Strike: Source";
    m.description = "Walk the maps with your team's weapons and player models.";
    m.games = {"cstrike"};
    m.maps = {"de_dust2", "cs_office", "de_inferno", "cs_italy", "de_nuke"};
    m.settings = {{"--team", "Team", {{"ct", "Counter-Terrorists"}, {"t", "Terrorists"}}, {}}};
    return m;
}

const bool kRegistered = (ose::game::addGameContent(OSE_CSTRIKE_CONTENT), ose::game::addLaunchMode(launchMode()), true);

}  // namespace
