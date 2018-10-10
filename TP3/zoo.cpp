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
