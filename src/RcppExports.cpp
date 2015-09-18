// This file was generated by Rcpp::compileAttributes
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// test_basic
int test_basic(std::string filename);
RcppExport SEXP facilitation_test_basic(SEXP filenameSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< std::string >::type filename(filenameSEXP);
    __result = Rcpp::wrap(test_basic(filename));
    return __result;
END_RCPP
}
// test_parameter
int test_parameter(Rcpp::NumericVector parameters, double w, double h, int nb, int nf);
RcppExport SEXP facilitation_test_parameter(SEXP parametersSEXP, SEXP wSEXP, SEXP hSEXP, SEXP nbSEXP, SEXP nfSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::NumericVector >::type parameters(parametersSEXP);
    Rcpp::traits::input_parameter< double >::type w(wSEXP);
    Rcpp::traits::input_parameter< double >::type h(hSEXP);
    Rcpp::traits::input_parameter< int >::type nb(nbSEXP);
    Rcpp::traits::input_parameter< int >::type nf(nfSEXP);
    __result = Rcpp::wrap(test_parameter(parameters, w, h, nb, nf));
    return __result;
END_RCPP
}
