#include "VM.h"

int main(int argc, char* argv[])
{
	srand(static_cast<unsigned int>(time(nullptr)));  // NOLINT(cert-msc51-cpp)
	
	VM::Start();

	while (VM::IsOn())
	{
		VM::Update();
	}
	
    return 0;
}
