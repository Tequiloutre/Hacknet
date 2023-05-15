#include "shutdown.h"

#include "../VM.h"

bool shutdown::Execute(const std::vector<std::string>& _args)
{
	if (!_args.empty()) return false;

	VM::Log("Shutting down...");
	VM::Shutdown();
	
	return true;
}
