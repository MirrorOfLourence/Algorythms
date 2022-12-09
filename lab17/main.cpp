#include <string>
#include <stdio.h>
#include <chrono>

#include "externalmergesort.h"

// ������� ���� �� ���������� �������
void CreateFileWithRandomMember(const std::string& pathfile) {
    std::ofstream file(pathfile, std::ios::binary | std::ios::out);
    //file.unsetf(std::ios::skipws);
    if(!file.is_open()) {
        return;
    }
    for (int i = 1; i < 200000000; ++i) {
        int val = static_cast<int>(std::rand());
        file.write(reinterpret_cast<char *>(&val), sizeof(val));    
    }
    file.close();
}

int main(int argc, char *argv[]) {

    //CreateFileWithRandomMember("input");

    auto start_time = std::chrono::high_resolution_clock::now();

    std::string path("");
    std::string file_name_input(path + "input");
    std::string file_name_output(path + "output");
    // ������ ������ ������� �������. ��� ���������� ���������
    const size_t size_buf = (120 * 1024 * 1024) / sizeof(uint32_t);
    // ������� ���������� ��������
    ExternalMergeSort extMergeSort(size_buf, 2);
    extMergeSort.run(file_name_input);
    std::string sort_file_name = extMergeSort.getNameRezult();
    rename(sort_file_name.c_str(), file_name_output.c_str());

    auto end_time = std::chrono::high_resolution_clock::now();
    auto elapsed_ns = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    std::cout << elapsed_ns.count() << " ms\n";

    return 0;
}