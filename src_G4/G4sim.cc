#include "G4sim.hh"
#include "G4CMPPhysicsList.hh"
#include "G4CMPConfigManager.hh"
//#include "PhononConfigManager.hh"




G4simulation::G4simulation(int mainargc,char** mainargv)
{
     G4RunManager *runManager = new G4RunManager();	
	 G4Args = new MyG4Args(mainargc, mainargv);

    
    runManager->SetUserInitialization(new MyDetectorConstruction(G4Args));
	 G4VUserPhysicsList* physics = new G4CMPPhysicsList();
	 physics->SetCuts();
	 runManager->SetUserInitialization(physics);
    
    runManager->SetUserInitialization(new MyPhysicsList());
    //runManager->SetUserInitialization(new MicroElecPhysics());
    /*
     * You can change the type of the target material 
(G4_Ag G4_Al G4_C G4_Cu G4_Ge G4_KAPTON G4_Ni G4_Si G4_SILICON_DIOXIDE G4_Ti G4_W), 
if you uncomment one line (/microelectronics/det/setMat) into the .mac file.  
     */
    
    runManager->SetUserInitialization(new MyActionInitialization(G4Args));
    
    runManager->Initialize();

 // Create configuration managers to ensure macro commands exist
 G4CMPConfigManager::Instance();
 //PhononConfigManager::Instance();
// Check if a number of events is specified
if (G4Args->GetRunevt() > 0) {
    // Run the specified number of events
    G4int numberOfEvents = G4Args->GetRunevt();
    G4cout << "### Running " << numberOfEvents << " events." << G4endl;
    runManager->BeamOn(numberOfEvents);
} else {
    // Initialize the GUI
    G4UIExecutive *ui = new G4UIExecutive(mainargc, mainargv);

    // Initialize the visualization manager
    G4VisManager *visManager = new G4VisExecutive();
    visManager->Initialize();

    // Get the UI manager and apply visualization commands
    G4UImanager *UImanager = G4UImanager::GetUIpointer();

    // Open the visualization and set up the scene
    UImanager->ApplyCommand("/vis/open OGL");
    UImanager->ApplyCommand("/vis/viewer/set/viewpointVector -1 0 0");
    UImanager->ApplyCommand("/vis/drawVolume");
    UImanager->ApplyCommand("/vis/viewer/set/autoRefresh true");
    UImanager->ApplyCommand("/vis/scene/add/trajectories smooth");
    UImanager->ApplyCommand("/vis/scene/endOfEventAction accumulate");
    UImanager->ApplyCommand("/vis/scene/add/axes");
	UImanager->ApplyCommand("/tracking/verbose 1");
	UImanager->ApplyCommand("/vis/scene/add/trajectories smooth");
UImanager->ApplyCommand("/vis/modeling/trajectories/create smooth");
UImanager->ApplyCommand("/vis/modeling/trajectories/drawByCharge");
UImanager->ApplyCommand("/tracking/verbose 2");
UImanager->ApplyCommand("/process/verbose 2");
UImanager->ApplyCommand("/run/verbose 2");



    // Configure step point visualization
    //UImanager->ApplyCommand("/vis/modeling/trajectories/create/drawByCharge generic-0");
    //UImanager->ApplyCommand("/vis/modeling/trajectories/generic-0/default/setDrawStepPts true");
    //UImanager->ApplyCommand("/vis/modeling/trajectories/generic-0/default/setStepPtsSize 10");
    //UImanager->ApplyCommand("/vis/modeling/trajectories/generic-0/default/setStepPtsColour chargePos red");
    //UImanager->ApplyCommand("/vis/modeling/trajectories/generic-0/default/setStepPtsColour chargeNeg blue");
    //UImanager->ApplyCommand("/vis/modeling/trajectories/generic-0/default/setStepPtsColour chargeZero green");

    // Start the UI session
    ui->SessionStart();

    //delete ui;  // Clean up after the session
}

// Clean up the visualization manager
//delete visManager;


}
G4simulation::~G4simulation()
{}

