
#include"Facilitation.hpp"
#include"Random.hpp"

unsigned long Individual::id_MAX = 0;

Individual::Individual(Species *sp, double x, double y) : p(x,y), id(id_MAX++){
	setSpecies(sp);
}
Individual::Individual(Species *sp, Position p) : p(p), id(id_MAX++){
	setSpecies(sp);
}

void	Individual::setSpecies(Species *sp) {
	species = sp;
	G = species->getG();
	R = species->getR();
	D = species->getD(p);
	facilitation = species->getFac();
	Rad = species->getRad();
	SqRad = Rad*Rad;
	seedStage = species->getSeedStage();
	ref = species->add(this);

	if(facilitation > D) facilitation = D;
	if(facilitation > 0) initNeighbours();

}

double Individual::getTotalRate(){

	if(facilitation > 0 && !neighbours.empty()) return G+R+D-facilitation;
	else return G+R+D;
}

bool   Individual::isPresent(Position p2){
	p2 -= p;
	if((p2.x)*(p2.x) + (p2.y)*(p2.y) < SqRad) return true;
	else return false;
}

void   Individual::act(){
	double r = Random(G+R+D);

	//	std::cout << "sp=" << species->getId() << "\n";

	if(r < G) grow();
	else if (r < G+R) reproduce();
	else die();
}

void Individual::print(){
	std::cout << id <<  "," << p.x << "," << p.y << "\n";
}

status_line Individual::getStatus(){
	/* NOTE: on changing this type please change the typedef on Facilitation.hpp */
	status_line ret  = {species->getId(),id,p.x,p.y};
	return ret;
}

void 	Individual::grow(){
	species->remove(this->ref);
	setSpecies(species->getNextStage());
}

void	Individual::reproduce(){
	seedStage->disperseIndividual(p);
}

void 	Individual::die(){
	std::list<Individual*>::iterator i;
	species->remove(this->ref);

	for(i=neighbours.begin();i!=neighbours.end();i++){
		(*i)->removeNeighbour(this);
	}
	delete(this);
}

void Individual::initNeighbours(){
	std::list<Individual*>::iterator i;
	neighbours = species->getFacilitators(p);

	for(i=neighbours.begin();i!=neighbours.end();i++){
		(*i)->addNeighbour(this);
	}
}

void 	Individual::addNeighbour(Individual *i){
	neighbours.push_back(i);
}

void 	Individual::removeNeighbour(Individual *i){
	neighbours.remove(i);
}

