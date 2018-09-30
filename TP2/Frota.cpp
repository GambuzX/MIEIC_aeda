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
		int ano = veiculos[i]->getAno();
		if (ano < menor) {
			menor = ano;
		}
	}
	return menor;
}


