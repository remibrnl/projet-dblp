#include "FastMapCalculs.h"

double FastMapCalculs::AxeX = 0;
double FastMapCalculs::AxeY = 0;
Reference FastMapCalculs::AxeXReferenceA(0);
Reference FastMapCalculs::AxeXReferenceB(0);
Reference FastMapCalculs::AxeYReferenceA(0);
Reference FastMapCalculs::AxeYReferenceB(0);
std::vector<std::array<double, 3>> FastMapCalculs::distanceMatrix;
std::vector<std::array<double, 3>> FastMapCalculs::finalCoord;

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
    int randomFileA = 0;
    int randomFileB = 0;
    int firstRandomIndex = 0;
    int secondRandomIndex = 0;
    AxeX = 0;

    for (int i = 0; i < numberOfDistances; i++) {

        //We first determine which file will be picked the ref
        randomFileA = rand() % references.size();
        randomFileB = rand() % references.size();

        double firstRandomIndex = rand() % references.at(randomFileA)->size();
        double secondRandomIndex = rand() % references.at(randomFileB)->size();

        //We store the corresponding references to the number selected
        Reference* firstReference = references.at(randomFileA)->at(firstRandomIndex);
        Reference* secondReference = references.at(randomFileB)->at(secondRandomIndex);

        double distance = calculateDistance(firstReference, secondReference);
        if (AxeX < distance) {
            // on recalcule l'axe X
            AxeX = distance;

            // on copie les refs A et B de cette distance / copy constructor
            AxeXReferenceA = *firstReference;
            AxeXReferenceB = *secondReference;
        }
        std::array<double, 3> distanceInfo = { firstRandomIndex,secondRandomIndex,distance };
        distanceMatrix.push_back(distanceInfo);
    }

}

void FastMapCalculs::generateMatrixDistanceP(std::vector<std::vector<Reference*>*>& references, int numberOfDistances)
{
    
}

double FastMapCalculs::calculateXcoord(Reference* refToCalculate)
{
    // param : AxeX, reference a et reference b qui font l'axe X

	// x = (Dan² + X² + dbn²)/X
	
    double xpos = ( pow(calculateDistance(refToCalculate, &AxeXReferenceA), 2) + pow(calculateDistance(refToCalculate, &AxeXReferenceB), 2) + pow(AxeX, 2) ) / AxeX;
	
    return xpos;
}

double FastMapCalculs::calculateYcoord(Reference* refToCalculate)
{
    return 0;
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
            finalCoord.push_back({ (double) references.at(i)->at(j)->getReferenceNumber(), calculateXcoord(references.at(i)->at(j)), 0 });
        }
    }

    /*
    //Etape 3:
    generateMatrixDistanceP(references, numberOfRandomPicks);

    //Etape 4:
    for (int i = 0; i < references.size(); i++) {
        for (int j = 0; j < references.at(i)->size(); j++)
        {
            finalCoord.at(i).at(2) = calculateYcoord(references.at(i)->at(j));
        }

    }
    */
}

void FastMapCalculs::printCoords()
{
    for (std::array<double, 3> ref : finalCoord) {
        cout << "id: " << ref.at(0) << ", x: " << ref.at(1) << ", y: " << ref.at(2) << endl;
    }
}
