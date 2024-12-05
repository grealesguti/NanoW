#ifndef DETECTOR_HH
#define DETECTOR_HH

// Include necessary Geant4 headers for sensitive detectors and analysis
#include "G4VSensitiveDetector.hh" // Base class for sensitive detectors in Geant4
#include "G4RunManager.hh" // Class for managing the simulation run
#include "G4AnalysisManager.hh" // Class for managing analysis of simulation data
#include "G4SystemOfUnits.hh" // System of units for Geant4
#include "G4PhysicsOrderedFreeVector.hh" // Class for ordered free vector of physics processes
#include "G4GenericMessenger.hh" // Class for handling command-line arguments

// Include custom headers for event handling and argument handling
//#include "event.hh" // Custom header for event-related actions
//#include "G4Args.hh" // Custom header for argument handling

// Declare the MySensitiveDetector class, inheriting from G4VSensitiveDetector
// This class is used to define a custom sensitive detector for a Geant4 simulation.
// In this case this defines the SiPMs at both ends of the LYSO as sensitive detectors to store
// values related to the incident photons. Called within construction.cc 
class MySensitiveDetector : public G4VSensitiveDetector
{
public:
    // Constructor takes a G4String and a pointer to MyG4Args, presumably for configuration and passing arguments
    MySensitiveDetector(G4String);
    // Destructor
    ~MySensitiveDetector();


private:

    virtual G4bool ProcessHits(G4Step *, G4TouchableHistory *);


};

#endif
