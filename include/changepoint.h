#ifndef changepoint_H
#define changepoint_H
#include <math.h>
#define DATASIZE 30
#define ETA 0.5
#define OMEGA 4
#define EPSILON 0.125

#define U0_INIT 470
#define V_INIT 1
#define alpha_INIT 1
#define beta_INIT 0.1

struct paramerters
{
    double u0[DATASIZE];
    double v[DATASIZE];
    double alpha[DATASIZE];
    double beta[DATASIZE];
    int length;
};

struct values
{
    int delays[DATASIZE];
    double message[DATASIZE];
    double R[DATASIZE][DATASIZE];
    int length;
};

int IsChagePoint(int,struct paramerters *, struct values *);
double Norm_Pdf(int,double,double);
void RefeshParameters(int,struct paramerters *);
void InitParameters(struct paramerters *);
void InitValues(struct values *);
void AddDataToDelays(int data,struct values * val);
void CalGroPro(double *, double * , struct values *);
void CalCpPro(double *, double * , struct values *);
void GetNewJoint(double ,double *,struct values *);
void GetEvi(double *,struct values *);
void GetR(struct values *,double);
#endif
