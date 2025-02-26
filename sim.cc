#include <iostream>

//#include <iostream>

//#include "G4RunManager.hh"
#include "G4MTRunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
//#include "QGSP_BERT.hh"

#include "src_G4/G4sim.hh"
#include "src_G4/physics.hh"
#include "src_G4/action.hh"
#include "src_G4/G4sim.hh"

int main(int argc, char** argv)
{
		
	G4simulation *sim = new G4simulation(argc, argv);

    return 0;
}
