#include "\bmkhs_helisim\fmOverride.hpp"

class CfgVehicles {
    class vn_helicopter_base;
    //The base OH-6A, reopened with its own parent so its config is extended, not replaced.
    //Everything else about the aircraft - model, crew, weapons, fuel capacity - stays as it is.
    //TODO(OH6A): check no class below the base (vn_air_oh6a_cargo_base, vn_b_air_oh6a_01, ...)
    //sets the force coefficients again - if one does, it needs BMKHS_FM_OVERRIDE too, as the
    //Bo 105's variants did.
    class vn_air_oh6a_base : vn_helicopter_base {
        //Core owns the force coefficients - packs cannot tune them
        BMKHS_FM_OVERRIDE

        #include "bmkhs_oh6a_config.hpp"
    };
};
