# OH-6A - status

Where the pack is, what is settled, and what is next. Updated after every task.

Started 2026-10-26 on HeliSim Core 1.4.0.0. Built from the Bo 105 pack (`E:\bmkhs_bo105`,
`f514bc9`), following Core's `docs/AIRCRAFT_GUIDE.md`. On GitHub, `BradMick/BradMicks-HeliSim-OH6A`; needs HeliSim Core 1.4.3.0.

## Where it is

| # | Work | State |
|---|---|---|
| 1 | Pack scaffold from the Bo 105, renamed, Bo 105 values as `TODO(OH6A)` placeholders | **Done** - `hemtt check` clean |
| 2 | Fuselage and wings generated from the OH-6A's `fm.p3d` | **Done** - `hemtt check` clean; not yet seen in game |

## Aerosurfaces (task 2)

Generated 2026-10-26 by Core's `fm_generateAeroSurfacePoints.py`, then placed from the in-game
nudge with `--add`: pitch -1.500, forward 0.200, down -2.700 (turn, roll, yaw, right 0). The same
nudge set the rotor hubs - main `pivot[]` {0, 0.860, -0.280}, tail {-0.850, -4.177, -0.675} -
and `comCorrection[]` {0, -1.550, 1.674}.

| Surface | Facing | Quads |
|---|---|---|
| `fuselageTop` | up | 8 (01 is a triangle) |
| `fuselageSide` | right | 14 (08 is a triangle) |
| `fuselageFront` | forward | 7 |
| `horizontalStabilizer` | up | 1 - right side only, ~24 deg dihedral, NACA 0012 |
| `verticalFin` | right | 2 - upper fin and ventral fin, NACA 4418 |

fm.p3d's stray point in `fuselageTop01` is fixed, but the 2026-10-27 save has the selection back
as `horizontalStab` - regenerated from a scratch copy with it renamed. **Rename it to
`horizontalStabilizer` in Object Builder.** That save also added point-only references
(`refDatum`, CG limits, rotor masts and pivots), which the generator skips.

Datum and CG limits (2026-10-27) from fm.p3d's `refDatum`, `fwdCgLimit`, `aftCgLimit`, put through
the fm placement (midpoint of each line): `fsDatum` 3.426, `fwdCgLimit` 0.967 (FS 96.8 in),
`aftCgLimit` 0.787 (FS 103.9 in). `emptyMom` 1335.676 puts the empty CG at model y 0.877
(FS 100.4 in), midway between the limits, for the OH-6A's `emptyMass` 524 kg. If the mass
changes, set `emptyMom = emptyMass x 2.549` to keep the CG there.

Seats and loadout (2026-10-27) from `tools/seats.sqf` and `tools/dump.sqf`: 4 seats (the FFV
cargo seat could not be measured - door gunner mirrored), 7 internal magazines, rocket station
on pylon 1 with 4 FFAR stores, 5 equipment items. Round masses are real-world; launcher and
equipment masses and every non-seat arm are estimates (TODO in the file).

`comCorrection[]` y reset to 0 (2026-10-27). The nudge's -1.550 compensated the Bo 105's datum,
limits and seats; with the OH-6A's arms it put the CoM 1.55 m aft of the computed CG (first test
flight: overlay y -0.568 = model 0.908 before the offset). z 1.674 kept - the SOG CoM height.

Fuel (2026-10-27) from the fuel moment chart: JP-8, full 366 lb = 166.0 kg; moment/100 equals
weight in lb, so the arm is FS 100.0 in = model y 0.886.

**Empty CG (2026-10-27): model y 0.657, FS 109.0 in, `emptyMom` 1450.956** - aft of the aft
limit on purpose. With the pilots at y 1.68, no empty CG inside the limits works: even at the
aft limit, pilot and copilot alone give 1.034. Every loading checked (pilot alone to full, each
variant, fuel and ammo empty to full) stays in limits for an empty CG between y 0.616 and 0.697;
0.657 is the middle. Pilot alone 0.821, pilot + copilot no fuel 0.940 (the most forward), `_01`
full 0.899. Revisit if the seat arms, equipment or a real empty CG change.

Flight controls (2026-10-27): no SAS, no holds - `class FMC` removed, `class HydraulicBoost`
(no gate) declared, so the controls are boosted and skip `inputLagValue`. Casual-mode auto
PIDs kept.

Engine (2026-10-27): T63-A-5A. 100% torque = 317 shp (`powerKw` 236.4), so the -10's torque psi
reads as % (80 psi = 252.5 shp limit). PR 6.2, 3.0 lb/s. Limits from the -10 markings (TOT
693/749/843, N1 104/105, N2 104/110, torque 70/80, oil 50-130 psi); starter cutout N1 58%, idle
62%. Compressor map from `tools/oh6a_ratings.txt` (MCP 270 shp at 693 C, TOP 317 shp at 749 C;
N1 at each rating estimated 0.970 / 1.000) - both land in the rig; `fuelIdle` 0.392.
`airflowTable` flat 1.0 until the max torque available chart is fitted. Core's rig
(`python/dev/engine.py`, `airframe.py`, `tools/compressor_map.py`) now runs the engine count the
pack declares - it was hard-wired to two (Core working tree, uncommitted).

Main rotor tables (2026-10-27) fitted with `rotortables.py`, record in Core's
`python/dev/fits/oh6a.txt`: hovers 2200 lb 62%, 2550 lb 76%, peak 2640 lb 80%; the -10's
2200 lb cruise curve, max range 115 kt. Fit OK, every point within 0.5%. Hover collective 0.686.
Front drag 0.278 flat (0.330 before the tail surfaces moved aft, 2026-10-27; the wings then moved
a further 0.2 m aft, 0.1 m up from the in-game nudge, in fm.p3d), fitted to 6 deg nose
low at max range (book: 5-7 deg); tables refitted with it - 100 kt 5.2,
115 kt 6.0, 130 kt 6.6 deg in the rig.

Rocket station measured in `_06` (2026-10-27): PylonRight1 {0.885, 1.175, 0.842}. Most forward
gunship loading (pilot + copilot, no fuel or ammo, M229 x4) 0.959 - inside 0.967. Still to
measure: the FFV seat (sit in it in `_01`, run seats.sqf); equipment and ammo arms are estimates.

Start (2026-10-27): Nr did not move until idle - the compressor map's rows below the first rating
held the compressor turbine's expansion, which outgrew the compressor's pressure ratio, so the
power turbine made nothing (0% torque even at idle). Core's `compressor_map.py` now holds the
turbine's share instead (Core working tree, uncommitted); map regenerated, `fuelIdle` 0.533 (idle
5.7% torque, TGT 436 C).

Core engine start rework (2026-10-27, Core working tree, uncommitted): `runawayNg` replaced by
`motoringNg` (dry crank speed; Core solves the starter curve from it); the spool balance now
takes the turbines' power surplus over Ng, so every term is a torque (steady states unchanged);
Core's T700 map corrected below idle. OH-6A `motoringNg` 0.25. Rig start (lever IDLE at 7 s):
dry crank 0.250, N1 58% at 19.9 s with Nr 0.20, peak TGT 674 C at 13 s, idle at 36 s, idle Nr
0.63. Not fitted - needs the OH-6A's own start data (time to 58%, peak TOT).

Start at altitude (2026-10-27): the engine overtemped off sea level. Core now meters fuel below FLY
on inlet pressure (Wf/P3 on corrected Ng), which held the peak under `startTgt`, but in Asia it still
sat over 749 C past the 6 s tier and took damage. `startFuelBase` 0.25 -> 0.06: rig peak with the
lever to IDLE at once 634 C standard day, 689 C Asia, 717 C Central Asia Summer (the worst); 52% at
23-26 s.

First flight tests (2026-10-27): flies well. Changed after them - cyclic `rollLiftCoef` /
`pitchLiftCoef` x 1.3 then x 1.1 (0.238 / 0.451); tail `liftCoefTable` x 1.5 then x 1.2, then x 0.7 and x 1.1 after later flights (x 1.386); tail drag at full left pedal
0.2519 -> 0.0760, from ~50% torque to ~15% (estimate, no OH-6A figure).

Blade masses (2026-10-27): main 7.5 kg, tail 0.5 kg (were the Bo 105's 25 / 1.49). Main rotor
inertia 525 -> 161 kg m2 - Nr decays and recovers about three times faster.

Drivetrain (2026-10-27): engine output 6000 rpm, main rotor 484 rpm, tail rotor 3120 rpm -
`gearRatio` 12.397 / 1.923 in `helisim_simpleRotor.hpp`, same in `rotorGearRatio[]`.

Every value is the generator's default; the Bo 105's tuned front drag (CD 0.358 flat) is gone,
front is now 0.800 rising to 3.000. Check the quads on the airframe with FM debugging, and move
them with `tools/fm_nudge.sqf` if they sit off it.

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
| `helisim_mass.hpp` | seat arms - measure with `tools/seats.sqf` |
| `helisim_fuel.hpp` | tank arm and `lowFuelKg` |
| `helisim_fuselage.hpp`, `helisim_wings.hpp` | geometry is the OH-6A's; drag tables, airfoils and `numElements` are generator defaults |
| `helisim_flightControls.hpp` | the gains |
