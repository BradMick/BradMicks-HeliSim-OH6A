/////////////////////////////////////////////////////////////////////////////////////////////
// Engine ////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////
    // Engines - the gas turbine model  /////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////
    //numEngines is declared at the top of bmkhs_oh6a_config.hpp, beside useSystems - it is
    //the airframe's count, not an engine's property. No hitpoints here, so it IS the count.
    //One Allison T63-A-5A (250-C10): 317 shp takeoff, 270 shp normal, at 6000 rpm output.
    //The OH-6A torquemeter reads psi; 1 psi is taken as 1% of 317 shp, so 80 psi (the 252.5 shp
    //transmission limit) is 80%.
    class Engines {
        class Engine01 {
            name            = "eng01";
            damageRole      = "engines";
            damageRoleIndex = 0;

            //Whole-assembly properties - not owned by any one section.
            engineType  = "turboShaftEngine";   //dispatches to bmkhs_fnc_turboShaftEngine
            designRpm   = 6000;                 //100% Np, the shaft reference
            npFly       = 1.00;                 //governed Np in FLY, as a fraction of designRpm
            maxFuelFlow = 0.0122;               //kg/s per unit of fuel - the 250-C20B's, scaled by power
            powerKw     = 236.4;                //100% torque, 317 shp - the torque reference, refTq

            //Hard shutdowns - both CUT FUEL rather than restricting it.
            maxNg        = 1.10;                //mechanical fly weights
            npOvrspdProt = 0;                   //no electrical overspeed trip

            //Engine Limits - TM 55-1520-214-10 instrument markings
            oilPsiLimits[] = {0.385, 1.000};    //50 psi minimum for flight / 130 psi maximum
            ngMin          = 0.59;              //N1 minimum, engine unloaded
            ngLimits[]     = {{1.04, 15, 10}, {1.05, 0, 20}};          //104% normal, 105% 15 s
            npLimits[]     = {{1.04, 15, 10}, {1.10, 0, 20}};          //104% max, 110% 15 s
            tqLimits[]     = {{0.70, 300, 5}, {0.80, 0, 10}};         //70 psi continuous, 80 psi 5 min
            tgtLimits[]    = {{693, 300, 1000}, {749, 6, 2000}, {843, 0, 2000}};   //TOT
            tqLimitsSe[]   = {{0.70, 300, 5}, {0.80, 0, 10}};
            tgtLimitsSe[]  = {{693, 300, 1000}, {749, 6, 2000}, {843, 0, 2000}};

            //Compressor - stations 2 -> 3.
            class Compressor {
                pressureRatio = 6.2;     //at Ng 1.0
                massFlow      = 1.36;    //kg/s at Ng 1.0, standard day - 3.0 lb/s
                inletDiameter = 0.396;   //m - for inlet losses, not yet modelled
                ramRecovery   = 1.0;     //share of the ram pressure rise the inlet keeps

                //Spooling down only - an unfired compressor is pure load, and that stops it.
                compDrag      = 3.4;     //as compDrag * ng^2
                compDragFloor = 0.10;    //finishes the stop - ng^2 alone only asymptotes

                //Airflow trim by FAT, {FAT, multiplier} - the OGE chart's engine-limited cells. 15 C held.
                //TODO(OH6A): untrimmed - fit from the OH-6A's max torque available chart.
                airflowTable[] = {
                     {-40, 1.0000}
                    ,{ 15, 1.0000}
                    ,{ 40, 1.0000}
                };

                //Compressor map - compressor_map.py tools/oh6a_ratings.txt: MCP 15 C 0.970 693 0.852, TOP 15 C 1.000 749 1.000.
                compressorMap[] = {
                     {0.0000, 0.1612, 0.0000, 0.544, 0.0000}
                    ,{0.0500, 0.1625, 0.0116, 0.544, 0.0037}
                    ,{0.1000, 0.1665, 0.0329, 0.544, 0.0158}
                    ,{0.1500, 0.1730, 0.0604, 0.544, 0.0348}
                    ,{0.2000, 0.1824, 0.0930, 0.544, 0.0610}
                    ,{0.2500, 0.1949, 0.1300, 0.544, 0.0938}
                    ,{0.3000, 0.2107, 0.1709, 0.544, 0.1326}
                    ,{0.3500, 0.2305, 0.2153, 0.544, 0.1770}
                    ,{0.4000, 0.2545, 0.2631, 0.544, 0.2261}
                    ,{0.4500, 0.2832, 0.3139, 0.544, 0.2792}
                    ,{0.5000, 0.3174, 0.3676, 0.544, 0.3357}
                    ,{0.5500, 0.3577, 0.4241, 0.544, 0.3949}
                    ,{0.6000, 0.4049, 0.4833, 0.544, 0.4564}
                    ,{0.6173, 0.4230, 0.5043, 0.544, 0.4781}
                    ,{0.6768, 0.4925, 0.5891, 0.595, 0.4779}
                    ,{0.7546, 0.6030, 0.7130, 0.642, 0.4882}
                    ,{0.8125, 0.7174, 0.8152, 0.657, 0.5148}
                    ,{0.8818, 0.9188, 0.9928, 0.650, 0.5872}
                    ,{0.9091, 0.9976, 0.9898, 0.652, 0.5869}
                    ,{0.9167, 1.0196, 0.9889, 0.653, 0.5868}
                    ,{0.9500, 1.1104, 0.9853, 0.656, 0.5865}
                    ,{1.0000, 1.2396, 0.9798, 0.659, 0.5859}
                };

                //Start thresholds - discrete events the model branches on.
                lightOffNg = 0.15;       //fuel introduced
                selfSustNg = 0.58;       //starter cuts out - N1 58% (5-9.1)
                //Where the start fuel ramp reaches full and residual heat has faded. Raise it
                //to hold fuel lean longer and peak cooler.
                idleNg     = 0.62;       //62% N1 minimum driving the rotor

                //Ng limiter - ngLimitMax min (ngLimitBase + ngLimitSlope * FAT).
                ngLimitMax   = 1.05;
                ngLimitBase  = 1.05;
                ngLimitSlope = 0.0;
            };

            //Combustor - stations 3 -> 4.
            class Combustor {
                fuelLhv             = 43000;    //kJ/kg - JP-8
                combustorEfficiency = 0.99;

                maxTgt      = 843;       //deg C - TGT limiter, twin engine
                maxTgtSe    = 843;       //deg C - TGT limiter, single engine
                startTgt    = 927;       //deg C - the transient START limit, not the peak
                startMinTgt = 80;        //deg C - below this before the power lever is moved

                //How violently an un-purged engine runs away, latched from TGT at the lever.
                residualHeatGain = 0.003;
            };

            //Compressor turbine - stations 4 -> 4.5. Drives the compressor, steps Ng; TGT is read here.
            class CompressorTurbine {
                turbineEfficiency = 0.88;
                spoolInertia      = 5.0; //how fast Ng answers a torque change
            };

            //The free turbine - stations 4.5 -> 5. Np is state with its own torque balance.
            class PowerTurbine {
                ptEfficiency  = 0.88;    //isentropic efficiency
                ptInertia     = 0.60;    //the free turbine's own inertia
                ptDrag        = 0.06;    //drag on a released turbine, as ptDrag * np^2
                ptDragFloor   = 0.05;    //finishes the stop - windmilling only
            };

            //The ECU - what it schedules, and the ceilings it will not pass.
            class Governor {
                //Minimum fuel the power lever schedules.
                fuelIdle = 0.533;        //settles Ng at 0.62 - compressor_map.py
                fuelFly  = 3.136;        //WIDE OPEN - the governor cuts back from here

                //Fuel metered at light-off as a fraction of idle fuel. Sets the start PEAK.
                startFuelBase = 0.25;     //keeps the start peak under the 749 C normal start limit (rig 671 C) - not fitted to OH-6A start data

                ffwdGain = 1.00;         //collective anticipation - the load demand spindle

                leverTravelTime = 15.0;   //seconds, idle to fly - the fuel ramp, Np and the lever animation
                loadShareGain   = 8.0;   //how hard an engine below its matched partners trims up to them

                //Np governor, {kp, ki, kd, ki_clamp}.
                pid[] = {80.0000, 40.0000, 0.0000, 0.0750};

                gate[] = {};             //nothing gates it - no systems modelled here
            };

            //Air turbine or electric, and what it needs available before the spool turns.
            //No systems are modelled here, so nothing gates it.
            class Starter {
                type   = "pneumatic";
                torque    = 0.45;               //maximum, on the spool, normalised - then power-limited
                motoringNg = 0.25;              //starter alone, no fuel
                gate[] = {};
            };
        };
    };
