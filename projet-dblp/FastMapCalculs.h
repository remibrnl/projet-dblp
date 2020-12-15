#pragma once
#include <vector>
#include <exception>
#include <cstdlib>
#include <cmath>
#include <array>
#include "Reference.h"
#include "Tag.h"

class FastMapCalculs
{
	private:

		static double AxeX;
		static double AxeY;
	
		/*
		 * Copies of the references used to make the axes
		 */
		static Reference AxeXReferenceA;
		static Reference AxeXReferenceB;
		static Reference AxeYReferenceA;
		static Reference AxeYReferenceB;
	

		//This matrix contains all the distances on the references, first index is the number of the first references, second index is for the second, and the last is the distance between the two references
		/**
			Like this : [ Ref1 | Ref 2 | Distance 1-2]
		*/
		static std::vector<std::array<double, 3>> distanceMatrix;

		//This matrix contains all coordinates of the references
		/*
			Like this : [ RefNumber | coordX | coordY ]
		*/
		static std::vector<std::array<double, 3>> finalCoord; 

	public:
		/**
			This method is a mathematical calculation to determine distance between two object of N Dimensions.
			It returns its distance as a double variable.
		*/
		static double calculateDistance(Reference* firstRefNumber, Reference* secondRefNumber);

		
		/*
			This method generates a Matrix of distances between different references.
			The parameter is the number of references used in the Heuristic to determine later the X Axe.
			Finally, after having determined the matrix, the X Axe is choosen as the biggets distance between all the distances referenced
		*/
		static void generateMatrixDistance(std::vector<std::vector<Reference*>*>& references, int numberOfDistances);

		/*
			These two methods are the getters in access on the Axe X and Axe Y;
		*/
		static double getAxeX();
		static double getAxeY();
		
		/*
			In this method, the matrix generated is calculated based on the previous distances matrix.
			The new distances used to calculate Y Axe are calculated following:

			D' = Dab - (xa - xb) Where a and b are two references

			This new "distance" is the result of the difference between the old distance and other difference between the two X coordonates of references calculated previously

			As a condition, the x coordinates must be calculated
		*/
		static void generateMatrixDistanceP(std::vector<std::vector<Reference*>*>& references, int numberOfDistances);

		/*
			These methods calculate the coordinates x and y of each references
		*/
		static double calculateXcoord(Reference* refToCalculate);
		static double calculateYcoord(Reference* refToCalculate);

		/*
			This method start all the process;
			The parameters are a containers of all the references we want to operate on, and a number of the distances calculated by an heuristic to determine the axes
		*/
		static void calculateCoord(std::vector<std::vector<Reference*>*>& references, int numberOfRandomPicks);

		
		static void printCoords();
};