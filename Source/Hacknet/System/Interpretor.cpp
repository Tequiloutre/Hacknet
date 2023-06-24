#include "Interpretor.h"

#include "System/VM.h"
#include <vector>

using namespace std;

void Interpretor::Read(const std::string& _line)
{
	vector<string> _args;
	size_t _lastIndex = 0;
	
	size_t _index = _line.find_first_of(' ');
	while (_index  != string::npos)
	{
		_args.push_back(_line.substr(_lastIndex, _index - _lastIndex));
		_lastIndex = _index + 1;
		_index = _line.find_first_of(' ', _lastIndex);
	}
	_args.push_back(_line.substr(_lastIndex, _index));
	
	if (_args.empty()) return;
	
	const string _process = _args[0];
	_args.erase(_args.begin());
	VM::GetInstance()->Execute(_process, _args);
}
