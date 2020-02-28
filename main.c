//
//  main.c
// 
//
//  Created by Aslihan Celik on 9/24/19.
//  Copyright © 2019 Aslihan Celik. All rights reserved.
//
#include <stdlib.h>
#include <stdio.h>
#include "km.h"

int main(int argc, char *argv[]) {
    FILE *trainfp;
    
    
    trainfp = fopen(argv[1], "r");
    
    
    if( trainfp == NULL) {
        printf("inputfile io error");
        return 1;
        
    }
    fclose(trainfp); // close when you're done
    
   
    
    int k= atoi(argv[2]);
    
    if(k>0){
        
        printf("%d ",k);
        Matrix* m = SetMatrixData(argv[1]); //matrix m for data
        
        Matrix *d =Centeroids(k, m); //matrix d for centeroid matrix, assigns the first centeroid coordinates
   
    
        int i;
        double e= atof(argv[4]);

        int steps=atoi(argv[3]);
        
        int n=1;
        printf("Step %d",n);
        
        AssignClusters(k,m,d); //assigns clusters to data point
        printf("\n \n");
        double temp = UpdateCenteroids(m,d,k); //updates centeroids' coordinates and calculates RMS
        PrintMatrix(d);
        printf("\n%lf \n", temp);
        
    
        for(i=0; i < steps-1; i++){
            n++;
            printf("\nStep %d \n",n);
            AssignClusters(k,m,d); //assigns clusters to data point
            double new = UpdateCenteroids(m,d,k);
            PrintMatrix(d);
            printf("\n%lf \n", new);
            
            if(e>0){
                if(new-temp <= e){
                printf("Final cluster assignment is: \n");
                AssignClusters(k,m,d);
                PrintMatrix(m);
                break;
                    
                }
                
            }
            
            else if(e==0){
                if(new-temp == e){
                    printf("\nFinal cluster assignment is: \n");
                    AssignClusters(k,m,d);
                    PrintMatrix(m);
                    break;
                    
                }
                
            }
            temp = new;

        }
        
        PrintResult(argv[5], m, k);
        
    }
    else{
    printf("Error:Enter a positive k value. \n");
    }

    return 0;
}
