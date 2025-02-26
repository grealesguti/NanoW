#ifndef RUN_HH
#define RUN_HH

// Include necessary Geant4 and custom headers
#include "G4UserRunAction.hh" // Base class for user run actions
#include "G4Run.hh" // Class representing a run in Geant4
#include "G4UImanager.hh" // Class for user interface management
#include "Randomize.hh" // Custom header for random number generation
//#include "G4Args.hh" // Custom header for argument handling
#include "detector.hh"

// Include standard C++ headers
#include <string.h> // For string manipulation functions
//#include "G4AnalysisManager.hh" // Class for managing analysis tools
#include "G4GenericAnalysisManager.hh"

//#include "G4AnalysisManager.hh"
#include "G4Run.hh" // Base class for run actions
#include "G4String.hh"
#include "G4SystemOfUnits.hh"
#include "G4SDManager.hh"

// Declare the MyRunAction class, inheriting from G4UserRunAction
// This class is used to define custom actions that occur at the beginning and end of a simulation run.
class MyRunAction : public G4UserRunAction
{
public:
    // Constructor takes a G4String for command and a pointer to MyG4Args, presumably for configuration
    MyRunAction(MyG4Args*);
    // Destructor
    ~MyRunAction();

    // Virtual methods to perform custom actions at the beginning and end of a simulation run
    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);

private:
    // Command string, possibly for user input or configuration
    G4String command;
    // Output name string, likely used for specifying the output file or directory
    G4String OutputName;

    // Pointer to MyG4Args for passing arguments
    MyG4Args* PassArgs;
};

#endif // RUN_HH
