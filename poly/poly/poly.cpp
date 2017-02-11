#include <iostream>
#include <memory.h>

using namespace std;

//����� Polynom
class Polynom{
private:
	unsigned int deg; //������� ��������
	double *koef; //��������� �� ������ ������������� ��������
	//koef[i] - ����������� ��� i-� �������,
	//koef[0] - ����������� ��� ������� �������
	void CorrectDeg(); // ������� ������������� ������� ��������

public:
	Polynom(); //����������� ��� ����������
	Polynom(unsigned int, double*); //����������� � �����������
	Polynom(const Polynom &); //���������� �����������
	Polynom::~Polynom(); //����������

	unsigned int GetDeg(); //������� ��������� ������� ��������
	double GetKoef(unsigned int); //������� ��������� ������������ ��� i-� �������
	unsigned int SetKoef(double, unsigned int); //������� ������� ������������ ��� i-� 
	//�������, ���������� ������� ��������
	Polynom operator + (const Polynom &);   //�������� �������� ���� ���������
	Polynom operator = (const Polynom &);   //�������� ������������
	friend Polynom MultConst(double, Polynom &); //������������� ������� ��������� ��������
	//�� ���������
	void InputPolynom();    //������� ����� ��������
	void OutputPolynom();   //������� ������ ��������
};

// ����������� ��� ����������: ��������� ������� ������� �������
// � ������������� ��� ������� ������� ������ ����
Polynom::Polynom(){
	deg = 0;
	koef = new double[deg + 1];
	koef[0] = 0.0;
}

// ����������� � �����������
// new_deg - ������� ������������ ��������
// newkoef - ��������� �� new_deg+1 - ���������� ������ � �������������� 
//           ��������, ��� newkoef[i] - ���������� ��� i-� �������
//           � newkoef[0] - ����������� ��� ������� �������
// � ���������� ������� �������� ����� ���������� ������� ����������
// �������� ������� new_koef � ������ ��� ����� new_deg (�� ����������� ������� ��������)
Polynom::Polynom(unsigned int new_deg, double *new_koef){
	deg = 0;
	for (int i = 0; i <= new_deg; i++)
		if (new_koef[i] != 0) deg = i;   //������������� ���������� �������
	koef = new double[deg + 1];
	for (int i = 0; i <= deg; i++)
		koef[i] = new_koef[i]; //������������� ������� �������������
}

//���������� �����������
Polynom::Polynom(const Polynom &f){
	deg = f.deg;
	koef = new double[deg + 1];
	for (int i = 0; i <= deg; i++)
		koef[i] = f.koef[i];
}

//����������
Polynom::~Polynom(){
	delete[] koef;
}
// ������� ��������� ������� ��������
unsigned int Polynom::GetDeg(){
	return deg;
}

// ������� ��������� ������������ ��� i-� �������
double Polynom::GetKoef(unsigned int i){
	if (i <= deg)
		return koef[i];
	else
		return 0.0;
}

// ������� ������� ������������ ��� i-� �������
unsigned int Polynom::SetKoef(double new_koef, unsigned int i){
	if (i <= deg) koef[i] = new_koef;
	else return deg;
	CorrectDeg();
	return deg;
}

//�������� �������� ���� ���������
Polynom Polynom::operator + (const Polynom &t){
	int i;
	Polynom *result;

	if (deg >= t.deg){ //���� ������� ������� �������� ������ ������� �������
		result = new Polynom(deg, koef);
		for (i = 0; i <= t.deg; i++)
			result->koef[i] = result->koef[i] + t.koef[i];
	}
	else{                   //���� ������� ������� �������� ������ ������� �������
		result = new Polynom(t.deg, t.koef);
		for (i = 0; i <= deg; i++)
			result->koef[i] = result->koef[i] + koef[i];
	}
	result->CorrectDeg();
	return *result;
}

//�������� ������������
Polynom Polynom::operator = (const Polynom &t){
	deg = t.deg;
	delete[] koef;
	koef = new double[deg + 1];
	for (int i = 0; i <= deg; i++)
		koef[i] = t.koef[i];
	return *this;
}


//�������� ��������� ����� �� �������
Polynom operator * (double K, Polynom &t){
	return MultConst(K, t);
}

//�������� ��������� �������� �� �����
Polynom operator * (Polynom &t, double K){
	return MultConst(K, t);
}

//������� ����������� ��������� �������� �� �����
Polynom MultConst(double K, Polynom &t){
	if (K == 0){
		Polynom result;
		return result;
	}
	else{
		int deg = t.deg;
		double *tmp_koef = new double[deg + 1];
		for (int i = 0; i <= deg; i++)
			tmp_koef[i] = K*t.koef[i];
		Polynom result(deg, tmp_koef);
		delete[] tmp_koef;
		return result;
	}
}

// ������� ������������� ������� ��������: ����������� 
// ��� ������������ ������� ������ ���� ���������
void Polynom::CorrectDeg(){
	if (koef[deg] == 0){
		do{
			deg--;
		} while (deg && koef[deg] == 0);
	}
}

//������� ����� ��������
void Polynom::InputPolynom(){
	cout << "Input degree: ";
	cin >> deg;
	delete[] koef;
	koef = new double[deg + 1];
	for (int i = 0; i<deg; i++){
		//cout << "K" << i << " = ";
		//cin >> koef[i];
		koef[i] = i ;
		cout << "K" << i << " = " << koef[i] << endl;
	}
	do{
		cout << "K" << deg << " = ";
		cin >> koef[deg];
		if (koef[deg] == 0)
			cout << "K" << deg << " must not be zero!!!\n";
	} while (!koef[deg]);
}

void Polynom::OutputPolynom(){
	if (koef[deg] == 1)
		cout << "X^" << deg;
	else if (koef[deg] == -1)
		cout << "-X^" << deg;
	else
		cout << koef[deg] << "X^" << deg;

	for (int i = deg - 1; i > 0; i--){
		if (koef[i] > 0){
			if (koef[i] == 1)
				cout << " + " << "X^" << i;
			else
				cout << " + " << koef[i] << "X^" << i;
		}
		else if (koef[i] < 0)
			if (koef[i] == -1)
				cout << " - " << "X^" << i;//2i
			else
				cout << " - " << (-1)*koef[i] << "X^" << i;
	}

	int sum = 0,poww = 1,XX;
	cout << "\nEnter X \n";
	cin >> XX;
	if (koef[deg] == 1)
	{
		poww = pow(XX, deg);
		sum += poww;
	}
	else if (koef[deg] == -1)
	{
		poww = pow((-1)*XX, deg);
		sum += poww;
	}
	else
	{
		poww = pow(XX, deg);
		sum += koef[deg] * poww;
	}
	for (int i = deg - 1; i > 0; i--){
		if (koef[i] > 0){
			if (koef[i] == 1)
			{
				poww = pow(XX, i);
				sum += poww;
			}
			else
			{
				poww = pow(XX, i);
				sum += koef[i] * poww;
			}
		}
		else if (koef[i] < 0)
			if (koef[i] == -1)
			{
				poww = pow(XX, i);
				sum -= poww;
			}
			else
			{
				poww = pow(XX, i);
				sum -= (-1)*koef[i] * poww;
			}
	}
	cout << "Result = " << sum << endl;


	if (koef[0]>0)
		cout << " + " << koef[0] << "\n";
	else if (koef[0] < 0)
		cout << " - " << (-1)*koef[0] << "\n";
	cout << "-----\n\n";
	int res = 0;
	if (deg % 2 != 0) res = deg;
	if (deg % 2 == 0) { res = deg;  koef[deg + 1] = 0; }
	for (int i = 0; i <= res; i+=2)
	{
		{
			if (koef[i] > 0)
			{
				if (koef[i + 1] > 0)
					cout << " + (" << koef[i] << " + " << koef[i + 1] << "X) * X^" << i;
				if (koef[i + 1] < 0)
					cout << " + (" << koef[i] << " - " << koef[i + 1] << "X) * X^" << i;
				if (koef[i + 1] == 0)
					cout << " + " << koef[i] << " * X^" << i;
				if (koef[i + 1] == 1)
					cout << " + (" << koef[i] << " + X) * X^" << i;
			}
			if (koef[i] < 0)
			{
				if (koef[i + 1] > 0)
					cout << " - (" << (-1)*koef[i] << " - " << (-1)*koef[i + 1] << "X) * X^" << i;
				if (koef[i + 1] < 0)
					cout << " - (" << (-1)*koef[i] << " + " << (-1)*koef[i + 1] << "X) * X^" << i;
				if (koef[i + 1] == 0)
					cout << " - " << (-1)*koef[i] << " * X^" << i;
				if (koef[i + 1] == 1)
					cout << " - (" << koef[i] << " + X) * X^" << i;
			}
			if (koef[i] == 0)
			{
				if (koef[i + 1] > 1)
					cout << " + " << koef[i + 1] << " X^" << i + 1;
				if (koef[i + 1] < 0)
					cout << " - " << koef[i + 1] << "X^" << i + 1;
				if (koef[i + 1] == 0)
					cout << " ";
				if (koef[i + 1] == 1)
					cout << " + X^" << i + 1;
			}
		}
	}

	int resultat = 0, X, sumskob=0,sumpowx = 0,powx = 1;
	cout << "\nCalculate: \nEnter X" << endl;
	cin >> X;
	if (koef[0]>0)
		resultat += koef[0];
	else if (koef[0] < 0)
		resultat -= (-1)*koef[0];
	int ress = 0;
	if (deg % 2 != 0) ress = deg;
	if (deg % 2 == 0) { ress = deg;  koef[deg + 1] = 0; }
	for (int i = 0; i <= ress; i += 2)
	{
		{
			if (koef[i] > 0)
			{
				if (koef[i + 1] > 0)
				{
					sumskob = (koef[i + 1] * X) + koef[i];
					powx = pow(X, i);
					sumpowx = sumskob * powx;
					resultat += sumpowx;
				}
				if (koef[i + 1] < 0)
				{
					sumskob = (-1)*(koef[i + 1] * X) + koef[i];
					powx = pow(X, i);
					sumpowx = sumskob * powx;
					resultat += sumpowx;
				}
				if (koef[i + 1] == 0)
				{
					sumskob =  koef[i];
					powx = pow(X, i);
					sumpowx = sumskob * powx;
					resultat += sumpowx;
				}
				if (koef[i + 1] == 1)
				{
					sumskob =  X + koef[i];
					powx = pow(X, i);
					sumpowx = sumskob * powx;
					resultat += sumpowx;
				}
			}
			if (koef[i] < 0)
			{
				if (koef[i + 1] > 0)
				{
					sumskob = (-1)*koef[i] - (-1)*(koef[i + 1] * X);
					powx = pow(X, i);
					sumpowx = sumskob * powx;
					resultat -= sumpowx;
				}
				if (koef[i + 1] < 0)
				{
					sumskob = (-1)*koef[i] + (-1)*(koef[i + 1] * X);
					powx = pow(X, i);
					sumpowx = sumskob * powx;
					resultat -= sumpowx;
				}
				if (koef[i + 1] == 0)
				{
					sumskob = (-1)*koef[i];
					powx = pow(X, i);
					sumpowx = sumskob * powx;
					resultat -= sumpowx;
				}
				if (koef[i + 1] == 1)
				{
					sumskob = koef[i]  + X;
					powx = pow(X, i);
					sumpowx = sumskob * powx;
					resultat -= sumpowx;
				}
			}
			if (koef[i] == 0)
			{
				if (koef[i + 1] > 1)
				{
					sumskob = koef[i+1];
					powx = pow(X, i+1);
					sumpowx = sumskob * powx;
					resultat += sumpowx;
				}
				if (koef[i + 1] < 0)
				{
					sumskob = koef[i + 1];
					powx = pow(X, i + 1);
					sumpowx = sumskob * powx;
					resultat -= sumpowx;
				}
				if (koef[i + 1] == 0)
					resultat += 0;
				if (koef[i + 1] == 1)
				{
					sumskob = 1;
					powx = pow(X, i + 1);
					sumpowx = sumskob * powx;
					resultat += sumpowx;
				}
			}
		}
	}

	cout << "REsult = " << resultat << endl;
}
int main()
{
	Polynom polynom;
	polynom.InputPolynom();
	polynom.OutputPolynom();
	cout << endl;
	return 0;
}