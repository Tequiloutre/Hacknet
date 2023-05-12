#include "connect.h"

#include "../VM.h"
#include "../Network/WAN.h"

using namespace std;

bool connect::Execute(const std::vector<std::string>& _args)
{
	const size_t _length = _args.size();
	if (_length != 1) return false;

	string _targetIP = _args[0];	
	Node* _targetNode = nullptr;
	if (!WAN::GetNode(_targetIP, &_targetNode))
	{
		VM::Log("Can't find node : {}", _targetIP);
		return false;
	}

	VM::Connect(_targetNode);

	return true;
}
