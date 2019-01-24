
#include "veterinario.h"

Veterinario::Veterinario(string n, int c) {
	nome = n;
	codOrdem = c;
}

string Veterinario::getNome() const {
	return nome;
}

long Veterinario::getCodOrdem() const {
	return codOrdem;
}



