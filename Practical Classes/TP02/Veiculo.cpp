#include "Veiculo.h"
#include <iostream>


using namespace std;

Veiculo::Veiculo(string mc, int m, int a) {
	marca = mc;
	mes = m;
	ano = a;
}

int Veiculo::getAno() const {
	return ano;
}

int Veiculo::getMes() const {
	return mes;
}

string Veiculo::getMarca() const {
	return marca;
}

int Veiculo::info() const {
	cout << "Marca: " << marca << endl;
	cout << "Mes: " << mes << endl;
	cout << "Ano: " << ano << endl;
	return 3;
}

bool Veiculo::operator<(const Veiculo & v) const {
	if (ano == v.getAno())
		return mes > v.getMes() ? false : true;
	else
		return ano > v.getAno() ? false : true;
}

Motorizado::Motorizado(string mc, int m, int a, string c, int cil): Veiculo(mc, m, a) {
	combustivel = c;
	cilindrada = cil;
}

string Motorizado::getCombustivel() const {
	return combustivel;
}

int Motorizado::info() const {
	Veiculo::info();
	cout << "Combustivel: " << combustivel << endl;
	cout << "Cilindrada: " << cilindrada << endl;
	return 5;
}

float Motorizado::calcImposto() const {
	float imposto = 0;
	string co = combustivel;
	int ci = cilindrada;
	if ((co == "gasolina" && ci <= 1000) || (co != "gasolina" && ci <= 1500)) {
		if (getAno() > 1995) imposto = 14.56;
		else imposto = 8.10;
	}
	else if ((co == "gasolina" && ci > 1000 && ci <= 1300) || (co != "gasolina" && ci > 1500 && ci <= 2000)) {
		if (getAno() > 1995) imposto = 29.06;
		else imposto = 14.56;
	}
	else if ((co == "gasolina" && ci > 1300 && ci <= 1750) || (co != "gasolina" && ci > 2000 && ci <= 3000)) {
		if (getAno() > 1995) imposto = 45.15;
		else imposto = 22.65;
	}
	else if ((co == "gasolina" && ci > 1750 && ci <= 2600) || (co != "gasolina" && ci > 3000)) {
		if (getAno() > 1995) imposto = 113.98;
		else imposto = 54.89;
	}
	else if (co == "gasolina" && ci > 2600 && ci <= 3500) {
		if (getAno() > 1995) imposto = 181.17;
		else imposto = 87.13;
	}
	else if (co == "gasolina" && ci > 3500) {
		if (getAno() > 1995) imposto = 320.89;
		else imposto = 148.37;
	}
	return imposto;
}

Automovel::Automovel(string mc, int m, int a, string c, int cil): Motorizado(mc,m,a,c,cil) {}

int Automovel::info() const {
	return Motorizado::info();
}

Camiao::Camiao(string mc, int m, int a, string c, int cil, int cm): Motorizado(mc,m,a,c,cil) {
	carga_maxima = cm;
}

int Camiao::info() const {
	Motorizado::info();
	cout << "Carga maxima: " << carga_maxima << endl;
	return 6;
}

Bicicleta::Bicicleta(string mc, int m, int a, string t): Veiculo(mc, m ,a) {
	tipo = t;
}

int Bicicleta::info() const {
	Veiculo::info();
	cout << "Tipo: " << tipo << endl;
	return 4;
}

float Bicicleta::calcImposto() const { return 0; }



