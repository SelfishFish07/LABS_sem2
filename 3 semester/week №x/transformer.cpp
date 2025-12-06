#include <iostream>
#include <string>
#include <cctype>
#include <iomanip>

template<typename ForwardIterator, typename UnaryOperation>
void transform_inplace(ForwardIterator first, ForwardIterator last, UnaryOperation op) {
    while (first != last) {
        op(*first);
        ++first;
    }
}

void to_uppercase_inplace(char& c) {
    c = std::toupper(static_cast<unsigned char>(c)); //преобразует строчный алфавит в заглавный
}

void transform_example(std::string word) {
    transform_inplace(word.begin(), word.end(), to_uppercase_inplace);
    std::cout << "word = " << std::quoted(word) << '\n';
}

int main() {
    transform_example("hello, world"); 
    return 0;
}