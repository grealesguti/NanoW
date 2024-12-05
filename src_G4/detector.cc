#include "detector.hh"

MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{
	
		    G4cout << "### Sensitive detector '" << name << "' is being created!" << G4endl;

}

MySensitiveDetector::~MySensitiveDetector()
{
}

G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
	

    // Accessing step information
    G4double edep = aStep->GetTotalEnergyDeposit();
    
    // Only process hits where energy deposition is greater than 0
    if (edep > 0) {
        
        // Get position of the hit
        G4ThreeVector position = aStep->GetPostStepPoint()->GetPosition();
        
        // Get the time of the hit (time at the post step point)
        G4double time = aStep->GetPostStepPoint()->GetGlobalTime();
        
        // Get particle type (the track associated with the step)
        G4Track *track = aStep->GetTrack();
        G4ParticleDefinition *particle = track->GetDefinition();
        G4String particleType = particle->GetParticleName();
        
        // Store the hit data
        HitData hit;
        hit.energyDeposit = edep;
        hit.position = position;
        hit.time = time;
        hit.particleType = particleType;

        // Add the hit data to the vector of recorded hits
        hitRecords.push_back(hit);

        // Accumulate the energy deposited by each particle type
        totalEnergyByParticle[particleType] += edep;

        // Optionally, print hit data for debugging
        G4cout << "Hit recorded: " 
               << "Energy Deposit: " << edep / MeV << " MeV, "
               << "Position: (" << position.x() / mm << ", " << position.y() / mm << ", " << position.z() / mm << ") mm, "
               << "Time: " << time / ns << " ns, "
               << "Particle Type: " << particleType << G4endl;

        // Print the total energy deposited by this particle type so far (for debugging)
        G4cout << "Total energy deposited by " << particleType 
               << ": " << totalEnergyByParticle[particleType] / MeV << " MeV" << G4endl;
    }
    
    return true;
}
