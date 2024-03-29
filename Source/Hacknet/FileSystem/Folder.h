﻿#pragma once

#include <Network/UserLevel.h>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

class File;

class Folder
{
	std::string name;
	Folder* parentFolder = nullptr;
	std::vector<Folder*> folders;
	std::vector<File*> files;
	UserLevel requiredLevel = UserLevel::User;

public:

	Folder(const std::string& _name, UserLevel _requiredLevel = UserLevel::Guest);
	Folder(const std::string& _name, const std::vector<Folder*>& _folders, UserLevel _requiredLevel = UserLevel::Guest);
	~Folder();

	std::string GetName() const { return name; }
	Folder* GetParentFolder() const { return parentFolder; }
	std::vector<Folder*> GetFolders() const { return folders; }
	Folder* GetFolderByName(const std::string& _folderName) const;
	std::vector<File*> GetFiles() const { return files; }
	File* GetFileByName(const std::string& _fileName) const;
	std::string GetPath() const;
	UserLevel GetRequiredLevel() const { return requiredLevel; }

	void SetParentFolder(Folder* _parent);
	bool ContainsFolder(const std::string& _folderName) const;
	void AddFolder(Folder* _folder);
	void RemoveFolder(const Folder* _folder);
	bool ContainsFile(const std::string& _fileName) const;
	void AddFile(File* _file);
	void RemoveFile(const File* _file);

	nlohmann::json ToJson();
	static Folder* FromJson(const nlohmann::json& _json);
};
