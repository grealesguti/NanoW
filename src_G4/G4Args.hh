#ifndef G4ARGS_HH
#define G4ARGS_HH

// Include necessary Geant4 headers for managing the simulation run
#include "G4RunManager.hh" // Class for managing the simulation run

// Include standard C++ headers
#include <cstdlib> // Standard library functions, including dynamic memory management, random number generation, and others
#include <iostream> // Standard input/output stream objects
#include <algorithm> // Template functions for algorithms like std::sort
#include <vector> // Template class for dynamic arrays
#include <fstream> // File stream operations
#include <cstring> // Functions for manipulating C-style strings
#include <ctime> // Functions for time and date
#include <string.h> // Functions for manipulating strings
#include <sstream> // String stream operations
#include <stdio.h> // Standard input/output functions

// Include custom utility header
//#include "util.hh" // Custom utility functions and definitions

// Include Geant4 header for user interface management
#include "G4UImanager.hh" // Class for managing the user interface

// Include Geant4 header for logical volumes
#include "G4LogicalVolume.hh" // Class representing a logical volume in Geant4


// This class provides all tuning or modification potential within all other classes.
// This class contains functions to store values within each part of each run and or event of 
// GEANT4. Furthermore, it reads and stores all values introduced by cmd.
// Possible inputs and default values or possible options:


// Include necessary Geant4 headers for sensitive detectors and analysis
#include "G4VSensitiveDetector.hh" // Base class for sensitive detectors in Geant4
#include "G4RunManager.hh" // Class for managing the simulation run
#include "G4AnalysisManager.hh" // Class for managing analysis of simulation data
#include "G4SystemOfUnits.hh" // System of units for Geant4
#include "G4PhysicsOrderedFreeVector.hh" // Class for ordered free vector of physics processes
#include "G4GenericMessenger.hh" // Class for handling command-line arguments
#include "G4Step.hh" // Class for storing step information
#include "G4TouchableHistory.hh" // Class for storing touchable history
#include "G4ParticleDefinition.hh" // For accessing particle types
#include "G4Track.hh" // Class for track information
#include "G4ThreeVector.hh" // Class for 3D vector operations
#include <unordered_map> // For storing energy deposited by each particle type
// Custom hash function for G4String (needed for unordered_map)
struct G4StringHasher {
    std::size_t operator()(const G4String &key) const {
        // Hashing based on the string data
        return std::hash<std::string>()(key.c_str());
    }
};

class MyG4Args 
{

public:
    MyG4Args(int, char**);
    ~MyG4Args();
    // Setting up functions
    G4String GetOutName() const {return OutName;} 	// Get output name

    // Function to add energy deposition to a particle type in the map
    void AddToEnergyByParticle(const G4String& particleType, G4double energyDeposit);

    // Function to add a hit record to the vector
    void AddHitRecord(const G4double energyDeposit, const G4ThreeVector& position, 
                      const G4double time, const G4String& particleType);


    // Store energy deposition, position, time, and particle type for each hit
    struct HitData {
        G4double energyDeposit;
        G4ThreeVector position;
        G4double time;
        G4String particleType;
    };
    

private:

	// Setting up variables
    G4String OutName, MacName;    
    // Store total energy deposited by each particle type
    std::unordered_map<G4String, G4double, G4StringHasher> totalEnergyByParticle;
    // Vector to store individual hit data
    std::vector<HitData> hitRecords;  

};    

#endif
