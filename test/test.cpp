#include "CppUnitTest.h"

#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <chrono>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <random>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace all_tests
{

	bool prime(int n) {
		int m = n / 2;

		for (auto i = 2; i < m; ++i) {
			if (n % i == 0)
				return false;
		}
		return true;
	}

	TEST_CLASS(test_v10)
	{
	public:
		TEST_METHOD(test_01)
		{
			std::stringstream ss("14 -78 22");
			std::vector<int> v;
			std::istream_iterator<int> input(ss);
			std::copy(input, std::istream_iterator<int>(),back_inserter(v));
			Assert::AreEqual(3ull, v.size());
			Assert::AreEqual(14, v[0]);
			Assert::AreEqual(-78, v[1]);
			Assert::AreEqual(22, v[2]);

		}

		TEST_METHOD(test_02a)
		{
			std::vector<int> v(10);
			//fill_n(v.begin(), v.end(), );
			std::iota(v.begin(), v.end(), 1);
			std::generate(v.begin(), v.end(), [] {static int i = 0; return ++i; });
			Assert::AreEqual(10ull, v.size());
			Assert::IsTrue(std::is_sorted(v.cbegin(), v.cend()));
			Assert::AreEqual(1, v[0]);
			Assert::AreEqual(10, v[9]);
		}
		TEST_METHOD(test_02b)
		{
			std::vector<int> v(10);
			std::generate(v.begin(), v.end(), [] {static int i = -1; return i += 2; });
			Assert::IsTrue(std::is_sorted(v.cbegin(), v.cend()));
			Assert::IsTrue(v.cend() == std::adjacent_find(v.cbegin(), v.cend(), [](int a, int b) { return b - a != 2;  }));
			Assert::AreEqual(1, v[0]);
			Assert::AreEqual(19, v[9]);
		}

		TEST_METHOD(test_03a)
		{
			std::vector<int> v = { 1, 5, 10 };
			std::transform(v.begin(), v.end(),v.begin(), [](int n) {return pow(n, 3); });
			Assert::AreEqual(3ull, v.size());
			Assert::AreEqual(1, v[0]);
			Assert::AreEqual(125, v[1]);
			Assert::AreEqual(1000, v[2]);
		}
		TEST_METHOD(test_03b)
		{
			int x[] = { 3, 5, 10 };
			std::vector<int> y = { 4, 12, 10 };
			std::vector<double> d;
			std::transform(y.begin(), y.end(), x, std::back_inserter(d),
				[](unsigned int x, unsigned int y) {return hypot(x, y); });
			Assert::AreEqual(3ull, d.size());
			Assert::AreEqual(5., d[0]);
			Assert::AreEqual(13., d[1]);
			Assert::AreEqual(sqrt(200), d[2]);
		}

		TEST_METHOD(test_04a)
		{
			std::stringstream ss("1.5 2.5 3.5");
			std::istream_iterator<double> input(ss);
			auto res = std::accumulate(input, std::istream_iterator<double>(), 0.0); 
			Assert::AreEqual(7.5, res);
		}
		TEST_METHOD(test_04b)
		{
			std::vector<std::string> v{ "V", "S", "I", "T", "E", "!" };
			std::string s{ "GO " };
			auto res = std::accumulate(v.begin(), v.end(), s);
			Assert::AreEqual("GO VSITE!", res.c_str());
		}
		TEST_METHOD(test_04c)
		{
			struct person { std::string name; int age; };
			std::vector<person> v{ {"Pero", 33}, {"Iva", 25} };
			auto total_age = std::accumulate(v.begin(), v.end(), 0, [](int all_ages, const person& p) {return all_ages += p.age; });
			Assert::AreEqual(58, total_age);
		}

		TEST_METHOD(test_05a)
		{
			std::vector<int> v{ -5, 8, 11, 0, -9, 77, -4 };
			auto number_of_negative = std::count_if(v.begin(), v.end(), [](int i) {return i < 0; });
			Assert::AreEqual(3ll, number_of_negative);
		}
		TEST_METHOD(test_05b)
		{
			std::vector<double> v{ 1.5, 8, -11.23, 0, 1e10, 1e10, 1e10, 0, 99 };
			auto number_of_invalid = std::count(v.begin(), v.end(), 1e10);
			Assert::AreEqual(3ll, number_of_invalid);
		}
		TEST_METHOD(test_05c)
		{
			struct point { int x, y; };
			std::vector<point> v{ {1,1}, {-5,3}, {2,2}, {-7,-6}, {9,-4} };
			auto number_in_first_quadrant = std::count_if(v.begin(), v.end(), [](const point& p) {
				return (p.x > 0 && p.y > 0); });
			Assert::AreEqual(2ll, number_in_first_quadrant);
		}

		TEST_METHOD(test_06)
		{

			std::vector<int> v{ 33, 16, 24, 41, 25, 19, 9 };
			auto first_prime = *std::find_if(v.begin(), v.end(), prime);
			Assert::AreEqual(41, first_prime);
		}

		TEST_METHOD(test_07a)
		{
			std::vector<double> v{ 1e10, 8, -11.23, 0, 1e10, 1e10, 1e10, 0, 99 };
			std::replace(v.begin(), v.end(), 1e10, -1.0);
			Assert::AreEqual(-1., v[0]);
			Assert::AreEqual(-1., v[4]);
			Assert::AreEqual(-1., v[6]);
		}
		TEST_METHOD(test_07b)
		{
			std::string s("neisporuka");
			std::vector<char> v{ 'a','e','i','o','u','A','E','I','O','U'};
			std::replace_if(s.begin(), s.end(), [v](char& c) {if(std::find(v.begin(), v.end(), c) != v.end()) return true; }, 'x');
			Assert::AreEqual("nxxspxrxkx", s.c_str());
		}

		TEST_METHOD(test_08a)
		{
			std::vector<double> v{ 1e10, 8, -11.23, 0, 1e10, 1e10, 1e10, 0, 99 };
			v.erase(std::remove(v.begin(), v.end(),1e10) ,v.end());
			Assert::AreEqual(5ull, v.size());
			Assert::AreEqual(8., v[0]);
			Assert::AreEqual(99., v[4]);
		}
		TEST_METHOD(test_08b)
		{
			std::string s("poliuretan");
			std::vector<char> v{ 'a','e','i','o','u','A','E','I','O','U'};
			auto inex = std::remove_if(s.begin(), s.end(), [v](char c) {if (std::find(v.begin(), v.end(), c) != v.end()) return true;});
			s.erase(inex, s.end());
			Assert::AreEqual("plrtn", s.c_str());
		}

		TEST_METHOD(test_09)
		{
			struct exam { std::string name; int points, grade; };
			std::vector<exam> v{ {"Pero", 55, 2}, {"Iva", 93, 5}, {"Marko", 89, 5} };
			std::sort(v.begin(), v.end(), [](const exam& e1, const exam& e2) {
				if (e1.grade == e2.grade) { return (e1.points > e2.points); }
				else { return (e1.grade > e2.grade); }
				});
			Assert::AreEqual("Iva", v[0].name.c_str());
			Assert::AreEqual("Marko", v[1].name.c_str());
			Assert::AreEqual("Pero", v[2].name.c_str());

		}

		TEST_METHOD(test_10)
		{
			std::vector<double> v(2e7);
			// half of the values less than 1000
			std::generate(v.begin(), v.begin() + v.size() / 2, []() { return rand() % 1000; });
			// other half of the values greater than 1000
			std::generate(v.begin() + v.size() / 2, v.end(), []() { return 1001 + rand() % 1000; });
			v.push_back(1000); // to be median

			std::random_device rd;
			std::mt19937 g(rd());
			std::shuffle(v.begin(), v.end(), g);

			std::nth_element(v.begin(), v.begin() + v.size() / 2, v.end());
			Assert::AreEqual(1000., v[v.size() / 2]); // median value
		}

		TEST_METHOD(test_11)
		{
			std::vector<double> v{ 11, 0.5, -97.23, -23.11, 48.78, 22.96, -77 };
			auto smallest_value = *std::min_element(v.begin(), v.end());
			Assert::AreEqual(-97.23, smallest_value);
			auto largest_value = *std::max_element(v.begin(), v.end());
			Assert::AreEqual(48.78, largest_value);
		}

		TEST_METHOD(test_12)
		{
			std::vector<int> atp_points{ 8445, 7480, 6220, 5300, 5285 };
			std::sort(atp_points.begin(), atp_points.end());
			std::vector<int> diff;
			std::adjacent_difference(atp_points.begin(), atp_points.end(), std::back_inserter(diff));
			auto smallest_difference = *std::min_element(diff.begin(), diff.end());
			Assert::AreEqual(15, smallest_difference);
		}
	};
}
