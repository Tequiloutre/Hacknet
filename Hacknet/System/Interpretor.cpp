#include "Interpretor.h"

#include <vector>
#include "VM.h"

using namespace std;

void Interpretor::Read(const std::string& _line)
{
	vector<string> _args = GetArgs(_line);
	if (_args.empty()) return;
	const string _process = _args[0];
	_args = vector(_args.begin() + 1, _args.end());
	VM::Execute(_process, _args);
}

std::vector<std::string> Interpretor::GetArgs(const std::string& _line)
{
	std::vector<std::string> _args;
	const size_t _length = _line.length();

	size_t _lastIndex = 0;
	for (size_t i = 0; i < _length; ++i)
	{
		if (_line[i] != ' ') continue;
		_args.push_back(_line.substr(_lastIndex, i - _lastIndex));
		_lastIndex = i + 1;
	}
	_args.push_back(_line.substr(_lastIndex, _length - _lastIndex));

	return _args;
}
