#include "detector.hh"

MySensitiveDetector::MySensitiveDetector(G4String name, MyG4Args *MainArgs) : G4VSensitiveDetector(name)
{
			PassArgs=MainArgs;
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
        /*
        HitData hit;
        hit.energyDeposit = edep;
        hit.position = position;
        hit.time = time;
        hit.particleType = particleType;
        */
        // Add the hit data to the vector of recorded hits
        //hitRecords.push_back(hit);
		PassArgs->AddHitRecord(edep, position, time, particleType);

        // Accumulate the energy deposited by each particle type
        //totalEnergyByParticle[particleType] += edep;
		// Get the event number
        G4int eventNumber = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
        
		PassArgs->AddToEnergyByParticleAndEvent(particleType, edep, eventNumber);
		PassArgs->AddCurrentEvtEdep(edep);
		
    }

    
    return true;
}
