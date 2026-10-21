# Counter-Strike: Source game module

Makes Counter-Strike: Source playable with weapons in OpenSE.

The game's weapon scripts (`scripts/weapon_*.ctx`) are encrypted, so the engine cannot read
them. This module ships readable `WeaponData` scripts in `content/scripts/` that use the
game's own view and world models and soundscripts; the engine mounts `content/` after the
game's files (`game::addGameContent`).

| Script | Weapon | Slot | Clip / reserve | Damage | Seconds per shot |
| --- | --- | --- | --- | --- | --- |
| `weapon_ak47` | AK-47 | 1 | 30 / 90 | 36 | 0.1 |
| `weapon_m4a1` | M4A1 (unsilenced) | 1 | 30 / 90 | 33 | 0.09 |
| `weapon_mp5navy` | MP5 | 1 | 30 / 120 | 26 | 0.075 |
| `weapon_awp` | AWP (no scope) | 1 | 10 / 30 | 115 | 1.455 |
| `weapon_glock` | Glock 18 (single fire) | 2 | 20 / 120 | 25 | 0.15 |
| `weapon_usp` | USP .45 (unsilenced) | 2 | 12 / 96 | 34 | 0.15 |
| `weapon_deagle` | Desert Eagle | 2 | 7 / 35 | 54 | 0.225 |
| `weapon_knife` | Knife (melee) | 3 | - | 20 | 0.4 |

The numbers are approximations of the game's publicly known values, not read from the
game; spread and recoil are chosen. Silencers, burst fire, scopes, armour and buying are
not implemented.

Loadouts (cvars): `loadout_t` = knife, Glock, AK-47; `loadout_ct` = knife, USP, M4A1. The
last weapon listed is drawn first. `give <weapon>` (with `sv_cheats 1`) adds any of them.

Tests: `unit_cstrike` (scripts parse into the intended weapons); `assets_cstrike` with
`OSE_CSS_DIR` set to the directory containing `cstrike/` (the models and sounds exist).
