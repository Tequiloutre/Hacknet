#include "Commands.h"

#include "Network/WAN.h"
#include "System/VM.h"

using namespace std;

bool cat::Execute(const std::vector<std::string>& _args)
{
	if (_args.size() != 1) return false;

	const string& _targetFile = _args[0];
	const File* _file = VM::GetActiveFolder()->GetFileByName(_targetFile);
	if (!_file)
	{
		VM::Log("cat : can't find {}", _targetFile);
		return false;
	}

	VM::Log(_file->GetContent());
	return true;
}

bool cd::Execute(const vector<string>& _args)
{
	if (_args.size() != 1) return false;
	
	const string& _target = _args[0];

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
Folder* cd::GetChildFolder(const string& _targetFolderName)
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

bool connect::Execute(const vector<string>& _args)
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

bool disconnect::Execute(const vector<string>& _args)
{
	if (!_args.empty()) return false;
	VM::Disconnect();
	return true;
}

bool ip::Execute(const vector<string>& _args)
{
	if (!_args.empty()) return false;
	VM::Log("eth0: {}", VM::GetActiveNode()->GetIP());
	return true;
}

bool ls::Execute(const vector<string>& _args)
{
	if (!_args.empty()) return false;

	const Folder* _activeFolder = VM::GetActiveFolder();

	const vector<Folder*> _folders = _activeFolder->GetFolders();
	const size_t _folderCount = _folders.size();
	for (size_t i = 0; i < _folderCount; ++i)
		VM::Log("{}/", _folders[i]->GetName());

	const vector<File*> _files = _activeFolder->GetFiles();
	const size_t _fileCount = _files.size();
	for (size_t i = 0; i < _fileCount; ++i)
		VM::Log("{}", _files[i]->GetName());
	
	return true;
}

bool probe::Execute(const vector<string>& _args)
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

bool rm::Execute(const std::vector<std::string>& _args)
{
	if (_args.empty()) return false;

	Folder* _folder = VM::GetActiveFolder();
	for (const string& _arg : _args)
	{
		const File* _file = _folder->GetFileByName(_arg);
		if (!_file) continue;
		_folder->RemoveFile(_file);
	}

	return true;
}

bool say::Execute(const vector<string>& _args)
{
	const size_t _length = _args.size();
	if (_length < 1) return false;

	string _message;
	for (size_t i = 0; i < _length; ++i)
		_message.append(_args[i] + ' ');

	VM::Log("{}", _message);

	return true;
}

bool shutdown::Execute(const vector<string>& _args)
{
	if (!_args.empty()) return false;
	
	VM::Shutdown();
	
	return true;
}

bool touch::Execute(const vector<string>& _args)
{
	if (_args.empty()) return false;

	Folder* _folder = VM::GetActiveFolder();
	for (const string& _arg : _args)
		_folder->AddFile(new File(_arg));

	return true;
}
