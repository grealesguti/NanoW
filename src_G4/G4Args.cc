#include "G4Args.hh"
#include <unistd.h> /* for exit() */


MyG4Args :: MyG4Args(int mainargc,char** mainargv)
{
	
    G4cout << " ### Processing Command line Arguments to the sim : " << G4endl;
    for (int j = 1; j < mainargc; j=j+1){
    G4cout << mainargv[j] <<"\n"<< G4endl;
                if(strcmp(mainargv[j],"-o")==0)
                {   
                    OutName = mainargv[j+1];      j=j+1;
                    G4cout<< " ### Changed Ouput name to : " << OutName<<G4endl;            
                }
	}
			
	
}
MyG4Args :: ~MyG4Args()
{}

void MyG4Args::AddToEnergyByParticle(const G4String& particleType, G4double energyDeposit) {
    // Add energy deposition to the total for the given particle type
    totalEnergyByParticle[particleType] += energyDeposit;
}

void MyG4Args::AddHitRecord(const G4double energyDeposit, const G4ThreeVector& position, 
                            const G4double time, const G4String& particleType) {
    // Create a new hit record and append it to the hitRecords vector
    HitData newHit = {energyDeposit, position, time, particleType};
    hitRecords.push_back(newHit);
}
