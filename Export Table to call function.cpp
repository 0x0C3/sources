typedef int(*InternalFunction)(int, int);

int main() {
    HANDLE process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, GetCurrentProcessId());


    // base address 
    HMODULE module = GetModuleHandle(NULL);


    // حصول على عنوان ال export directory
    PIMAGE_DOS_HEADER dosHeader = (PIMAGE_DOS_HEADER)module;
    PIMAGE_NT_HEADERS ntHeader = (PIMAGE_NT_HEADERS)((char*)module + dosHeader->e_lfanew); 
    PIMAGE_EXPORT_DIRECTORY exportDirectory = (PIMAGE_EXPORT_DIRECTORY)((char*)module + ntHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);

    // حصول على عنوان اسم الوظيفة
    unsigned int* functionNames = (unsigned int*)((char*)module + exportDirectory->AddressOfNames);
    CHAR* functionName = (CHAR*)((char*)module + functionNames[0]);

    // احصل على عنوان ال function ordinal array
    unsigned short* functionOrdinals = (unsigned short*)((char*)module + exportDirectory->AddressOfNameOrdinals);
    unsigned short functionOrdinal = functionOrdinals[0];

    // احصل على عنوان الوظيفة داخل العملية
    unsigned int* functionAddresses = (unsigned int*)((char*)module + exportDirectory->AddressOfFunctions);
    unsigned int functionAddress = functionAddresses[functionOrdinal];
    InternalFunction internalFunction = (InternalFunction)functionAddress;

    // الاتصال
    int res = internalFunction(6, 9);
    std::cout << "res : " << res << std::endl;

    return 0;
}