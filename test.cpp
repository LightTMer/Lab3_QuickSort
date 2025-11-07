#include "pch.h"
#include "sort.h"
#include "CppUnitTest.h"
#include <vector>
#include <string>
#include <random>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SortTests
{
    template<typename T, typename Compare>
    bool is_sorted_range(const T* first, const T* last, Compare comp) {
        if (first == last) return true;
        const T* it = first;
        ++it;
        for (; it != last; ++it, ++first) {
            if (comp(*it, *first)) return false;
        }
        return true;
    }

    TEST_CLASS(QuickSortTests)
    {
    public:

        TEST_METHOD(SingleElement)
        {
            int a[] = { 42 };
            Sort(a, a + 1, [](int a, int b) { return a < b; });
            Assert::AreEqual(42, a[0]);
        }

        TEST_METHOD(AlreadySorted)
        {
            int a[] = { 1,2,3,4,5,6 };
            Sort(a, a + 6, [](int a, int b) { return a < b; });
            Assert::IsTrue(std::is_sorted(a, a + 6));
        }

        TEST_METHOD(ReverseSorted)
        {
            int a[] = { 6,5,4,3,2,1 };
            Sort(a, a + 6, [](int a, int b) { return a < b; });
            Assert::IsTrue(std::is_sorted(a, a + 6));
        }

        TEST_METHOD(AllEqual)
        {
            int a[] = { 5,5,5,5,5 };
            Sort(a, a + 5, [](int a, int b) { return a < b; });
            for (int i = 0; i < 5; ++i)
                Assert::AreEqual(5, a[i]);
        }

        TEST_METHOD(RandomIntArray)
        {
            std::vector<int> v(200);
            std::mt19937 rng(12345);
            std::uniform_int_distribution<int> dist(0, 1000);
            for (auto& x : v) x = dist(rng);

            std::vector<int> copy = v;
            Sort(v.data(), v.data() + v.size(), [](int a, int b) { return a < b; });
            std::sort(copy.begin(), copy.end());

            for (size_t i = 0; i < v.size(); ++i)
                Assert::AreEqual(copy[i], v[i]);
        }

        TEST_METHOD(Strings)
        {
            std::string a[] = { "pear","apple","orange","banana" };
            Sort(a, a + 4, [](const std::string& a, const std::string& b) { return a < b; });
            Assert::IsTrue(std::is_sorted(a, a + 4));
        }

        TEST_METHOD(CustomStruct)
        {
            struct Person { int id; std::string name; };
            Person arr[] = { {3,"C"}, {1,"A"}, {2,"B"}, {4,"D"} };
            Sort(arr, arr + 4, [](const Person& a, const Person& b) { return a.id < b.id; });
            for (int i = 0; i < 4; ++i)
                Assert::AreEqual(i + 1, arr[i].id);
        }

        TEST_METHOD(DescendingOrder)
        {
            int a[] = { 1, 3, 2, 5, 4 };
            Sort(a, a + 5, [](int a, int b) { return a > b; });
            Assert::IsTrue(std::is_sorted(a, a + 5, [](int a, int b) { return a > b; }));
        }

        TEST_METHOD(SmallArrayInsertionSort)
        {
            int a[] = { 4,2,5,3,1 };
            Sort(a, a + 5, [](int a, int b) { return a < b; });
            Assert::IsTrue(std::is_sorted(a, a + 5));
        }
    };
}