#include<iostream>
using namespace std;

int mini(int a, int b){
    if(a > b) return b;
    return a;
}
int maxi(int a, int b){
    if(a > b) return a;
    return b;
}

class polinom {
public:
	polinom(int gradMaximLocal) {
		gradMaxim = gradMaximLocal;
		coeficienti = new double [gradMaxim+1];
	}
	polinom(){
	    gradMaxim = 1;
	    coeficienti = new double [gradMaxim+1];
	}
	double *coeficienti;
	int gradMaxim;
	friend ostream &operator << (ostream &output, const polinom &p);
	friend istream &operator >> (istream &input, polinom &p);
	polinom operator + (polinom poll);
	polinom operator - (polinom poll);
	polinom operator * (polinom poll);

};

ostream &operator << (ostream &output, const polinom &p) {
	if (p.coeficienti[0] != 0){
			if(p.coeficienti[1] > 0) output << p.coeficienti[0] << " +";
			else output << p.coeficienti[0] << " ";
		}
	int i = 1;
	for (i = 1; i < p.gradMaxim; i++) {
		if (p.coeficienti[i] != 0){
			if(p.coeficienti[i+1] > 0) output << p.coeficienti[i] << "x^" << i << " +";
			else output << p.coeficienti[i] << "x^" << i << " ";
		}
	}
    output << p.coeficienti[i] << "x^" << i;
    output << endl;
	return output;
}

istream &operator >> (istream &input, polinom &p) {
	for (int i = 0; i <= p.gradMaxim; i++) {
		input >> p.coeficienti[i];
	}
	return input;
}

polinom polinom::operator + (polinom poll) {
	polinom newPol(gradMaxim + poll.gradMaxim);

	int i = 0;
	while (i <= poll.gradMaxim && i <= gradMaxim){
		newPol.coeficienti[i] = poll.coeficienti[i] + coeficienti[i];
		i++;
	}
	if (poll.gradMaxim > gradMaxim) {
		newPol.gradMaxim = poll.gradMaxim;
		while (i <= poll.gradMaxim) {
			newPol.coeficienti[i] = poll.coeficienti[i];
			i++;
		}
	}
	if (poll.gradMaxim < gradMaxim) {
		newPol.gradMaxim = gradMaxim;
		while (i <= gradMaxim){
			newPol.coeficienti[i] = coeficienti[i];
			i++;
		}
	}
    return newPol;
}

polinom polinom::operator - (polinom poll){
    polinom newPol(gradMaxim + poll.gradMaxim);
    int i = 0;
	while (i <= mini(gradMaxim, poll.gradMaxim)){
		newPol.coeficienti[i] = coeficienti[i] - poll.coeficienti[i];
        i++;
	}
	if (poll.gradMaxim > gradMaxim) {
		newPol.gradMaxim = poll.gradMaxim;
		while (i <= poll.gradMaxim) {
			newPol.coeficienti[i] = (-1) * poll.coeficienti[i];
			i++;
		}
	}
	else {
		newPol.gradMaxim = gradMaxim;
		while (i <= gradMaxim){
			newPol.coeficienti[i] = (-1) * coeficienti[i];
			i++;
		}
	}
    return newPol;
}

polinom polinom::operator * (polinom poll){
    polinom newPol(gradMaxim + poll.gradMaxim);
    for(int i = 0; i <= gradMaxim; i++){
        for(int j = 0; j <= poll.gradMaxim; j++){
            newPol.coeficienti[i+j] = newPol.coeficienti[i+j] + (coeficienti[i] * poll.coeficienti[j]);
        }
    }
    return newPol;
}

int main()
{
	polinom f(1),g(1);
	cin>>f>>g;
	cout<<f<<endl<<g<<endl;
	cout<<f+g;
    return 0;
}
