#include "FastMapCalculs.h"
#include <cmath>
#include <array>

#define TOTAL_CHAR_NUMBER 1369

double FastMapCalculs::calculateDistance(Reference* firstRefNumber, Reference* secondRefNumber)
{
    double distance = 0;
    for (int i = 0; i < TOTAL_CHAR_NUMBER; i++)
    {
        distance += pow((firstRefNumber->getTag("title")->getTwoGram(i) - secondRefNumber->getTag("title")->getTwoGram(i)) , 2);
    }
    return sqrt(distance);
}

void FastMapCalculs::generateMatrixDistance(std::vector<std::vector<Reference*>*>& references, int numberOfDistances)
{
    //We declare three variable which will be changed at every loop step
    //The first is on the file of the reference selected, because we parse different files so differents arrays are created
    //And we choose randomly two references to get a distance value
    int randomFile = 0;
    int firstRandomIndex = 0;
    int secondRandomIndex = 0;

    for (int i = 0; i < numberOfDistances; i++) {

        //We first determine on which file will be picked the ref
        randomFile = rand() % references.size();

        double firstRandomIndex = rand() % references.at(randomFile)->size();//+numérodefichier*maxlignes (une fois le problème de dédoublement d'ID réglé)
        double secondRandomIndex = rand() % references.at(randomFile)->size();

        //We storage the corresponding references to the number selected
        Reference* firstReference = references.at(randomFile)->at(firstRandomIndex);
        Reference* secondReference = references.at(randomFile)->at(secondRandomIndex);

        double distance = calculateDistance(firstReference, secondReference);
        std::array<double, 3> distanceInfo = { firstRandomIndex,secondRandomIndex,distance };
        distanceMatrix.push_back(distanceInfo);
    }

    double AxeX = 0;

    for (int i = 0; i < distanceMatrix.size(); i++) {
        //The distances are stored ate third psoition of the array of the distanceMatrix vector
        if (AxeX < distanceMatrix.at(1).at(3)) {
            AxeX = distanceMatrix.at(1).at(3);
        }
    }
}


void FastMapCalculs::calculateCoord(std::vector<std::vector<Reference*>*>& references, int numberOfRandomPicks)
{
    // Etape 1 :
	// Heuristique : comparaison deux à deux de références sélectionnées au hasard
    // But : calculer longueur axe X max
    //This method is very long to operate
    generateMatrixDistance(references,numberOfRandomPicks);

    //Etape 2:
    //For each files and
    //for each reference, operate on the reference to determine its X coordinate
    for (int i = 0; i < references.size(); i++) {
        for (int j = 0; j < references.at(i)->size();j++)
        {
            calculateXcoord(references.at(i)->at(j));
        }

    }

    //Etape 3:
    generateMatrixDistanceP();

    //Etape 4:
    for (int i = 0; i < references.size(); i++) {
        for (int j = 0; j < references.at(i)->size(); j++)
        {
            calculateYcoord(references.at(i)->at(j));
        }

    }
}
