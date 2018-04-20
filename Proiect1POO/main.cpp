#include<iostream>
#include<stdlib.h>
using namespace std;

double power(double base, int p){
    if(p == 0)
        return 1;
    if(base == 0)
        return 0;
    for(int i = 1; i < p; i++)
        base = base * base;
    return base;
}

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
		for(int i = 1; i <= gradMaximLocal; i++){
            coeficienti[i] = 0;
		}
	}

	polinom(const polinom &p){
	    gradMaxim = p.gradMaxim;
        for(int i = 0; i <= p.gradMaxim; i++){
            coeficienti[i] = p.coeficienti[i];
        }
	}

	~polinom();
	polinom(){
	    gradMaxim = 1;
	    coeficienti = new double [gradMaxim+1];
	}

	void setGrad(int n);
private:
	double *coeficienti;
	int gradMaxim;
public:
	friend ostream &operator << (ostream &output, const polinom &p);
	friend istream &operator >> (istream &input, polinom &p);
	polinom operator + (polinom poll);
	polinom operator - (polinom poll);
	polinom operator * (polinom poll);
	polinom operator / (polinom impartitor); // nu merge
	polinom operator % (polinom impartitor); // nu merge
	bool operator == (polinom poll);
    bool operator != (polinom poll);
	double operator [] (int index);

	friend class pereche;
};

bool polinom::operator == (polinom poll){
    if(gradMaxim != poll.gradMaxim)
        return 0;
    for(int i = 0; i <= gradMaxim; i++){
        if(coeficienti[i] != poll.coeficienti[i])
            return 0;
    }
    return 1;
}

bool polinom::operator != (polinom poll){
    if(gradMaxim != poll.gradMaxim)
        return 1;
    for(int i = 0; i <= gradMaxim; i++){
        if(coeficienti[i] != poll.coeficienti[i])
            return 1;
    }
    return 0;
}

void polinom::setGrad(int n){
    gradMaxim = n;
}

double polinom::operator [] (int index){
    return coeficienti[index];
}

polinom::~polinom(){
    delete coeficienti;
}

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

polinom polinom::operator / (polinom impartitor){// nu merge
    polinom caat(gradMaxim);
    polinom deimpartit(gradMaxim);
    polinom polinomAjutator(gradMaxim);
    for(int i = 0; i <= gradMaxim; i++){
        deimpartit.coeficienti[i] = coeficienti[i];
    }

    int putere;
    int i = gradMaxim;
    int j = impartitor.gradMaxim;
    while(i >= j){
        polinom polinomAjutator(gradMaxim);
        putere = i - j;
        caat.coeficienti[putere] = deimpartit.coeficienti[i] / impartitor.coeficienti[j];
        polinomAjutator.coeficienti[putere] = caat.coeficienti[putere];
        deimpartit = deimpartit - (impartitor * polinomAjutator);
        i = i - j;
        polinomAjutator.~polinom();
    }
    return caat;
}

class pereche{
/*public:
    pereche()
    pereche(const pereche &p){
        real = p.real;
        poll = p.poll;
    }*/
private:
    double real;
    polinom poll;
public:
    friend ostream &operator << (ostream &output, const pereche &p);
    friend istream &operator >> (istream &input, pereche &p);
    bool operator == (pereche p);
    bool operator != (pereche p);
    bool radacina();
    void setPollGrad(int n);

};

bool pereche::operator != (pereche p){
    if(p.real != real)
        return 1;
    if(p.poll == poll)
        return 0;
    return 1;
}

bool pereche::operator == (pereche p){
    if(p.real != real)
        return 0;
    if(p.poll == poll)
        return 1;
    return 0;
}

void pereche::setPollGrad(int n){
    poll.setGrad(n);
}

bool pereche::radacina(){
    double sum = 0;
    for(int i = 0; i <= poll.gradMaxim; i++){
        sum = sum + poll.coeficienti[i]*power(real, i);
    }
    if(sum == 0)
        return 1;
    return 0;
}

ostream &operator << (ostream &output, const pereche &p){
    output << "real number: " << p.real << endl;
    output << "polynomial: " << p.poll;
    return output;
}

istream &operator >> (istream &input, pereche &p){
    input >> p.real;
    input >> p.poll;
    return input;
}



int main()
{
	int comanda;
    do{
        cout<<" ______________this is a polynomial calculator___________ "<<endl;
        cout<<"|select any option                                       |"<<endl;
        cout<<"|sum....................................................1|"<<endl;
        cout<<"|subtract...............................................2|"<<endl;
        cout<<"|multiply...............................................3|"<<endl;
        cout<<"|check root.............................................4|"<<endl;
        cout<<"|compare polynomial.....................................5|"<<endl;
        cout<<"|compare pair...........................................6|"<<endl;
        cout<<"|________________________________________________________|"<<endl;

        cin>>comanda;

        if(comanda == 1){
            int n1,n2;
            cout<<"enter maximum power you wish your first polynome to have: ";
            cin>>n1;
            cout<<"now enter the coeficients in ascending order coresponding to the powers - first corresponds to x^0 etc.";
            polinom p1(n1);
            cin>>p1;
            cout<<"enter maximum power you wish your second polynome to have: ";
            cin>>n2;
            cout<<"now enter the coeficients in ascending order coresponding to the powers - first corresponds to x^0 etc.";
            polinom p2(n2);
            cin>>p2;
            system("CLS");
            cout<<p1<<endl<<p2<<endl;
            cout<<endl<<"your sum is: "<<p1 + p2;
            cout<<endl<<"press any key to continue...";
            system("PAUSE");
            system("CLS");
        }

        if(comanda == 2){
            int n1,n2;
            cout<<"enter maximum power you wish your first polynome to have: ";
            cin>>n1;
            cout<<"now enter the coeficients in ascending order coresponding to the powers - first corresponds to x^0 etc.";
            polinom p1(n1);
            cin>>p1;
            cout<<"enter maximum power you wish your second polynome to have: ";
            cin>>n2;
            cout<<"now enter the coeficients in ascending order coresponding to the powers - first corresponds to x^0 etc.";
            polinom p2(n2);
            cin>>p2;
            system("CLS");
            cout<<p1<<endl<<p2<<endl;
            cout<<endl<<"the result is: "<<p1 - p2;
            cout<<endl<<"press any key to continue...";
            system("PAUSE");
            p1.~polinom();
            p2.~polinom();
            system("CLS");
        }

        if(comanda == 3){
            int n1,n2;
            cout<<"enter maximum power you wish your first polynome to have: ";
            cin>>n1;
            cout<<"now enter the coeficients in ascending order coresponding to the powers - first corresponds to x^0 etc.";
            polinom p1(n1);
            cin>>p1;
            cout<<"enter maximum power you wish your second polynome to have: ";
            cin>>n2;
            cout<<"now enter the coeficients in ascending order coresponding to the powers - first corresponds to x^0 etc.";
            polinom p2(n2);
            cin>>p2;
            system("CLS");
            cout<<p1<<endl<<p2<<endl;
            cout<<endl<<"the result is: "<<p1 * p2;
            cout<<endl<<"press any key to continue...";
            system("PAUSE");
            p1.~polinom();
            p2.~polinom();
            system("CLS");
        }

        if(comanda == 4){
            int n;
            cout<<"enter maximum power you wish the polynome to have: " << endl;
            pereche p;
            cin>>n;
            p.setPollGrad(n);
            cout<<"now enter the root and the coeficients in ascending order coresponding to the powers - first corresponds to x^0 etc. after that"<<endl;
            cin>>p;
            system("CLS");
            cout<<p;
            if(p.radacina())
                cout<<"it's a root";
            else
                cout<<"it's not a root";
            cout<<endl<<"press any key to continue";
            system("PAUSE");
            system("CLS");
        }

        if(comanda == 5){
            system("CLS");
            int n1,n2;
            cout<<"enter maximum power you wish your first polynome to have: ";
            cin>>n1;
            cout<<"now enter the coeficients in ascending order coresponding to the powers - first corresponds to x^0 etc.";
            polinom p1(n1);
            cin>>p1;
            cout<<"enter maximum power you wish your second polynome to have: ";
            cin>>n2;
            cout<<"now enter the coeficients in ascending order coresponding to the powers - first corresponds to x^0 etc.";
            polinom p2(n2);
            cin>>p2;
            system("CLS");
            cout<<p1<<endl<<p2<<endl;
            if(p1 == p2)
                cout<<"they are equal";
            else
                cout<<"they are not equal";
            cout<<endl<<"press any key to continue...";
            system("PAUSE");
            system("CLS");
        }

        if(comanda == 6){
            system("CLS");
            int n1,n2;
            cout<<"enter maximum power you wish the polynome to have: " << endl;
            pereche p1;
            cin>>n1;
            p1.setPollGrad(n1);
            cout<<"now enter the root and the coeficients in ascending order coresponding to the powers - first corresponds to x^0 etc. after that"<<endl;
            cin>>p1;
            cout<<"enter maximum power you wish the polynome to have: " << endl;
            pereche p2;
            cin>>n2;
            p2.setPollGrad(n2);
            cout<<"now enter the root and the coeficients in ascending order coresponding to the powers - first corresponds to x^0 etc. after that"<<endl;
            cin>>p2;
            if(p1 == p2)
                cout<<"they are equal";
            else
                cout<<"they are not equal";
            cout<<endl<<"press any key to continue";
            system("PAUSE");
            system("CLS");
        }
    }while(comanda);

    return 0;
}

