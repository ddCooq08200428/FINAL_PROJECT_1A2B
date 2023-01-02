#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <string.h>
#include <time.h>

using namespace std;
int* aas;
int* bbs;

class GuessMyNumber {
public:
	void GuessNumber() {
		rng = mt19937(random_device{}());
		for (int i = 0; i < 10000; i++) {
			stringstream os;
			os << setfill('0') << setw(4) << i;
			solutions.push_back(os.str());
		}
		solutions.erase(remove_if(solutions.begin(), solutions.end()
			,[](string& s) {
				for (int j = 0; j < 4; ++j)
					for (int k = 0; k < j; ++k)
						if (s[j] == s[k]) return true;
				return false;
			}), solutions.end());
	}

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

	void testsee(string testyyy)
	{
		srand(time(NULL));
		int bbb[4] = {0};
		int aaa[4] = { 0 };
		int wa = 0;
		int wb = 0;
		string pp = testyyy;
		char p[8];
		int i, j;
		for (int k = 0; k < 4; k++) {
			bbb[k] = rand() % 8999 + 1000;
		}
		for (i = 0; i < pp.length(); i++)
			p[i] = pp[i];
		for (i = 0; i < 4; i++){
			aaa[i] = (int)(p[i] - '0');
			if (aaa[i] == bbb[i]){
				wa++;
				bbb[i] = 99;
			}
		}
		for (i = 0; i < 4; i++){
			for (j = 0; j < 4; j++){
				if (aaa[i] == bbb[j])wb++;
			}
		}
		printf("%dA%dB\n", wa, wb);
		*aas = wa;
		*bbs = wb;
	}

	string guess() {
		uniform_int_distribution<>dis(0, size() - 1);
		my_guess = solutions[dis(rng)];
		return my_guess;
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
	mt19937 rng;
	string my_guess;
	vector<string> solutions;
};

int main()
{
	GuessMyNumber gn;
	string testiii;
	int maxguess = 8;
	int choice;



	cout << "請選擇要甚麼功能(1是我們猜，2是電腦猜，3是看電腦互猜，4是結束程式)" << endl;
	cin >> choice;
	while (choice != 4)
	{
		if (choice == 1)//自己猜數字
		{
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
			cout << "請選擇要甚麼功能(1是我們猜，2是電腦猜，3是看電腦互猜，4是結束程式)" << endl;
			cin >> choice;
		}
		else if (choice == 2)//電腦猜的程式
		{
			while (gn.size() > 0) {
				cout << gn.guess() << endl;
				cout << "? A ? B" << endl;
				int A, B;
				cin >> A >> B;

				gn.trim(A, B);
	
				if (gn.size()  == 1) {
					cout << "I got it!" << endl;
					break;
				}
				if (gn.size() == 0) {
					cout << "No way!" << endl;
					break;
				}	
			}
			cout << "請選擇要甚麼功能(1是我們猜，2是電腦猜，3是看電腦互猜，4是結束程式)" << endl;
			cin >> choice;
		}
		else if (choice == 3)
		{
			while (gn.size() > 1) {
				int A, B;
				aas = &A;
				bbs = &B;

				testiii = gn.guess();
				cout << testiii << endl;
				gn.testsee(testiii);

				gn.trim(A, B);
	
				if (A == 4) {
					cout << "I got it!" << endl;
					break;
				}
				if (gn.size() == 0) {
					cout << "No way!" << endl;
					break;
				}
			}
			cout << "請選擇要甚麼功能(1是我們猜，2是電腦猜，3是看電腦互猜，4是結束程式)" << endl;
			cin >> choice;
		}
		else
		{
			cout << "程式結束" << endl;
			break;
		}
	}
}
