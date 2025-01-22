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
    MyPrimaryGenerator *generator = new MyPrimaryGenerator(PassArgs);
    SetUserAction(generator);
    
    // Actions performed at begining and end of a run
    MyRunAction *runAction = new MyRunAction(PassArgs);
    SetUserAction(runAction);
    
    // Actions at the begining and end of each event in a runs
    MyEventAction *eventAction = new MyEventAction(runAction,PassArgs);
    SetUserAction(eventAction);
    
}
