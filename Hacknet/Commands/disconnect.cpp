#include "disconnect.h"

#include "../VM.h"

bool disconnect::Execute(const std::vector<std::string>& _args)
{
	if (!_args.empty()) return false;
	VM::Disconnect();
	return true;
}
