#include<list>
#include<cstdlib>
#include<iostream>
#include<array>
#include"Position.hpp"
#include<Rcpp.h>

#ifndef FACILITATION_H
#define FACILITATON_H
#define FACILITATION_NUMPARAMETERS 4

class Species;
class Individual;

typedef std::list<double> status_line;
typedef std::list<status_line> status_list;

class Arena {
	private:
	int lifestages,spnum;
	double width, height;
	double totalRate, *ratesList, totalTime;
	Species **stages;
	Species *facilitator;
	int bcond;

	public:
	Arena(int lifestages, double * baserates, double * facilitation, double width, double height, int bcond);

	/* high level functions */
	bool populate(int *stagesinit);
	bool turn();

	/* acessors for Species and Individuals */
	bool findFacilitator(Position p);
	std::list<Individual*> getFacilitators(Position p);
	std::list<Individual*> addFacilitated(Individual *ind,Position p, double radius);
	Position boundaryCondition(Position p);

	/* output functions */
	status_list getStatus();
	double* getAbundance();
	double getTotalTime();
	void print();
};

class Species {
	private:
	unsigned int id;
	double G, R, D, Rad, facilitation, dispersalRadius;
	double totalRate;

	Arena *arena;
	std::list<Individual*> population;
	Species *nextStage, *seedStage;

	public:
	Species(Arena *ar,int id, double *par);
	Species(Arena *ar,int id, double D, double G, double R, double Rad,double dispersalRadius);
	void setFacilitation(double f);

	double getTotalRate();
	double getG();
	double getR();
	double getD(Position p);
	double getRad();
	double getFac();
	unsigned int getId();
	Species* getNextStage();
	Species* getSeedStage();

	/* if radius is unspecified (=0), the radius used is the species own radius */
	bool isPresent(Position p, double radius = 0);
	std::list<Individual*> getFacilitators(Position p);
	/* if radius is unspecified (=0), the radius used is the species own radius */
	std::list<Individual*> getPresent(Position p, double radius = 0);
	void addIndividual(double x, double y);
	void addIndividual(Position p);	
	void disperseIndividual(double x, double y);
	void disperseIndividual(Position p);	
	Position dispersalKernel();
	void act();

	void setNextStage(Species *st);
	void setSeedStage(Species *st);

	void remove(std::list<Individual*>::iterator i);
	std::list<Individual*>::iterator add(Individual *i);

	void print(double time);

	status_list getStatus(double time);
	double getAbundance();
};


class Individual {
	private:
	static unsigned long id_MAX;
	Position p;
	const unsigned long id;
	double R, D, G, Rad, SqRad, facilitation;
	double actualD();
	double totalRate;
	Species *species, *seedStage;
	std::list<Individual*>::iterator ref;
	std::list<Individual*> neighbours;
	void initNeighbours();

	public:
	Individual(Species *sp, Position p);
	Individual(Species *sp, double x, double y);
	double getTotalRate();
	bool isPresent(Position p, double radius = 0);
	void print();
	void act();
	/** adds a neighbour list and cross-adds yourself to everyone in that list */
	void addNeighbourList(std::list<Individual*> neighList);
	/** adds a neighbour to the list. Don't forget to add cross-reference to neighbour's list! */
	void addNeighbour(Individual *i);
	/** removes neighbour from list. Doesn't remove cross-reference from neighbour's list */
	void removeNeighbour(Individual *i);
	
	status_line getStatus();

	private:
	void setSpecies(Species *sp);
	void grow();
	void reproduce();
	void die();

};




#endif
