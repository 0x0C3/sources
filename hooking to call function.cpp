typedef char(*deffunction)(char, char);

int Trampoline(char a, char b) {
    deffunction originalFunction = (deffunction)0xDEADBEEF;
    char res = originalFunction(a, b);
    return res;
}

int main() {


    // الحصول على مقبض العملية
    HANDLE process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, GetCurrentProcessId());

    // عنوان الخاص في 
    void* internalFunctionAddress = (void*)0xDEADBEEF;

    // تبديل العنواين الاولى للوظيفة الداخلية للقفز الى وظيفتنا "Trampoline"
    char hookjump[] = { 0xE9, 0x00, 0x00, 0x00, 0x00 };
    DWORD oldProtect;
    VirtualProtectEx(process, internalFunctionAddress, sizeof(hookjump), PAGE_EXECUTE_READWRITE, &oldProtect);
    DWORD trampolineAddress = (DWORD)Trampoline - (DWORD)internalFunctionAddress - 5;
    *(DWORD*)(hookjump + 1) = trampolineAddress;
    WriteProcessMemory(process, internalFunctionAddress, hookjump, sizeof(hookjump), NULL);
    VirtualProtectEx(process, internalFunctionAddress, sizeof(hookjump), oldProtect, &oldProtect);

    // استدعاء الوظيفة من خلال الترامبولين
    deffunction internalFunction = (deffunction)internalFunctionAddress;
    int result = internalFunction('A', 'B');
    std::cout << "res : " << result << std::endl;
    return 0;
}