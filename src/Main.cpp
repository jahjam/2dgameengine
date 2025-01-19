#include "Stage/Stage.h"
#include "easylogging++.h"

// This is to initialise the logger
// and only needs to be used one here
INITIALIZE_EASYLOGGINGPP

int main(int argc, char *argv[])
{
    el::Loggers::addFlag(el::LoggingFlag::ColoredTerminalOutput);
    Stage stage;

    stage.initialise_();
    stage.run_();
    stage.destroy_();

    return 0;
}
