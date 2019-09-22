/* 
 * File:    lab1part5.c
 *
 * Description:
 *    Print messages from all processes
 *
 * Compile:    
 *    mpicc ...
 * Usage:        
 *    mpiexec ...
 *
 * Input:
 *    none
 * Output:
 *    none
 */
#include <stdio.h>
#include <string.h>
#include <mpi.h> 

const int MAX_STRING = 100;

int main(void) {
   int src;
   char msg[MAX_STRING];
   
   int my_rank, comm_sz;
   MPI_Comm comm;
   
   MPI_Init(NULL, NULL); 
   comm = MPI_COMM_WORLD;
   MPI_Comm_size(MPI_COMM_WORLD, &comm_sz); 
   MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); 

   if (my_rank == 0) {
       printf("Proc %d of %d > Does anyone have a toothpick?\n", my_rank, comm_sz);
       for(src = 1; src < comm_sz; src++){
         MPI_Recv(msg, MAX_STRING, MPI_CHAR, MPI_ANY_SOURCE, 0, comm, MPI_STATUS_IGNORE);
         printf("%s", msg);
   }} else {
       int buffer;
       MPI_Status status;
       MPI_Probe(MPI_ANY_SOURCE, 0, comm, &status);
       MPI_Get_count(&status, MPI_CHAR, &buffer);
       if (buffer == 1) {
           printf("Proc = %d of = %d Does anyone have a toothpick = %d \n",my_rank, comm_sz);
           MPI_Recv(&msg, buffer, MPI_CHAR, MPI_ANY_SOURCE, 0, comm, &status);
           if (my_rank + 1 != comm_sz) {
               MPI_Send(&msg, 1, MPI_CHAR, ++my_rank, 0, comm);
           };
       };
   };
   
   MPI_Finalize();
   return 0;
}  /* main */
