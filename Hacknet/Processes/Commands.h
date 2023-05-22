#pragma once

#include "../Processes/Process.h"

class Folder;

class cd : public Process
{
public:
	
	cd(const std::string& _name) : Process(_name) { }
	bool Execute(const std::vector<std::string>& _args) override;

private:
	
	static Folder* GetChildFolder(const std::string& _targetFolderName);
	static Folder* GetParentFolder();
	static void GoToFolder(Folder* _targetFolder);
};

class connect : public Process
{
public:

	connect(const std::string& _name) : Process(_name) { }
	bool Execute(const std::vector<std::string>& _args) override;
};

class disconnect : public Process
{
public:

	disconnect(const std::string& _name) : Process(_name) { }
	bool Execute(const std::vector<std::string>& _args) override;
};

class ls : public Process
{
public:

	ls(const std::string& _name) : Process(_name) { }
	bool Execute(const std::vector<std::string>& _args) override;
};

class say : public Process
{
public:

	say(const std::string& _name) : Process(_name) { }
	bool Execute(const std::vector<std::string>& _args) override;
};

class shutdown : public Process
{
public:

	shutdown(const std::string& _name) : Process(_name) { }
	bool Execute(const std::vector<std::string>& _args) override;
};
