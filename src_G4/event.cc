#include "event.hh"

MyEventAction::MyEventAction(MyRunAction*, MyG4Args* MainArgs)
{

    PassArgs = MainArgs;

}

MyEventAction::~MyEventAction()
{

}

void MyEventAction::BeginOfEventAction(const G4Event *anEvent)
{
	
    if (PassArgs) {
        PassArgs->ResetCurrentEvtEdep();
    } else {
        G4cerr << "Error: PassArgs is null!" << G4endl;
    }
	
}


void MyEventAction::EndOfEventAction(const G4Event *anEvent)
{
  
    if(PassArgs->GetCurrentEvtEdep() <1e-9){
        G4int eventNumber = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
        PassArgs->AddToEnergyByParticleAndEvent("none", 0, eventNumber);
    }
  
}

