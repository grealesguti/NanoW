#include "action.hh"

MyActionInitialization:: MyActionInitialization(MyG4Args *MainArgs)
{
// Saving output name
PassArgs=MainArgs;
OutputName=MainArgs->GetOutName();
}
MyActionInitialization::~MyActionInitialization()
{}

void MyActionInitialization::Build() const
{
    MyPrimaryGenerator *generator = new MyPrimaryGenerator();
    SetUserAction(generator);
    
    // Actions performed at begining and end of a run
    MyRunAction *runAction = new MyRunAction(PassArgs);
    SetUserAction(runAction);
}
