#include "construction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{}

MyDetectorConstruction::~MyDetectorConstruction()
{}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
	//////////////////
	// Materials //
	//////////////////	
 	G4cout<< " ### Starting Material Definition " <<G4endl;    

    G4NistManager *nist = G4NistManager::Instance();

	G4cout<< " ### - Define SiO2" <<G4endl;    
    SiO2 = new G4Material("SiO2", 2.201*g/cm3, 2);
    SiO2->AddElement(nist->FindOrBuildElement("Si"), 1);
    SiO2->AddElement(nist->FindOrBuildElement("O"), 2);
		G4MaterialPropertiesTable *mptSiO2 = new G4MaterialPropertiesTable();
		G4double energySiO2[2] = {1.378*eV, 6.199*eV};
		G4double rindexSiO2[2] = {1.4585, 1.53};
		G4double ABSSiO2[2] = {0.01*mm, 0.01*mm};
		mptSiO2->AddProperty("RINDEX", energySiO2, rindexSiO2, 2);
		//mptSiO2->AddProperty("ABSLENGTH", energySiO2, ABSSiO2, 2);
		SiO2->SetMaterialPropertiesTable(mptSiO2);

	G4cout<< " ### - Define Air" <<G4endl;    
    AirMat = nist->FindOrBuildMaterial("G4_AIR");
		G4double energyWorld[2] = {1.378*eV, 6.199*eV};
		G4double rindexWorld[2] = {1.0, 1.0};
		G4MaterialPropertiesTable *mptWorld = new G4MaterialPropertiesTable();
		mptWorld->AddProperty("RINDEX", energyWorld, rindexWorld, 2);
		AirMat->SetMaterialPropertiesTable(mptWorld);
    
	G4cout<< " ### - Define Cu" <<G4endl;    
	CuMat = nist->FindOrBuildMaterial("G4_Cu");
		G4MaterialPropertiesTable *mptCu = new G4MaterialPropertiesTable();
		G4double energyCu[2] = {2*eV, 6*eV};
		G4double rindexCu[2] = {0.7, 1};
		G4double ABSCu[2] = {1.68e-9*m, 1.68e-9*m};
		mptCu->AddProperty("RINDEX", energyCu, ABSCu, 2);
		mptCu->AddProperty("ABSLENGTH", energyCu, ABSCu, 2);
		CuMat->SetMaterialPropertiesTable(mptCu);
	
	G4cout<< " ### - Define Al" <<G4endl;    
    AlMat = nist->FindOrBuildMaterial("G4_Al");
		G4MaterialPropertiesTable *mptAl = new G4MaterialPropertiesTable();
		G4double energyAl[2] = {400*eV, 1000*eV};
		G4double rindexAl[2] = {0.99, 0.99};
		G4double ABSAl[2] = {6.6e-9*m, 6.63e-9*m};
		mptAl->AddProperty("RINDEX", energyAl, ABSAl, 2);
		mptAl->AddProperty("ABSLENGTH", energyAl, ABSAl, 2);
		AlMat->SetMaterialPropertiesTable(mptAl);
   
    
	G4cout<< " ### - Define a-Si" <<G4endl;    
    // Define Amorphous Silicon (a-Si)
    G4double density_aSi = 2.32 * g/cm3;  // Typical density for Amorphous Silicon
    G4Element* Si = nist->FindOrBuildElement("Si");  // Silicon element
    aSiMat = new G4Material("AmorphousSi", density_aSi, 1);
    aSiMat->AddElement(Si, 1);  // 1 Silicon atom
		G4MaterialPropertiesTable *mptSi = new G4MaterialPropertiesTable();
		G4double energySi[2] = {1.378*eV, 6.199*eV};
		G4double rindexSi[2] = {4, 4};
		G4double ABSSi[2] = {0.01*mm, 0.01*mm};
		mptSi->AddProperty("RINDEX", energySi, rindexSi, 2);
		mptSi->AddProperty("ABSLENGTH", energySi, ABSSi, 2);
		aSiMat->SetMaterialPropertiesTable(mptSi);

	G4cout<< " ### - Define WSi" <<G4endl;    
    // Define Tungsten Silicide (WSi)
    G4double density_WSi = 9.3 * g/cm3;  // Approximate density of WSi
    G4Element* W = nist->FindOrBuildElement("W");  // Tungsten element
    WSiMat = new G4Material("WSi", density_WSi, 2);  // 2 elements in WSi
    WSiMat->AddElement(W, 1);  // 1 Tungsten atom
    WSiMat->AddElement(Si, 2); // 2 Silicon atoms
    
		G4MaterialPropertiesTable *mptWSi = new G4MaterialPropertiesTable();
		G4double energyWSi[2] = {1.5*eV, 3*eV};
		G4double rindexWSi[2] = {4, 4};
		mptWSi->AddProperty("RINDEX", energyWSi, rindexWSi, 2);
		WSiMat->SetMaterialPropertiesTable(mptWSi);
    
    G4cout<< " ### Finished Material Definition " <<G4endl;    

	//////////////////
	// Construction //
	//////////////////

	//////////////////
	// World //
	G4double WorldL = ((0.02+0.01+0.02)*2+0.006);
    G4Box *solidWorld = new G4Box("solidWorld", WorldL/2*m, WorldL/2*m, WorldL/2*m);
    //G4Box *solidWorld = new G4Box("solidWorld", ((0.02+0.01+0.02)*2+0.006)*m, ((0.02+0.01+0.02)*2+0.006)*m, ((0.02+0.01+0.02)*2+0.006)*m);

    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, AirMat, "logicWorld");
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);

	//////////////////
    // Define the radiator as a cylinder 
    G4double innerRadius = 0.02 * m;  // Cylinder with no inner radius (solid cylinder)
    G4double outerRadius = 0.03 * m; // Radius of the cylinder
    G4double height = WorldL*m;    // Height of the cylinder
    G4double startAngle = 0.0 * deg; // Starting angle
    G4double spanningAngle = 360.0 * deg; // Full circle
    G4Tubs *solidRadiator = new G4Tubs("solidRadiator", innerRadius, outerRadius, height / 2, startAngle, spanningAngle);
    G4LogicalVolume *logicRadiator = new G4LogicalVolume(solidRadiator, AlMat, "logicalRadiator");
    // Create a rotation matrix to rotate 90 degrees around the Z-axis
    G4RotationMatrix *rotation = new G4RotationMatrix();
    rotation->rotateX(90 * deg); // Rotate 90 degrees around the Y-axis
    // Place the cylinder with the rotation
    G4VPhysicalVolume *physRadiator = new G4PVPlacement(rotation, G4ThreeVector(0., 0., 0. * m), logicRadiator, "physRadiator", logicWorld, false, 0, true);

	//////////////////
	// Copper holder
	solidCu1 = new G4Box("solidCu1", 6*mm/2, 6*mm/2-1*mm, 2*mm/2);
	logicCu1 = new G4LogicalVolume(solidCu1, CuMat, "logicCu1");
	physCu1 = new G4PVPlacement(0,G4ThreeVector(0.,0.,0.),logicCu1,"physCu1",logicWorld,false,0,true);
	solidCu2 = new G4Box("solidCu2", 6*mm/2, 2*mm/2, 6*mm/2);
	logicCu2 = new G4LogicalVolume(solidCu2, CuMat, "logicCu2");
	physCu2 = new G4PVPlacement(0,G4ThreeVector(0,3.,2),logicCu2,"physCu2",logicWorld,false,0,true);
	
	//////////////////
	// Substrate 
	G4double Sensor_z = -1 *mm;
	G4double Substrate_z = 0.5 * mm;
	G4double Sensor_x = 1 * mm;
	G4double Sensor_y = 1 * mm;
	G4Box *solidsubstrate = new G4Box("solidsubstrate", Sensor_x/2, Sensor_y/2, Substrate_z/2);
	G4LogicalVolume *logicsubstrate = new G4LogicalVolume(solidsubstrate, SiO2, "logicsubstrate");
	G4VPhysicalVolume *physsubstrate = new G4PVPlacement(
		0,
		G4ThreeVector(0., 0., Sensor_z-Substrate_z/2),
		logicsubstrate,
		"physsubstrate",
		logicWorld,
		false,
		0,
		true
	);

	//////////////////
	// SiO2 top layer
	G4double SiO2_z = 40 * nm;
	G4Box *solid_SiO2toplayer = new G4Box("solid_SiO2toplayer", Sensor_x*mm/2, Sensor_y*mm/2, SiO2_z*mm/2);
	G4LogicalVolume *logic_SiO2toplayer = new G4LogicalVolume(solid_SiO2toplayer, SiO2, "logic_SiO2toplayer");
	G4VPhysicalVolume *phys_SiO2toplayer = new G4PVPlacement(
		0,
		G4ThreeVector(0., 0., Sensor_z-Substrate_z-SiO2_z/2),
		logic_SiO2toplayer,
		"phys_SiO2toplayer",
		logicWorld,
		false,
		0,
		true
	);

	//////////////////
	// aSi top layer
	G4double aSi_z = 3 * nm;
	G4Box *solid_aSitoplayer = new G4Box("solid_aSitoplayer", Sensor_x/2, Sensor_y/2, aSi_z/2);
	G4LogicalVolume *logic_aSitoplayer = new G4LogicalVolume(solid_aSitoplayer, aSiMat, "logic_aSitoplayer");
	G4VPhysicalVolume *phys_aSitoplayer = new G4PVPlacement(
		0,
		G4ThreeVector(0., 0., Sensor_z-Substrate_z-SiO2_z-aSi_z/2),
		logic_aSitoplayer,
		"phys_aSitoplayer",
		logicWorld,
		false,
		0,
		true
	);

	//////////////////
	// Sensor
	G4double wire_z = 3 * nm;
	G4double wire_x = Sensor_x*0.9;
	G4double strip_thickness  = 2250 *nm;
	G4double strip_spacing = 1500 *nm;
	/*
	G4Box *solid_sensor = new G4Box("solid_sensor", Sensor_x*0.9/2, Sensor_y*0.9/2, wire_z*mm/2);
	G4LogicalVolume *logic_sensor = new G4LogicalVolume(solid_sensor, WSiMat, "logic_sensor");
	G4VPhysicalVolume *phys_sensor = new G4PVPlacement(
		0,
		G4ThreeVector(0., 0., 0.*mm), // Adjusted to align correctly with aSi layer
		logic_sensor,
		"phys_sensor",
		logic_SiO2toplayer,
		false,
		0,
		true
	);
	*/
	G4int num_strips = 240; // Number of strips

	for (G4int i = 0; i < num_strips; i++) {
		// Position along y for each strip, considering the thickness and the spacing
		G4double strip_y_pos = -(Sensor_y * 0.9 / 2) + i * (strip_thickness + strip_spacing); 

		// Create a strip solid with specified dimensions
		G4Box *solid_strip = new G4Box("solid_strip_" + std::to_string(i), Sensor_x * 0.9 / 2, strip_thickness / 2, wire_z * mm / 2);

		// Create the logical volume for the strip
		G4LogicalVolume *logic_strip = new G4LogicalVolume(solid_strip, WSiMat, "logic_strip_" + std::to_string(i));

		// Place each strip with translation in the y-axis
		new G4PVPlacement(
			0, // No rotation
			G4ThreeVector(0., strip_y_pos, 0.), // Translation in y for each strip
			logic_strip,
			"phys_strip_" + std::to_string(i),
			logic_SiO2toplayer,
			false,
			i, // Unique copy number for each strip
			true
		);
	}
		
    
    return physWorld;
}
