#ifndef ACTION_HH
#define ACTION_HH

#include "G4VUserActionInitialization.hh"

#include "generator.hh"
#include "run.hh"
#include "event.hh"


class MyActionInitialization : public G4VUserActionInitialization
{
public:
    MyActionInitialization(MyG4Args*);
    ~MyActionInitialization();
    
    virtual void Build() const;
private:
    // String to specify the output name
    G4String OutputName;
    // Pointer to MyG4Args for passing arguments
    MyG4Args* PassArgs;
};

#endif
