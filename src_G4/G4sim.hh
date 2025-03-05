#ifndef G4SIM_HH
#define G4SIM_HH


//#include "G4RunManager.hh"
#include "G4MTRunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

// Include necessary standard and Geant4 headers
#include <iostream> // For input/output operations

// Include Geant4 headers for visualization
#include "G4VisManager.hh" // Class for managing visualization
#include "G4VisExecutive.hh" // Class for executing visualization
#include "G4UIExecutive.hh" // Class for executing user interface

// Include custom headers for construction, physics, and action
#include "construction.hh"
#include "physics.hh"
#include "action.hh"
#include <cstdlib> // For standard library functions
#include <unistd.h> // For exit() function
//#include "MicroElecPhysics.hh"
#include "G4Args.hh"
#include "PhononConfigManager.hh"


// Declare the G4simulation class
// This class defines each run. Prepared to run the visualization module!!!
class G4simulation 
{
public:
    // Constructor takes command-line arguments, and optional parameters for node configuration
    G4simulation(int ,char**);
    // Destructor
    ~G4simulation();


private:

    MyG4Args *G4Args;


};    

#endif
