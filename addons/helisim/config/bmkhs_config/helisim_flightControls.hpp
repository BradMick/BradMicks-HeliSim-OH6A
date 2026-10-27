/////////////////////////////////////////////////////////////////////////////////////////////
// Flight Controls //////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//TODO(OH6A): the Bo 105's gains (the EC665 Tiger's) as a placeholder - retune once the OH-6A flies.
    inputLagValue     = 0.95;
    //Casual mode auto pitch target
    autoAttLevelPitch = -5.0;     //deg
    autoAttRollLimit  = 30.0;     //deg, bank commanded by the roll key

/////////////////////////////////////////////////////////////////////////////////////////////
// Hydraulic boost //////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//The OH-6A has no SAS, no holds and no FMC - boosted controls only. While boost is on
//(bmkhs_hydBoostOn, default true) and the gate holds, every axis skips the inputLagValue lag.
//No systems (useSystems = 0), so nothing gates it.
    class HydraulicBoost {
        gate[] = {};
    };

    //Auto-pedal
    pidAutoAttPitch[]   = {0.0925, 0.0025, 0.0220, 0.0025};
    pidAutoAttRoll[]    = {0.0400, 0.0015, 0.0250, 0.0015};
    pidAutoPedalHdg[]   = {0.0500, 0.0025, 0.0125, 30.000};
    pidAutoPedalNtt[]   = {0.0150, 0.0040, 0.0025, 18.750};
    pidAutoPedalAero[]  = {0.3000, 0.2500, 0.1000, 0.2000};
