#ifndef PHYSICS_HH
#define PHYSICS_HH

// Include necessary Geant4 headers for physics processes
#include "G4VModularPhysicsList.hh" // Base class for modular physics lists
#include "G4EmStandardPhysics.hh" // Standard electromagnetic physics
#include "G4OpticalPhysics.hh" // Optical physics
#include "G4DecayPhysics.hh" // Decay physics
#include "G4RadioactiveDecayPhysics.hh" // Radioactive decay physics
#include "G4StepLimiterPhysics.hh" // Step limiter physics
#include "G4EmLivermorePhysics.hh"

class MyPhysicsList : public G4VModularPhysicsList
{
public:
    MyPhysicsList();
    ~MyPhysicsList();
};

#endif

