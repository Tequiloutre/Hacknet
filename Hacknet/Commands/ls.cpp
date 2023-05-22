#include "ls.h"

#include "../VM.h"
#include "../FileSystem/Folder.h"

bool ls::Execute(const std::vector<std::string>& _args)
{
	if (!_args.empty()) return false;

	const std::vector<Folder*> _folders = VM::GetActiveFolder()->GetFolders();
	const size_t _count = _folders.size();
	for (size_t i = 0; i < _count; ++i)
		VM::Log("{}", _folders[i]->GetName());
	
	return true;
}
