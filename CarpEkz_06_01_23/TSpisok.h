#pragma once
#include <string>
#include <fstream>
#include <utools.h> // GO to general linker and C++ settings, and set Additional Library Directories
#include <algorithm>
#include <vector>
using namespace std;

struct Person
{
	string name;
	int usedSum;
	int givenSum;
	int prem;
	int debt; // + -
};
struct Stat {
	int allUsedSum = 0;
	int givenAllSum = 0;
	int givenAllSumWithPercentage = 0;
	int left = 0;
	int backedDebts = 0;
};
class TCorr
{
	public:
		int num;
		int allSum;
		int prc;
		vector<Person> persons;

		TCorr() {}
		~TCorr() {
		}

		Stat getStat() {
			Stat res;
			for (auto p : persons) {
				res.allUsedSum += p.usedSum;
				res.givenAllSum += p.givenSum;
				res.givenAllSumWithPercentage += p.prem;
				if (p.debt < 0)
					res.backedDebts += abs(p.debt);
			}

			res.left = allSum - res.givenAllSumWithPercentage + res.backedDebts;
			
			return res;
		}


		friend ofstream& operator << (ofstream& of, TCorr& spis) {
			
			int i = 0;
			while (i < spis.num) {
				of << spis.persons[i].name << "\t" << spis.persons[i].givenSum << "\t" << spis.persons[i].usedSum << "\t" << spis.persons[i].prem << "\t" << spis.persons[i].debt << endl;
				i = i + 1;
			}

			Stat stat = spis.getStat();
			of << "kol-vo sotr = " << spis.num << endl
				<< "OTSUM = " << stat.allUsedSum << endl
				<< "OSUM = " << stat.givenAllSum << endl
				<< "ORSUM = " << stat.givenAllSumWithPercentage << endl
				<< "vernuli " << stat.backedDebts << endl
				<< "ostalos " << stat.left << endl;

			return of;
		}
		friend ifstream& operator >> (ifstream& in, TCorr& spis)
		{	
			int allSum, prc;
			string line;

			getline(in, line); // ALL SUM
			allSum = stoi(line);

			getline(in, line);
			prc = stoi(line);

			spis.allSum = allSum;
			spis.prc = prc;

			int i = 0;
			while (!in.eof()) {
				getline(in, line);
				if (line.empty())
					continue;
				auto dividedLine = StringHelper::separateByDelimiter(line, { ' ' });

				Person p = { dividedLine[0], stoi(dividedLine[3]), stoi(dividedLine[4]) };
				p.prem = p.givenSum + p.givenSum * prc / 100;
				p.debt = p.prem - p.usedSum;

				spis.persons.push_back(p);

				i++;

			}
			spis.num = i;
			return in;
		}

		void sortBySum() {
			for (int i = 0; i < num - 1; i++) {
				for (int j = 0; j < num - i - 1; j++) {
					if (persons[j].givenSum > persons[j+1].givenSum) {
						// swap
						swap(persons[j], persons[j + 1]);

					}
				}
			}
		}

		void defaultSortBySum() {
			sort(persons.begin(), persons.end(), [](Person& p1, Person& p2) {
				return p1.givenSum < p2.givenSum;
			});
		}
		
};

