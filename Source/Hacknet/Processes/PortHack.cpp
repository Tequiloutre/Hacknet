#include "PortHack.h"

#include "Network/Node.h"
#include "Network/User.h"
#include "System/Account.h"
#include "System/VM.h"

bool PortHack::Execute(const std::vector<std::string>& _args)
{
	if (!_args.empty())
	{
		VM::Log("[PortHack] Syntax : PortHack");
		return false;
	}

	Node* _activeNode = VM::GetInstance()->GetActiveNode();
	if (_activeNode->GetOpenedPorts() < _activeNode->GetRequiredPorts())
	{
		VM::Log("[PortHack] Not enough opened ports");
		return false;
	}

	const Account* _activeAccount = VM::GetInstance()->GetActiveAccount();
	_activeNode->AddUser(new User(_activeAccount->GetName(), _activeAccount->GetUsername(),
		_activeAccount->GetPassword(), UserLevel::Admin));
	return true;
}
