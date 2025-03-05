#ifndef GENERATOR_HH
#define GENERATOR_HH

#include "G4VUserPrimaryGeneratorAction.hh"

#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"
#include "G4Args.hh"
#include "globals.hh"
//#include "G4VUserPrimaryGeneratorAction.hh"

class MyPrimaryGenerator : public G4VUserPrimaryGeneratorAction
{
public:
    MyPrimaryGenerator(MyG4Args*);
    ~MyPrimaryGenerator();
    
    virtual void GeneratePrimaries(G4Event*);
    
private:
    G4ParticleGun *fParticleGun;
	MyG4Args* PassArgs;
};

#endif
