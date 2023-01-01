#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;
/*
class GuessNumber {
public:
	GuessNumber() {
		rng = mt19937(random_device{}());
		for (int i = 0; i < 10000; i++) {
			stringstream os;
			os << setfill('0') << setw(4) << i;
			solutions.push_back(os.str());
		}
		solutions.erase(remove_if(solutions.begin(), solutions.end(),
			[](string& s) {
				for (int j = 0; j < 4; ++j)
					for (int k = 0; k < j; ++k)
						if (s[j] == s[k]) return true;
				return false;
			}), solutions.end());
	}
	void trim(int A, int B) {
		string cur = my_guess;
		solutions.erase(remove_if(solutions.begin(), solutions.end(),
			[=](string& str) {
				int AA = A, BB = B;
				for (int j = 0; j < 4; ++j) {
					if (str[j] == cur[j]) --AA;
					for (int k = 0; k < 4; ++k)
						if (j != k && str[j] == cur[k]) --BB;
				}
				if (AA == 0 && BB == 0) return false;
				else return true;
			}), solutions.end());
	}
	string guess() {
		uniform_int_distribution<>dis(0, size() - 1);
		my_guess = solutions[dis(rng)];
		return my_guess;
	}
	size_t size() {
		return solutions.size();
	}
	void show() {
		for (auto s : solutions)
			cout << s << endl;
	}
private:
	mt19937 rng;
	string my_guess;
	vector<string> solutions;
};
int main()
{

	GuessNumber gn;

	while (gn.size() > 1) {
		cout << gn.guess() << endl;
		cout << "? A ? B" << endl;
		int A, B;
		cin >> A >> B;

		gn.trim(A, B);
		if (gn.size() < 10) {
			cout << "------" << endl;
			gn.show();
			cout << "------" << endl;
		}

		if (gn.size() == 1)
			cout << "I got it!" << endl;
		if (gn.size() == 0)
			cout << "No way!" << endl;
	}
}*/
class GuessMyNumber {
public:
	GuessMyNumber() {
		for (int i = 0; i < 10000; i++) {
			stringstream os;
			os << setfill('0') << setw(4) << i;
			solutions.push_back(os.str());
		}
		solutions.erase(remove_if(solutions.begin(), solutions.end(),
			[](string& s) {
				for (int j = 0; j < 4; ++j)
					for (int k = 0; k < j; ++k)
						if (s[j] == s[k]) return true;
				return false;
			}), solutions.end());
	}
	vector<string> trim(int A, int B, string cur) {
		vector<string> sols{ solutions };
		sols.erase(remove_if(sols.begin(), sols.end(),
			[=](string& str) {
				int AA = A, BB = B;
				for (int j = 0; j < 4; ++j) {
					if (str[j] == cur[j]) --AA;
					for (int k = 0; k < 4; ++k)
						if (j != k && str[j] == cur[k]) --BB;
				}
				if (AA == 0 && BB == 0) return false;
				else return true;
			}), sols.end());;
		return sols;
	}
	void set_solutions(vector<string>& sols){
		solutions = sols;
	}
	size_t size() {
		return solutions.size();
	}
	void show() {
		for (auto s : solutions)
			cout << s << endl;
	}
private:
	vector<string> solutions;
};

int main()
{
	GuessMyNumber gn;
	int maxguess = 8;


	while (gn.size() > 0) {
		cout << "Your guess: ";
		string guess;
		cin >> guess;
		vector<string> best_sols;
		int bestA = 0, bestB = 0;
		for (int A = 0; A <= 4; ++A) {
			for (int B = 0; B <= 4 - A; ++B) {
				vector<string> sols = gn.trim(A, B, guess);
				if (best_sols.size() < sols.size()) {
					best_sols = sols;
					bestA = A;
					bestB = B;
				}
			}
		}
		gn.set_solutions(best_sols);
		cout << bestA << "A" << bestB << "B" << endl;

		if (bestA == 4) {
			cout << "恭喜猜對了" << endl;
			break;
		}
		else if (gn.size() < 20) {
			cout << "-----" << endl;
			cout << "提示:" << endl;
			gn.show();
			cout << "-----" << endl;
		}
	}
}