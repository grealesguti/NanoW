#include "detector.hh"
//#include "util.hh"


MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{

}

MySensitiveDetector::~MySensitiveDetector()
{}


G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
 
         // Add code here to process hits
        G4cout << "Processing a hit!" << G4endl;

        // Example: Accessing step information
        G4double edep = aStep->GetTotalEnergyDeposit();
        if (edep > 0) {
            // Store energy deposition or other information
        }
 
    return true;
}
