#include "VM.h"
#include "Network/WAN.h"

int main(int argc, char* argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	// _CrtSetBreakAlloc(151);
	
	srand(static_cast<unsigned int>(time(nullptr)));  // NOLINT(cert-msc51-cpp)

	static VM vm;
	static WAN wan;

	VM::StartUp();

	while (VM::IsOn())
	{
		VM::Update();
	}

    return 0;
}
