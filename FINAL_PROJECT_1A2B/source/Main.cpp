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

	void resetting() {
		for (int i = 0; i < 10000; i++) {
			stringstream os;
			os << setfill('0') << setw(4) << i;
			solutions.push_back(os.str());
			solutions.erase(remove_if(solutions.begin(), solutions.end(),
				[](string& s) {
					for (int j = 1; j < 4; ++j)
						for (int k = 0; k < j; ++k)
							if (s[j] == s[k]) return true;
					return false;
				}), solutions.end());
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
	vector<string> solutions;
};



int main() {
	GuessMyNumber gn;
	string testiii;
	int maxguess = 8;
	int choice;

	cout << "�п�ܭn�ƻ�\��(1�O�ڭ̲q�A2�O�q���q�A3�O�ݹq�����q�A4�O�����{��)" << endl;
	cin >> choice;
	while (choice != 4) {
		if (choice == 1) {   //�ۤv�q�Ʀr
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
					cout << "���߲q��F" << endl;
					gn.resetting();
					break;
				}
				else if (gn.size() < 20) {
					cout << "-----" << endl;
					cout << "����:" << endl;
					gn.show();
					cout << "-----" << endl;
				}
			}
			cout << "�п�ܭn�ƻ�\��(1�O�ڭ̲q�A2�O�q���q�A3�O�ݹq�����q�A4�O�����{��)" << endl;
			cin >> choice;
		}
		else if (choice == 2)//�q���q���{��
		{
			while (gn.size() > 0) {
				cout << gn.guess() << endl;
				cout << "? A ? B" << endl;
				int A, B;
				cin >> A >> B;

				gn.trim(A, B);

				if (gn.size() == 1) {
					cout << "I got it!" << endl;
					gn.resetting();
					break;
				}
				if (gn.size() == 0) {
					cout << "No way!" << endl;
					break;
				}
			}
			cout << "�п�ܭn�ƻ�\��(1�O�ڭ̲q�A2�O�q���q�A3�O�ݹq�����q�A4�O�����{��)" << endl;
			cin >> choice;
		}
		else if (choice == 3) {
			unsigned seed;
			seed = (unsigned)time(NULL); // ���o�ɶ��ǦC
			srand(seed); // �H�ɶ��ǦC��üƺؤl
			int testbbb[4] = { 0 };
			int k;

			for (int k = 0; k < 4; k++)
				for (int m = 0; m < k; m++)
					while (testbbb[m] == testbbb[k])testbbb[k] = rand() % 10;
			while (gn.size() > 0) {
				printf("���׬O");
				for (int k = 0; k < 4; k++)	printf("%d", testbbb[k]);
				printf("\n");
				int A, B;
				aas = &A;
				bbs = &B;

				testiii = gn.guess();
				cout << testiii << endl;
				gn.testsee(testiii, testbbb);
				gn.trim(A, B);
				if (A == 4) {
					cout << "I got it!" << endl;
					gn.resetting();
					break;
				}
			}
			
			cout << "�п�ܭn�ƻ�\��(1�O�ڭ̲q�A2�O�q���q�A3�O�ݹq�����q�A4�O�����{��)" << endl;
			cin >> choice;
		}
		else {
			cout << "�{������" << endl;
			break;
		}
	}
}

