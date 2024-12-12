#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4GenericMessenger.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4UserLimits.hh"
#include "G4SubtractionSolid.hh"
#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"
//#include "event.hh"
#include "G4Trap.hh"
#include "G4UnionSolid.hh"
#include "G4Args.hh"
#include "G4TriangularFacet.hh"
#include "G4TessellatedSolid.hh"
#include "G4QuadrangularFacet.hh"
#include "G4Tubs.hh"

#include "detector.hh"
#include "G4UserLimits.hh"
#include "G4SystemOfUnits.hh"

class MyDetectorConstruction : public G4VUserDetectorConstruction
{
public:
    MyDetectorConstruction(MyG4Args*);
    ~MyDetectorConstruction();

    G4LogicalVolume *GetScoringVolume() const { return fScoringVolume; }

    virtual G4VPhysicalVolume *Construct();
    void ConstructCherenkov();
    void ConstructScintillator();
    void ConstructTOF();
    void ConstructAtmosphere();

private:
    G4Box *solidWorld, *solidRadiator, *solidDetector, *solidScintillator, *solidAir, *solidCu1, *solidCu2, *solidAl1, *solidAl2;
    G4LogicalVolume *logicWorld, *logicRadiator, *logicDetector, *logicScintillator, *logicAir[10], *logicCu1, *logicCu2, *logicAl1, *logicAl2, *logicsubstrate;
    G4VPhysicalVolume *physWorld, *physDetector, *physRadiator, *physScintillator, *physAir[10], *physCu1, *physCu2, *physAl1, *physAl2;

    G4OpticalSurface *mirrorSurface;

    G4Material *SiO2, *H2O, *Aerogel, *worldMat, *NaI, *Air[10], *AirMat, *CuMat, *AlMat, *aSiMat, *WSiMat;
    G4Element *C, *Na, *I;

    //void DefineMaterials();
    //virtual void ConstructSDandField();

    G4GenericMessenger *fMessenger;

    G4LogicalVolume *fScoringVolume;

    G4int nRows, nCols, two;

    G4bool isCherenkov, isScintillator, isTOF, isAtmosphere;
        virtual void ConstructSDandField(); // SD==Sensitive Detector
    MyG4Args* PassArgs;

};

#endif
