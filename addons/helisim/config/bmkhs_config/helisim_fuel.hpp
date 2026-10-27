/////////////////////////////////////////////////////////////////////////////////////////////
// Fuel //////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// Fuel tanks ///////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  variableName - the aircraft names its own tank variables. Core prefixes bmkhs_ and appends
//              the field: "fwdTank" publishes bmkhs_fwdTankMass, bmkhs_fwdTankMax,
//              bmkhs_fwdTankLow. Names must be unique. Do not include the bmkhs_ prefix.
//  arm[]     - {lateral, longitudinal, vertical} in m, right-positive / nose-positive
//  capacity  - kg of usable fuel
//  lowFuelKg - low-level caution threshold in kg; 0 for no caution on this tank
//  removable - 1 if the tank can be taken out; 0 is always fitted
//  role      - "main" (an engine can draw from it) or "xfer" (feeds the mains only)

    //The one tank under the cabin floor - full is 366 lb of JP-8 (6.7 lb/gal). Arm from the
    //fuel moment chart: moment/100 equals weight in lb, so FS 100.0 in. TODO(OH6A): lowFuelKg.
    numCrossfeedModes = 1;
    class CrossfeedModes {
        class Norm { position = "NORM"; engSources[] = {"mainTank"}; };
    };

    numFuelTanks = 1;
    class FuelTanks {
        class FuelTank01 {
            variableName = "mainTank";
            arm[]     = {0.000, 0.886, 0.000};  //FS 100.0 in, fsDatum 3.426
            capacity  = 166.0;                  //kg, 366 lb
            lowFuelKg = 0.0;
            removable = 0;
            role      = "main";
        };
    };

    numAuxTanks = 0;
