/*
 * FEUPConsulting.cpp
 *
 *  Created on: 10/12/2017
 *      Author: CS
 */

#include "FEUPConsulting.h"
#include <iostream>

FEUPConsulting::FEUPConsulting(): expertizes(Expertize("", 0)) {
}

FEUPConsulting::FEUPConsulting(vector<Project*> projects): expertizes(Expertize("", 0)) {
	this->projects = projects;
}

void FEUPConsulting::addProjects(vector<Project*> projects) {
	this->projects = projects;
}

vector<Project*> FEUPConsulting::getProjects() const{
	return this->projects;
}


// get the expertize objet with the given name, including all students with the corresponding skills
Expertize FEUPConsulting::getExpertize(string name, unsigned cost) {
	Expertize itemNotFound("", 0);
	Expertize expertize(name, cost);
	Expertize search = expertizes.find(expertize);

	return search;
}


void FEUPConsulting::addProject(Project* project) {
	//TODO
	Expertize itemNotFound("", 0);
	Expertize expertize(project->getExpertize(), project->getCost());
	Expertize search = expertizes.find(expertize);

	if(search == itemNotFound) {
		this->expertizes.insert(expertize);
	}

	projects.push_back(project);
}

BST<Expertize> FEUPConsulting::getExpertizes() const {
	return this->expertizes;
}

void FEUPConsulting::addNewExpertize(const Expertize & expertize1) {
	this->expertizes.insert(expertize1);
}

vector<StudentPtr> FEUPConsulting::getStudents() const {
	vector<StudentPtr> ptrs;
	HashTabStudentPtr::const_iterator it1 = this->students.begin();
	HashTabStudentPtr::const_iterator it2 = this->students.end();
	for(; it1 != it2; it1++) {
			ptrs.push_back(*it1); //We can make it a bit more complex by considering only records with a condition!
	}
	return ptrs;
}

void FEUPConsulting::setStudents(vector<StudentPtr>& newStudents) {
	for(unsigned i = 0; i < newStudents.size(); i++) students.insert(newStudents[i]);
}

priority_queue<Student> FEUPConsulting::getActiveStudents() const {
	return activeStudents;
}
void FEUPConsulting::setActiveStudents(priority_queue<Student>& students) {
	activeStudents = students;
}


//
// TODO: Part I   - BST
//

void FEUPConsulting::addAvailability(Student* student, string expertizeAvailable, unsigned cost) {
	BSTItrIn<Expertize> it(expertizes);
	while (!it.isAtEnd()) {
		Expertize & exp = it.retrieve();
		if (exp.getName() == expertizeAvailable && exp.getCost() == cost) {
			exp.addConsultant(student);
			return;
		}
		it.advance();
	}

	Expertize newExp(expertizeAvailable, cost);
	newExp.addConsultant(student);
	expertizes.insert(newExp);
}


Expertize getExpertize(string name, unsigned cost);

vector<Student*> FEUPConsulting::getCandidateStudents(Project* project) const {
	vector<Student*> temp;

	FEUPConsulting copy = *this;

	Expertize exp = copy.getExpertize(project->getExpertize(), project->getCost());
	vector<Student*> curr = exp.getConsultants();
	for (unsigned i = 0; i < curr.size(); i++){

		if (curr.at(i)->getCurrentProject() == "")
			temp.push_back(curr.at(i));
	}

	return temp;

}


bool FEUPConsulting::assignProjectToStudent(Project* project, Student* student) {

	if (project->getConsultant() != 0 || student->getCurrentProject() != "")
		return false;

	vector<Student*> valid = getCandidateStudents(project);
	for (unsigned i = 0; i < valid.size(); i++) {
		if (valid.at(i)->getName() == student->getName()) {
			student->addProject(project->getTitle());
			project->setConsultant(student);
			return true;
		}
	}
	return false;
}

//
// TODO: Part II  - Hash Table
//

void FEUPConsulting::addStudent(Student* student) {
	students.insert(StudentPtr(student));

}

void FEUPConsulting::changeStudentEMail(Student* student, string newEMail) {
	HashTabStudentPtr::iterator it = students.find(student);
	StudentPtr oldS = *it;
	if (it == students.end()) return;

	students.erase(it);
	oldS.setEMail(newEMail);
	students.insert(oldS);
}


//
// TODO: Part III - Priority Queue
//

void FEUPConsulting::addActiveStudents(const vector<Student>& candidates, int min) {
	for (unsigned i = 0; i < candidates.size(); i++) {
		if (candidates.at(i).getPastProjects().size() >= (unsigned) min)
			activeStudents.push(candidates.at(i));
	}
}


int FEUPConsulting::mostActiveStudent(Student& studentMaximus) {

	if (activeStudents.size() == 0) return 0;

	priority_queue<Student> copy = activeStudents;
	Student top = copy.top();
	copy.pop();
	Student secondTop = copy.top();

	if (top.getPastProjects().size() == secondTop.getPastProjects().size() ) return 0;

	studentMaximus = activeStudents.top();
	return (int) activeStudents.size();
}





















