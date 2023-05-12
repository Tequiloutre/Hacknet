#include "VM.h"

int main(int argc, char* argv[])
{
	VM::Start();

	while (VM::IsOn())
	{
		VM::Update();
	}
	
    return 0;
}
