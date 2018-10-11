#include "zoo.h"
#include <sstream>


int Zoo::numAnimais() const {
	return animais.size();
}

int Zoo::numVeterinarios() const {
	return veterinarios.size();
}

void Zoo::adicionaAnimal(Animal *a1) {
	animais.push_back(a1);
}

string Zoo::getInformacao() const {
	string info = "";
	vector<Animal *>::const_iterator it;
	for (it = animais.begin(); it != animais.end(); it++) {
		info += (*it)->getInformacao() + "; ";
	}
	return info;
}

bool Zoo::animalJovem(string nomeA) {
	vector<Animal *>::const_iterator it;
	for (it = animais.begin(); it != animais.end(); it++) {
		if ((*it)->getNome() == nomeA)
			return (*it)->eJovem();
	}
	return false;
}

void Zoo::alocaVeterinarios(istream &isV) {
	string name;
	while(getline(isV, name)) {
		string codeS;
		getline(isV, codeS);
		long code = stoi(codeS);
		Veterinario * vet = new Veterinario(name, code);
		veterinarios.push_back(vet);
	}

	size_t vetNum = veterinarios.size();
	for (size_t i = 0; i < animais.size(); i++) {
		animais[i]->alocaVet(veterinarios[i%vetNum]);
	}
}

bool Zoo::removeVeterinario(string nomeV) {

	size_t vetIndex = -1;
	for (size_t i = 0; i < veterinarios.size(); i++) {
		if (veterinarios[i]->getNome() == nomeV) {
			vetIndex = i;
			break;
		}
	}

	if ((int) vetIndex == -1) return false;

	vector<Animal *>::const_iterator it;
	for (it = animais.begin(); it != animais.end(); it++) {
		if (veterinarios.size() <= 1)
			(*it)->alocaVet(NULL);
		else if ((*it)->getVet()->getNome() == nomeV)
			(*it)->alocaVet(veterinarios[(vetIndex + 1) % veterinarios.size()]);
	}

	veterinarios.erase(veterinarios.begin() + vetIndex);
	return true;
}

bool Zoo::operator<(Zoo& zoo2) const {
	int sum1 = 0, sum2 = 0;
	vector<Animal *>::const_iterator it;

	for (it = animais.begin(); it != animais.end(); it++)
		sum1 += (*it)->getIdade();

	for (it = zoo2.animais.begin(); it != zoo2.animais.end(); it++)
		sum2 += (*it)->getIdade();

	return sum1 < sum2 ? sum1 : sum2;
}

