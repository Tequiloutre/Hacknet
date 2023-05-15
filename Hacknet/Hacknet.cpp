#include "VM.h"
#include "Network/WAN.h"

int main(int argc, char* argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	// _CrtSetBreakAlloc(160);
	
	srand(static_cast<unsigned int>(time(nullptr)));  // NOLINT(cert-msc51-cpp)
	
	VM::StartUp();

	while (VM::IsOn())
	{
		VM::Update();
	}

	WAN::Destroy();

    return 0;
}
