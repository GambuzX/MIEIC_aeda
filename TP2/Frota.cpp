#include "Frota.h"
#include "Veiculo.h"
#include <string>

using namespace std;

void Frota::adicionaVeiculo(Veiculo * v1) {
	veiculos.push_back(v1);
}

int Frota::numVeiculos() const {
	return veiculos.size();
}

int Frota::menorAno() const {
	int menor = 0;
	for (unsigned i = 0; i < veiculos.size(); i++) {
		int ano = (veiculos.at(i))->getAno();
		if (ano < menor || menor == 0) {
			menor = ano;
		}
	}
	return menor;
}

vector<Veiculo *> Frota::operator() (int anoM) const {
	vector<Veiculo *> vehicles;
	for (const auto & veic : veiculos) {
		if (anoM == veic->getAno()) vehicles.push_back(veic);
	}
	return vehicles;
}

float Frota::totalImposto() const{
	float total;
	for (const auto & veic: veiculos) {
		total += veic->calcImposto();
	}
	return total;
}

