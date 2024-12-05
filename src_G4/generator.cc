#include "generator.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{
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
    
    
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0, 0, 1)); // Direction -X
    G4ThreeVector pos(0. * mm, 0. * m, -(20+10+20+3) * mm);
    fParticleGun->SetParticlePosition(pos);
		G4cout<< " ### Finshing Generator  " <<G4endl;    
    
    fParticleGun->GeneratePrimaryVertex(anEvent);
}
