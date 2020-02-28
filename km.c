//
//  km.c
// 
//
//  Created by Aslihan Celik on 9/24/19.
//  Copyright © 2019 Aslihan Celik. All rights reserved.
//

#include "km.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>



Matrix* CreateMatrix(int nrow,int ncol)
{
    int size = nrow*sizeof(double*) // storage size for row data pointers
    + nrow*ncol*sizeof(double) // storage for actual data
    + sizeof(Matrix);
    Matrix* m = (Matrix*) malloc(size);
    m->M = nrow;
    m->N = ncol;
    m->A = (double**)((char*)m + sizeof(Matrix)); //casting the pointer to char to get the size
    int i;
    double* d = (double*)((char*)m->A + nrow*sizeof(double**)); //casting the pointer to char is necessary to get the size //assigning the size of row pointers
    for (i=0; i<nrow; i++)
    {
        m->A[i] = d;
        d += ncol;
    }
    return m;
}

void DeleteMatrix(Matrix* m)
{
    free(m);
}

Matrix* SetMatrixData(const char *filename)//for creating and filling the data matrix containing data points' coordinates
{
    FILE* fp = fopen(filename, "r");
    if (fp==NULL)
    {
        printf("Cannot open %s\n", filename);
        return 0;
    }
    int nrow, ncol;
    fscanf(fp, "%d %d",&nrow,&ncol);
    printf("SetMatrixData: nrow=%d ncol=%d\n",nrow,ncol);
    ncol=ncol+1;
    Matrix* m = CreateMatrix(nrow,ncol); //creates the data matrix
    int i,j;
    for (i=0; i<nrow; i++) //fills the matrix with data point coordinates
    {
        for(j=0; j<(ncol-1); j++)
        {
           
            fscanf(fp, "%lf",&m->A[i][j]);
        }
    }
    
    
    fclose(fp);
    return m;
}
void PrintMatrix(Matrix* m) //prints matrix
{
    int i;
    for (i=0; i<m->M; i++)
    {
        int j=0;
        printf("[%.6f",m->A[i][j]);
        for(j=1; j<m->N; j++)
        {
            printf(", %.6f",m->A[i][j]);
        }
        printf("]\n");
    }
}

Matrix* Centeroids(int k, Matrix *c){ //to keep the information of centeroids
    
    Matrix *m = CreateMatrix(k,c->N); //centeroids
    
    //to get the centeroids initially
    
    int i,j;
    //for loop assigns the first centeroids from first k data points
    
    for (i=0; i<k; i++)
    {
        for(j=0; j<c->N; j++){
            
            m->A[i][j] = c->A[i][j];
        }
    }
    
    
    
    return m;
}

void AssignClusters(int k,Matrix* c,Matrix* m){ //assigning clusters
    
    int nrow=c->M; //data matrix
    int ncol=c->N;
    
    int i,j,z;
    
    for (i=0; i<nrow; i++) //for each data point
        
    {
        double d=-1;
        
        for (z=0; z<k; z++){ //calculate distance for each different k
            double distance=0;
            
            for(j=0; j<ncol-1; j++){ //use each dimension
                
                
                distance += (fabs((c->A[i][j])-(m->A[z][j])))*(fabs((c->A[i][j])-(m->A[z][j]))); //sum of squares distance
                
                
            }
            
            if(d==-1){
                d=distance;
                c->A[i][ncol-1]=z;
                
            }
            else if(distance<d){
                
                d=distance;
                c->A[i][ncol-1]=z;
                
            }
            
            
        }
        
    }
    
}

double UpdateCenteroids(Matrix *m, Matrix *c, int k){
    
    int i,j,z;
    int nrow= m->M; //data matrix
    int ncol= m->N;
    
    //updates centroids
    for(i=0; i<k; i++){
        
        for(z=0;z<ncol-1;z++){
            
            double sum=0;
            int count=0;
            
            for(j=0;j<nrow;j++){
                
                if(m->A[j][ncol-1]==i){ 
                    
                    sum+=m->A[j][z];
                    count++;
                    
                }
                
            }
            c->A[i][z]=sum/count; //centeroid matrix
            
        }
        
    }
    
    //calculate the root mean square distance
    
    double distance=0;
    int number=0;

         //calculate distance for each different k
            
        for (i=0; i<nrow; i++){ //for each data point
                
             for (z=0; z<k; z++){
            
                 for(j=0; j<ncol-1; j++){ //use each dimension
                     
                     if(m->A[i][ncol-1]==z){
                
                        distance += (fabs((m->A[i][j])-(c->A[z][j])))*(fabs((m->A[i][j])-(c->A[z][j])));
                        number++;
                         
                     }
                     
                 }
                 
             }
            
        }
    
    distance= distance/number;
    distance= sqrt(distance);
    
    return distance;
}

void PrintResult(const char *filename, Matrix* m, int k) //prints to the output file
{
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Could not open file\n");
        return;
    }
    fprintf(fp,"%d %d %d\n",m->M, m->N - 1, k);
    for (int i=0; i<m->M; i++)
    {
        for(int j=0; j<m->N; j++)
        {
            if(j == m->N - 1){
                fprintf(fp,"%d\n",(int)m->A[i][j]);
            }else{
                fprintf(fp,"%lf ",m->A[i][j]);
            }
        }
    }
    fclose(fp);
}
