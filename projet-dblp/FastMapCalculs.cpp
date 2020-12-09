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

        //We first determine which file will be picked the ref
        randomFile = rand() % references.size();

        double firstRandomIndex = rand() % references.at(randomFile)->size();//+numérodefichier*maxlignes (une fois le problème de dédoublement d'ID réglé)
        double secondRandomIndex = rand() % references.at(randomFile)->size();

        //We store the corresponding references to the number selected
        Reference* firstReference = references.at(randomFile)->at(firstRandomIndex);
        Reference* secondReference = references.at(randomFile)->at(secondRandomIndex);

        double distance = calculateDistance(firstReference, secondReference);
        std::array<double, 3> distanceInfo = { firstRandomIndex,secondRandomIndex,distance };
        distanceMatrix.push_back(distanceInfo);
    }

    // Calcul de l'axe X

    //double AxeX = 0;
    AxeX = 0;
    int IdLastReferenceA = 0;
    int IdLastReferenceB = 0;

    for (int i = 0; i < distanceMatrix.size(); i++) {
        //The distances are stored at third position of the array of the distanceMatrix vector

        if (AxeX < distanceMatrix.at(i).at(2)) {
            // on recalcule l'axe X
            AxeX = distanceMatrix.at(i).at(2);

            // on sauvegarde l'id des refs A et B de cette distance
            IdLastReferenceA = distanceMatrix.at(i).at(0);
            IdLastReferenceB = distanceMatrix.at(i).at(1);
        }
    }

    // AFAIRE :  Trouver un moyen de recuperer les references a partir de leur id
    // 0 et 0 PROVISOIRES 
    AxeXReferenceA = *references.at(0)->at(0); // IdLastReferenceA
    AxeXReferenceB = *references.at(0)->at(0); // IdLastReferenceB

}

void FastMapCalculs::generateMatrixDistanceP(std::vector<std::vector<Reference*>*>& references, int numberOfDistances)
{
    // juste recopié et modifiée de generateMatrixDistance

    int randomFile = 0;
    int firstRandomIndex = 0;
    int secondRandomIndex = 0;

    for (int i = 0; i < numberOfDistances; i++) {

        //We first determine which file will be picked the ref
        randomFile = rand() % references.size();

        double firstRandomIndex = rand() % references.at(randomFile)->size();//+numérodefichier*maxlignes (une fois le problème de dédoublement d'ID réglé)
        double secondRandomIndex = rand() % references.at(randomFile)->size();

        //We store the corresponding references to the number selected
        Reference* firstReference = references.at(randomFile)->at(firstRandomIndex);
        Reference* secondReference = references.at(randomFile)->at(secondRandomIndex);

        double distance = calculateDistance(firstReference, secondReference);
        std::array<double, 3> distanceInfo = { firstRandomIndex,secondRandomIndex,distance };
        distancePMatrix.push_back(distanceInfo);
    }

    // Calcul de l'axe X

    //double AxeX = 0;
    AxeY = 0;
    int IdLastReferenceA = 0;
    int IdLastReferenceB = 0;

    for (int i = 0; i < distancePMatrix.size(); i++) {
        //The distances are stored at third position of the array of the distanceMatrix vector

        if (AxeX < distancePMatrix.at(i).at(2)) {
            // on recalcule l'axe X
            AxeX = distancePMatrix.at(i).at(2);

            // on sauvegarde l'id des refs A et B de cette distance
            IdLastReferenceA = distancePMatrix.at(i).at(0);
            IdLastReferenceB = distancePMatrix.at(i).at(1);
        }
    }

    // A FAIRE :  Trouver un moyen de recuperer les references a partir de leur id
    // 0 et 0 PROVISOIRES 
    AxeYReferenceA = *references.at(0)->at(0); // IdLastReferenceA
    AxeYReferenceB = *references.at(0)->at(0); // IdLastReferenceB
}

double FastMapCalculs::calculateXcoord(Reference* refToCalculate)
{
    // param : AxeX, reference a et reference b qui font l'axe X

	// x = (Dan² + X² + dbn²)/X
	
    int xpos = (int) ( pow(calculateDistance(refToCalculate, &AxeXReferenceA), 2) + pow(calculateDistance(refToCalculate, &AxeXReferenceB), 2) + pow(AxeX, 2) ) / AxeX;
	
    return xpos;
}

double FastMapCalculs::calculateYcoord(Reference* refToCalculate)
{
    // param : AxeY, reference a et reference b qui font l'axe Y

    // x = (Dan² + X² + dbn²)/X

    int ypos = (int) ( pow(calculateDistance(refToCalculate, &AxeYReferenceA), 2) + pow(calculateDistance(refToCalculate, &AxeYReferenceB), 2) + pow(AxeY, 2) ) / AxeY;

    return ypos;
}

void FastMapCalculs::calculateCoord(std::vector<std::vector<Reference*>*>& references, int numberOfRandomPicks)
{
    // Etape 1 :
	// Heuristique : comparaison deux à deux de références sélectionnées au hasard
    // But : calculer longueur axe X max
    //This method is very long to operate

	// remplire matrice des distances ref a ref des ref selectionnees au hasard
    generateMatrixDistance(references, numberOfRandomPicks);

	

    //Etape 2:
    // Calcul projeté des refs sur AxeX
    //For each files and
    //for each reference, operate on the reference to determine its X coordinate
    for (int i = 0; i < references.size(); i++) {
        for (int j = 0; j < references.at(i)->size(); j++)
        {
            finalCoord.push_back({ references.at(i)->at(j)->getReferenceNumber(), calculateXcoord(references.at(i)->at(j)), -1 });
            // pas sur de cette solution
        }
    }

    //Etape 3:
    generateMatrixDistanceP(references, numberOfRandomPicks);

    //Etape 4:
    for (int i = 0; i < references.size(); i++) {
        for (int j = 0; j < references.at(i)->size(); j++)
        {
            finalCoord.at(i).at(2) = calculateYcoord(references.at(i)->at(j));
            // pas sur de cette solution
        }

    }
}
