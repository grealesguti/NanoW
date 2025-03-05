#include "construction.hh"

MyDetectorConstruction::MyDetectorConstruction(MyG4Args *MainArgs)
{
	PassArgs = MainArgs;
	}

MyDetectorConstruction::~MyDetectorConstruction()
{}

void MyDetectorConstruction::DefineMaterials(){ 
  G4NistManager* nistManager = G4NistManager::Instance();

  fLiquidHelium = nistManager->FindOrBuildMaterial("G4_AIR"); // to be corrected
  fGermanium = nistManager->FindOrBuildMaterial("G4_Ge");
  fAluminum = nistManager->FindOrBuildMaterial("G4_Al");
  fTungsten = nistManager->FindOrBuildMaterial("G4_W");
  
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
    
	G4cout << " ### - Define Vacuum" << G4endl;    
	VacuumMat = nist->FindOrBuildMaterial("G4_Galactic");

	// For a vacuum, you may want to define properties like the refractive index (which is typically 1 for vacuum).
	G4double energyVacuum[2] = {1.378*eV, 6.199*eV}; 
	G4double rindexVacuum[2] = {1.0, 1.0};  // Refractive index for vacuum is 1
	G4MaterialPropertiesTable* mptVacuum = new G4MaterialPropertiesTable();
	mptVacuum->AddProperty("RINDEX", energyVacuum, rindexVacuum, 2);

	// Set the material properties table for the vacuum material
	VacuumMat->SetMaterialPropertiesTable(mptVacuum);

    	G4cout << " ### - Define Cu" << G4endl;    
	CuMat = nist->FindOrBuildMaterial("G4_Cu");
	G4MaterialPropertiesTable *mptCu = new G4MaterialPropertiesTable();
	// Valores realistas para el índice de refracción del cobre en el rango de 2-6 eV
	G4double energyCu[2] = {2*eV, 6*eV};
	G4double realRindexCu[2] = {0.271, 0.238};  // Parte real del índice de refracción
	G4double imagRindexCu[2] = {3.56, 4.24};    // Parte imaginaria para la absorción
	mptCu->AddProperty("REALRINDEX", energyCu, realRindexCu, 2);
	mptCu->AddProperty("IMAGINARYRINDEX", energyCu, imagRindexCu, 2);
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
   
  // https://refractiveindex.info/?shelf=main&book=Si3N4&page=Kischkat
  // https://refractiveindex.info/?shelf=main&book=Si3N4&page=Luke
	G4cout << "### - Define Silicon Nitride (Si3N4)" << G4endl;
	// Define the material using the NIST database or creating a custom material
	Si3N4Mat = new G4Material("SiliconNitride", 3.44*g/cm3, 2);
	Si3N4Mat->AddElement(nist->FindOrBuildElement("Si"), 3);
	Si3N4Mat->AddElement(nist->FindOrBuildElement("N"), 4);
	// Define optical properties
	G4MaterialPropertiesTable* mptSi3N4 = new G4MaterialPropertiesTable();
	G4double energySi3N4[2] = {400*eV, 1000*eV}; // Define photon energy range
	//G4double rindexSi3N4[2] = {2.05, 2.05};      // Example refractive index values
	G4double absLengthSi3N4[2] = {4.08*mm, 4.08*mm}; // Absorption length in mm
	// Define photon energies in eV
	const G4int numEntries = 10;
	G4double photonEnergy[numEntries] = {
		4.465*eV, 3.79*eV, 3.115*eV, 2.647*eV, 2.18*eV,
		1.712*eV, 1.245*eV, 0.8294*eV, 0.5178*eV, 0.3619*eV};
	// Corresponding refractive indices
	G4double refractiveIndex[numEntries] = {
		1.8721213170359, 1.9110346794217, 1.943231277958, 1.9619062604624, 1.9778699738446,
		1.9917473810267, 2.0050993473208, 2.0222778887066, 2.0590472271639, 2.1244526847835};
	// Add properties to the material properties table
	mptSi3N4->AddProperty("RINDEX", photonEnergy, refractiveIndex, numEntries);
	mptSi3N4->AddProperty("ABSLENGTH", energySi3N4, absLengthSi3N4, 2);
	// Assign the properties table to the material
	Si3N4Mat->SetMaterialPropertiesTable(mptSi3N4);
	G4cout << "### - Silicon Nitride (Si3N4) defined" << G4endl;

    
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
  
}



G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
	
	if (fConstructed) {
		if (!G4RunManager::IfGeometryHasBeenDestroyed()) {
		  // Run manager hasn't cleaned volume stores. This code shouldn't execute
		  G4GeometryManager::GetInstance()->OpenGeometry();
		  G4PhysicalVolumeStore::GetInstance()->Clean();
		  G4LogicalVolumeStore::GetInstance()->Clean();
		  G4SolidStore::GetInstance()->Clean();
			}
			// Have to completely remove all lattices to avoid warning on reconstruction
			G4LatticeManager::GetLatticeManager()->Reset();
			// Clear all LogicalSurfaces
			// NOTE: No need to redefine the G4CMPSurfaceProperties
			G4CMPLogicalBorderSurface::CleanSurfaceTable();
	  }
	
	DefineMaterials();
	//////////////////
	// Construction //
	//////////////////

	//////////////////
	// World // Big Box with vacuum where the rest of parts are created, outside the cryostat vacuum avoids further modification of the particle trajectory
	G4double WorldL = 0.127*2.2; //((0.02+0.01+0.02)*2+0.006);
    G4Box *solidWorld = new G4Box("solidWorld", WorldL/2*m, WorldL/2*m, WorldL/2*m);
    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, VacuumMat, "logicWorld");
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);

	//////////////////
    // Define the cryostat as a cylinder. The cryostat is composed of 2 cylindrical alumimium capsules
    // *TODO: Radiator is a historical name for these components and has nothing to do with its current nature
    G4double innerRadius = 0.114338 * m;  // Cylinder with no inner radius (solid cylinder)
    G4double outerRadius = 0.114846* m; // Radius of the cylinder
    
    G4double innerRadiusShield2 = 0.124155 * m;  // Cylinder with no inner radius (solid cylinder)
    G4double outerRadiusShield2 = 0.127* m; // Radius of the cylinder
    
    G4double height = WorldL*m;    // Height of the cylinder
    G4double startAngle = 0.0 * deg; // Starting angle
    G4double spanningAngle = 360.0 * deg; // Full circle
    G4Tubs *solidRadiator = new G4Tubs("solidRadiator", innerRadius, outerRadius, height / 2, startAngle, spanningAngle);
    G4Tubs *solidRadiatorShield2 = new G4Tubs("solidRadiator2", innerRadiusShield2, outerRadiusShield2, height / 2, startAngle, spanningAngle);

    G4LogicalVolume *logicRadiator = new G4LogicalVolume(solidRadiator, AlMat, "logicalRadiator");
    G4LogicalVolume *logicRadiatorShield2 = new G4LogicalVolume(solidRadiatorShield2, AlMat, "logicalRadiator2");

    // Create a rotation matrix to rotate 90 degrees around the Z-axis
    G4RotationMatrix *rotation = new G4RotationMatrix();
    rotation->rotateX(90 * deg); // Rotate 90 degrees around the Y-axis
    // Place the cylinder with the rotation
    G4VPhysicalVolume *physRadiator = new G4PVPlacement(rotation, G4ThreeVector(0., 0., 0. * m), logicRadiator, "physRadiator", logicWorld, false, 0, true);
    G4VPhysicalVolume *physRadiator2 = new G4PVPlacement(rotation, G4ThreeVector(0., 0., 0. * m), logicRadiatorShield2, "physRadiator2", logicWorld, false, 0, true);

	//////////////////
	// Copper holder
	// Holder of the sensing device in L shaped copper. It is still unknown how exactly this is attached!!!
	solidCu1 = new G4Box("solidCu1", 6*mm/2, 6*mm/2-1*mm, 2*mm/2);
	logicCu1 = new G4LogicalVolume(solidCu1, CuMat, "logicCu1");
	physCu1 = new G4PVPlacement(0,G4ThreeVector(0.,0.,0.),logicCu1,"physCu1",logicWorld,false,0,true);
	solidCu2 = new G4Box("solidCu2", 6*mm/2, 2*mm/2, 6*mm/2);
	logicCu2 = new G4LogicalVolume(solidCu2, CuMat, "logicCu2");
	physCu2 = new G4PVPlacement(0,G4ThreeVector(0,3.,2),logicCu2,"physCu2",logicWorld,false,0,true);
	
	G4UserLimits* userLimits = new G4UserLimits();
	userLimits->SetMaxAllowedStep(0.1 * mm);
		
	//////////////////
	// Contact material btw the copper holder and the sensor (UNKNOWN!!!)
	G4double Sensor_z = -1 *mm;
	G4double Substrate_z = 0.5 * mm;
	G4double Sensor_x = 1 * mm;
	G4double Sensor_y = 1 * mm;
	G4Box *solidsubstrate = new G4Box("solidsubstrate", Sensor_x/2, Sensor_y/2, Substrate_z/2);
	logicsubstrate = new G4LogicalVolume(solidsubstrate, Si3N4Mat, "logicsubstrate");
	logicsubstrate->SetUserLimits(userLimits);
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
	// Protective layer over the sensor
	G4double SiO2_z = 40 * nm;
	G4Box *solid_SiO2toplayer = new G4Box("solid_SiO2toplayer", Sensor_x*mm/2, Sensor_y*mm/2, SiO2_z*mm/2);
	G4LogicalVolume *logic_SiO2toplayer = new G4LogicalVolume(solid_SiO2toplayer, SiO2, "logic_SiO2toplayer");
	logic_SiO2toplayer->SetUserLimits(userLimits);
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
	// Sensor
	G4double wire_z = 3 * nm;
	G4double wire_x = Sensor_x*0.9;
	G4double strip_thickness  = 2250 *nm;
	G4double strip_spacing = 1500 *nm;
	G4int num_strips = 240; // Number of strips
	G4UserLimits* userLimits1 = new G4UserLimits();
	userLimits1->SetMaxAllowedStep(0.05 * nm);
	
	/* // Testing code for a single strip geometry
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
	
	MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector",PassArgs);
	
	
	// Loop for the creation of the sensor and substrate in form of lines uniformly distributed
	for (G4int i = 0; i < num_strips; i++) {
		// Position along y for each strip, considering the thickness and the spacing
		G4double strip_y_pos = -(Sensor_y * 0.9 / 2) + i * (strip_thickness + strip_spacing); 

		// Create a strip solid with specified dimensions
		G4Box *solid_strip = new G4Box("solid_strip_" + std::to_string(i), Sensor_x * 0.9 / 2, strip_thickness / 2, wire_z * mm / 2);
		G4Box *solid_aSistrip = new G4Box("solid_strip_" + std::to_string(i), Sensor_x * 0.9 / 2, strip_thickness / 2, wire_z * mm / 2);

		// Create the logical volume for the strip
		logicDetector = new G4LogicalVolume(solid_strip, WSiMat, "logic_strip_" + std::to_string(i));
		G4LogicalVolume *logic_aSiStrip = new G4LogicalVolume(solid_strip, aSiMat, "logic_strip_" + std::to_string(i));
		
		logicDetector->SetUserLimits(userLimits1);
		logic_aSiStrip->SetUserLimits(userLimits1);
		
		logicDetector->SetSensitiveDetector(sensDet);

		// Place each strip with translation in the y-axis
		new G4PVPlacement(
			0, // No rotation
			G4ThreeVector(0, strip_y_pos, +SiO2_z/2-wire_z / 2), // Translation in y for each strip
			logicDetector,
			"phys_strip_" + std::to_string(i),
			logic_SiO2toplayer,
			false,
			i, // Unique copy number for each strip
			true
		);
		

		// Place each strip with translation in the y-axis
		new G4PVPlacement(
			0, // No rotation
			G4ThreeVector(0, strip_y_pos, +SiO2_z/2-wire_z-wire_z/2), // Translation in y for each strip
			logic_aSiStrip,
			"phys_aSistrip_" + std::to_string(i),
			logic_SiO2toplayer,
			false,
			i, // Unique copy number for each strip 
			true
		);		
	}
		
	//ConstructSDandField(); 

    // Define step size limit (1 nm)
    //G4double maxStep = 0.1 * nm;
    //G4UserLimits* userLimits = new G4UserLimits(maxStep);
    //logicDetector->SetUserLimits(userLimits);
    
    //maxStep = 0.1 * mm;
    //userLimits = new G4UserLimits(maxStep);
    //logicsubstrate->SetUserLimits(userLimits);
    
  fConstructed = true;
    
    
    return physWorld;
}
