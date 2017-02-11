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
		cout << "K" << i << " = ";
		cin >> koef[i];
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
				cout << " - " << "X^" << i;
			else
				cout << " - " << (-1)*koef[i] << "X^" << i;
	}

	if (koef[0]>0)
		cout << " + " << koef[0] << "\n";
	else if (koef[0] < 0)
		cout << " - " << (-1)*koef[0] << "\n";
}
int main()
{
	Polynom polynom ;
	polynom.InputPolynom();
	polynom.OutputPolynom();
	return 0;
}