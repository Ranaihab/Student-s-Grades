/**
group cs-2
Rana Ihab Ahmed Fahmy	20190207
Omar Khaled Al Haj		20190351
**/


#include "mpi.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void readFile(const char* name, int points[], int numData){
    char *str[10];
    char* split;
    int i =0;
    FILE* file = fopen(name, "r");
    while(fgets(str,10,file && i<numData)){
        split = strtok(str, " ");
        points[i] = atoi(split);
        i++;
    }
    fclose (file);
}

int numData(const char* name){
    int i =0;
	char *str[15];
    FILE* file = fopen(name, "r");
    while(fgets(str,15,file)){
        i++;
    }
    fclose (file);
	return i;
}


	

int main(int argc , char * argv[]){
	int my_rank;		/* rank of process	*/
	int p;			/* number of process	*/
	int dest;		/* rank of sender	*/
	int i;		
	int my_sum = 0;		
	int sum;
	int *ids;
	int *grades;
	int myFirstIdx;
	int myLastIdx;
	int tag =0;
	int count;
	int remainder;
	
	MPI_Status status;	/* return status for 	*/

	/* Start up MPI */
	MPI_Init( &argc , &argv );
	
	/* Find out process rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	/* Find out number of process */
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	if(my_rank==0){
		printf("Hi");
		scanf("%d",&sum);
		printf("%d",sum);
		count = numData("Grades.txt");
		ids= malloc(count*sizeof(int));
		grades = malloc(count*sizeof(int));
		readFile("Grades.txt", ids, grades);
	}
	MPI_Bcast(&count, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(ids, count, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(grades, count, MPI_INT, 0, MPI_COMM_WORLD);
	if(my_rank==0){
		myFirstIdx =0;
		myLastIdx = count/p;
		remainder = count % p;
		for(dest =1; dest<p; dest++){
			myFirstIdx = myLastIdx;
			if(remainder!=0){
				myLastIdx++;
				remainder--;
			}
			myLastIdx+=count/p;
			MPI_Send(&myFirstIdx, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
			MPI_Send(&myLastIdx, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
		}
		myFirstIdx =0;
		myLastIdx = count/p;
	}
	else{
		MPI_Recv(&myFirstIdx, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &status );
		MPI_Recv(&myLastIdx, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &status );
	}
	
	for(i=myFirstIdx; i<myLastIdx;i++){
		if(grades[i]>=60){
			my_sum++;
			printf("%d Passed The Exam.\n",ids[i]);
		}else{
			printf("%d Failed. Please Repeat The Exam.\n",ids[i]);
		}
	}
	
	MPI_Reduce(&my_sum, &sum, 1, MPI_INT, MPI_SUM,0, MPI_COMM_WORLD);

	if( my_rank == 0)
	{
		printf("Total number of students passed the exam is %d out of %d\n",sum,count);
	}
	/* shutdown MPI */
	MPI_Finalize();
	return 0;
}


