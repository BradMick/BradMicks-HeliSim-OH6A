/////////////////////////////////////////////////////////////////////////////////////////////
// Rotors - Simple //////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//TODO(OH6A): the Bo 105's rotors, placed on the Bo 105. The OH-6A: 4-blade main, 8.03 m
//diameter, 484 rpm; 2-blade tail rotor on the left, 3120 rpm. Hubs placed with the nudge;
//gear ratios set from 6000 rpm engine output.
//A rotor is a hub at a position turning blades of a given size, so its geometry, its blade
//and what it does with the controls are defined together here. Core reads numSimpleRotors
//and loops; nothing downstream indexes by rotor NUMBER.
//
//The simple model works four fixed blade positions and scales by blade count, so the lift
//and drag tables carry what the rotor does rather than deriving it per blade element.
//
//  type         - "main" or "tail". What the rotor IS, so Core never assumes rotor 0 is
//                 the main one.
//  direction    - "ccw" or "cw", seen from above.
//  numBlades    - the four modelled positions are scaled to this.
//  pivot[]      - hub position, {lateral, longitudinal, vertical} in m,
//                 right-positive / nose-positive / up-positive
//  rotation[]   - disc orientation, {pitch, roll, yaw} in deg
//  mastLength   - m along the disc's own up axis, from pivot to hub
//  gearRatio    - rotor to engine shaft; shared with the transmission model
//  torqueTau    - s, torque filter time constant
//  damageRole   - the hitpoint role that destroys this rotor. A rotor that declares none
//                 cannot be destroyed.
//
//  BLADE
//  bladeRadius  - m
//  bladeChord   - m
//  bladeMass    - kg, one blade
//
//  DISC TILT - min / mid / max in deg, interpolated from the centred stick. A rotor whose
//  disc does not tilt declares zeroes.
//
//  coneAngle    - deg at full collective. Coning lifts the tips, so the thrust position
//                 moves inboard and the disc carries a vertical arm.
//  flapBackRollMax / flapBackPitchMax - deg at an advance ratio of 1.0. The advancing blade
//                 lifts more than the retreating one, so the disc tilts as speed builds.
//                 Applied as blade flap, which moves both the thrust position and its
//                 direction - it is NOT also applied to the lift coefficient.
//  rollLiftCoef / pitchLiftCoef - the cyclic lift coefficient, independent of the
//                 collective's. This is what makes the fore/aft and left/right blades carry
//                 different lift, so the pitch and roll moments come out of real forces at
//                 real positions rather than being applied as a torque.
//  gndEffValue  - thrust multiplier on the deck, fading to 1.0 by one rotor diameter up.
//                 A rotor that does not sit in ground effect declares 1.0.
//  reacTqScalar - scales the tangential blade drag that produces the yaw reaction. The same
//                 drag drives the transmission, which this does not touch.
//
//  liftCoefTable / dragCoefTable - rows are the control axis that loads this rotor
//  (collective for a main, pedal for a tail), columns are the airspeeds in the header row,
//  m/s. The drag table carries induced and profile together, and its airspeed columns carry
//  how they vary with speed - that is what the transmission feels.

    numSimpleRotors = 2;
    //Rotor limits, Nr - {normal low, normal high, high rotor, maximum}; below and above normal is transient.
    nrLimits[] = {0.98, 1.02, 1.05, 1.10};
    class SimpleRotors {
        class SimpleRotor01 {
            type             = "main";
            direction        = "ccw";
            damageRole       = "mainRotor";
            numBlades        = 4;
            pivot[]          = {0.000, 0.860, -0.280};
            rotation[]       = {0.00, 0.00, 0.00};
            mastLength       = 0.66;      //m
            gearRatio        = 12.397;    //6000 / 484 rpm
            torqueTau        = 0.10;      //s

            bladeRadius      = 4.015;     //m, 26.33 ft diameter
            bladeChord       = 0.1715;    //m, 6.75 in
            bladeMass        = 7.500;     //kg, 16.5 lb

            pitchFlapMin     = -10.0;     //deg
            pitchFlapMid     =   0.0;
            pitchFlapMax     =  20.0;
            rollFlapMin      = -10.5;
            rollFlapMid      =   0.0;
            rollFlapMax      =   7.0;

            coneAngle        = 12.0;  //deg at full collective
            flapBackRollMax  = 15.0;  //deg per unit advance ratio
            flapBackPitchMax =  9.0;  //deg per unit advance ratio
            rollLiftCoef     = 0.238;   //0.166 x 1.3 x 1.1 - flight tests 2026-10-27
            pitchLiftCoef    = 0.451;   //0.315 x 1.3 x 1.1 - flight tests 2026-10-27
            gndEffValue      = 1.225;
            reacTqScalar     = 0.50;
            autoTorque       = 80.0;

            //rotortables.py --bc 0.003 -0.074 2.365 --cg 0.054 0.983 -0.691 --hover 2200lb:62 2550lb:76 2640lb:80
            //  --curve 0:62 10:56 20:48 30:40 40:35 50:32 60:31 70:31 80:34 90:38 100:44 110:50 120:60 130:71
            //  140:82 150:93 160:104 --mr 115. 140-160 kt extended along the chart's last slope.
            //Front drag 0.330 (helisim_fuselage.hpp) from --cruise-pitch -6: 115 kt trims 6 deg nose low.
            liftCoefTable[] = {
                        {"A/S", 0.00, 5.14, 10.29, 15.43, 20.58, 25.72, 30.87, 36.01, 41.16, 46.30, 51.44, 56.59, 61.73, 66.88, 72.02, 77.17, 82.31, 92.60}
                        ,{0.000, 0.0322, 0.0354, 0.0407, 0.0484, 0.0559, 0.0634, 0.0688, 0.0738, 0.0717, 0.0680, 0.0610, 0.0557, 0.0491, 0.0476, 0.0473, 0.0476, 0.0481, 0.0491}
                        ,{0.850, 0.3039, 0.3343, 0.3841, 0.4563, 0.5274, 0.5978, 0.6491, 0.6960, 0.6761, 0.6411, 0.5751, 0.5253, 0.4629, 0.4495, 0.4464, 0.4486, 0.4534, 0.4630}
                        ,{0.900, 0.2909, 0.3199, 0.3675, 0.4367, 0.5047, 0.5721, 0.6212, 0.6661, 0.6470, 0.6136, 0.5504, 0.5027, 0.4430, 0.4302, 0.4272, 0.4293, 0.4339, 0.4431}
                        ,{0.950, 0.2684, 0.2952, 0.3391, 0.4029, 0.4657, 0.5279, 0.5732, 0.6146, 0.5970, 0.5661, 0.5078, 0.4639, 0.4087, 0.3969, 0.3942, 0.3961, 0.4004, 0.4089}
                        ,{1.000, 0.2328, 0.2561, 0.2942, 0.3495, 0.4040, 0.4579, 0.4972, 0.5332, 0.5179, 0.4911, 0.4405, 0.4024, 0.3546, 0.3443, 0.3419, 0.3436, 0.3473, 0.3547}
                        };
            dragCoefTable[] = {
                        {"A/S", 0.00, 5.14, 10.29, 15.43, 20.58, 25.72, 30.87, 36.01, 41.16, 46.30, 51.44, 56.59, 61.73, 66.88, 72.02, 77.17, 82.31, 92.60}
                        ,{0.000, 0.0037, 0.0019, 0.0009, 0.0006, 0.0003, 0.0002, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001}
                        ,{0.686, 0.0225, 0.0222, 0.0218, 0.0214, 0.0214, 0.0214, 0.0214, 0.0214, 0.0214, 0.0214, 0.0214, 0.0214, 0.0223, 0.0243, 0.0262, 0.0282, 0.0301, 0.0301}
                        ,{0.815, 0.0280, 0.0276, 0.0272, 0.0267, 0.0266, 0.0266, 0.0266, 0.0266, 0.0266, 0.0266, 0.0266, 0.0266, 0.0278, 0.0302, 0.0326, 0.0351, 0.0375, 0.0375}
                        ,{0.850, 0.0294, 0.0290, 0.0285, 0.0280, 0.0279, 0.0279, 0.0279, 0.0279, 0.0279, 0.0279, 0.0279, 0.0279, 0.0292, 0.0317, 0.0343, 0.0368, 0.0393, 0.0393}
                        ,{0.900, 0.0382, 0.0377, 0.0371, 0.0364, 0.0363, 0.0363, 0.0363, 0.0363, 0.0363, 0.0363, 0.0363, 0.0363, 0.0379, 0.0412, 0.0445, 0.0479, 0.0512, 0.0512}
                        ,{0.950, 0.0529, 0.0522, 0.0513, 0.0504, 0.0503, 0.0503, 0.0503, 0.0503, 0.0503, 0.0503, 0.0503, 0.0503, 0.0525, 0.0571, 0.0617, 0.0663, 0.0708, 0.0708}
                        ,{1.000, 0.0764, 0.0754, 0.0741, 0.0728, 0.0726, 0.0726, 0.0726, 0.0726, 0.0726, 0.0726, 0.0726, 0.0726, 0.0759, 0.0825, 0.0891, 0.0957, 0.1023, 0.1023}
                        };
        };

        class SimpleRotor02 {
            type             = "tail";
            direction        = "ccw";
            damageRole       = "tailRotor";
            numBlades        = 2;
            pivot[]          = {-0.850, -4.177, -0.675};
            rotation[]       = {0.00, -90.00,  0.000};
            mastLength       = -0.56;     //m
            gearRatio        = 1.923;     //6000 / 3120 rpm
            torqueTau        = 0.10;      //s

            bladeRadius      = 0.648;     //m, 4.25 ft diameter
            bladeChord       = 0.1346;    //m, 5.3 in
            bladeMass        = 0.500;     //kg, 1.1 lb

            //The tail disc does not tilt - pedal changes its pitch, not its plane.
            pitchFlapMin     = 0.0;
            pitchFlapMid     = 0.0;
            pitchFlapMax     = 0.0;
            rollFlapMin      = 0.0;
            rollFlapMid      = 0.0;
            rollFlapMax      = 0.0;

            coneAngle        = 0.0;
            flapBackRollMax  = 0.0;
            flapBackPitchMax = 0.0;
            rollLiftCoef     = 0.0;
            pitchLiftCoef    = 0.0;
            gndEffValue      = 1.0;
            reacTqScalar     = 0.25;
            autoTorque       = 0.0;

            //Pedal through controlMap is the table key; rows are left / mid / right. The main
            //rotor turns counter-clockwise, so left pedal carries the torque.
            controlMap[] = {
                {-1.00, -1.0000},
                {-0.75, -0.8875},
                {-0.50, -0.6250},
                {-0.25, -0.2700},
                { 0.00,  0.0000},
                { 0.25,  0.3900},
                { 0.50,  0.7000},
                { 0.75,  0.8900},
                { 1.00,  1.0000}
            };
            //-----------Pedal----0.00---10.29---20.58---36.01---46.30---51.44---61.73---66.88---72.02
            //Lift x 1.5 x 1.2 (x 1.8) - flight tests 2026-10-27: more tail authority.
            liftCoefTable[] = {
                         {"A/S", 0.00,  10.29,  20.58,  36.01,  46.30,  51.44,  61.73,  66.88,  72.02}
                        ,{-1.00, -2.0966, -2.3045, -2.4878, -2.7293, -2.8739, -2.9423, -3.0727, -3.1346, -3.1950}
                        ,{ 0.00, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000}
                        ,{ 1.00, 2.0966, 2.3045, 2.4878, 2.7293, 2.8739, 2.9423, 3.0727, 3.1346, 3.1950}
                        };
            //-----------Pedal----0.00---10.29---20.58---36.01---46.30---51.44---61.73---66.88---72.02
            //Full left 0.2519 -> 0.0760 - flight test 2026-10-27: ~15% torque at full left pedal.
            dragCoefTable[] = {
                         {"A/S", 0.00,  10.29,  20.58,  36.01,  46.30,  51.44,  61.73,  66.88,  72.02}
                        ,{-1.00, 0.0760, 0.0760, 0.0760, 0.0760, 0.0760, 0.0760, 0.0760, 0.0760, 0.0760}
                        ,{ 0.00, 0.0273, 0.0273, 0.0273, 0.0273, 0.0273, 0.0273, 0.0273, 0.0273, 0.0273}
                        ,{ 1.00, 0.0084, 0.0084, 0.0084, 0.0084, 0.0084, 0.0084, 0.0084, 0.0084, 0.0084}
                        };
        };
    };
