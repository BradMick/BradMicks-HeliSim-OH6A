class CfgPatches
{
    class bmkhs_oh6a_helisim
    {
        units[] = {};
        author = "BradMick";
        weapons[] = {};
        requiredVersion = 2.10;
        //HeliSim Core, and the OH-6A - this pack modifies its class, so it must load after it.
        //TODO(OH6A): loadorder_f_vietnam stands in for the SOG addon that defines vn_air_oh6a_base -
        //read it in game with configSourceAddonList (configFile >> "CfgVehicles" >> "vn_air_oh6a_base").
        requiredAddons[] = {"bmkhs_helisim", "loadorder_f_vietnam"};
        //The airframe this pack drives. Every OH-6A variant inherits from it.
        bmkhsBaseClass   = "vn_air_oh6a_base";
        #include "version.hpp"
    };
};

#include "CfgFunctions.hpp"
#include "config\CfgEventHandlers.hpp"
#include "config\cfgVehicles.hpp"
