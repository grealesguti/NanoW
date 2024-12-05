#include "physics.hh"

MyPhysicsList::MyPhysicsList()
{
	G4cout<< " ### Starting Define Physics" <<G4endl;    
    RegisterPhysics (new G4EmStandardPhysics());    // Standard electromagnetic physics

    RegisterPhysics (new G4OpticalPhysics());
    RegisterPhysics(new G4DecayPhysics());
    RegisterPhysics(new G4RadioactiveDecayPhysics()); // For radioactive decay
	//RegisterPhysics(new G4MicroElecPhysics());
	
    G4StepLimiterPhysics* stepLimitPhys = new G4StepLimiterPhysics();
    stepLimitPhys->SetApplyToAll(true); // activates step limit for ALL particles
    RegisterPhysics(stepLimitPhys);
	G4cout<< " ### Finish Define Physics" <<G4endl;     
}


MyPhysicsList::~MyPhysicsList()
{}
