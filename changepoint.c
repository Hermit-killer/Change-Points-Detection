#include <stdio.h>
#include <changepoint.h>

int IsChagePoint(int data,struct paramerters * par, struct values * val){
    AddDataToDelays(data, val);
    double pis[DATASIZE] = {0};
    double P = 0;
    if(val->length>=2){
        for(int i=0;i<val->length;i++){
            pis[i]=Norm_Pdf(data,par->u0[i],(par->beta[i]*(par->v[i]+1))/(par->v[i]*par->alpha[i]));
        }
        double growth_probs[DATASIZE] = {0};
        CalGroPro(growth_probs,pis,val);
        double cp_prob;
        CalCpPro(&cp_prob,pis,val);
        GetNewJoint(cp_prob,growth_probs,val);
        double evidence;
        GetEvi(&evidence,val);
        GetR(val,evidence);
        if(val->length>=OMEGA-1){
            P = val->R[val->length-1][OMEGA-1];
        }
    }
    RefeshParameters(data,par);
    if(val->length <= OMEGA){
        printf("--------------------------------\n");
        printf("|Little data! Please input more|\n");
        printf("--------------------------------\n");
        return 0;
    }
    else if(P>ETA){
        printf("--------------------------------\n");
        printf("|Detection happens.Pay attention|\n");
        printf("|Sequence:%d,value:%d|\n",val->length-OMEGA+1,val->delays[val->length-OMEGA]);
        printf("--------------------------------\n");
        return 1;
    }
    return 0;
}


double Norm_Pdf(int data,double mean, double var){
    double coefficient = 1.0 / (var * sqrt(2 * M_PI));
    double exponent = -0.5 * pow((data - mean) / var, 2);
    double result = coefficient * exp(exponent);
    if(result < 0.000001){
        result = 0.000001;
    }
    return result;
}

void RefeshParameters(int data,struct paramerters * par){
    for(int i=DATASIZE-1;i>0;i--){
        par->u0[i] = (par->v[i-1]*par->u0[i-1]+data)/(par->v[i-1]+1);
        par->v[i] = par->v[i-1]+1;
        par->alpha[i] = par->alpha[i-1] + 1/2;
        par->beta[i] = par->beta[i-1] + (par->v[i-1]/(1+par->v[i-1]))*(data-par->u0[i-1])*(data-par->u0[i-1])/2;
    }
    par->u0[0]=U0_INIT;
    par->v[0]=V_INIT;
    par->alpha[0]=alpha_INIT;
    par->beta[0]=beta_INIT;
    par->length++;
}

void InitParameters(struct paramerters * par){
    for(int i=0;i<DATASIZE;i++){
        par->u0[i] = 0;
        par->v[i] = 0;
        par->alpha[i] = 0;
        par->beta[i] = 0;
    }
    par->u0[0]=U0_INIT;
    par->v[0]=V_INIT;
    par->alpha[0]=alpha_INIT;
    par->beta[0]=beta_INIT;
    par->length=1;
}

void InitValues(struct values * val){
    for(int i=0;i<DATASIZE;i++){
        val->delays[i]=0;
        val->message[i]=0;
        for(int j=0;j<DATASIZE;j++){
            val->R[i][j]=0;
        }
    }
    val->message[0]=1;
    val->R[0][0]=1;
    val->length = 0;
}

void AddDataToDelays(int data,struct values * val){
    val->delays[val->length] = data;
    val->length++;
}
void CalGroPro(double * pro,double * pis, struct values * val){
    for(int i =0;i<DATASIZE;i++){
        pro[i]=pis[i]*val->message[i]*(1-EPSILON);
    }
}

void CalCpPro(double * pro,double * pis, struct values * val){
    double tmp =0;
    for(int i=0;i<DATASIZE;i++){
        tmp += pis[i]*val->message[i]*EPSILON;
    }
    *pro = tmp;
}

void GetNewJoint(double cp,double *gro,struct values * val){
    for(int i=DATASIZE-1;i>0;i--){
        val->message[i] = gro[i-1];
    }
    val->message[0]= cp;
}

void GetEvi(double * evi,struct values * val){
    double tmp;
    for(int i=0;i<DATASIZE;i++){
        tmp += val->message[i];
    }
    *evi = tmp;
}

void GetR(struct values * val,double evi){
    for(int i=0;i<DATASIZE;i++){
        val->R[val->length-1][i]=val->message[i]/evi;
    }
}