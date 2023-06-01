#include "FileSystem/Folder.h"

using namespace std;
using namespace nlohmann;

Folder* Folder::GetFolderByName(const std::string& _folderName) const
{
	const size_t _count = folders.size();
	for (size_t i = 0; i < _count; ++i)
	{
		if (folders[i]->GetName() != _folderName) continue;
		return folders[i];
	}
	return nullptr;
}

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

Folder::Folder(const std::string& _name)
{
	name = _name;
}

Folder::Folder(const std::string& _name, const std::vector<Folder*>& _folders)
{
	name = _name;
	folders = _folders;
}

Folder::~Folder()
{
	for (const auto _folder : folders)
		delete _folder;
	folders.clear();
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

json Folder::ToJson()
{
	json _json;
	
	_json["name"] = name;
	
	const size_t _folderCount = folders.size();
	for (size_t i = 0; i < _folderCount; ++i)
		_json["folders"][i] = folders[i]->ToJson();
	
	return _json;
}

Folder Folder::FromJson(const json& _json)
{
	Folder _folder(_json["name"]);
	
	if (_json.contains("folders"))
	{
		const vector<json> _foldersJson = _json["folders"];
    	const size_t _folderCount = _foldersJson.size();
    	for (size_t i = 0; i < _folderCount; ++i)
    		_folder.AddFolder(new Folder(FromJson(_json["folders"][i])));
	}
	
	return _folder;
}
