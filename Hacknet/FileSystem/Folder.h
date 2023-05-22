#pragma once
#include <string>
#include <vector>

class Folder
{
	std::string name = "Folder";
	Folder* parentFolder = nullptr;
	std::vector<Folder*> folders;
	// std::vector<File*> files;

public:

	std::string GetName() const { return name; }
	Folder* GetParentFolder() const { return parentFolder; }
	std::vector<Folder*> GetFolders() const { return folders; }
	Folder* GetFolderByName(const std::string& _folderName) const;
	std::string GetPath() const;
	
	Folder(const std::string& _name);
	~Folder();

	void SetParentFolder(Folder* _parent);

	bool ContainsFolder(const std::string& _folderName) const;
	void AddFolder(Folder* _folder);
};
