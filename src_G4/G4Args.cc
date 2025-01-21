#include "G4Args.hh"
#include <cstring>  // For strcmp
#include <iostream> // For G4cout
#include <unistd.h> // For exit()

// Constructor: Process command-line arguments
MyG4Args::MyG4Args(int mainargc, char** mainargv) {
    G4cout << "### Processing Command Line Arguments for the Simulation: " << G4endl;

    for (int j = 1; j < mainargc; ++j) {
        G4cout << mainargv[j] << G4endl;

        // Check for "-o" argument to set the output name
        if (strcmp(mainargv[j], "-o") == 0) {
            if (j + 1 < mainargc) { // Ensure there's a next argument
                OutName = mainargv[j + 1];
                G4cout << "### Changed Output Name to: " << OutName << G4endl;
                ++j; // Skip the next argument since it's the value
            } else {
                G4cerr << "### Error: Missing output name after '-o'" << G4endl;
                exit(EXIT_FAILURE);
            }
        }
    }

    if (OutName.empty()) {
        G4cerr << "### Warning: Output name not provided. Using default value." << G4endl;
        OutName = "default_output";
    }
}

// Destructor
MyG4Args::~MyG4Args() {
    // No dynamic memory to clean up
}

// Add energy deposition to the total for the given particle type and event number
void MyG4Args::AddToEnergyByParticleAndEvent(const G4String& particleType, G4double energyDeposit, G4int eventNumber) {
    // Store energy deposit for the specific event number
    totalEnergyByParticleAndEvent[eventNumber][particleType] += energyDeposit;
}

// Create a new hit record and append it to the hitRecords vector
void MyG4Args::AddHitRecord(const G4double energyDeposit, const G4ThreeVector& position, 
                            const G4double time, const G4String& particleType) {
    HitData newHit = {energyDeposit, position, time, particleType};
    hitRecords.push_back(newHit);
}


void MyG4Args::ResetTotalEnergyByParticleAndEvent() {
    // Clear the entire map, removing all its contents
    totalEnergyByParticleAndEvent.clear();

    G4cout << "Total energy by particle and event has been reinitialized (cleared)." << G4endl;
}
