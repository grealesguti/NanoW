#include "physics.hh"

MyPhysicsList::MyPhysicsList()
{
	G4cout<< " ### Starting Define Physics" <<G4endl;    
    RegisterPhysics (new G4EmStandardPhysics());    // Standard electromagnetic physics

    RegisterPhysics (new G4OpticalPhysics());
    RegisterPhysics(new G4DecayPhysics());
    RegisterPhysics(new G4RadioactiveDecayPhysics()); // For radioactive decay
    RegisterPhysics(new G4EmLivermorePhysics()); // For low energy photons
    // Add G4CMPPhysicsList
    //G4CMPPhysicsList* cmpPhysics = new G4CMPPhysicsList();
    //cmpPhysics->SetCuts();
    //RegisterPhysics(cmpPhysics);
	//RegisterPhysics(new G4MicroElecPhysics());
    //G4VUserPhysicsList* physics = new G4CMPPhysicsList();
    //physics->SetCuts();
    //runManager->SetUserInitialization(physics);
    G4StepLimiterPhysics* stepLimitPhys = new G4StepLimiterPhysics();
    stepLimitPhys->SetApplyToAll(true); // activates step limit for ALL particles
    RegisterPhysics(stepLimitPhys);
	G4cout<< " ### Finish Define Physics" <<G4endl;     
	

/*
    // Create the step limiter process and apply it to electrons and protons with a 1 nm step size
    G4StepLimiter* stepLimiter = new G4StepLimiter();

    // Apply step limiter to electrons
    G4ProcessManager* electronManager = G4Electron::Electron()->GetProcessManager();
    electronManager->AddProcess(stepLimiter, -1, 1, 1);  // Add step limiter for electrons

    // Apply step limiter to protons
    G4ProcessManager* protonManager = G4Proton::Proton()->GetProcessManager();
    protonManager->AddProcess(stepLimiter, -1, 1, 1);  // Add step limiter for protons

    // Set the maximum step size to 1 nm for electrons and protons
    stepLimiter->SetStepLimit(1.0 * nm);  // Set the step limit to 1 nm for these particles
*/
	
}


MyPhysicsList::~MyPhysicsList()
{}
