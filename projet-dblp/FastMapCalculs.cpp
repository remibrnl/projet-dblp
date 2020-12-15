#include "FastMapCalculs.h"

double FastMapCalculs::AxeX = 0;
double FastMapCalculs::AxeY = 0;
Reference* FastMapCalculs::AxeXReferenceA = nullptr;
Reference* FastMapCalculs::AxeXReferenceB = nullptr;
Reference* FastMapCalculs::AxeYReferenceA = nullptr;
Reference* FastMapCalculs::AxeYReferenceB = nullptr;
std::vector<std::array<double, 3>> FastMapCalculs::distanceMatrix;
std::vector<std::array<double, 3>> FastMapCalculs::finalCoord;

double FastMapCalculs::calculateDistance(Reference* firstRefNumber, Reference* secondRefNumber)
{
    double distance = 0;
    for (int i = 0; i < TOTAL_CHAR_NUMBER; i++)
    {
        // distance += pow((firstRefNumber->getTag("title")->getTwoGram(i) - secondRefNumber->getTag("title")->getTwoGram(i)) , 2);
        distance += pow((secondRefNumber->getTag("title")->getTwoGram(i) - firstRefNumber->getTag("title")->getTwoGram(i)), 2);
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
            AxeXReferenceA = firstReference;
            AxeXReferenceB = secondReference;
        }
        std::array<double, 3> distanceInfo = { firstRandomIndex,secondRandomIndex,distance };
        distanceMatrix.push_back(distanceInfo);

        // cout << distance << endl;
        // cout << "A : " << AxeXReferenceA.getReferenceNumber() << endl;
        // cout << "B : " << AxeXReferenceB.getReferenceNumber() << endl;
        // cout << "X : " << AxeX << endl;

    }

}

double FastMapCalculs::calculateXcoord(Reference* refToCalculate)
{
    // param : AxeX, reference a et reference b qui font l'axe X

	// x = (Dan² + X² - dbn²)/X
	
    double xpos = 0.0;

    //xpos = ( pow(calculateDistance(refToCalculate, AxeXReferenceA), 2) - pow(calculateDistance(refToCalculate, AxeXReferenceB), 2) + pow(AxeX, 2) ) / AxeX;
	
    xpos = (pow(calculateDistance(refToCalculate, AxeXReferenceA), 2) - pow(calculateDistance(refToCalculate, AxeXReferenceB), 2) + pow(AxeX, 2)) / AxeX*2;

    cout << "AxeX: " << AxeX << "  Dan: " << calculateDistance(refToCalculate, AxeXReferenceA) << "  Dbn: " << calculateDistance(refToCalculate, AxeXReferenceB) << "  xpos: " << xpos << endl;

    return xpos;
}

void FastMapCalculs::generateAxeY(std::vector<std::vector<Reference*>*>& references)
{
    //CHERCHER, POUR CHAUE LIGNE DE LA MATRICE DE DISTANCE, LES ID DES REFERENCES QUI ONT SERVI A CALCULER LA DISTANCE
    // CHERCHER LES COORD X CORRESPONDANT AUX ID
    // FAIRE LE CALCUL DISTANCE MODIFIEE = sqrt(D² - (x1 -x2)²)
    // SI AXE Y < DISTANCE MODIFIEE, AXE Y = DISTANCE MODIFIEE

    int firstReferenceID = 0;
    int secondReferenceID = 0;
    double firstXcoord;
    double secondXcoord;
    int maxRefIdA = 0;
    int maxRefIdB = 0;

    //for(int loop = 0 ; loop<distanceMatrix.size(); loop++)
    for (std::array<double, 3> loop : distanceMatrix)
    {
        //firstReferenceID = distanceMatrix.at(loop).at(0);
        //secondReferenceID = distanceMatrix.at(loop).at(1);
        firstReferenceID = loop.at(0);
        secondReferenceID = loop.at(1);

        //VERY LONG PROCESS; A PARALLELISER
        #pragma omp parallel for
        for(int search = 0; search < finalCoord.size(); search++){
            if( firstReferenceID == finalCoord.at(search).at(0)){
                firstXcoord = finalCoord.at(search).at(1);
            }else if(secondReferenceID == finalCoord.at(search).at(0)){
                secondXcoord = finalCoord.at(search).at(1);
            }
        }

        // D'² = D² - (x1 - x2)²
        // double newD = sqrt(pow(distanceMatrix.at(loop).at(2), 2) - pow((firstXcoord - secondXcoord), 2));
        double newD = sqrt(pow(loop.at(2), 2) - pow((firstXcoord - secondXcoord), 2));

        if (newD > AxeY) {
            AxeY = newD;
            maxRefIdA = firstReferenceID;
            maxRefIdB = secondReferenceID;
        }
    }


    //RECHERCHE DE L'OBJET REFERENCE CORRESPONDANT
    //#pragma omp parallel for
    for(std::vector<Reference*>* file : references) {
        for(Reference* ref : *file) {
            if(ref->getReferenceNumber() == maxRefIdA){
                AxeYReferenceA = ref;
            }
            else if(ref->getReferenceNumber() == maxRefIdB){
                AxeYReferenceB = ref;
            }
        }
    }

}

void FastMapCalculs::calculateCoord(std::vector<std::vector<Reference*>*>& references, int numberOfRandomPicks)
{
    // Etape 1 :
	// Heuristique : comparaison deux à deux de références sélectionnées au hasard
    // But : calculer longueur axe X max
    //This method is very long to operate

	// remplire matrice des distances ref a ref des ref selectionnees au hasard
    generateMatrixDistance(references, numberOfRandomPicks);

    cout << "AxeXReferenceA : " << AxeXReferenceA->getReferenceNumber() << endl;
    cout << "AxeXReferenceB : " << AxeXReferenceB->getReferenceNumber() << endl;
    cout << "AxeX : " << AxeX << endl;

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

    
    //Etape 3:
    // generateAxeY(references);

    //Etape 4:
    /*
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
    cout << "AxeX : " << AxeX << endl;
    cout << "AxeY : " << AxeY << endl;

    for (std::array<double, 3> ref : finalCoord) {
        cout << "id: " << ref.at(0) << " x: " << ref.at(1) << " y: " << ref.at(2) << endl;
    }
}
