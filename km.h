//
//  km.h
// 
//
//  Created by Aslihan Celik on 9/24/19.
//  Copyright © 2019 Aslihan Celik. All rights reserved.
//

#ifndef km_h
#define km_h


#include <stdio.h>

typedef struct Matrix {
    
    double** A; // data is in type double
    int N, M; //N is the row and M is the column
} Matrix;


/*
 * Create a matrix.
 *
 * @param nrow and ncol are used to specify the size of the matrix as the row and column information of an array.
 * @return the data matrix pointer when in success.
 */
Matrix* CreateMatrix(int nrow,int ncol);

/*
 * Creates a matrix by calling CreateMatrix function as well as stores the coordinates of the data points in this array.
 *
 * @param *filename is used to get the row and column information of the data point matrix.
 * @return the data matrix pointer when in success.
 */
Matrix* SetMatrixData(const char *filename);

/*
 * Creates a matrix to keep the cluster centeroids cordinates as well as assigns the initial centeroid coordinates to the clusters.
 *
 * @param *c is used to get the first k data points' coordinates to assign as first centeroid coordinates and k is the number of clusters.
 * @return the centeroid matrix pointer when in success.
 */
Matrix* Centeroids(int k, Matrix *c);

/*
 * Updates clusters' centeroid coordinates to the average of points assigned to the cluster and calculates the root mean square of distances from the data points to their cluster centers.
 *
 * @param m is a data matrix pointer,c is the centeroid matrix pointer and k is the number of clusters.
 * @return the distance calculated.
 */
double UpdateCenteroids(Matrix *m,Matrix *c, int k);


/*
 * Assigns clusters to data points after they are updated.
 *
 * @param c is the data matrix pointer and m is the cluster's centeroid pointer and k is the number of clusters.
 */
void AssignClusters(int k,Matrix* c,Matrix* m);

/*
 * Prints the matrix.
 *
 * @param m is the matrix pointer.
 */
void PrintMatrix(Matrix* m);


/*
 * Prints the result to the output file.
 *
 * @param filename is output file pointer, m data matrix pointer and k is the number of clusters.
 */
void PrintResult(const char *filename, Matrix* m, int k);

void DeleteMatrix(Matrix* m);

#endif /* km_h */
