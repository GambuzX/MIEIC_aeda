/*
 * Garage.h
 *
 *  Created on: 24/10/2017
 *      Author: hlc
 */

#ifndef SRC_GARAGE_H_
#define SRC_GARAGE_H_

#include <vector>

template <class Vehicle>
class Garage {
	std::vector<Vehicle *> vehicles;
	const unsigned int capacity;
public:
	Garage(int size);
	~Garage();
	std::vector<Vehicle *> getVehicles() const;
	void setVehicles(std::vector<Vehicle *> vehicles);
	int getCapacity() const;
	bool addVehicle(Vehicle *vehicle);
	Vehicle* removeVehicle(std::string brand, std::string model);
	float avgPrice(std::string brand) const;
	void sortVehicles();
};

class NoSuchVehicleException {
public:
	NoSuchVehicleException() { }
};

class NoSuchBrandException {
	std::string brand;
public:
	NoSuchBrandException(std::string b) { brand = b; }
	std::string getBrand() { return brand; }
};

template <class Vehicle>
Garage<Vehicle>::Garage(int size) : capacity(size) {
}

template <class Vehicle>
Garage<Vehicle>::~Garage() {
	typename std::vector<Vehicle *>::const_iterator it;
	for (it=vehicles.begin(); it!=vehicles.end(); it++) {
		delete *it;
	}
}

template<class Vehicle>
std::vector<Vehicle *> Garage<Vehicle>::getVehicles() const {
	return vehicles;
}

template<class Vehicle>
void Garage<Vehicle>::setVehicles(std::vector<Vehicle*> vehicles) {
	this->vehicles = vehicles;
}

template<class Vehicle>
int Garage<Vehicle>::getCapacity() const {
	return capacity;
}

template<class Vehicle>
bool Garage<Vehicle>::addVehicle(Vehicle * vehicle) {
	if (vehicles.size() >= capacity) return false;
	for (size_t i = 0; i < vehicles.size(); i++)
		if (*vehicles[i] == *vehicle)
			return false;

	vehicles.push_back(vehicle);
	return true;
}

template<class Vehicle>
void Garage<Vehicle>::sortVehicles() {
	for (unsigned i = 1; i < vehicles.size(); i++) {
		Vehicle * tmp = vehicles.at(i);
		int j;
		for (j = i; j > 0 && *tmp < *(vehicles[j-1]); j--)
			vehicles[j] = vehicles[j-1];
		vehicles[j] = tmp;
	}
}

template<class Vehicle>
Vehicle* Garage<Vehicle>::removeVehicle(std::string brand, std::string model) {
	int index = -1;
	for (size_t i = 0; i < vehicles.size(); i++)
		if (vehicles.at(i)->getBrand() == brand && vehicles.at(i)->getModel() == model)
			index = i;
	if (index == -1) throw NoSuchVehicleException();

	Vehicle * vehicleToRemove = vehicles[index];
	vehicles.erase(vehicles.begin()+index);
	return vehicleToRemove;
}

template<class Vehicle>
float Garage<Vehicle>::avgPrice(std::string brand) const {
	float total = 0;
	int nV = 0;
	for (size_t i = 0; i < vehicles.size(); i++) {
		if (vehicles.at(i)->getBrand() == brand) {
			total += vehicles.at(i)->getPrice();
			nV++;
		}
	}

	if (total == 0) throw NoSuchBrandException(brand);
	return total/nV;
}

#endif /* SRC_GARAGE_H_ */
