#include "PortProcess.h"

#include "System/VM.h"

bool PortProcess::Execute(const std::vector<std::string>& _args)
{
	if (_args.size() != 1) return false;
	
	Port* _targetPort = VM::GetActiveNode()->GetPort(stoi(_args[0]));
	if (!_targetPort || _targetPort->GetType() != targetType) return false;
	_targetPort->Open();
	return true;
}
