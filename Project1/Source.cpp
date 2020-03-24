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
    std::cout << "1) Generated: ";
    print_vector(v);

    // 2)
    /*std::istream_iterator<int> intReader(std::cin);
    std::istream_iterator<int> intReaderEOF;
    std::copy(intReader, intReaderEOF, back_inserter(v));*/

    // 3)
    std::default_random_engine dre;
    std::shuffle(v.begin(), v.end(), dre);
    std::cout << "3) Shuffling: ";
    print_vector(v);

    // 4)
    sort(v.begin(), v.end());
    auto pos = unique(v.begin(), v.end());
    v.erase(pos, v.end());
    std::cout << "4) Unique: ";
    print_vector(v);

    // 5)
    std::cout << "5) Quantity of odd numbers: ";
    std::cout << count_if(v.begin(), v.end(),
                        [](int elem) {
                            return (elem % 2 == 1);
                        }) << '\n';

    // 6)
    std::cout << "6) ";
    std::cout << "min: " << *min_element(v.begin(), v.end());
    std::cout << "; max: " << *max_element(v.begin(), v.end()) << '\n';
	
    // 7)
    auto it = find_if(v.begin(), v.end(), Prime());
    std::cout << "7) ";
    if (v.cend() != it)
        std::cout << "prime: " << *it << '\n';
    else
        std::cout << "there are no prime numbers in the range\n";

    // 8)
    transform(v.cbegin(), v.cend(), v.begin(), Power_2());
    std::cout << "8) Powered: ";
    print_vector(v);
    
    // 9)
    std::vector<int> v2;
    std::uniform_int_distribution<> dr(1, 150);
    std::generate_n(back_inserter(v2), v.size(), 
        [&dr, &dre]() {
            return dr(dre);
        });
    std::cout << "9) Created random sequence: ";
    print_vector(v2);

    // 10)
    std::cout << "10) sum = " << std::accumulate(v2.cbegin(), v2.cend(), 0) << '\n';
    
    // 11)
    std::uniform_int_distribution<> dr2(1, v2.size() / 3 * 2);
    int amount = dr2(dre);
    std::fill_n(v2.begin(), amount, 1);
    std::cout << "11) replaced with 1: ";
    print_vector(v2);

    // 12)
    std::vector<int> v3;
    std::transform(v.begin(), v.end(), v2.begin(), std::back_inserter(v3), [](int& elem1, int& elem2) {
        return elem1 - elem2;
        });
    std::cout << "12) difference: ";
    print_vector(v3);

    // 13)
    std::replace_if(v3.begin(), v3.end(), [](const int& elem) {return elem < 0; }, 0);
    std::cout << "13) zero: ";
    print_vector(v3);

    // 14)
    v3.erase(std::remove_if(v3.begin(), v3.end(), [](auto x) {
        return x == 0;
        }), v3.end());
    std::cout << "14) erazed: ";
    print_vector(v3);

    // 15)
    std::reverse(v3.begin(), v3.end());
    std::cout << "15) reversed: ";
    print_vector(v3);

    // 16)
    std::nth_element(v3.begin(), std::next(v3.begin(), 2), v3.end(), std::greater<int>());
    std::cout << "16) Three greatest elements are: " << v3[0]
        << ' ' << v3[1] << ' ' << v3[2] << '\n';

    // 17)
    std::sort(v.begin(), v.end());
    std::sort(v2.begin(), v2.end());
    std::cout << "17) Sorted:\n";
    print_vector(v);
    print_vector(v2);

    // 18)
    std::vector<int> v4;
    std::merge(v.begin(), v.end(), v2.begin(), v2.end(), std::back_inserter(v4));
    std::cout << "18) Merged: ";
    print_vector(v4);

    // 19)
    auto range = std::equal_range(v4.begin(), v4.end(), 1);
    std::cout << "19) Range for insert: " << *range.first << ' ' << *range.second << '\n';

    // 20)
    std::cout << "20)\n";
    print_vector(v);
    print_vector(v2);
    print_vector(v3);
    print_vector(v4);
	return 0;
}