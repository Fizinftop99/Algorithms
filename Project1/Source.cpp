#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <random>


class IntSequence {
private:
    int value;
public:
    IntSequence(int initialValue) : value(initialValue) { }

    int operator() () {               // "function call"
        return value++;
    }
};

class Prime {
public:
    bool operator()(int value) {
        if (value < 2) return false;
        for (int i = 2; i <= sqrt(value); i++)
            if (value % i == 0) return false;
        return true;
    }
};

class Power_2 {
public:
    int operator()(int value) {
        return (int)pow(value, 2);
    }
};

int main() {
    std::istream_iterator<int> intReader(std::cin);
    std::istream_iterator<int> intReaderEOF;
    std::ostream_iterator<int> intWriter(std::cout, " ");

    std::vector<int> v;

    //1)�������� ������������������:
    std::generate_n(back_inserter(v), 10, IntSequence(1));

    // 2)������� � ����� �� cin:
    std::copy(intReader, intReaderEOF, back_inserter(v));

    // 3)�������������:
    {
        std::default_random_engine dre;
        std::shuffle(v.begin(), v.end(), dre);
        std::cout << "shuffling: ";
        std::copy(v.begin(), v.end(), intWriter);
        std::cout << '\n';
    }

    // 4)�������� ����������:
    sort(v.begin(), v.end());
    auto pos = unique(v.begin(), v.end());
    v.erase(pos, v.end());
    std::cout << "unique: ";
	copy(v.begin(), v.end(), intWriter);
    std::cout << '\n';

    // 5)������� ��������:
    std::cout << "quantity of odd numbers: ";
    std::cout << count_if(v.begin(), v.end(),
                        [](int elem) {
                            return (elem % 2 == 1);
                        }) << '\n';

    // 6)���������� ������������ � ������������� ��������:
    std::cout << "min: " << *min_element(v.begin(), v.end()) << '\n';
    std::cout << "max: " << *max_element(v.begin(), v.end()) << '\n';
	
    // 7)���������� �������� �����:
    auto it = find_if(v.begin(), v.end(), Prime());
    if (v.cend() != it)
        std::cout << "prime: " << *it << '\n';
    else
        std::cout << "there are no prime numbers in the range\n";

    // 8)���������� � �������:
    transform(v.cbegin(), v.cend(), v.begin(), Power_2());
    std::copy(v.cbegin(), v.cend(), intWriter);
    std::cout << '\n';

	return 0;
}