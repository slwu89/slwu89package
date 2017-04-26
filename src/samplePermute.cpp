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

// [[Rcpp::export]]
IntegerVector multinomGSL(int seed, unsigned int N, NumericVector probs){
  
  gsl_rng *r = gsl_rng_alloc(gsl_rng_mt19937);
  gsl_rng_set(r,seed);
  
  size_t K = probs.size(); // number of categories
  
  unsigned int sample[K]; // array of counts
  gsl_ran_multinomial(r,K,N,probs.begin(),sample); // sample
  
  IntegerVector out(K); // format output as IntegerVector
  for(int i=0; i<K; i++){
    out[i] = sample[i];
  }
  
  
  return(out);
}

// [[Rcpp::export]]
IntegerVector sampleGSL(int seed, int x, NumericVector probs){
  
  gsl_rng *r = gsl_rng_alloc(gsl_rng_mt19937);
  gsl_rng_set(r,seed);
  
  size_t K = int(x);
  
  gsl_ran_discrete_t * sampler;
  sampler = gsl_ran_discrete_preproc(K, probs.begin());
  
  size_t ii;
  IntegerVector out(x);
  
  for(int i=0; i<x; i++){
    ii = gsl_ran_discrete(r,sampler);
    out[i] = ii;
  }
  
  gsl_ran_discrete_free(sampler);
  gsl_rng_free(r);
  
  return(out);
}






