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
    //std::cout <<( 5 % 2) == 1;
    std::vector<int> v;
    // �������� ������������������
    std::generate_n(back_inserter(v), 10, IntSequence(1));
    // ������� � ����� �� cin
    std::istream_iterator<int> intReader(std::cin);
    std::istream_iterator<int> intReaderEOF;
    std::copy(intReader, intReaderEOF, back_inserter(v));
    // �������������
    std::random_shuffle(v.begin(), v.end());
    // �������� ����������
    std::sort(v.begin(), v.end());
    auto pos = std::unique(v.begin(), v.end());
    std::ostream_iterator<int> intWriter(std::cout, " ");
	std::copy(v.begin(), pos, intWriter);
    std::cout << '\n';
    // ������� ��������
    std::cout << count_if(v.begin(), v.end(),
                        [](int elem) {
                            return (elem%2==1);
                        }) << '\n';
    // ���������� ������������ � ������������� ��������
    std::cout << "min: " << *min_element(v.begin(), v.end()) << '\n';
    std::cout << "max: " << *max_element(v.begin(), v.end()) << '\n';
	
	return 0;
}