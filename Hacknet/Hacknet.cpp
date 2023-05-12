#include "VM.h"

int main(int argc, char* argv[])
{
	srand(time(nullptr));
	
	VM::Start();

	while (VM::IsOn())
	{
		VM::Update();
	}
	
    return 0;
}
