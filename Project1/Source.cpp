#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <cstdlib>
#include <cmath>


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
    //std::istream_iterator<int> intReader(std::cin);
    //std::istream_iterator<int> intReaderEOF;
    std::ostream_iterator<int> intWriter(std::cout, " ");

    std::vector<int> v;

    // создание последовательности:
    std::generate_n(back_inserter(v), 10, IntSequence(1));

    // добавка в конец из cin:
    //std::copy(intReader, intReaderEOF, back_inserter(v));

    // перемешивание:
    std::random_shuffle(v.begin(), v.end());
    std::copy(v.begin(), v.end(), intWriter);
    std::cout << '\n';

    // удаление дубликатов:
    std::sort(v.begin(), v.end());
    auto pos = std::unique(v.begin(), v.end());
	std::copy(v.begin(), pos, intWriter);
    std::cout << '\n';

    // подсчет нечетных:
    std::cout << "quantity of odd numbers: ";
    std::cout << count_if(v.begin(), v.end(),
                        [](int elem) {
                            return (elem % 2 == 1);
                        }) << '\n';

    // Нахождение минимального и максимального значения:
    std::cout << "min: " << *min_element(v.begin(), v.end()) << '\n';
    std::cout << "max: " << *max_element(v.begin(), v.end()) << '\n';
	
    // Нахождение простого числа:
    std::cout << "prime: " << *find_if(v.begin(), v.end(), Prime()) << '\n';

    // Возведение в квадрат:
    transform(v.cbegin(), v.cend(), v.begin(), Power_2());
    std::copy(v.cbegin(), v.cend(), intWriter);
    std::cout << '\n';

	return 0;
}