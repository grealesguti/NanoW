#include "run.hh"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

MyRunAction :: MyRunAction(MyG4Args *MainArgs)
{ // Constructor
    
    OutputName=MainArgs->GetOutName();
    PassArgs = MainArgs;

    G4GenericAnalysisManager *man = G4GenericAnalysisManager::Instance();

    // Content of output.root (tuples created only once in the constructor)
            man->CreateNtuple("Hits","Hits");   
    // Energy deposition, position (x, y, z), time, particle type
    man->CreateNtupleDColumn("EnergyDeposit");
    man->CreateNtupleDColumn("PositionX");
    man->CreateNtupleDColumn("PositionY");
    man->CreateNtupleDColumn("PositionZ");
    man->CreateNtupleDColumn("Time");
    man->CreateNtupleSColumn("ParticleType");    
			man->FinishNtuple(0); // Finish our first tuple or Ntuple number 0
			
    // Content of output.root (tuples created only once in the constructor)
            man->CreateNtuple("Event","Event");   
    // Energy deposition, position (x, y, z), time, particle type
    man->CreateNtupleIColumn("Event");
    man->CreateNtupleDColumn("EnergyDeposit");
    man->CreateNtupleDColumn("GunX");
    man->CreateNtupleDColumn("GunY");
    man->CreateNtupleDColumn("GunZ"); 
			man->FinishNtuple(1); // Finish our first tuple or Ntuple number 0
		

}
MyRunAction :: ~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run* run)
{
    G4UImanager *UImanager = G4UImanager::GetUIpointer();

    // Initialization of G4 random generator through computer time
    G4int timeseed1=time(NULL);
    G4int timeseed2=time(NULL)+128493729;
    G4int timeseed3=time(NULL)/23839;
    command ="/random/setSeeds "+std::to_string(timeseed1)+" "+std::to_string(timeseed2)+" "+std::to_string(timeseed3);
    UImanager->ApplyCommand(command); 
    G4cout<<command<< G4endl;
    G4double rand=G4UniformRand();  // Test of random number written to screen
    G4cout<<" Random number: " << rand << G4endl;


    G4GenericAnalysisManager *man = G4GenericAnalysisManager::Instance();

    // Get current Event number 
    G4int runID = run->GetRunID();
    std::stringstream strRunID;
    strRunID << runID;

    struct stat st;

    // Create the "Results" directory if it doesn't exist
    if (stat("Results", &st) == -1) {
        printf("Creating directory \"Results\" since it doesn't exist.\n");
        mkdir("Results", 0700);
    }

    // Creation of Output file using the OutputName from MainArgs
    std::string outputFileName = "Results/" + OutputName + ".root"; // Use OutputName for the ROOT file name
    man->OpenFile(outputFileName.c_str());
    
    PassArgs->ResetTotalEnergyByParticleAndEvent();

}
void MyRunAction::EndOfRunAction(const G4Run* run)
{
    G4cout << "### END OF RUN" << G4endl;

    G4GenericAnalysisManager* man = G4GenericAnalysisManager::Instance();
	if (!man) {
		G4cout << "Error: AnalysisManager instance is null!" << G4endl;
		return;
	}
    // Retrieve data from the sensitive detector (this assumes your sensitive detector is properly set up)
    // MySensitiveDetector* sensDetector = (MySensitiveDetector*)G4SDManager::GetSDMpointer()->FindSensitiveDetector("MySensitiveDetector");

    if (PassArgs) {
        // Iterate over all hit records and store them in the ROOT file
        const auto& hitRecords = PassArgs->GetHitRecords(); // Add a getter to MyG4Args for hitRecords

	if(PassArgs->GetAllrecord()){
    // Iterate over both vectors simultaneously
    for (size_t i = 0; i < hitRecords.size(); ++i) {
        const auto& hit = hitRecords[i];
        
            man->FillNtupleDColumn(0, 0, hit.energyDeposit);  // Energy deposit
            man->FillNtupleDColumn(0, 1, hit.position.x());   // Position X
            man->FillNtupleDColumn(0, 2, hit.position.y());   // Position Y
            man->FillNtupleDColumn(0, 3, hit.position.z());   // Position Z
            man->FillNtupleDColumn(0, 4, hit.time);           // Time
            man->FillNtupleSColumn(0, 5, hit.particleType);   // Particle type
               
            man->AddNtupleRow(0);

                  }
	}else{
   for (size_t i = 0; i < hitRecords.size(); ++i) {
        const auto& hit = hitRecords[i];
        
            man->FillNtupleDColumn(0, 0, hit.energyDeposit);  // Energy deposit
            man->FillNtupleDColumn(0, 1, hit.position.x());   // Position X
            man->FillNtupleDColumn(0, 2, hit.position.y());   // Position Y
            man->FillNtupleDColumn(0, 3, hit.position.z());   // Position Z
            man->FillNtupleDColumn(0, 4, hit.time);           // Time
            man->FillNtupleSColumn(0, 5, hit.particleType);   // Particle type
            
               
            man->AddNtupleRow(0);

                  }
		
		}


        G4int lastEventNumber = run->GetNumberOfEvent() - 1;
        G4cout << "Last event number: " << lastEventNumber << G4endl;

		// Get the entire map for total energy by particle and event
		const auto& totalEnergyMap = PassArgs->GetTotalEnergyByParticleAndEventAll();
        const auto& gunpositions = PassArgs->GetGunPositions(); // Retrieve gun positions

		// Print the sizes of both containers
		G4cout << "Size of totalEnergyMap: " << totalEnergyMap.size() << G4endl;
		G4cout << "Size of gunpositions: " << gunpositions.size() << G4endl;

		// Check if sizes match to ensure one-to-one correspondence
		if (totalEnergyMap.size() != gunpositions.size()) {
			G4cout << "Warning: Mismatch between totalEnergyMap and gunpositions sizes!" << G4endl;
		}
		// Initialize iterator for gunpositions
		auto gunPosIt = gunpositions.begin();
		
		// Iterate through the map and fill the N-tuple
			G4double TotEnEv = 0;

		for (const auto& eventEntry : totalEnergyMap) {
			TotEnEv = 0;
			G4int eventNumber = eventEntry.first;  // Event number

			const auto& energyByParticle = eventEntry.second;  // Energy by particle type for this event

			// Check if we have a valid gun position
			if (gunPosIt == gunpositions.end()) {
				G4cout << "Warning: Gun positions iterator exceeded size!" << G4endl;
				break; // Avoid out-of-bounds access
			}

			// Retrieve the gun position for this event
			const G4ThreeVector& gunPos = *gunPosIt; // Dereference iterator
			G4double GunX = gunPos.x();
			G4double GunY = gunPos.y();
			G4double GunZ = gunPos.z();
			

			// Print event number
			G4cout << "Event number: " << eventNumber << G4endl;

			// Iterate through the energy data for each particle type in this event
			for (const auto& energyEntry : energyByParticle) {
				G4cout << "  Particle type: " << energyEntry.first << ", "
					   << "Total energy deposited: " << energyEntry.second / MeV << " MeV" << G4endl;
			// Print event number and gun position
			G4cout << "  Impact location (mm): X = " << GunX
				   << ", Y = " << GunY
				   << ", Z = " << GunZ << G4endl;
					   
			}

			

			// Iterate through particle types and their associated energies in this event
			for (const auto& energyEntry : energyByParticle) {
				G4String particleType = energyEntry.first;       // Particle type
				G4double energy = energyEntry.second;           // Energy for this particle type

				// Accumulate total energy for the event
				TotEnEv += energy;

			}

			// Fill data for the event in the N-tuple
			man->FillNtupleIColumn(1,0, eventNumber);
			man->FillNtupleDColumn(1,1, TotEnEv);
			man->FillNtupleDColumn(1,2, GunX / mm);  // Ensure GunX, GunY, GunZ are accessible
			man->FillNtupleDColumn(1,3, GunY / mm);
			man->FillNtupleDColumn(1,4, GunZ / mm);
			man->AddNtupleRow(1);
			
			// Move to the next gun position
			++gunPosIt;
			
		}
		
		
    } else {
        // If MyG4Args is not accessible, print an error message
        G4cout << "Error: MyG4Args instance not found or accessible!" << G4endl;
    }

    // Write out the ROOT file to avoid damaging it
    man->Write();
    man->CloseFile();

	G4cout << "Finalizing ROOT file..." << G4endl;
	man->Write();
	man->CloseFile();
	G4cout << "ROOT file written and closed successfully."  << G4endl;
    
}
