#include <RcppGSL.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
using namespace Rcpp;

// [[Rcpp::depends(RcppGSL)]]

/*
 * gslSample: this shows how to sample without replacement
 */

// [[Rcpp::export]]
IntegerVector gslChoose(int seed, unsigned int k, unsigned int n){

  gsl_rng *r = gsl_rng_alloc(gsl_rng_mt19937);
  gsl_rng_set(r,seed);
  int b[size_t(n)];

  for (int i = 0; i < n; i++){
    b[i] = int(i+1);
  }

  IntegerVector out(k);

  gsl_ran_choose (r, out.begin(), size_t(k), b, size_t(n), sizeof (int));

  return(out);
}

// [[Rcpp::export]]
IntegerVector gslSample(int seed, unsigned int k, unsigned int n){

  gsl_rng *r = gsl_rng_alloc(gsl_rng_mt19937);
  gsl_rng_set(r,seed);
  int b[size_t(n)];

  for (int i = 0; i < n; i++){
    b[i] = int(i+1);
  }

  IntegerVector out(k);

  gsl_ran_sample(r, out.begin(), size_t(k), b, size_t(n), sizeof (int));

  return(out);
}


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
