#pragma once
#include <nlohmann/json.hpp>
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
	Folder(const std::string& _name, const std::vector<Folder*>& _folders);
	~Folder();

	void SetParentFolder(Folder* _parent);

	bool ContainsFolder(const std::string& _folderName) const;
	void AddFolder(Folder* _folder);

	nlohmann::json ToJson();
	static Folder FromJson(const nlohmann::json& _json);
};
