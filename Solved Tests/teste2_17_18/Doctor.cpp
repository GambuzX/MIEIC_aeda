/*
 * Doctor.cpp
 */

#include "Doctor.h"


Patient::Patient(unsigned codP, string mS): codeP(codP), medicalSpecialty(mS)
{}

string Patient::getMedicalSpecialty() const {
	return medicalSpecialty;
}

unsigned Patient::getCode() const {
	return codeP;
}

Doctor::Doctor(unsigned codM, string mS): codeM(codM), medicalSpecialty(mS)
{}


Doctor::Doctor(unsigned codM, string mS, queue<Patient> patients1): codeM(codM), medicalSpecialty(mS), patients(patients1)
{}

unsigned Doctor::getCode() const {
	return codeM;
}

string Doctor::getMedicalSpecialty() const {
	return medicalSpecialty;
}

queue<Patient> Doctor::getPatients() const {
	return patients;
}

void Doctor::addPatient(const Patient &p1) {
	patients.push(p1);
}

Patient Doctor::removeNextPatient() {
	if (!patients.empty()) {
		Patient p1 = patients.front();
		patients.pop();
		return p1;
	}
	else throw PatientInexistent();
}




void Doctor::moveToFront(unsigned codP1) {
	queue<Patient> temp = patients;
	queue<Patient> newQueue;
	while (temp.size() > 0) {
		Patient pat = temp.front();
		temp.pop();
		if (pat.getCode() == codP1) newQueue.push(pat);
	}
	while(patients.size() > 0) {
		Patient pat = patients.front();
		patients.pop();
		if (pat.getCode() != codP1) newQueue.push(pat);
	}
	patients = newQueue;


}

bool Doctor::operator<(Doctor & doc) {
	if (medicalSpecialty == doc.getMedicalSpecialty() && patients.size() == doc.getPatients().size())
		return codeM < doc.getCode();
	else if (patients.size() == doc.getPatients().size())
		return medicalSpecialty < doc.getMedicalSpecialty();
	return patients.size() < doc.getPatients().size();
}

