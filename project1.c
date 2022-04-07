#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<stdbool.h>
#define E 2.71828
#define t 0.001
double get_pa(double l){
	double n = t*l;
	double p = 1-(1/pow(E,n));
	return p;
}
double get_pd(double mu,int i){
        double n = t*mu*i;
        double p = 1-(1/pow(E,n));
        return p;
}


int main(int argc,char* argv[]){
	int server = 10;
	int in_s = 0;
	int queue = 0;
	int q = 0;
	int arrival = 0;
	int departure = 0;
	int block;
	double pa,pd;
	double a,d;
	double bp;
	double erl;
	srand(time(NULL));

	
	for(double l=0.01;l<=10;l=l*10.0){
		for(double mu=0.01;mu<=10.24;mu=mu*4.0){
			for(int i=0;i<10000;i++){
				a = (double)(rand()/(RAND_MAX+1.0))/100;
				d = (double)(rand()/(RAND_MAX+1.0))/100;
				pa = get_pa(l);
				//printf("%f, %f\n",a,pa);
				if(a<pa){
					arrival++;
					if(in_s<server){
						in_s++;
					}	
					else if(in_s>=server){
						//printf("hi\n");
						if(q<queue){
							q++;
						}
						else if(q>=queue){
							block++;
						}
					}

				}
				//printf("%d\n",in_s);
				pd = get_pd(mu,in_s);
				//printf("%f, %f\n",a,pa);
				//printf("%f, %f\n",d,pd);
				if((d<=pd)&&(in_s != 0)){
					departure++;
					in_s--;
					if(q!=0){
						q--;
						in_s++;	
					}
				}
				//printf("%d, %d, %d, %d, %d\n",arrival,departure,block,in_s,q);
			}
			
			//printf("%d, %d, %d, %d, %d\n",arrival,departure,block,in_s,q);
			
			erl = l/mu;
			bp = block / (double)arrival;
			printf("%f, %f\n\n",erl,bp);
			arrival = 0;
                	departure = 0;
               	 	block = 0;
                	q = 0;
                	in_s = 0;
		}
	}
	return 0;
}
