#ifndef SRC_ANIMAL_H_
#define SRC_ANIMAL_H_

#include "veterinario.h"
#include <string>
using namespace std;

class Animal {
protected:
	string nome;
	int idade;
	Veterinario *vet;
	static int maisJovem;
public:
	/**
	 * Constructor for the Animal class
	 * @param nome Animal name
	 * @param idade Animal age
	 */
	Animal(string nome, int idade);

	/**
	 * Animal class Destructor
	 */
	virtual ~Animal(){};

	/**
	 * Name getter method
	 * @return Animal name
	 */
	string getNome() const;

	/**
	 * Age getter method
	 * @return Animal age
	 */
	int getIdade() const;

	/**
	 * Assigned veterinary getter method
	 * @return Animal assigned veterinary
	 */
	Veterinario* getVet() const;

	/**
	 * Youngest animal getter method
	 * @return Younger of the existent animal's age
	 */
	static int getMaisJovem() { return maisJovem; }

	/**
	 * Verify if the animal is considered young
	 * @return bool representing if the animal is young
	 */
	virtual bool eJovem() const = 0;

	/**
	 * Get the attributes' information of the animal
	 * @return string with the animal's information
	 */
	virtual string getInformacao() const;

	/**
	 * Assign a veterinary to the animal
	 * @param Veterinary to assign
	 * @return bool representing operation success
	 */
	bool alocaVet(Veterinario *vet);
};

class Cao: public Animal {
	string raca;
public:
	/**
	 * Constructor for the Cao class
	 * @param nome Cao name
	 * @param idade Cao age
	 * @param raca Cao breed
	 */
	Cao(string nome, int idade, string raca);

	/**
	 * Verify if the cao is considered young
	 * @return bool representing if the cao is young
	 */
	bool eJovem() const;

	/**
	 * Get the attributes' information of the Cao
	 * @return string with the Cao's information
	 */
	string getInformacao() const;
};



class Voador {
	int velocidade_max;
	int altura_max;
public:
	/**
	 *
	 */
	Voador(int vmax, int amax);
	virtual ~Voador(){};
	virtual string getInformacao() const;
};



class Morcego: public Animal, public Voador {
public:
	Morcego(string nome, int idade, int vmax, int amax);
	bool eJovem() const;
	string getInformacao() const;
};


#endif /* SRC_ANIMAL_H_ */
