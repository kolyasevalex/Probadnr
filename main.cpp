#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <vector>
using namespace std;
using Match = pair<pair<double, int>, pair<int, int>>;
vector<Match> DNRTPM(vector <double>& stream, vector <double>& query, bool best_query, int n_query, bool disjoint, double threshold);

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
    int m=-1, r=-1;
    double t1,t2;
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
