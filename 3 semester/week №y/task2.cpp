#include <iostream>
#include <sstream>
#include <string>
#include <cctype> // для isdigit и isspace

class numfilterbuf : public std::streambuf {
private:
    std::istream *in;
    std::ostream *out;
    int cur;

protected:
    /* функции записи в поток: */
    virtual int overflow(int c) override {
        if (c == EOF) return EOF;
        if (out) {
            out->put(c);
            if (!(*out)) return EOF;
        }
        return c;
    }

	/* функции чтения из потока: */
	
	//реализация по-умолчанию инкрементирует позицию указателя в буфере и вызывает segmentation fault

    virtual int underflow() override {
        if (cur != EOF) return cur;
        if (!in) return EOF;

        int c;
        while ((c = in->get()) != EOF) {
            if (isdigit(c) || isspace(c)) {
                cur = c;
                return cur;
            }
        }
        return EOF;
    }


    virtual int uflow() override {
        if (underflow() == EOF) return EOF;
        int r = cur;
        cur = EOF;
        return r;
    }

public:
    numfilterbuf(std::istream &_in, std::ostream &_out)
        : in(&_in), out(&_out), cur(traits_type::eof())
    {}
};

int main() {
    const char str1[] = "In 4 bytes contains 32 bits";
    const char str2[] = "Unix time starts from Jan 1, 1970";
    std::istringstream str(str1);

	numfilterbuf buf(str, std::cout); // читать из stringstream, выводить в консоль
	std::iostream numfilter(&buf); // таким образом обходимся без реализации своего наследника iostream


    std::string val;
    std::getline(numfilter, val);
    numfilter.clear();// сбросить невалидное состояние после EOF в процессе чтения из stringstream

    std::cout << "Original: '" << str1 << "'" << std::endl;
    std::cout << "Read from numfilter: '" << val << "'" << std::endl;

    std::cout << "Original: '" << str2 << "'" << std::endl;
    std::cout << "Written to numfilter: '";
    numfilter << str2;
    std::cout << "'" << std::endl;

    return 0;
}
