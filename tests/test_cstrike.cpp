// The module's weapon scripts: they parse into the intended weapons, and (with the game
// installed) everything they name exists in the game's content.
#include <doctest/doctest.h>

#include <cstdlib>
#include <filesystem>

#include "fs/filesystem.h"
#include "game/weapons.h"

using namespace ose;
using namespace ose::game;

namespace {
const char* kWeapons[] = {"weapon_glock", "weapon_usp", "weapon_deagle", "weapon_ak47",
                          "weapon_m4a1",  "weapon_mp5navy", "weapon_awp", "weapon_knife"};
}

TEST_CASE("weapon scripts: firearms and a knife") {
    fs::FileSystem fsys;
    REQUIRE(fsys.addDirectory(OSE_CSTRIKE_CONTENT));
    WeaponScripts scripts(fsys);
    for (const char* name : kWeapons) {
        CAPTURE(name);
        const WeaponDef* d = scripts.find(name);
        REQUIRE(d);
        CHECK(d->kind == (std::string(name) == "weapon_knife" ? WeaponDef::Melee : WeaponDef::Firearm));
        CHECK(!d->viewModel.empty());
    }
    const WeaponDef* ak = scripts.find("weapon_ak47");
    CHECK(ak->clipSize == 30);
    CHECK(ak->sound("single_shot") == "Weapon_AK47.Single");
    const WeaponDef* glock = scripts.find("weapon_glock");
    CHECK(glock->clipSize == 20);
    CHECK(glock->bucket == 1);
}

TEST_CASE("weapon scripts: models and sounds exist in the game content") {
    const char* css = std::getenv("OSE_CSS_DIR");
    if (!css) return;
    fs::FileSystem fsys;
    REQUIRE(fsys.mountGameInfo(std::string(css) + "/cstrike/gameinfo.txt"));
    REQUIRE(fsys.addDirectory(OSE_CSTRIKE_CONTENT));
    auto sounds = fsys.readText("scripts/game_sounds_weapons.txt");
    REQUIRE(sounds);
    WeaponScripts scripts(fsys);
    for (const char* name : kWeapons) {
        CAPTURE(name);
        const WeaponDef* d = scripts.find(name);
        REQUIRE(d);
        CHECK(fsys.exists(d->viewModel));
        CHECK(fsys.exists(d->worldModel));
        for (const auto& [key, script] : d->sounds) {
            CAPTURE(script);
            CHECK(sounds->find("\"" + script + "\"") != std::string::npos);
        }
    }
}
