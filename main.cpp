#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <vector>
using namespace std;


//Print function for debugging
void printArray(double *x, int len)
{   for(int i=0; i<len; i++)
        printf(" %6.2lf",x[i]);
    printf("\n");
}

// If expected error happens, teminated the program.
void error(int id)
{
    if(id==1)
        printf("ERROR : Memory can't be allocated!!!\n\n");
    else if ( id == 2 )
        printf("ERROR : File not Found!!!\n\n");
    else if ( id == 3 )
        printf("ERROR : Can't create Output File!!!\n\n");
    else if ( id == 4 )
        printf("ERROR : Invalid Number of Arguments!!!\n");
	else if (id == 5)
		printf("No digits in file");
        
    
    exit(1);
}

int read_double_numbers(FILE* fp, bool onlycount, vector<double>& a) {
	double d;
	char c;
	int cnt = 0;
	fseek(fp, 0, SEEK_SET);
	while (1) {
		int i = fscanf(fp, "%lf", &d);
		if (i && isfinite(d)) {
			if (!onlycount) a[cnt] = d;
			cnt++;
		}
		else fscanf(fp, "%c", &c);
		if (feof(fp)) break;
	}
	return cnt;
}


// Main Function
int main(  int argc , char *argv[] )
{
    FILE *fp;            // data file pointer
    FILE *qp;            // query file pointer
    double bsf;          // best-so-far
    vector<double> t, q;       // data array and query array
    int *order;          //new order of the query
    double *u, *l, *qo, *uo, *lo,*tz,*cb, *cb1, *cb2,*u_d, *l_d;


    double d;
    long long i , j;
    double ex , ex2 , mean, std;
    int m=-1, r=-1;
    long long loc = 0;
    double t1,t2;
    int kim = 0,keogh = 0, keogh2 = 0;
    double dist=0, lb_kim=0, lb_k=0, lb_k2=0;
    double *buffer, *u_buff, *l_buff;
    Index *Q_tmp;

    //For every EPOCH points, all cummulative values, such as ex (sum), ex2 (sum square), will be restarted for reducing the floating point error.
    int EPOCH = 100000;

    // If not enough input, display an error.
    if (argc<3)
        error(4);

   
    fp = fopen(argv[1],"r");
    if( fp == NULL )
        error(2);


    qp = fopen(argv[2],"r");
    if( qp == NULL )
        error(2);

    // start the clock
    t1 = clock();
    m= read_double_numbers(fp, true, t);
	if (!m) 
		error(5);
	r = read_double_numbers(qp, true, q);
	if (!r)
		error(5);
    
    q.resize(r);
    t.resize(m);
	read_double_numbers(fp, false, t);
	read_double_numbers(qp, false, q);
    fclose(fp);
	fclose(qp);
    t2 = clock();
    printf("\n");

    
    cout << "Total Execution Time : " << (t2-t1)/CLOCKS_PER_SEC << " sec" << endl;

    
    return 0;
}
