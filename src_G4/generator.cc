#include "generator.hh"

MyPrimaryGenerator::MyPrimaryGenerator(MyG4Args* MainArgs)
{
	PassArgs=MainArgs;
    fParticleGun = new G4ParticleGun(1);
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
    delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
	
		G4cout<< " ### Starting Generator  " <<G4endl;    

    fParticleGun = new G4ParticleGun(1); /*Number of particles*/	
    
    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();

    // Define the proton particle
    G4String particleName = "proton";
    G4ParticleDefinition *particle_p = particleTable->FindParticle(particleName);
    
    // Set particle properties for 120 GeV proton
    fParticleGun->SetParticleDefinition(particle_p);
    fParticleGun->SetParticleMomentum(120. * GeV); // Set momentum to 120 GeV    
    
    //G4String particleName = "e-";
    //G4ParticleDefinition *particle_e = particleTable->FindParticle(particleName);
    
    // Set particle properties for 120 GeV proton
    //fParticleGun->SetParticleDefinition(particle_e);
    //fParticleGun->SetParticleMomentum(8. * GeV); // Set momentum to 120 GeV    
    
	// Declare pos outside the if-else blocks
	G4ThreeVector pos;
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0, 0, 1)); // Direction -Z

	// Check if randomGunLocation is true or false
	if (PassArgs->GetRandomGunLocation()) {
		// Generate random positions within a 10-micron width in X and Y (range: -5 microns to +5 microns)
G4double randomX = -25.0 + (static_cast<double>(rand()) / RAND_MAX) * 50.0;  // Random value between -50 and +50 microns
G4double randomY = -25.0 + (static_cast<double>(rand()) / RAND_MAX) * 50.0;  // Random value between -50 and +50 microns


		// Set position with random X and Y, fixed Z at -200 mm
		pos = G4ThreeVector(randomX / 1000 * mm, randomY / 1000 * mm, -200 * mm);
		
    // Print the position vector to the screen
    G4cout << "### RandomGunLocation is true. Position: "
           << "X = " << pos.x() / mm << " mm, "
           << "Y = " << pos.y() / mm << " mm, "
           << "Z = " << pos.z() / mm << " mm" << G4endl;
	} else {
		// Set position to -200 mm in Z with X and Y as 0 if randomGunLocation is false
		pos = G4ThreeVector(0. * mm, 0. * mm, -200 * mm);
	}
	
	PassArgs->StorePosition(pos);

	// Set the particle gun position
	fParticleGun->SetParticlePosition(pos);

		G4cout<< " ### Finshing Generator  " <<G4endl;    
    
    fParticleGun->GeneratePrimaryVertex(anEvent);
}
