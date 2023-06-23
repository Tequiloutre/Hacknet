#include "Folder.h"

#include "FileSystem/File.h"

using namespace nlohmann;
using namespace std;

Folder::Folder(const std::string& _name, const UserLevel _requiredLevel)
{
	name = _name;
	requiredLevel = _requiredLevel;
}

Folder::Folder(const std::string& _name, const std::vector<Folder*>& _folders, const UserLevel _requiredLevel)
{
	name = _name;
	folders = _folders;
	requiredLevel = _requiredLevel;
}

Folder::~Folder()
{
	for (const Folder* _folder : folders)
		delete _folder;
	folders.clear();

	for (const File* _file : files)
		delete _file;
	files.clear();
}

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

File* Folder::GetFileByName(const std::string& _fileName) const
{
	const size_t _count = files.size();
	for (size_t i = 0; i < _count; ++i)
	{
		if (files[i]->GetName() != _fileName) continue;
		return files[i];
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
	if (ContainsFolder(_folder->GetName()))
	{
		delete _folder;
		return;
	}
	_folder->SetParentFolder(this);
	folders.push_back(_folder);
}

void Folder::RemoveFolder(const Folder* _folder)
{
	if (!ContainsFolder(_folder->GetName())) return;
	const size_t _folderCount = folders.size();
	for (size_t i = 0; i < _folderCount; ++i)
	{
		if (folders[i] != _folder) continue;
		delete folders[i];
		folders.erase(folders.begin() + i);
	}
}

bool Folder::ContainsFile(const std::string& _fileName) const
{
	for (const File* _file : files)
		if (_file->GetName() == _fileName) return true;
	return false;
}

void Folder::AddFile(File* _file)
{
	if (ContainsFile(_file->GetName()))
	{
		delete _file;
		return;
	}
	files.push_back(_file);
}

void Folder::RemoveFile(const File* _file)
{
	const size_t _fileCount = files.size();
	for (size_t i = 0; i < _fileCount; ++i)
	{
		if (files[i] != _file) continue;
		delete files[i];
		files.erase(files.begin() + i);
		return;
	}
}

json Folder::ToJson()
{
	json _json;
	
	_json["name"] = name;
	
	const size_t _folderCount = folders.size();
	for (size_t i = 0; i < _folderCount; ++i)
		_json["folders"][i] = folders[i]->ToJson();

	const size_t _fileCount = files.size();
	for (size_t i = 0; i < _fileCount; ++i)
		_json["files"][i] = files[i]->ToJson();
	
	return _json;
}

Folder* Folder::FromJson(const json& _json)
{
	Folder* _folder = new Folder(_json["name"]);
	
	if (_json.contains("folders"))
	{
		const vector<json> _foldersJson = _json["folders"];
    	const size_t _folderCount = _foldersJson.size();
    	for (size_t i = 0; i < _folderCount; ++i)
    		_folder->AddFolder(FromJson(_foldersJson[i]));
	}

	if (_json.contains("files"))
	{
		const vector<json> _filesJson = _json["files"];
		const size_t _fileCount = _filesJson.size();
		for (size_t i = 0; i < _fileCount; ++i)
			_folder->AddFile(File::FromJson(_filesJson[i]));
	}
	
	return _folder;
}
