#include "action.hh"

MyActionInitialization::MyActionInitialization()
{}

MyActionInitialization::~MyActionInitialization()
{}

void MyActionInitialization::Build() const
{
    MyPrimaryGenerator *generator = new MyPrimaryGenerator();
    SetUserAction(generator);
    
    // Actions performed at begining and end of a run
    MyRunAction *runAction = new MyRunAction("Output");
    SetUserAction(runAction);
}
