#include "FastMapCalculs.h"
//In this file, all the "cout" statement have been left under commentary to let you understand how the code can work, and to make your debugging session less difficult


std::string FastMapCalculs::tagName;
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
        distance += pow((firstRefNumber->getTag(tagName)->getTwoGram(i) - secondRefNumber->getTag(tagName)->getTwoGram(i)), 2);
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

        //Then in each file we choose randomly references to compute
        double firstRandomIndex = rand() % references.at(randomFileA)->size();
        double secondRandomIndex = rand() % references.at(randomFileB)->size();
        
        //We store the corresponding references to the number selected
        Reference* firstReference = references.at(randomFileA)->at(firstRandomIndex);
        Reference* secondReference = references.at(randomFileB)->at(secondRandomIndex);

        double distance = calculateDistance(firstReference, secondReference);
        if (AxeX < distance) {
            // We modify the Axe X if we found a bigger value of distance
            AxeX = distance;

            //We copy the references corresponding to the Calculated distance, and keep it as attribute and to not have to look for them in a loop after
            AxeXReferenceA = firstReference;
            AxeXReferenceB = secondReference;
        }
        std::array<double, 3> distanceInfo = { firstRandomIndex,secondRandomIndex,distance };

        //After having created the array with the two references ID and the distance value, we add it to the Arrayof distances,  attribute of the class FastMapCalculs
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
    //To avoid the problems of computation while getting the projection of the coordinates of the references of the Axes, we return exactly the coordinates they should have
    if (refToCalculate->getReferenceNumber() == AxeXReferenceA->getReferenceNumber()) {
        return 0;
    }
    else if (refToCalculate->getReferenceNumber() == AxeXReferenceB->getReferenceNumber()) {
        return AxeX;
    }

    // x = (Dan² + X² - dbn²)/X
    double firstDistance = calculateDistance(refToCalculate, AxeXReferenceA);
    double secondDistance = calculateDistance(refToCalculate, AxeXReferenceB);

    double xpos = (pow(firstDistance, 2) - pow(secondDistance, 2) + pow(AxeX, 2)) / (AxeX*2);

    //cout << "AxeX: " << AxeX << "  Dan: " << calculateDistance(refToCalculate, AxeXReferenceA) << "  Dbn: " << calculateDistance(refToCalculate, AxeXReferenceB) << "  xpos: " << xpos << endl;
  
    return xpos;
}

double FastMapCalculs::calculateYcoord(Reference* refToCalculate, double xCoordinate)
{
    if (refToCalculate->getReferenceNumber() == AxeXReferenceA->getReferenceNumber()) {
        return 0;
    }
    else if (refToCalculate->getReferenceNumber() == AxeXReferenceB->getReferenceNumber()) {
        return AxeY;
    }

    double newDistancetoA = calculateDistance(refToCalculate, AxeYReferenceA);
    double newDistancetoB = calculateDistance(refToCalculate, AxeYReferenceB);
    
    //cout << "ref: " << refToCalculate->getReferenceNumber() << endl;
    //cout << "Distance to A: " << newDistancetoA << " Distance to B:" << newDistancetoB << endl;

    double ypos = (pow(newDistancetoA, 2) - pow(newDistancetoB, 2) + pow(AxeY, 2)) /( AxeY * 2);

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
    int firstReferenceID = -1;
    int secondReferenceID = -1;
    double firstXcoord = 0;
    double secondXcoord = 0;

    //These will be the final ID determined when searching the Axe Y, we initialze them at -1 to avoid computation conflicts
    int maxRefIdA = -1;
    int maxRefIdB = -1;

    for (std::array<double, 3> loop : distanceMatrix)
    {
        //For every distance calculated we must get the id of the references
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

        // D'² = D² - (x1 - x2)²
        double newD = sqrt(pow(loop.at(2), 2) - pow((firstXcoord - secondXcoord), 2));

        //We Change the value of the Axe Y if we find a grater value
        if (newD > AxeY) {
            AxeY = newD;

            maxRefIdA = firstReferenceID;
            maxRefIdB = secondReferenceID;
        }
    }

    //Research of the Corresponding references Objects

    //This part is the most time consuming
    //Due to a implementation of the code, which is to avoid to create objects to save memory, we have to loop a long time on the array of reference to get the good reference
    //So the big way of improve this project is to work on this part of the Calculations
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

void FastMapCalculs::calculateCoord(std::vector<std::vector<Reference*>*>& references, int numberOfRandomPicks, string name)
{
    //We define on which XML tag the operations will proceed
    tagName = name;

    /*
    generateMatrixDistance(references, numberOfRandomPicks);
    cout << "Axe X: " << AxeX << endl;

    cout << "La premiere reference a le numero: " << AxeXReferenceA->getReferenceNumber() << endl;
    cout << "De contenu: " << AxeXReferenceA->getTag(tagName)->getSentence() << endl;
    cout << "De coordonnee x: " << calculateXcoord(AxeXReferenceA) << endl;

    cout << "La seconde reference a le numero: " << AxeXReferenceB->getReferenceNumber() << endl;
    cout << "De contenu: " << AxeXReferenceB->getTag(tagName)->getSentence() << endl;
    cout << "De coordonnee x: " << calculateXcoord(AxeXReferenceB) << endl;
    */


    // Step 1:
    // Heuristic : We compare two by two randomly picked references and determine their distance
    // Goal : calculate longueur axe X max

    // Fill the distance Matrix with the distances value we calculated
    generateMatrixDistance(references, numberOfRandomPicks);

    // assert
    if (AxeXReferenceA == nullptr || AxeXReferenceB == nullptr) {
        cerr << "assert AxeXReferenceA/B = nullptr" << endl;
        ::exit(EXIT_FAILURE);
    }

    //Step 2:
    // Calculation of the X coordinates of the references
    //For each files and
    //for each reference, operate on the reference to determine its X coordinate
    for (int i = 0; i < references.size(); i++) {
        for (int j = 0; j < references.at(i)->size(); j++)
        {
            finalCoord.push_back({(double) references.at(i)->at(j)->getReferenceNumber(), calculateXcoord(references.at(i)->at(j)), 0 });
        }
    }

    cout << "AxeXReferenceA : " << AxeXReferenceA->getReferenceNumber() << " Element Parsed :" << AxeXReferenceA->getTag("title")->getSentence() << endl;
    //cout << "a pour coordonnes x :" << getXCoordinate(AxeXReferenceA->getReferenceNumber()) << endl;
    cout << endl;
    cout << "AxeXReferenceB : " << AxeXReferenceB->getReferenceNumber() << " Element Parsed :" << AxeXReferenceB->getTag("title")->getSentence() << endl;
    //cout << "a pour coordonnes x :" << getXCoordinate(AxeXReferenceB->getReferenceNumber()) << endl;
    cout << "AxeX : " << AxeX << endl;


    //Step 3:
    // Goal : Operate on the same matrix distance created earlier, and Make an operation on every distances calculated to determine a new dimension
    generateAxeY(references);

    // assert
    if (AxeYReferenceA == nullptr || AxeYReferenceB == nullptr) {
        cerr << "assert AxeYReferenceA/B = nullptr" << endl;
        ::exit(EXIT_FAILURE);
    }

    cout << "AxeYReferenceA : " << AxeYReferenceA->getReferenceNumber() << " Element Parsed :" << AxeYReferenceA->getTag("title")->getSentence() << endl<<endl;
    cout << "AxeYReferenceB : " << AxeYReferenceB->getReferenceNumber() << " Element Parsed :" << AxeYReferenceB->getTag("title")->getSentence() << endl;
    cout << "AxeY : " << AxeY << endl;


    //Etape 4
    //Calculations of the coordinates Y of each references
    //For Each File and for each references, 
    for (int i = 0; i < references.size(); i++) {
        for (int j = 0; j < references.at(i)->size(); j++)
        {
            double xCoord = getXCoordinate(references.at(i)->at(j)->getReferenceNumber()); //This step make the calculation very long
            finalCoord.at(j).at(2) = calculateYcoord(references.at(i)->at(j), xCoord);
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
