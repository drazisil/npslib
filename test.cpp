#include "NPSLib.cpp"

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <test_name>" << std::endl;
        return 1;
    }

    std::string test_name = argv[1];

    if (test_name == "test_say_hello") {
        // Call a function from the library to test its functionality
        say_hello();
    } else if (test_name == "test_pack") {
        // Example usage of NPS_Pack for packing
        NPS_Pack packer;
        unsigned char buffer[1024];
        char packcode[] = "bclp";
        void *p4 = nullptr;
        void *p5 = nullptr;
        int result = packer.pack(buffer, sizeof(buffer), packcode, p4, p5);
        if (result < 0) {
            std::cerr << "Packing failed with error code: " << result << std::endl;
        } else {
            std::cout << "Packing succeeded, packed size: " << result << std::endl;
        }
    } else if (test_name == "test_unpack") {
        // Example usage of NPS_Pack for unpacking
        NPS_Pack packer;
        _NPS_CommData commData;
        unsigned char data[1024];
        char unpackCode[] = "bclp";
        int result = packer.unpack(&packer, data, sizeof(data), unpackCode, &commData);
        if (result < 0) {
            std::cerr << "Unpacking failed with error code: " << result << std::endl;
        } else {
            std::cout << "Unpacking succeeded, unpacked size: " << result << std::endl;
        }
    } else {
        std::cerr << "Unknown test: " << test_name << std::endl;
        return 1;
    }

    return 0;
}