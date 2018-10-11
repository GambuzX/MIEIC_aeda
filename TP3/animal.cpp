
#include "animal.h"
#include <sstream>

string Animal::getNome() const {
	return nome;
}

int Animal::getIdade() const {
	return idade;
}

Veterinario* Animal::getVet() const {
	return vet;
}

Animal::Animal(string nome, int idade) {
	this->nome = nome;
	this->idade = idade;
	vet = NULL;
	if (Animal::maisJovem == -1 || Animal::maisJovem > idade) Animal::maisJovem = idade;
}

int Animal::maisJovem = -1;

string Animal::getInformacao() const {
	ostringstream oss;
	oss << nome << ", " << idade;
	if (vet != NULL) {
		oss << ", " << vet->getNome() << ", " << vet->getCodOrdem();
	}
	return oss.str();
}

bool Animal::alocaVet(Veterinario *vete) {
	if (vete == NULL) return 1;
	vet = vete;
	return 1;
}

Cao::Cao(string nome, int idade, string raca): Animal(nome,idade) {
	this->raca = raca;
}

bool Cao::eJovem() const { return idade<5; }

string Cao::getInformacao() const {
	return (Animal::getInformacao() + ", " + raca);
}

Voador::Voador(int vmax, int amax) {
	velocidade_max = vmax;
	altura_max = amax;
}

string Voador::getInformacao() const {
	ostringstream oss;
	oss << velocidade_max << ", " << altura_max;
	return oss.str();
}

Morcego::Morcego(string nome, int idade, int vmax, int amax): Animal(nome, idade), Voador(vmax, amax) { }

bool Morcego::eJovem() const { return idade<4; }

string Morcego::getInformacao() const {
	return (Animal::getInformacao() + ", " + Voador::getInformacao());
}

