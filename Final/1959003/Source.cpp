#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <bitset>
#include <iomanip>
using namespace std;
class Detail
{
protected:
	vector<Detail*> List;
	static float WeightSum, PriceSum;
public:
	virtual string getID()
	{
		return NULL;
	}
	void AddDetail(Detail* P)
	{
		List.push_back(P);
	}
	Detail() {}
	~Detail()
	{
		while (!List.empty())
		{
			delete List.back();
			List.pop_back();
		}
	}
	void CreateMachine();
	virtual float getWeight()
	{
		return 0;
	}
	virtual float getPrice()
	{
		return 0;
	}
};
class Single : public Detail
{
protected:
	float Weight, Price;
	string ID;
public:
	Single()
	{
		ID = "";
		Weight = 0;
		Price = 0;
	}
	Single(string id, int pri, int wei) : ID(id), Price(pri), Weight(wei)
	{
		WeightSum += Weight;
		PriceSum += Price;
	}
	string getID()
	{
		return ID;
	}
	void CreateSingle()
	{
		cout << "\nEnter single ID: ";
		getline(cin, ID);
		bool f = true;
		do
		{
			if (!f) cout << "\tInvalid value !!!\n";
			cout << "Enter price of [" << ID << "]: ";
			cin >> Price;
			f = false;
		} while (Price <= 0);
		f = true;
		do
		{
			if (!f) cout << "\tInvalid value !!!\n";
			cout << "Enter weight of [" << ID << "]: ";
			cin >> Weight;
			f = false;
		} while (Weight <= 0);
		AddDetail(new Single(ID, Price, Weight));
	}
	float getWeight()
	{
		return Weight;
	}
	float getPrice()
	{
		return Price;
	}
};
class Complex : public Single
{
public:
	Complex() {}
	Complex(string id, int pri, int wei)
	{
		ID = id;
		Price = pri;
		Weight = wei;
		WeightSum += Weight * 1.1;
		PriceSum += Price * 1.2;
	}
	void CreateComplex()
	{
		Single temp1;
		Complex temp2;
		cout << "\nEnter complex ID: ";
		getline(cin, ID);
		//bool f = true;
		//do
		//{
		//	if (!f) cout << "\tInvalid value !!!\n";
		//	cout << "Enter price of [" << ID << "]: ";
		//	cin >> Price;
		//	f = false;
		//} while (Price <= 0);
		//f = true;
		//do
		//{
		//	if (!f) cout << "\tInvalid value !!!\n";
		//	cout << "Enter weight of [" << ID << "]: ";
		//	cin >> Weight;
		//	f = false;
		//} while (Weight <= 0);
		//AddDetail(new Complex(ID, Price, Weight));
		AddDetail(new Complex(ID, 0, 0));
		int n1, n2;
		cout << "\nEnter number of single detail in [" << ID << "]: ";
		cin >> n1;
		cout << "\nEnter number of complex detail in [" << ID << "]: ";
		cin >> n2;
		cin.ignore();
		for (int i = 0; i < n1; i++)
		{
			cout << "\tSingle No. " << i << " of [" << ID << "]\n";
			temp1.CreateSingle();
			this->Weight += temp1.getWeight();
			this->Price += temp1.getPrice();
		}
		cin.ignore();
		for (int i = 0; i < n2; i++)
		{
			cout << "\tComplex No. " << i << " of [" << ID << "]\n";
			temp2.CreateComplex();
			this->Weight += temp2.getWeight();
			this->Price += temp2.getPrice();
		}
	}
};
void Detail::CreateMachine()
{
	int temp;
	do
	{
		Single* t1;
		Complex* t2;
		cout << "\n\tEnter 1 to create single detail\n";
		cout << "\tEnter 2 to create complex detail\n";
		cout << "\tEnter 3 to exit\n";
		cout << "\nEnter your choice: ";
		cin >> temp;
		cin.ignore();
		switch (temp)
		{
		case 1:
			t1 = new Single();
			t1->CreateSingle();
			break;
		case 2:
			t2 = new Complex();
			t2->CreateComplex();
			break;
		}
	} while (temp != 3);
	cout << "\n\tMachine info\n";
	cout << "Machine price: " << this->PriceSum << endl;
	cout << "Machine weight: " << this->WeightSum << endl;
}
float Detail::PriceSum = 0;
float Detail::WeightSum = 0;
void main()
{
	Detail P;
	P.CreateMachine();
}