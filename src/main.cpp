#include"Individual.h"
#include<iostream>
#include<fstream>
#include<string>
#include<Rcpp.h>

// [[Rcpp::export]]
Rcpp::DataFrame simulation(double maxtime, int num_pops, Rcpp::IntegerVector num_stages,Rcpp::NumericVector parameters, double dispersal, Rcpp::NumericVector interactions, 
        Rcpp::IntegerVector init, Rcpp::DataFrame history,
        bool restore=false, double w=100, double h=100, int bcond=1, int dkernel=1, int maxpop=30000){
	int *in, i,n, n_total=0;
    double *par, *inter;
	bool test=true,populated;
	Arena *arena;
	int numturns=0;
	History * ret;

    in = init.begin();
    par = parameters.begin();
    inter = interactions.begin();

    for(i=0;i<num_pops;i++){
        n_total+=num_stages[i];
    }

	arena = new Arena(n_total,par,w,h,bcond);
	arena->setInteractions(inter,0); // 0 interaction slope because it's not implemented yet

    for(i=0,n=1; i<num_pops; i++){
        if(num_stages[i] == 1){
            // create sigle-stage species
            arena->createSimpleSpecies(n,dispersal,dkernel);
            n++;
        }
        else {
            // create structured species
            arena->createStructuredSpecies(n,num_stages[i],dispersal,dkernel);
            n+=num_stages[i];
        }
    }

    if(restore){
        populated = arena->populate(history);
    }
    else{
        populated = arena->populate(in);
    }
    if(!populated) return NULL;

	while(arena->getTotalTime() < maxtime && test){
		test = arena->turn();
		numturns++;
		if(arena->getTotalAbundance() > maxpop) {
			Rcpp::warning("Maximum population reached. Stopping...");
			test = false;
		}
	}

	ret = arena->finalStatus();

	return Rcpp::DataFrame::create(Rcpp::Named("sp")=ret->sp_list,Rcpp::Named("id")=ret->id_list,
			Rcpp::Named("x")=ret->x_list,Rcpp::Named("y")=ret->y_list,
			Rcpp::Named("begintime")=ret->beginTime_list,Rcpp::Named("endtime")=ret->endTime_list);
}
