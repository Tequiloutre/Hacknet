#include "Commands.h"

#include "Network/WAN.h"
#include "System/VM.h"

using namespace std;

bool cd::Execute(const std::vector<std::string>& _args)
{
	if (_args.size() != 1) return false;
	
	const std::string& _target = _args[0];

	if (_target == "..")
	{
		Folder* _parentFolder = GetParentFolder();
		if (_parentFolder == nullptr) return false;
		GoToFolder(_parentFolder);
		return true;
	}

	Folder* _targetFolder = GetChildFolder(_target);
	if (_targetFolder == nullptr) return false;
	GoToFolder(_targetFolder);
	return true;
}
Folder* cd::GetChildFolder(const std::string& _targetFolderName)
{
	const Folder* _activeFolder = VM::GetActiveFolder();
	return _activeFolder->GetFolderByName(_targetFolderName);
}
Folder* cd::GetParentFolder()
{
	const Folder* _activeFolder = VM::GetActiveFolder();
	return _activeFolder->GetParentFolder();
}
void cd::GoToFolder(Folder* _targetFolder)
{
	VM::SetActiveFolder(_targetFolder);
}

bool connect::Execute(const std::vector<std::string>& _args)
{
	const size_t _length = _args.size();
	if (_length != 1) return false;

	const string& _targetIP = _args[0];	
	Node* _targetNode = WAN::GetNode(_targetIP);
	if (!_targetNode)
	{
		VM::Log("Can't find node : {}", _targetIP);
		return false;
	}

	VM::Connect(_targetNode);

	return true;
}

bool disconnect::Execute(const std::vector<std::string>& _args)
{
	if (!_args.empty()) return false;
	VM::Disconnect();
	return true;
}

bool ip::Execute(const std::vector<std::string>& _args)
{
	if (!_args.empty()) return false;
	VM::Log("eth0: {}", VM::GetActiveNode()->GetIP());
	return true;
}

bool ls::Execute(const std::vector<std::string>& _args)
{
	if (!_args.empty()) return false;

	const std::vector<Folder*> _folders = VM::GetActiveFolder()->GetFolders();
	const size_t _count = _folders.size();
	for (size_t i = 0; i < _count; ++i)
		VM::Log("{}", _folders[i]->GetName());
	
	return true;
}

bool probe::Execute(const std::vector<std::string>& _args)
{
	if (!_args.empty()) return false;
	const Node* _currentNode = VM::GetActiveNode();
	VM::Log("Available ports at : {}", _currentNode->GetName());
	const vector<Port*> _ports = _currentNode->GetPorts();
	const size_t _count = _ports.size();
	for (size_t i = 0; i < _count; ++i)
	{
		const Port* _port = _ports[i];
		VM::Log("{}\t\t{}\t\t{}", _port->GetNumber(), _port->ToString(), _port->IsOpened() ? "opened" : "closed");
	}
	VM::Log("Open ports needed for hack : {}", _currentNode->GetRequiredPorts());
	return true;
}

bool say::Execute(const std::vector<std::string>& _args)
{
	const size_t _length = _args.size();
	if (_length < 1) return false;

	string _message;
	for (size_t i = 0; i < _length; ++i)
		_message.append(_args[i] + ' ');

	VM::Log("{}", _message);

	return true;
}

bool shutdown::Execute(const std::vector<std::string>& _args)
{
	if (!_args.empty()) return false;
	
	VM::Shutdown();
	
	return true;
}


