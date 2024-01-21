#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <locale>
#include <codecvt>

int main() {

    std::locale::global(std::locale("pl_PL.UTF-8"));


    std::vector<std::wstring> names = {
        L"żubr", L"jeż", L"róża", L"jałowiec", L"świerk",
        L"szakal", L"różyca", L"łania", L"dzik", L"byk",
        L"czapla", L"bóbr", L"ananas", L"akacja", L"ślimak"
    };

    std::sort(names.begin(), names.end(), [](const std::wstring& a, const std::wstring& b) {
        return std::use_facet<std::collate<wchar_t>>(std::locale()).compare(
            a.data(), a.data() + a.size(),
            b.data(), b.data() + b.size()) < 0;
    });


    for (const auto& name : names) {
        std::wcout << name << std::endl;
    }

    return 0;
}
