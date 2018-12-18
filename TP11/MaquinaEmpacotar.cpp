/*
 * Empacotador.cpp
 */

#include "MaquinaEmpacotar.h"
#include <sstream>


MaquinaEmpacotar::MaquinaEmpacotar(int capCaixas): capacidadeCaixas(capCaixas)
{}

unsigned MaquinaEmpacotar::numCaixasUsadas() {
	return caixas.size();
}

unsigned MaquinaEmpacotar::addCaixa(Caixa& cx) {
	caixas.push(cx);
	return caixas.size();
}

HEAP_OBJS MaquinaEmpacotar::getObjetos() const {
	return this->objetos;
}

HEAP_CAIXAS MaquinaEmpacotar::getCaixas() const {
	return this->caixas;
}


/* a implementar pelos estudantes */

unsigned MaquinaEmpacotar::carregaPaletaObjetos(vector<Objeto> &objs) {

	unsigned loaded = 0;
	vector<Objeto>::iterator it;
	for (it = objs.begin(); it != objs.end(); it++) {
		if (it->getPeso() > capacidadeCaixas) continue;
		loaded++;
		objetos.push(*it);
		it = objs.erase(it);
		it--;
	}
	return loaded;
}


Caixa MaquinaEmpacotar::procuraCaixa(Objeto& obj) {
	Caixa cx = Caixa(capacidadeCaixas);
	unsigned size = caixas.size();
	vector<Caixa> vecCaixas;
	for (size_t i = 0; i < size; i++) {
		vecCaixas.push_back(caixas.top());
		caixas.pop();
	}

	vector<Caixa>::iterator it;
	for (it = vecCaixas.begin(); it != vecCaixas.end(); it++) {
		if (it->getCargaLivre() >= obj.getPeso()) {
			cx = *it;
			vecCaixas.erase(it);
			break;
		}
	}

	for (size_t i = 0; i < vecCaixas.size(); i++)
		caixas.push(vecCaixas[i]);

	return cx;
}


unsigned MaquinaEmpacotar::empacotaObjetos() {
	unsigned usedBoxes = 0;

	vector<unsigned> ids;

	unsigned n_objs = objetos.size();
	for (unsigned i = 0; i < n_objs; i++) {
		Objeto obj = objetos.top();
		objetos.pop();

		Caixa box = procuraCaixa(obj);
		box.addObjeto(obj);
		caixas.push(box);
		bool repeatedBox = false;
		for (unsigned j = 0; j < ids.size(); j++)
			if (ids[j] == box.getID())
				repeatedBox = true;

		if (!repeatedBox) {
			ids.push_back(box.getID());
			usedBoxes++;
		}
	}

	return usedBoxes;
}

string MaquinaEmpacotar::imprimeObjetosPorEmpacotar() const {
	string retString = "";

	if (objetos.size() == 0) return "Nao ha objetos!\n";

	HEAP_OBJS copy = objetos;

	unsigned n_objs = copy.size();
	for (unsigned i = 0; i < n_objs; i++) {
		Objeto obj = copy.top();
		copy.pop();

		ostringstream oss;
		oss << obj;
		retString += oss.str() + '\n';
	}

	return retString;
}



Caixa MaquinaEmpacotar::caixaMaisObjetos() const {
	if (caixas.size() == 0) throw MaquinaSemCaixas();

	HEAP_CAIXAS copy = caixas;
	unsigned n_boxes = copy.size();

	unsigned maxObjs = 0;
	Caixa cx;
	for (unsigned i = 0; i < n_boxes; i++) {
		Caixa temp = copy.top();
		copy.pop();
		if (temp.getSize() > maxObjs) {
			maxObjs = temp.getSize();
			cx = temp;
		}
	}
	return cx;
}



