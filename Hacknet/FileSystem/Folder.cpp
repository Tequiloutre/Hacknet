#include "Folder.h"

using namespace std;

std::string Folder::GetPath() const
{
	string _path = name;
	const Folder* _parentFolder = parentFolder;
	while (_parentFolder != nullptr)
	{
		_path = _parentFolder->GetName() + '/' + _path;
		_parentFolder = _parentFolder->GetParentFolder();
	}
	return _path;
}

Folder::Folder(const std::string& _name, Folder* _parentFolder)
{
	name = _name;
	parentFolder = _parentFolder;
}

Folder::~Folder()
{
	std::vector<Folder*>().swap(folders);
}

void Folder::SetParentFolder(Folder* _parent)
{
	parentFolder = _parent;
}

bool Folder::ContainsFolder(const std::string& _folderName) const
{
	for (const Folder* _folder : folders)
		if (_folder->GetName() == _folderName) return true;
	return false;
}

void Folder::AddFolder(Folder* _folder)
{
	if (ContainsFolder(_folder->GetName())) return;
	_folder->SetParentFolder(this);
	folders.push_back(_folder);
}
