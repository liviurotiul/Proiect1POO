#include "stdafx.h"
#include<iostream>
using namespace std;
class polinom {
public:
	polinom(int gradMaximLocal) {
		gradMaxim = gradMaximLocal;
		coeficienti = new double [gradMaxim+1];
	}
	double *coeficienti;
	int gradMaxim;
	friend ostream &operator << (ostream &output, const polinom &p);
	friend istream &operator >> (istream &input, polinom &p);
	friend polinom operator + (polinom pol1, polinom pol2);
	};

ostream &operator << (ostream &output, const polinom &p) {
	output << p.coeficienti[0] << " +";
	for (int i = 1; i <= p.gradMaxim; i++) {
		if (p.coeficienti[i] != 0)
			output << p.coeficienti[i] << "x^" << i << " +";
		};
	return output;
}
istream &operator >> (istream &input, polinom &p) {
	for (int i = 0; i <= p.gradMaxim; i++) {
		input >> p.coeficienti[i];
	}
	return input;
}

polinom operator + (polinom pol1, polinom pol2) {
	polinom newPol;
	
	int i = 0;
	while (i <= pol1.gradMaxim && i <= pol2.gradMaxim){
		newPol.coeficienti[i] = pol1.coeficienti[i] + pol2.coeficienti[i];
		i++;
	}
	if (pol1.gradMaxim > pol2.gradMaxim) {
		newPol.gradMaxim = pol1.gradMaxim;
		while (i <= pol1.gradMaxim) {
			newPol.coeficienti[i] = pol1.coeficienti[i];
		}
	}
	else {
		newPol.gradMaxim = pol2.gradMaxim;
		while (){
			newPol.coeficienti[i] = pol2.coeficienti[i];
		}
	}
	return newPol;
}
int main()
{
	polinom p(3);int dummy;
	cout << "introduceti coeficientii";
	cin >> p;
	cout << p;
	cin >> dummy;
    return 0;
}

