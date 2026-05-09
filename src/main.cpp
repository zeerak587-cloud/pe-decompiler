#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>

#pragma pack(push, 1)

struct IMAGE_DOS_HEADER {
    uint16_t e_magic;
    uint8_t  e_unused[58];
    uint32_t e_lfanew;
};

struct IMAGE_FILE_HEADER {
    uint16_t Machine;
    uint16_t NumberOfSections;
    uint32_t TimeDateStamp;
    uint32_t PointerToSymbolTable;
    uint32_t NumberOfSymbols;
    uint16_t SizeOfOptionalHeader;
    uint16_t Characteristics;
};

struct IMAGE_OPTIONAL_HEADER {
    uint16_t Magic;
    uint8_t  data[94]; // simplified
    uint32_t AddressOfEntryPoint;
};

struct IMAGE_NT_HEADERS {
    uint32_t Signature;
    IMAGE_FILE_HEADER FileHeader;
    IMAGE_OPTIONAL_HEADER OptionalHeader;
};

struct IMAGE_SECTION_HEADER {
    char Name[8];
    uint32_t VirtualSize;
    uint32_t VirtualAddress;
    uint32_t SizeOfRawData;
    uint32_t PointerToRawData;
    uint8_t  rest[16];
};

#pragma pack(pop)

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: peparser <file.exe>\n";
        return 1;
    }

    std::ifstream file(argv[1], std::ios::binary);
    if (!file) {
        std::cout << "Failed to open file\n";
        return 1;
    }

    std::vector<uint8_t> buffer((std::istreambuf_iterator<char>(file)), {});

    auto dos = (IMAGE_DOS_HEADER*)buffer.data();

    if (dos->e_magic != 0x5A4D) {
        std::cout << "Not a valid PE file\n";
        return 1;
    }

    auto nt = (IMAGE_NT_HEADERS*)(buffer.data() + dos->e_lfanew);

    std::cout << "Entry Point: 0x" 
              << std::hex << nt->OptionalHeader.AddressOfEntryPoint << "\n";

    auto section = (IMAGE_SECTION_HEADER*)((uint8_t*)&nt->OptionalHeader + nt->FileHeader.SizeOfOptionalHeader);

    for (int i = 0; i < nt->FileHeader.NumberOfSections; i++) {
        std::string name(section[i].Name, 8);

        std::cout << "Section: " << name << "\n";

        if (name.find(".text") != std::string::npos) {
            std::cout << "  -> Found code section!\n";
            std::cout << "  Raw size: " << section[i].SizeOfRawData << "\n";
        }
    }

    return 0;
}
