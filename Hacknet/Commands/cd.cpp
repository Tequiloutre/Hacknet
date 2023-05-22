#include "cd.h"

#include "../VM.h"

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
