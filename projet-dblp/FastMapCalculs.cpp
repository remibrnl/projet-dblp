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

double FastMapCalculs::calculateModifiedDistance(Reference* firstRefNumber, double firstxCoordinate, Reference* secondRefNumber, double secondxCoordinate)
{
    double distance = calculateDistance(firstRefNumber, secondRefNumber);
    double newDistance = sqrt(pow(distance, 2) - pow(firstxCoordinate - secondxCoordinate, 2));

    //cout << "Reference A :" << firstRefNumber->getReferenceNumber() << " Reference B :" << secondRefNumber->getReferenceNumber() << " NewDistance :" << newDistance << endl;
    return newDistance;


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

double FastMapCalculs::getAxeX()
{
    return AxeX;
}

double FastMapCalculs::getAxeY()
{
    return AxeY;
}

double FastMapCalculs::getXCoordinate(int referenceNumber)
{
    for (int i = 0; i < finalCoord.size(); i++) {
        if (referenceNumber == finalCoord.at(i).at(0)) return finalCoord.at(i).at(1);
    }
}

double FastMapCalculs::getYCoordinate(int referenceNumber)
{
    for (int i = 0; i < finalCoord.size(); i++) {
        if (referenceNumber == finalCoord.at(i).at(0)) return finalCoord.at(i).at(2);
    }
}

double FastMapCalculs::calculateXcoord(Reference* refToCalculate)
{
	// x = (Dan� + X� - dbn�)/X
	
    double xpos = (pow(calculateDistance(refToCalculate, AxeXReferenceA), 2) - pow(calculateDistance(refToCalculate, AxeXReferenceB), 2) + pow(AxeX, 2)) / AxeX*2;

    //cout << "AxeX: " << AxeX << "  Dan: " << calculateDistance(refToCalculate, AxeXReferenceA) << "  Dbn: " << calculateDistance(refToCalculate, AxeXReferenceB) << "  xpos: " << xpos << endl;

    return xpos;
}

double FastMapCalculs::calculateYcoord(Reference* refToCalculate, double xCoordinate)
{
    //We collect the coordinate X of the references used to determine the Y Axe
    double AxeYrefACoordX = getXCoordinate(AxeXReferenceA->getReferenceNumber());
    double AxeYrefBCoordX = getXCoordinate(AxeXReferenceB->getReferenceNumber());//Comme on appelle plusieurs fois la m�thode, on calcule plusieurs fois ces deux coordonn�es et �a rallonge bcp l'execution
                                                                                 //Soit on passe en prametre les coordonn�es des ref de l'axeY, soit on les gardes en attribut de la classe (je pr�f�re le parametre)

    double newDistancetoA = calculateModifiedDistance(refToCalculate, xCoordinate, AxeYReferenceA, AxeYrefACoordX);
    double newDistancetoB = calculateModifiedDistance(refToCalculate, xCoordinate, AxeYReferenceB, AxeYrefBCoordX);
    double ypos = (pow(newDistancetoA, 2) - pow(newDistancetoB, 2) + pow(AxeY, 2)) / AxeY * 2;

    //cout << "AxeY: " << AxeY << "  Dan: " << newDistancetoA << "  Dbn: " << newDistancetoB << "  ypos: " << ypos << endl;
    
    return ypos;
}

void FastMapCalculs::generateAxeY(std::vector<std::vector<Reference*>*>& references)
{
    //This method proceed in 4 steps
    // Search, for each row of the distance Matrix, the id of the reference corresponding to this distance row
    // Search, for these ID, their corresponding X coordinate
    // Calculate the new "modified" distance
    // Determine the Axe Y, which is the maximum of these modified distances

    //These are the informations searched during the two first steps
    int firstReferenceID = 0;
    int secondReferenceID = 0;
    double firstXcoord = 0;
    double secondXcoord = 0;

    //These are the id determined when searching the Axe Y
    int maxRefIdA = 0;
    int maxRefIdB = 0;

    //for(int loop = 0 ; loop<distanceMatrix.size(); loop++)
    for (std::array<double, 3> loop : distanceMatrix)
    {
        //firstReferenceID = distanceMatrix.at(loop).at(0);
        //secondReferenceID = distanceMatrix.at(loop).at(1);
        firstReferenceID = loop.at(0);
        secondReferenceID = loop.at(1);

        #pragma omp parallel for
        for(int search = 0; search < finalCoord.size(); search++){
            if( firstReferenceID == finalCoord.at(search).at(0)){
                firstXcoord = finalCoord.at(search).at(1);
            }else if(secondReferenceID == finalCoord.at(search).at(0)){
                secondXcoord = finalCoord.at(search).at(1);
            }
        }

        // D'� = D� - (x1 - x2)�
        // double newD = sqrt(pow(distanceMatrix.at(loop).at(2), 2) - pow((firstXcoord - secondXcoord), 2));
        double newD = sqrt(pow(loop.at(2), 2) - pow((firstXcoord - secondXcoord), 2));

        if (newD > AxeY) {
            AxeY = newD;
            maxRefIdA = firstReferenceID;
            maxRefIdB = secondReferenceID;
        }
    }
    //RECHERCHE DE L'OBJET REFERENCE CORRESPONDANT //paralleliser
    //#pragma omp parallel for
    for(std::vector<Reference*>* file : references) {
        for(Reference* ref : *file) {
            if(ref->getReferenceNumber() == maxRefIdA){
                AxeYReferenceA = ref;
            }
            else if(ref->getReferenceNumber() == maxRefIdB){
                AxeYReferenceB = ref;
            }

            //free(ref); //Once the y coordinate calculated, we don't need the reference anymore and  we free the object
        }
    }

}

void FastMapCalculs::calculateCoord(std::vector<std::vector<Reference*>*>& references, int numberOfRandomPicks)
{
    // Etape 1 :
	// Heuristique : comparaison deux � deux de r�f�rences s�lectionn�es au hasard
    // But : calculer longueur axe X max
    //This method is very long to operate

	// remplire matrice des distances ref a ref des ref selectionnees au hasard
    generateMatrixDistance(references, numberOfRandomPicks);

    cout << "AxeXReferenceA : " << AxeXReferenceA->getReferenceNumber() << " Element Parsed :"<< AxeXReferenceA->getTag("title")->getSentence() << endl;
    cout << "AxeXReferenceB : " << AxeXReferenceB->getReferenceNumber() << " Element Parsed :"<< AxeXReferenceB->getTag("title")->getSentence() << endl;
    cout << "AxeX : " << AxeX << endl;

    //Etape 2:
    // Calcul projet� des refs sur AxeX
    //For each files and
    //for each reference, operate on the reference to determine its X coordinate
    for (int i = 0; i < references.size(); i++) {
        for (int j = 0; j < references.at(i)->size(); j++)
        {
            finalCoord.push_back({ (double) references.at(i)->at(j)->getReferenceNumber(), calculateXcoord(references.at(i)->at(j)), 0 });
        }
    }

    
    //Etape 3:
    generateAxeY(references);

    cout << "AxeYReferenceA : " << AxeYReferenceA->getReferenceNumber() << " Element Parsed :" << AxeYReferenceA->getTag("title")->getSentence() << endl;
    cout << "AxeYReferenceB : " << AxeYReferenceB->getReferenceNumber() << " Element Parsed :" << AxeYReferenceA->getTag("title")->getSentence() << endl;
    cout << "AxeY : " << AxeY << endl;


    //Etape 4:

    //Calculations of the coordinates Y of each references
    //For Each File and for each references, 
    #pragma omp parallel for
    for (int i = 0; i < references.size(); i++) {
        for (int j = 0; j < references.at(i)->size(); j++)
        {
            double xCoord = getXCoordinate(references.at(i)->at(j)->getReferenceNumber()); //This step make the calculation very long
            finalCoord.at(j).at(2) = calculateYcoord(references.at(i)->at(j),xCoord);
        }
    }
    
}

void FastMapCalculs::printCoords()
{
    cout << "AxeX : " << AxeX << endl;
    cout << "AxeY : " << AxeY << endl;

    for (std::array<double, 3> ref : finalCoord) {
        cout << "id: " << ref.at(0) << " x: " << ref.at(1) << " y: " << ref.at(2) << endl;
    }
}
