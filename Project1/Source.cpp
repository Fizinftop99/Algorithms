#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <cstdlib>

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
    std::random_shuffle(v.begin(), v.end());
    std::sort(v.begin(), v.end());
    auto pos = std::unique(v.begin(), v.end());
    std::ostream_iterator<int> intWriter(std::cout, " ");
	std::copy(v.begin(), pos, intWriter);
    std::cout << std::count(v.begin(), v.end(),
                        [](int elem) {
                            return (elem%2==1);
                        });
	std::copy(v.begin(), v.end(), intWriter);
	return 0;
}