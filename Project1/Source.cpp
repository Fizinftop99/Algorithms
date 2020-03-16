#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

class IntSequence {
private:
    int value;
public:
    IntSequence(int initialValue) : value(initialValue) { }

    int operator() () {               // "function call"
        return value++;
    }
};

int main()
{
    std::vector<int> v;
    std::generate_n(back_inserter(v), 10, IntSequence(1));
    std::istream_iterator<int> intReader(std::cin);
    std::istream_iterator<int> intReaderEOF;
    std::copy(intReader, intReaderEOF, back_inserter(v));
    std::ostream_iterator<int> intWriter(std::cout, "\n");
	std::copy(v.cbegin(), v.cend(), intWriter);
	return 0;
}