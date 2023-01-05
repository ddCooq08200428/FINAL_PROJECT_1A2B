#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>
#include <string>
#include <algorithm>
#include <random>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

using namespace std;
int* aas;
int* bbs;
int flag = 0;



class GuessMyNumber {
public:

	void resetting() { //重新設定數值
		for (int i = 0; i < 10000; i++) { //利用迴圈跑過0到9999整數
			stringstream os; //整數寫入stringstream os
			os << setfill('0') << setw(4) << i; //設定格式為四個字元、不足的前面補零
			solutions.push_back(os.str()); //用 os.str() 取出已寫入 stream 中的字串，然後
										   //用 push_back 放入 vector solutions 中
			solutions.erase(remove_if(solutions.begin(), solutions.end(),
				[](string& s) {  //用 erase 搭配 remove_if過濾掉不符規定的(有重複數字的)字串
				for (int j = 1; j < 4; ++j)
					for (int k = 0; k < j; ++k)
						if (s[j] == s[k]) return true; //檢查一個字串當中，是否包含重複的數字，如果有的話就傳回 true        
				return false; //如果數字都不相同，就傳回 false。
			}), solutions.end()); //清除到原本的 end()，就會把那些該被過濾的元素從vector當中移除
		}
	}
	void GuessNumber() {
		rng = mt19937(random_device{}());
		for (int i = 0; i < 10000; i++) {
			stringstream os;
			os << setfill('0') << setw(4) << i;
			solutions.push_back(os.str());
		}
		solutions.erase(remove_if(solutions.begin(), solutions.end()
			, [](string& s) {
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

	void testsee(string testyyy, int testbbbiii[])
	{
		int aaa[4] = { 0 };
		int wa = 0;
		int wb = 0;
		string pp = testyyy;
		char p[8];
		int i, j;
		int bbb[4];
		for (i = 0; i < 4; i++)
		{
			bbb[i] = testbbbiii[i];
		}
		for (i = 0; i < pp.length(); i++)
			p[i] = pp[i];
		for (i = 0; i < 4; i++) {
			aaa[i] = (int)(p[i] - '0');
			if (aaa[i] == bbb[i]) {
				wa++;
				bbb[i] = 99;
			}
		}
		for (i = 0; i < 4; i++) {
			for (j = 0; j < 4; j++) {
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


	void set_solutions(vector<string>& sols) {
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
	vector<string> solutions; //用字串表達每個4位數，把可能數字放在vector裡
};



int main() {
	GuessMyNumber gn;
	string testiii;
	int maxguess = 8;
	int choice;

	cout << "Please choose what function you want(1: our guess, 2: computer guess, 3: computer mutual guessing, 4: end)" << endl;
	cin >> choice;
	while (choice != 4) {
		if (choice == 1) {   //自己猜數字
			while (gn.size() > 0) {
				cout << "Your guess: ";
				string guess;
				cin >> guess;
				vector<string> best_sols;
				int bestA = 0, bestB = 0;
				for (int A = 0; A <= 4; ++A) {
					for (int B = 0; B <= 4 - A; ++B) {
						vector<string> sols = gn.trim(A, B, guess); //用 trim 把不符合的字串刪
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
					printf("Correct\n");
					gn.resetting();
					break;
				}
				else if (gn.size() < 20) {
					cout << "-----" << endl;
					cout << "Hint:" << endl;
					gn.show();
					cout << "-----" << endl;
				}
			}
			cout << "Please choose what function you want(1: our guess, 2: computer guess, 3: computer mutual guessing, 4: end)" << endl;
			cin >> choice;
		}
		else if (choice == 2)//電腦猜的程式
		{
			while (gn.size() > 1) {
				cout << gn.guess() << endl;
				cout << "? A ? B" << endl;
				int A, B;
				cin >> A >> B;

				gn.trim(A, B);

				if (gn.size() == 1) {
					printf("Answer:");
					gn.show();
					cout << "I got it!" << endl;
					//gn.resetting();
					break;
				}
				if (gn.size() == 0) {
					cout << "No way!" << endl;
					//gn.resetting();
					break;
				}
			}
			gn.resetting();
			cout << "Please choose what function you want(1: our guess, 2: computer guess, 3: computer mutual guessing, 4: end)" << endl;
			cin >> choice;
		}
		else if (choice == 3) {
			unsigned seed;
			seed = (unsigned)time(NULL); // 取得時間序列
			srand(seed); // 以時間序列當亂數種子
			int testbbb[4] = { 0 };
			int k;

			for (int k = 0; k < 4; k++)
				for (int m = 0; m < k; m++)
					while (testbbb[m] == testbbb[k])testbbb[k] = rand() % 10;
			while (gn.size() > 0) {
				printf("\n");
				int A, B;
				aas = &A;
				bbs = &B;

				testiii = gn.guess();
				cout << testiii << endl;
				gn.testsee(testiii, testbbb);
				gn.trim(A, B);
				if (A == 4) {
					printf("answer:");
					for (int k = 0; k < 4; k++)	printf("%d", testbbb[k]);
					cout << "\nI got it!" << endl;
					gn.resetting();
					break;
				}
			}
			cout << "Please choose what function you want(1: our guess, 2: computer guess, 3: computer mutual guessing, 4: end)" << endl;
			cin >> choice;
		}
		else {
			cout << "end of program" << endl;
			break;
		}
	}
}