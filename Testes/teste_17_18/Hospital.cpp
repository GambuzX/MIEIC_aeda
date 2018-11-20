/*
 * Hospital.cpp
 */

#include "Hospital.h"
//
#include <algorithm>


Hospital::Hospital(unsigned trayC):trayCapacity(trayC)
{ }

void Hospital::addDoctor(const Doctor &d1) {
	doctors.push_back(d1);
}

list<Doctor> Hospital::getDoctors() const {
	return doctors;
}

void Hospital::addTrays(stack<Patient> tray1) {
	letterTray.push_back(tray1);
}

list<stack<Patient> > Hospital::getTrays() const {
	return letterTray;
}



unsigned Hospital::numPatients(string medicalSpecialty) const
{
	unsigned total = 0;

	for (const auto & doctor: doctors){
		if (doctor.getMedicalSpecialty() == medicalSpecialty){
			total += doctor.getPatients().size();
		}
	}

	return total;

}

void Hospital::sortDoctors() {
	vector<Doctor> ord;
	for (const auto & doc : doctors) ord.push_back(doc);

	for (unsigned int p = 1; p < ord.size(); p++)
	{
		Doctor tmp = ord[p];
		int j;
		for (j = p; j > 0 && tmp < ord[j-1]; j--)
			ord[j] = ord[j-1];
		ord[j] = tmp;
	}

	doctors.clear();
	for (auto & ele : ord) doctors.push_back(ele);
}





bool Hospital::addDoctor(unsigned codM1, string medicalSpecialty1) {
	int nDocs = 0;
	for (const auto & doc : doctors)
		if (doc.getMedicalSpecialty() == medicalSpecialty1)
			nDocs++;
	if (nDocs >= 3) return false;
	doctors.push_back(Doctor(codM1, medicalSpecialty1));
	return true;
}



queue<Patient> Hospital::removeDoctor(unsigned codM1) {
	list<Doctor>::iterator it;
	queue<Patient> p1;
	for (it = doctors.begin(); it != doctors.end(); it++)
		if (it->getCode() == codM1) {
			p1 = it->getPatients();
			doctors.erase(it);
			return p1;
		}

	throw DoctorInexistent();

}


bool Hospital::putInLessBusyDoctor(unsigned cod1, string medicalSpecialty1) {

	int stackSize = -1;
	Doctor * lessOcupied = NULL;

	for (auto & doctor: doctors) {
		if (doctor.getMedicalSpecialty() == medicalSpecialty1) {
			if ((int) doctor.getPatients().size() < stackSize || stackSize == -1) {
				stackSize = doctor.getPatients().size();
				lessOcupied = &doctor;
			}
		}
	}

	if (stackSize == -1) return false;

	lessOcupied->addPatient(Patient(cod1, medicalSpecialty1));
	return true;

}



void Hospital::processPatient(unsigned codM1) {

	for (Doctor & doc: doctors) {
		if(doc.getCode() == codM1) {
			Patient pat(1, "");
			try {
				pat = doc.removeNextPatient();
			}
			catch(Doctor::PatientInexistent & excp) {
				break;
			}
			bool inserted = false;
			for (auto & band : letterTray) {
				if (band.size() < trayCapacity) {
					band.push(pat);
					inserted = true;
					break;
				}
			}
			if (!inserted) {
				stack<Patient> newS;
				newS.push(pat);
				letterTray.push_back(newS);
			}
			break;
		}
	}

}


unsigned Hospital::removePatients(unsigned codP1) {
	unsigned total = 0;
	list<stack<Patient>>::iterator it;
	for (it = letterTray.begin(); it != letterTray.end(); it++) {
		if (it->top().getCode() == codP1){
			it->pop();
			total++;
		}
		if (it->size() == 0) letterTray.erase(it--);
	}

	return total;
}



