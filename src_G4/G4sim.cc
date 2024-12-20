#include "G4sim.hh"

G4simulation::G4simulation(int mainargc,char** mainargv)
{
     G4RunManager *runManager = new G4RunManager();	
	 G4Args = new MyG4Args(mainargc, mainargv);

    
    runManager->SetUserInitialization(new MyDetectorConstruction(G4Args));
    runManager->SetUserInitialization(new MyPhysicsList());
    //runManager->SetUserInitialization(new MicroElecPhysics());
    /*
     * You can change the type of the target material 
(G4_Ag G4_Al G4_C G4_Cu G4_Ge G4_KAPTON G4_Ni G4_Si G4_SILICON_DIOXIDE G4_Ti G4_W), 
if you uncomment one line (/microelectronics/det/setMat) into the .mac file.  
     */
    
    runManager->SetUserInitialization(new MyActionInitialization(G4Args));
    
    runManager->Initialize();

    G4UIExecutive *ui = new G4UIExecutive(mainargc, mainargv);
    
    G4VisManager *visManager = new G4VisExecutive();
    visManager->Initialize();
    
    G4UImanager *UImanager = G4UImanager::GetUIpointer();
    
	// Open the visualization
	UImanager->ApplyCommand("/vis/open OGL");
	// Set the viewpoint
	UImanager->ApplyCommand("/vis/viewer/set/viewpointVector 1 0 0");
	// Draw the volumes
	UImanager->ApplyCommand("/vis/drawVolume");
	// Set auto-refresh to true
	UImanager->ApplyCommand("/vis/viewer/set/autoRefresh true");
	// Add trajectories to the scene (smooth rendering)
	UImanager->ApplyCommand("/vis/scene/add/trajectories smooth");
	// Accumulate the end-of-event action
	UImanager->ApplyCommand("/vis/scene/endOfEventAction accumulate");
	// Add the coordinate axes (e.g., with length 1 meter)
	UImanager->ApplyCommand("/vis/scene/add/axes");


	// --- Additional commands to plot dots at step endpoints ---
	UImanager->ApplyCommand("/vis/modeling/trajectories/create/drawByCharge generic-0");
	UImanager->ApplyCommand("/vis/modeling/trajectories/generic-0/default/setDrawStepPts true");
	UImanager->ApplyCommand("/vis/modeling/trajectories/generic-0/default/setStepPtsSize 10");

// Example for a conditionally colored step point
UImanager->ApplyCommand("/vis/modeling/trajectories/generic-0/default/setStepPtsColour chargePos red");   // Positive charge -> red
UImanager->ApplyCommand("/vis/modeling/trajectories/generic-0/default/setStepPtsColour chargeNeg blue");   // Negative charge -> blue
UImanager->ApplyCommand("/vis/modeling/trajectories/generic-0/default/setStepPtsColour chargeZero green");  // Zero charge -> green

    
    ui->SessionStart();

}
G4simulation::~G4simulation()
{}

