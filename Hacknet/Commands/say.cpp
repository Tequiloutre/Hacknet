#include "say.h"

#include "../VM.h"

using namespace std;

bool say::Execute(const std::vector<std::string>& _args)
{
	const size_t _length = _args.size();
	if (_length < 1) return false;

	string _message;
	for (size_t i = 0; i < _length; ++i)
		_message.append(_args[i] + ' ');

	VM::Log("{}", _message);

	return true;
}
