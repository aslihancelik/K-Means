Author          : Aslihan Celik
Created         : September 21, 2019
Last Modified   : September 27, 2018

Affiliation          : Georgia Institute of Technology


Description
-------------


This program is designed to implement a K means algorithm in order to classifty data. Input to the program are set of data samples as a tuple of n data values. Program partitions data samples into k distinct clusters. In order to assign the data points to the correct cluster program keep updates the kluster centeroids and assign the data points to clusters until the root mean square falls below the threshold that is entered to the command line when running the program.



Installation
------------

To install, simply run
K-Means:
  gcc main.c km.c -std=c99 -o hw4



Execution
-----------

run it using

./knn <training_file> <data_file> <output_file> <k>
	for example:
	./knn output.txt faithful-KNN.txt knn.txt 4

