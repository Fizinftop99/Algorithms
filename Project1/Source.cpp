#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <random>
#include <numeric>
#include <algorithm>
#include <iostream>
#include <vector>


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

void print_vector(const std::vector<int>& v) {
    std::ostream_iterator<int> intWriter(std::cout, " ");
    std::copy(v.cbegin(), v.cend(), intWriter);
    std::cout << '\n';
}

int main() {

    //1)
    std::vector<int> v;
    std::generate_n(back_inserter(v), 10, IntSequence(1));

    // 2)
    /*std::istream_iterator<int> intReader(std::cin);
    std::istream_iterator<int> intReaderEOF;
    std::copy(intReader, intReaderEOF, back_inserter(v));*/

    // 3)
    std::default_random_engine dre;
    std::shuffle(v.begin(), v.end(), dre);
    std::cout << "shuffling: ";
    print_vector(v);

    // 4)
    sort(v.begin(), v.end());
    auto pos = unique(v.begin(), v.end());
    v.erase(pos, v.end());
    std::cout << "unique: ";
    print_vector(v);

    // 5)
    std::cout << "quantity of odd numbers: ";
    std::cout << count_if(v.begin(), v.end(),
                        [](int elem) {
                            return (elem % 2 == 1);
                        }) << '\n';

    // 6)
    std::cout << "min: " << *min_element(v.begin(), v.end()) << '\n';
    std::cout << "max: " << *max_element(v.begin(), v.end()) << '\n';
	
    // 7)
    auto it = find_if(v.begin(), v.end(), Prime());
    if (v.cend() != it)
        std::cout << "prime: " << *it << '\n';
    else
        std::cout << "there are no prime numbers in the range\n";

    // 8)
    transform(v.cbegin(), v.cend(), v.begin(), Power_2());
    print_vector(v);
    
    // 9)
    std::vector<int> v2;
    std::uniform_int_distribution<> dr(1, 150);
    std::generate_n(back_inserter(v2), v.size(), 
        [&dr, &dre]() {
            return dr(dre);
        });
    std::cout << "Created random sequence: ";
    print_vector(v2);

    // 10)
    std::cout << "sum = " << std::accumulate(v2.cbegin(), v2.cend(), 0) << '\n';
    
    // 11)
    std::uniform_int_distribution<> dr2(1, v2.size() / 2);
    int amount = dr2(dre);
    std::fill_n(v2.begin(), amount, 1);
    std::cout << "replaced with 1: ";
    print_vector(v2);

    // 12)
    std::vector<int> v3;
    std::transform(v.begin(), v.end(), v2.begin(), std::back_inserter(v3), [](int& elem1, int& elem2) {
        return elem1 - elem2;
        });
    std::cout << "difference: ";
    print_vector(v3);

    // 13)
    std::replace_if(v3.begin(), v3.end(), [](const int& elem) {return elem < 0; }, 0);
    std::cout << "zero: ";
    print_vector(v3);

	return 0;
}