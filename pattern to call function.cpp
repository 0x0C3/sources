typedef int(*InternalFunction)(int, int);

int main() {
    HANDLE process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, GetCurrentProcessId());


    // النمط المراد البحث عنه
    char pattern[] = { 0x69, 0x33, 0x13, 0x12, 0x40 };
    int patternlenght = sizeof(pattern) / sizeof(pattern[0]);

    void* startaddress = (void*)0x10000000;

    void* endAddress = (void*)0x50000000;

    int lem = (&startaddress - endAddress - patternlenght);
    //البحث عن الانماط عن ذاكرة البرنامج او العبة
    for (int i = 0; i < (lem); i++) {
        char* currentAddress = (char*)startaddress + i;
        bool found = true;

        // التحقق من النمط ان كان مطابق لعنوان للذاكرة

        for (int j = 0; j < patternlenght; j++) {
            if (*(currentAddress + j) != pattern[j]) {
                found = false;
                break;

        // ان عثرت على النمط اتصل في الوظيفة
                if (found) {
                    InternalFunction internalFunction = (InternalFunction)(currentAddress + patternlenght);
                    int res = internalFunction(6, 9);
                    std::cout << "res : " << res << std::endl;
                    break;
                }
            }
        }
    }
}