#include "PortProcess.h"

#include "Network/Node.h"
#include "Network/Port.h"
#include "System/VM.h"

PortProcess::PortProcess(const std::string& _name, const PortType _portType) : Process(_name)
{
	targetType = _portType;
}

bool PortProcess::Execute(const std::vector<std::string>& _args)
{
	if (_args.size() != 1) return false;
	
	Port* _targetPort = VM::GetInstance()->GetActiveNode()->GetPort(stoi(_args[0]));
	if (!_targetPort || _targetPort->GetType() != targetType) return false;
	_targetPort->Open();
	return true;
}
