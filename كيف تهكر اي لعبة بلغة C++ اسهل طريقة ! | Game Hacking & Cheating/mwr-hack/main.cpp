#include "includes.h"

uintptr_t baseAddr = (uintptr_t)GetModuleHandleA(0);

void commands()
{
	std::string input;

cmd:
	printf("Hack > ");
	std::getline(std::cin, input);
	printf("\n");

	if (input == "quit")
	{
		ExitProcess(0);
	}
	else if (input == "clear" || input == "cls")
	{
		system("cls");
		goto cmd;
	}
	else if (input == "ammo")
	{
		std::string option;
		printf("Enter Ammo Option (primary, secondary): ");
		std::getline(std::cin, option);
		printf("\n");

		if (option == "primary")
		{
			int ammo;
			printf("Enter Amount of Ammo: ");
			std::cin >> ammo;
			printf("\n");

			*(int*)(baseAddr + 0x73EDDCC) = ammo; // Magazine
			*(int*)(baseAddr + 0x73EDE98) = ammo; // Clip

			goto cmd;
		}
		else if (option == "secondary")
		{
			int ammo;
			printf("Enter Amount of Ammo: ");
			std::cin >> ammo;
			printf("\n");

			*(int*)(baseAddr + 0x73EDDB4) = ammo; // Magazine
			*(int*)(baseAddr + 0x73EDE68) = ammo; // Clip

			goto cmd;
		}
		else
		{
			printf("No Such Option.\n");
			goto cmd;
		}
	}
	else if (input == "ability")
	{
		std::string option;
		printf("Enter Option (1, 2, 3): ");
		std::getline(std::cin, option);
		printf("\n");

		if (option == "1")
		{
			int amount;
			printf("Enter Amount: ");
			std::cin >> amount;
			printf("\n");

			*(int*)(baseAddr + 0x73EDE80) = amount;

			goto cmd;
		}
		else if (option == "2")
		{
			int amount;
			printf("Enter Amount: ");
			std::cin >> amount;
			printf("\n");

			*(int*)(baseAddr + 0x73EDEB0) = amount;

			goto cmd;
		}
		else if (option == "3")
		{
			int amount;
			printf("Enter Amount: ");
			std::cin >> amount;
			printf("\n");

			*(int*)(baseAddr + 0x73EDEC8) = amount;

			goto cmd;
		}
		else
		{
			printf("No Such Option.\n");
			goto cmd;
		}
	}
	else
	{
		printf("No Such Command.\n");
		goto cmd;
	}
}

DWORD WINAPI console(LPVOID lp)
{
	AllocConsole();
	AttachConsole(GetCurrentProcessId());

	SetConsoleTitleA("MWR HACK"); // console title

	FILE* file;
	freopen_s(&file, "CONIN$", "r", stdin);
	freopen_s(&file, "CONOUT$", "w", stdout);
	freopen_s(&file, "CONOUT$", "w", stderr);

	commands();

	FreeLibraryAndExitThread((HMODULE)lp, 0);
}

static void Init()
{
	CreateThread(0, 0, console, 0, 0, 0);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		Init();
	}

	return TRUE;
}