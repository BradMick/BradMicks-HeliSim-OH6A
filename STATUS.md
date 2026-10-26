# OH-6A - status

Where the pack is, what is settled, and what is next. Updated after every task.

Started 2026-10-26 on HeliSim Core 1.4.0.0. Built from the Bo 105 pack (`E:\bmkhs_bo105`,
`f514bc9`), following Core's `docs/AIRCRAFT_GUIDE.md`. Local git repo, nothing committed.

## Where it is

| # | Work | State |
|---|---|---|
| 1 | Pack scaffold from the Bo 105, renamed, Bo 105 values as `TODO(OH6A)` placeholders | **Done** - `hemtt check` clean |

## The airframe in game

From the config viewer (`vn_b_air_oh6a_01`, 2026-10-26):

- Mod: S.O.G. Prairie Fire (CDLC), author Savage Game Design.
- Parents: `vn_air_oh6a_cargo_base` > `vn_air_oh6a_base` > `vn_helicopter_base` > `Helicopter_Base_H`.
- `bmkhsBaseClass = "vn_air_oh6a_base"` - every OH-6A variant inherits from it.
- Force coefficients seen on `vn_b_air_oh6a_01`: `backRotorForceCoef` 1.5, `bodyFrictionCoef` 0.17.
  The override sits on `vn_air_oh6a_base` only - not yet checked which class declares them.

## Scaffold notes (task 1)

- Not copied from the Bo 105: `fm.p3d`, `tools/`, `docs/BO105_FM.md`, `releases/`.
- Removed: the `BO105_VARIANT` overrides and the Swooper seat block, the HOT stations and store.
- One engine (`numEngines` 1, `Engine02` removed); one fuel tank, 181 kg (61.5 US gal JP-4), no
  transfer - `fn_setup` no longer sets an XFER mode.

## Placeholders still to replace

| File | Still a placeholder |
|---|---|
| `config.cpp` | `requiredAddons` - `loadorder_f_vietnam` until the SOG addon is read with `configSourceAddonList` |
| `cfgVehicles.hpp` | whether a class below `vn_air_oh6a_base` sets the force coefficients again |
| `helisim_engine.hpp` | the Bo 105's 250-C20B - the OH-6A has one T63-A-5A (250-C10), 317 shp, transmission-limited to 252.5 shp |
| `helisim_simpleRotor.hpp` | the Bo 105's rotors and tables - OH-6A 4-blade, 8.03 m, 483 rpm; hubs to place |
| `helisim_rotor.hpp` | the blade element rotors |
| `helisim_mass.hpp` | every mass, arm and limit; seats to measure with `tools/seats.sqf` |
| `helisim_fuel.hpp` | tank arm and `lowFuelKg` |
| `helisim_fuselage.hpp`, `helisim_wings.hpp` | the Bo 105's surfaces - needs the OH-6A's fm.p3d |
| `helisim_flightControls.hpp` | the gains |
