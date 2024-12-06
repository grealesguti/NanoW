#include "run.hh"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

MyRunAction :: MyRunAction(MyG4Args *MainArgs)
{ // Constructor
    
    OutputName=MainArgs->GetOutName();
    PassArgs = MainArgs;

    G4AnalysisManager *man = G4AnalysisManager::Instance();

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


    G4AnalysisManager *man = G4AnalysisManager::Instance();

    // Get current Event number 
    G4int runID = run->GetRunID();
    std::stringstream strRunID;
    strRunID << runID;

    struct stat st;

        printf("Creating directory \"Results\" since it doesn't exist.\n");
        mkdir("Results", 0700);

    // Creation of Output file
    man->OpenFile("Results/Output.root");

}
void MyRunAction::EndOfRunAction(const G4Run* run)
{
    G4AnalysisManager* man = G4AnalysisManager::Instance();

    // Retrieve data from the sensitive detector (this assumes your sensitive detector is properly set up)
    MySensitiveDetector* sensDetector = (MySensitiveDetector*)G4SDManager::GetSDMpointer()->FindSensitiveDetector("MySensitiveDetector");

    if (sensDetector) {
        // Iterate over all hit records and store in ROOT
        for (auto& hit : sensDetector->hitRecords) {
            man->FillNtupleDColumn(0, 0, hit.energyDeposit);  // Energy deposit
            man->FillNtupleDColumn(0, 1, hit.position.x());   // Position X
            man->FillNtupleDColumn(0, 2, hit.position.y());   // Position Y
            man->FillNtupleDColumn(0, 3, hit.position.z());   // Position Z
            man->FillNtupleDColumn(0, 4, hit.time);           // Time
            man->FillNtupleSColumn(0, 5, hit.particleType);   // Particle type
            man->AddNtupleRow(0);
        }

        // Optionally store total energy by particle type
        for (auto& energyEntry : sensDetector->totalEnergyByParticle) {
            G4cout << "Total energy deposited by " << energyEntry.first << ": " << energyEntry.second / MeV << " MeV" << G4endl;
        }
        
        // Optionally store total energy by particle type and print to screen
        G4cout << "Total energy deposited by each particle type:" << G4endl;
        for (auto& energyEntry : sensDetector->totalEnergyByParticle) {
            G4cout << "Particle type: " << energyEntry.first << ", "
                   << "Total energy: " << energyEntry.second / MeV << " MeV" << G4endl;
        }
        
    } else {
        // If no sensitive detector is found, print an error message
        G4cout << "Error: Sensitive detector 'MySensitiveDetector' not found!" << G4endl;
    }


    man->Write();// Write out the root file to avoid damaging it
    man->CloseFile();

}
