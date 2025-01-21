#ifndef MY_G4_ARGS_HH
#define MY_G4_ARGS_HH

#include <string>
#include <unordered_map>
#include <vector>
#include "G4String.hh"
#include "G4ThreeVector.hh" // For G4ThreeVector

class MyG4Args 
{
public:
    // Constructor and Destructor
    MyG4Args(int, char**);
    ~MyG4Args();
    
    struct G4StringHasher {
    std::size_t operator()(const G4String& key) const {
        return std::hash<std::string>()(key);
    }
};


    // Struct to store hit data
    struct HitData {
        G4double energyDeposit;
        G4ThreeVector position;
        G4double time;
        G4String particleType;
    };

    // Getter for the output name
    const G4String& GetOutName() const { return OutName; }

    // Function to add energy deposition to a particle type in the map
    void AddToEnergyByParticleAndEvent(const G4String& particleType, G4double energyDeposit, G4int eventNumber);

    // Function to add a hit record to the vector
    void AddHitRecord(const G4double energyDeposit, const G4ThreeVector& position, 
                      const G4double time, const G4String& particleType);

    // Getter for hit records
    const std::vector<HitData>& GetHitRecords() const { return hitRecords; }

    // Getter for total energy by particle type for a specific event
    const std::unordered_map<G4String, G4double, G4StringHasher>& GetTotalEnergyByParticleAndEvent(G4int eventNumber) const {
        return totalEnergyByParticleAndEvent.at(eventNumber);  // Access energy by event number
    }
    
	// Getter for total energy by particle type and event number
	const std::unordered_map<G4int, std::unordered_map<G4String, G4double, G4StringHasher>>& GetTotalEnergyByParticleAndEventAll() const {
		return totalEnergyByParticleAndEvent;  // Return the entire map
	}

    void ResetTotalEnergyByParticleAndEvent();

    
private:
    // Member variables
    G4String OutName;
    G4String MacName;    
    std::unordered_map<G4String, G4double, G4StringHasher> totalEnergyByParticle; // Total energy by particle type
        std::unordered_map<G4int, std::unordered_map<G4String, G4double, G4StringHasher>> totalEnergyByParticleAndEvent; // Energy by event and particle type
    std::vector<HitData> hitRecords; // Vector to store hit data
};
#endif
