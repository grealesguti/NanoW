#ifndef G4SIM_HH
#define G4SIM_HH

// Include necessary standard and Geant4 headers
#include <iostream> // For input/output operations
#include "G4RunManager.hh" // Class for managing the simulation run
#include "G4UImanager.hh" // Class for user interface management

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
#include "MicroElecPhysics.hh"


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
};    

#endif
