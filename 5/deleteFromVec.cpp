#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

template<class T>
int test_deleteFromVec(std::vector<T> v, T value, std::vector<T> expected_res);
template<class T>
void print_vec(std::vector<T> v);

template<class T>
void deleteFromVec(std::vector<T> &vec, T value) 
{
    size_t deleted_amount = 0;
    auto is_value = [value](T i){ return i == value; };
    auto match = std::find(vec.begin(), vec.end(), value); 
    auto temp_end = match;
    while (true) {
        if (match == vec.end()) {
            break;
        }
        auto part_begin = std::find_if_not(match, vec.end(), is_value);
        deleted_amount += part_begin - match;
        if (part_begin == vec.end()) {
            break;
        }
        auto part_end = std::find(part_begin, vec.end(), value);
        while (part_begin != part_end) {
            *temp_end = *part_begin;
            temp_end++;
            part_begin++;
        }
        if (part_end == vec.end()) {
            break;
        }
        match = part_end;
    }

    vec.resize(vec.size() - deleted_amount);
    return;
}

int main(int argc, char const *argv[])
{
    std::vector<int> v1{3,1,2}, v1_exp{1,2};
    std::vector<int> v2{1,2,3}, v2_exp{1,2};
    std::vector<int> v3{3,1,2,3}, v3_exp{1,2};
    std::vector<int> v4{3,1,2,3,4,5,3}, v4_exp{1,2,4,5};
    std::vector<int> v5{3,3,1,2,3,3,4,5,3,3}, v5_exp{1,2,4,5};
    std::vector<int> v6{3,3,3}, v6_exp{};
    std::vector<int> v7{1,2}, v7_exp{1,2};

    test_deleteFromVec(v1, 3, v1_exp);
    test_deleteFromVec(v2, 3, v2_exp);
    test_deleteFromVec(v3, 3, v3_exp);
    test_deleteFromVec(v4, 3, v4_exp);
    test_deleteFromVec(v5, 3, v5_exp);
    test_deleteFromVec(v6, 3, v6_exp);
    test_deleteFromVec(v7, 3, v7_exp);

    return 0;
}

template<class T>
int test_deleteFromVec(std::vector<T> v, T value, std::vector<T> expected_res) 
{
    static int test_num = 0;
    test_num++;

    deleteFromVec(v, value);
    if (v != expected_res) {
        std::cout << "TEST " << test_num << " FAILED: " << std::endl;
        std::cout << "actual:   ";
        print_vec(v);
        std::cout << std::endl;
        std::cout << "expected: ";
        print_vec(expected_res);
        std::cout << std::endl;
    }
    return 0;
}

template<class T>
void print_vec(std::vector<T> v)
{
    for (auto it = v.begin(); it < v.end(); it++) {
        std::cout << *it << " ";
    }
}
