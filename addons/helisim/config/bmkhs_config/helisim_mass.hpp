/////////////////////////////////////////////////////////////////////////////////////////////
// Mass and Balance /////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

    //Empty and max gross mass, datum, CG limits, empty CG and seats are the OH-6A's. The
    //loadout (magazines, stores, equipment) is from tools/dump.sqf; its TODOs say what is estimated.

    //Empty airframe. No EmptyMassVariants - no fitted equipment changes it.
    emptyMass         = 524.0; //kg
    emptyMom          = 1450.956;   //empty CG at model y 0.657 (FS 109.0 in) - aft of the aft limit,
                                    //so every loading from pilot alone to full sits in limits

    //Maximum gross mass - bounds the fixed test weight
    maxGrossMass      = 1225.0; //kg

    //Fuselage station datum and CG limits
    //From fm.p3d's refDatum / fwdCgLimit / aftCgLimit, through the fm placement, midpoint of each line
    fsDatum             = 3.426;      //m, station 0 reference
    fwdCgLimit          = 0.967;    //m, FS 96.8 in
    aftCgLimit          = 0.787;    //m, FS 103.9 in
    comCorrection[]     = {0.000, 0.000, 1.674};   //z: the SOG model's CoM height, from seats.sqf
    //Casual mode center of mass
    casualModeCom[]     = {0.000, 0.810, 0.975};

/////////////////////////////////////////////////////////////////////////////////////////////
// Indexed mass items ///////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
    //Every mass item is {arm, mass}: arm[] is {lateral, longitudinal, vertical} in metres,
    //right-positive / nose-positive, in the same surveyed frame as fsDatum.

    //SEATS. Occupancy is resolved against fullCrew, so an empty seat adds no mass.
    //  role       - "driver" | "gunner" | "commander" | "turret" | "cargo"
    //  turret[]   - turret path for gunner/commander/turret seats; {} for the driver
    //  cargoIndex - cargo slot for role = "cargo"; -1 otherwise
    //Measured with tools/seats.sqf in vn_b_air_oh6a_01. The cargo seat (turret [2], FFV) is on
    //_01 only; on the other variants it is never occupied, so it adds nothing.
    numSeats = 4;
    class Seats {
        class Seat01 {  //pilot
            arm[]      = {0.309, 1.679, 1.437};
            mass       = 100.0;
            role       = "driver";
            turret[]   = {};
            cargoIndex = -1;
        };
        class Seat02 {  //copilot
            arm[]      = {-0.350, 1.685, 1.382};
            mass       = 100.0;
            role       = "turret";
            turret[]   = {0};
            cargoIndex = -1;
        };
        class Seat03 {  //door gunner
            arm[]      = {0.416, 0.806, 1.360};
            mass       = 100.0;
            role       = "gunner";
            turret[]   = {1};
            cargoIndex = -1;
        };
        //TODO(OH6A): seats.sqf could not seat the FFV turret - the door gunner mirrored.
        class Seat04 {  //cargo (FFV)
            arm[]      = {-0.416, 0.806, 1.360};
            mass       = 100.0;
            role       = "turret";
            turret[]   = {2};
            cargoIndex = 0;
        };
    };

    //STATIONS - the rocket launcher, _04 to _07. Measured with tools/seats.sqf in _06.
    numStations = 1;
    class Stations {
        class Station01 {  //right, PylonRight1
            arm[]    = {0.885, 1.175, 0.842};
            pylons[] = {1};
        };
    };

    //MAGAZINES - internal rounds, every turret's and the driver's. massPerRound is the real
    //round (7.62 mm linked, 40 mm, hand grenades), not the magazine's Arma mass.
    //TODO(OH6A): arms - the ammunition's stowage, placed in the rear cabin for now.
    numMagazines = 7;
    class Magazines {
        class Mag01 {  //M60 door gun, 7.62 mm linked
            match        = "vn_m60_v_";
            arm[]        = {0.416, 0.806, 1.000};
            massPerRound = 0.0275;  //kg
        };
        class Mag02 {  //M134, XM27E1 - 7.62 mm linked
            match        = "vn_m134_v_";
            arm[]        = {-0.416, 0.806, 1.000};
            massPerRound = 0.0275;  //kg
        };
        class Mag03 {  //M129, XM8 - 40 mm
            match        = "vn_m75_v_";
            arm[]        = {-0.416, 0.806, 1.000};
            massPerRound = 0.36;    //kg
        };
        class Mag04 {  //M18 smoke
            match        = "vn_v_m18r_mag";
            arm[]        = {0.000, 0.806, 1.000};
            massPerRound = 0.54;    //kg
        };
        class Mag05 {  //M61 fragmentation
            match        = "vn_v_m61_mag";
            arm[]        = {0.000, 0.806, 1.000};
            massPerRound = 0.45;    //kg
        };
        class Mag06 {  //M7 CS
            match        = "vn_v_m7_mag";
            arm[]        = {0.000, 0.806, 1.000};
            massPerRound = 0.45;    //kg
        };
        class Mag07 {  //M127 parachute flare
            match        = "vn_v_m127_mag";
            arm[]        = {0.000, 0.806, 1.000};
            massPerRound = 0.29;    //kg
        };
    };

    //STORES - 2.75 in FFAR, four to a launcher. Mk 40 motor plus warhead.
    //TODO(OH6A): launcherMass is an estimate.
    numStores = 4;
    class Stores {
        class Store01 {  //M151 HE
            match        = "vn_rocket_ffar_m151";
            launcherMass = 20.0;    //kg
            massPerRound = 10.4;    //kg
            isTank       = 0;
        };
        class Store02 {  //M229 HE, 17 lb
            match        = "vn_rocket_ffar_m229";
            launcherMass = 20.0;
            massPerRound = 13.9;
            isTank       = 0;
        };
        class Store03 {  //WDU-4 flechette
            match        = "vn_rocket_ffar_wdu4";
            launcherMass = 20.0;
            massPerRound = 10.9;
            isTank       = 0;
        };
        class Store04 {  //M156 WP
            match        = "vn_rocket_ffar_m156";
            launcherMass = 20.0;
            massPerRound = 10.4;
            isTank       = 0;
        };
    };

    //EQUIPMENT - parts the variants show and hide. emptyMass is the airframe with none fitted.
    //TODO(OH6A): masses are estimates and arms are placed by eye - left armament mount and the
    //pilot's sight forward, the rear seat aft.
    numEquipment = 5;
    class Equipment {
        class Equipment01 {  //Armament mount, XM27E1 / XM8 - _02 to _07
            animation      = "hide_gunpod_source";
            installedPhase = 0;
            mass           = 18.0;  //kg
            arm[]          = {-0.800, 0.850, 1.000};
        };
        class Equipment02 {  //M134 minigun - _02, _04 to _07
            animation      = "mg5_hide_source";
            installedPhase = 0;
            mass           = 39.0;
            arm[]          = {-0.900, 0.850, 1.000};
        };
        class Equipment03 {  //M129 grenade launcher - _03
            animation      = "xm8_hide_source";
            installedPhase = 0;
            mass           = 21.0;
            arm[]          = {-0.900, 0.850, 1.000};
        };
        class Equipment04 {  //XM70 reflex sight - _02 to _07
            animation      = "hide_xm70_sight_source";
            installedPhase = 0;
            mass           = 3.0;
            arm[]          = {0.309, 2.000, 1.700};
        };
        class Equipment05 {  //rear seat - _01
            animation      = "hide_seat_source";
            installedPhase = 0;
            mass           = 8.0;
            arm[]          = {-0.416, 0.806, 1.200};
        };
    };
