#include <iostream>
#include <memory.h>

using namespace std;

//класс Polynom
class Polynom{
private:
	unsigned int deg; //степень полинома
	double *koef; //указатель на массив коэффициентов полинома
	//koef[i] - коэффициент при i-й степени,
	//koef[0] - коэффициент при нулевой степени
	void CorrectDeg(); // функция корректировки степени полинома

public:
	Polynom(); //конструктор без параметров
	Polynom(unsigned int, double*); //конструктор с параметрами
	Polynom(const Polynom &); //копирующий контсруктор
	Polynom::~Polynom(); //деструктор

	unsigned int GetDeg(); //функция получения степени полинома
	double GetKoef(unsigned int); //функция получения коэффициента при i-й степени
	unsigned int SetKoef(double, unsigned int); //функция задания коэффициента при i-й 
	//степени, возвращает степень полинома
	Polynom operator + (const Polynom &);   //оператор сложения двух полиномов
	Polynom operator = (const Polynom &);   //оператор присваивания
	friend Polynom MultConst(double, Polynom &); //дружественная функция умножения полинома
	//на константу
	void InputPolynom();    //функция ввода полинома
	void OutputPolynom();   //функция вывода полинома
};

// конструктор без параметров: создается полином нулевой степени
// с коэффициентом при нулевой степени равным нулю
Polynom::Polynom(){
	deg = 0;
	koef = new double[deg + 1];
	koef[0] = 0.0;
}

// конструктор с параметрами
// new_deg - степень создаваемого полинома
// newkoef - указатель на new_deg+1 - элементный массив с коэффициентами 
//           полинома, где newkoef[i] - коффициент при i-й степени
//           и newkoef[0] - коэффициент при нулевой степени
// В результате степень полинома будет наибольшим номером ненулевого
// элемента массива new_koef и меньше или равна new_deg (по определению степени полинома)
Polynom::Polynom(unsigned int new_deg, double *new_koef){
	deg = 0;
	for (int i = 0; i <= new_deg; i++)
		if (new_koef[i] != 0) deg = i;   //инициализация переменной степени
	koef = new double[deg + 1];
	for (int i = 0; i <= deg; i++)
		koef[i] = new_koef[i]; //инициализация массива коэффициентов
}

//копирующий конструктор
Polynom::Polynom(const Polynom &f){
	deg = f.deg;
	koef = new double[deg + 1];
	for (int i = 0; i <= deg; i++)
		koef[i] = f.koef[i];
}

//деструктор
Polynom::~Polynom(){
	delete[] koef;
}
// функция получения степени полинома
unsigned int Polynom::GetDeg(){
	return deg;
}

// функция получения коэффициента при i-й степени
double Polynom::GetKoef(unsigned int i){
	if (i <= deg)
		return koef[i];
	else
		return 0.0;
}

// функция задания коэффициента при i-й степени
unsigned int Polynom::SetKoef(double new_koef, unsigned int i){
	if (i <= deg) koef[i] = new_koef;
	else return deg;
	CorrectDeg();
	return deg;
}

//оператор сложения двух полиномов
Polynom Polynom::operator + (const Polynom &t){
	int i;
	Polynom *result;

	if (deg >= t.deg){ //если степень первого полинома больше степени второго
		result = new Polynom(deg, koef);
		for (i = 0; i <= t.deg; i++)
			result->koef[i] = result->koef[i] + t.koef[i];
	}
	else{                   //если степень второго полинома больше степень первого
		result = new Polynom(t.deg, t.koef);
		for (i = 0; i <= deg; i++)
			result->koef[i] = result->koef[i] + koef[i];
	}
	result->CorrectDeg();
	return *result;
}

//оператор присваивания
Polynom Polynom::operator = (const Polynom &t){
	deg = t.deg;
	delete[] koef;
	koef = new double[deg + 1];
	for (int i = 0; i <= deg; i++)
		koef[i] = t.koef[i];
	return *this;
}


//оператор умножения числа на полином
Polynom operator * (double K, Polynom &t){
	return MultConst(K, t);
}

//оператор умножения полинома на число
Polynom operator * (Polynom &t, double K){
	return MultConst(K, t);
}

//функция реализующая умножение полинома на число
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

// функция корректировки степени полинома: коэффициент 
// при максимальной степени должен быть ненулевым
void Polynom::CorrectDeg(){
	if (koef[deg] == 0){
		do{
			deg--;
		} while (deg && koef[deg] == 0);
	}
}

//функция ввода полинома
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