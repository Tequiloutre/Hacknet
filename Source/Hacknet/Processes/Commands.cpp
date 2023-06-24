#include "Commands.h"

#include "FileSystem/File.h"
#include "FileSystem/Folder.h"
#include "Network/Node.h"
#include "Network/Port.h"
#include "Network/WAN.h"
#include "System/Account.h"
#include "System/Saver.h"
#include "System/VM.h"

using namespace std;

bool cat::Execute(const std::vector<std::string>& _args)
{
	if (_args.size() != 1) return false;

	const string& _targetFile = _args[0];
	const File* _file = VM::GetInstance()->GetActiveFolder()->GetFileByName(_targetFile);
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
	if (_args.size() != 1)
	{
		VM::Log("[cd] Usage : cd <path>");
		return false;
	}
	
	VM* _vm = VM::GetInstance();	
	const string& _target = _args[0];
	const Folder* _activeFolder = _vm->GetActiveFolder();
	
	Folder* _targetFolder;
	if (_target == "..") _targetFolder = _activeFolder->GetParentFolder();
	else _targetFolder = _activeFolder->GetFolderByName(_target);
	
	if (_targetFolder == nullptr)
	{
		VM::Log("[cd] Can't find directory : {}", _target);
		return false;
	}

	if (_targetFolder->GetRequiredLevel() > _vm->GetActiveNode()->GetUserLevel(_vm->GetActiveAccount()->GetUsername()))
	{
		VM::Log("[cd] You don't have permission to access : {}", _target);
		return false;
	}
	_vm->SetActiveFolder(_targetFolder);
	return true;
}

bool connect::Execute(const vector<string>& _args)
{
	if (_args.size() != 1)
	{
		VM::Log("[connect] Usage : connect <ip>");
		return false;
	}

	const string& _targetIP = _args[0];	
	Node* _targetNode = WAN::GetInstance()->GetNode(_targetIP);
	if (!_targetNode)
	{
		VM::Log("[connect] Can't find node at : {}", _targetIP);
		return false;
	}

	VM::GetInstance()->Connect(_targetNode);
	return true;
}

bool disconnect::Execute(const vector<string>& _args)
{
	if (!_args.empty()) return false;
	VM::GetInstance()->Disconnect();
	return true;
}

bool ip::Execute(const vector<string>& _args)
{
	if (!_args.empty()) return false;
	VM::Log("eth0: {}", VM::GetInstance()->GetActiveNode()->GetIP());
	return true;
}

bool ls::Execute(const vector<string>& _args)
{
	if (!_args.empty()) return false;

	const Folder* _activeFolder = VM::GetInstance()->GetActiveFolder();

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

bool mkdir::Execute(const vector<string>& _args)
{
	if (_args.empty()) return false;

	Folder* _activeFolder = VM::GetInstance()->GetActiveFolder();
	for (const string& _arg : _args)
		_activeFolder->AddFolder(new Folder(_arg));

	return true;
}

bool probe::Execute(const vector<string>& _args)
{
	if (!_args.empty()) return false;
	const Node* _currentNode = VM::GetInstance()->GetActiveNode();
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

	Folder* _folder = VM::GetInstance()->GetActiveFolder();
	for (const string& _arg : _args)
	{
		const File* _file = _folder->GetFileByName(_arg);
		if (!_file) continue;
		_folder->RemoveFile(_file);
	}

	return true;
}

bool rmdir::Execute(const std::vector<std::string>& _args)
{
	if (_args.empty()) return false;

	Folder* _activeFolder = VM::GetInstance()->GetActiveFolder();
	for (const string& _arg : _args)
	{
		const Folder* _folder = _activeFolder->GetFolderByName(_arg);
		if (!_folder) continue;
		_activeFolder->RemoveFolder(_folder);
	}

	return true;
}

bool save::Execute(const std::vector<std::string>& _args)
{
	Saver::SaveGame();
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
	
	VM::GetInstance()->Shutdown();
	
	return true;
}

bool touch::Execute(const vector<string>& _args)
{
	if (_args.empty()) return false;

	Folder* _folder = VM::GetInstance()->GetActiveFolder();
	for (const string& _arg : _args)
		_folder->AddFile(new File(_arg));

	return true;
}
