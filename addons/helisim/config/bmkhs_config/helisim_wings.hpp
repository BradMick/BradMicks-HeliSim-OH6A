/////////////////////////////////////////////////////////////////////////////////////////////
// Wings ////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//Written by fm_generateAeroSurfacePoints.py from fm.p3d - re-running resets every value.
//Placement: turn 0 pitch -1.500 roll 0.000 yaw 0.000 forward 0.200 down -2.700 right 0.000
//
//  name             - "leftWing", "rightWing", "horizontalStabilizer", "stabilator",
//                     "verticalFin", "leftVerticalFin" or "rightVerticalFin".
//  facing           - the way the lift acts.
//  numElements      - elements along the span.
//  airfoil          - section name.
//  chordLinePos     - chord fraction from the leading edge the force acts at.
//  panels[]         - quads, corners {right, forward, up} m.
//  heliSimStabTable - stabilator incidence deg; rows collective 0..1, columns 30-180 kt.

    class Wings {
        class Wing01 {
            name           = "horizontalStabilizer";
            facing         = "up";
            numElements    = 4;
            airfoil        = "NACA 0012";
            chordLinePos   = 0.25;
            panels[] = {
                 {{-0.050,-3.869, 1.761},{ 1.620,-3.912, 2.480},{ 1.620,-4.461, 2.446},{-0.050,-4.417, 1.727}}
            };
        };
        class Wing02 {
            name           = "verticalFin";
            facing         = "right";
            numElements    = 4;
            airfoil        = "NACA 4418";
            chordLinePos   = 0.25;
            panels[] = {
                 {{ 0.000,-4.547, 2.989},{ 0.000,-3.877, 1.801},{ 0.000,-4.357, 1.814},{ 0.000,-4.807, 2.996}}
                ,{{ 0.000,-3.963, 1.583},{ 0.000,-4.198, 1.009},{ 0.000,-4.358, 1.013},{ 0.000,-4.283, 1.592}}
            };
        };
    };
