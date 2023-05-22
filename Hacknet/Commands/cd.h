#pragma once
#include "../Process.h"
#include "../FileSystem/Folder.h"

class cd : public Process
{
public:
	
	cd()
	{
		name = "cd";
	}

	bool Execute(const std::vector<std::string>& _args) override;

private:
	static Folder* GetChildFolder(const std::string& _targetFolderName);
	static Folder* GetParentFolder();
	static void GoToFolder(Folder* _targetFolder);
};
