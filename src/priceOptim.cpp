#include <RcppGSL.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
using namespace Rcpp;

// [[Rcpp::depends(RcppGSL)]]

/*
 * gslShuffle
 *
*/

// [[Rcpp::export]]
IntegerVector gslShuffle(int seed, int size){

  gsl_rng *r = gsl_rng_alloc(gsl_rng_mt19937);
  gsl_rng_set(r,seed);

  IntegerVector out(size);
  for(int i=0; i<size; i++){
    out[i] = (i+1);
  }

  gsl_ran_shuffle(r, out.begin(), size, sizeof(int));

  return(out);
}
