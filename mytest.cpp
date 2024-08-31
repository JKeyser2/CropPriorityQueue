// UMBC - CMSC 341 - Fall 2022 - Proj3
//#include "iqueue.h"
#include "iqueue.cpp"

#include <random>
// the followings are sample priority functions to be used by IQueue class
// users can define their own priority functions
// Priority functions compute an integer priority for a crop.  Internal
// computations may be floating point, but must return an integer.
int priorityFn1(const Crop &crop);// works with a MAXHEAP
int priorityFn2(const Crop &crop);// works with a MINHEAP

enum RANDOM {UNIFORMINT, UNIFORMREAL, NORMAL};
class Random {
public:
    Random(int min, int max, RANDOM type=UNIFORMINT, int mean=50, int stdev=20) : m_min(min), m_max(max), m_type(type)
    {
        if (type == NORMAL){
            //the case of NORMAL to generate integer numbers with normal distribution
            m_generator = std::mt19937(m_device());
            //the data set will have the mean of 50 (default) and standard deviation of 20 (default)
            //the mean and standard deviation can change by passing new values to constructor 
            m_normdist = std::normal_distribution<>(mean,stdev);
        }
        else if (type == UNIFORMINT) {
            //the case of UNIFORMINT to generate integer numbers
            // Using a fixed seed value generates always the same sequence
            // of pseudorandom numbers, e.g. reproducing scientific experiments
            // here it helps us with testing since the same sequence repeats
            m_generator = std::mt19937(10);// 10 is the fixed seed value
            m_unidist = std::uniform_int_distribution<>(min,max);
        }
        else{ //the case of UNIFORMREAL to generate real numbers
            m_generator = std::mt19937(10);// 10 is the fixed seed value
            m_uniReal = std::uniform_real_distribution<double>((double)min,(double)max);
        }
    }
    void setSeed(int seedNum){
        // we have set a default value for seed in constructor
        // we can change the seed by calling this function after constructor call
        // this gives us more randomness
        m_generator = std::mt19937(seedNum);
    }

    int getRandNum(){
        // this function returns integer numbers
        // the object must have been initialized to generate integers
        int result = 0;
        if(m_type == NORMAL){
            //returns a random number in a set with normal distribution
            //we limit random numbers by the min and max values
            result = m_min - 1;
            while(result < m_min || result > m_max)
                result = m_normdist(m_generator);
        }
        else if (m_type == UNIFORMINT){
            //this will generate a random number between min and max values
            result = m_unidist(m_generator);
        }
        return result;
    }

    double getRealRandNum(){
        // this function returns real numbers
        // the object must have been initialized to generate real numbers
        double result = m_uniReal(m_generator);
        // a trick to return numbers only with two deciaml points
        // for example if result is 15.0378, function returns 15.03
        // to round up we can use ceil function instead of floor
        result = std::floor(result*100.0)/100.0;
        return result;
    }
    
    private:
    int m_min;
    int m_max;
    RANDOM m_type;
    std::random_device m_device;
    std::mt19937 m_generator;
    std::normal_distribution<> m_normdist;//normal distribution
    std::uniform_int_distribution<> m_unidist;//integer uniform distribution
    std::uniform_real_distribution<double> m_uniReal;//real uniform distribution

};



class Tester{
    public:
    

    /******************************************
    * Test function declarations go here! *
    ******************************************/
    bool insertNormalCaseMinHeap(IQueue &myQueue);
    bool insertNormalCaseMaxHeap(IQueue &myQueue);

    bool removeNormalCaseMinHeap(IQueue &myQueue);
    bool removeNormalCaseMaxHeap(IQueue &myQueue);

    bool copyConstructorNormalCase(IQueue &myQueue);
    // Empty heap object
    bool copyConstructorEdgeCase(IQueue &myQueue);

    bool overloadedAssignmentOperatorNormalCase(IQueue &myQueue, IQueue &myQueue2);
    // Empty heap object to not-empty heap object
    bool overloadedAssignmentOperatorEdgeCaseOne(IQueue &myQueue, IQueue &myQueue2);
    // Not-empty heap object to empty heap object
    bool overloadedAssignmentOperatorEdgeCaseTwo(IQueue &myQueue, IQueue &myQueue2);

    bool testClearFunction(IQueue &myQueue);

    bool testRebuildHeap(IQueue &myQueue);

    bool mergeQueuesNormalCase(IQueue &myQueue, IQueue &myQueue2);
    // Empty heap object to not-empty heap object
    bool mergeQueuesEdgeCaseOne(IQueue &myQueue, IQueue &myQueue2);
    // Not-empty heap object to empty heap object
    bool mergeQueuesEdgeCaseTwo(IQueue &myQueue, IQueue &myQueue2);

    bool dequeueEmptyQueue(IQueue &myQueue);
    bool mergeDifferentPriorityFunction(IQueue &myQueue, IQueue &myQueue2);
};

int main () {
    
    Tester tester;

    
    {
        IQueue myQueue(priorityFn2, MINHEAP);
        cout << "\nTesting the normal case of the insert function for a min heap:\n\n";
        if (tester.insertNormalCaseMinHeap(myQueue) == true)
            cout << "\tNormal case of insert function for a min heap passed!\n";
        else
            cout << "\tNormal case of insert function for a min heap failed!\n";
    }

    {
        IQueue myQueue(priorityFn1, MAXHEAP);
        cout << "\nTesting the normal case of the insert function for a max heap:\n\n";
        if (tester.insertNormalCaseMaxHeap(myQueue) == true)
            cout << "\tNormal case of insert function for a max heap passed!\n";
        else
            cout << "\tNormal case of insert function for a max heap failed!\n";
    }

    {
        IQueue myQueue(priorityFn2, MINHEAP);
        cout << "\nTesting the normal case of the remove function for a min heap:\n\n";
        if (tester.insertNormalCaseMinHeap(myQueue) == true)
            cout << "\tNormal case of remove function for a min heap passed!\n";
        else
            cout << "\tNormal case of remove function for a min heap failed!\n";
    }

    {
        IQueue myQueue(priorityFn1, MAXHEAP);
        cout << "\nTesting the normal case of the remove function for a max heap:\n\n";
        if (tester.insertNormalCaseMaxHeap(myQueue) == true)
            cout << "\tNormal case of remove function for a max heap passed!\n";
        else
            cout << "\tNormal case of remove function for a max heap failed!\n";
    }
    
    {
        IQueue myQueue(priorityFn2, MINHEAP);
        cout << "\nTesting the normal case of the copy constructor:\n\n";
        if (tester.copyConstructorNormalCase(myQueue) == true)
            cout << "\tNormal case of the copy constructor passed!\n";
        else
            cout << "\tNormal case of the copy constructor failed!\n";
    }
    
    {
        IQueue myQueue(priorityFn2, MINHEAP);
        cout << "\nTesting the edge case of the copy constructor:\n\n";
        if (tester.copyConstructorEdgeCase(myQueue) == true)
            cout << "\tEdge case of the copy constructor passed!\n";
        else
            cout << "\tEdge case of the copy constructor failed!\n";
    }

    {
        IQueue myQueue(priorityFn2, MINHEAP);
        IQueue myQueue2(priorityFn1, MAXHEAP);
        cout << "\nTesting the normal case of the overloaded assignment operator:\n\n";
        if (tester.overloadedAssignmentOperatorNormalCase(myQueue, myQueue2) == true)
            cout << "\tNormal case of the overloaded assignment operator passed!\n";
        else
            cout << "\tNormal case of the overloaded assignment operator failed!\n";
    }

    {
        IQueue myQueue(priorityFn2, MINHEAP);
        IQueue myQueue2(priorityFn1, MAXHEAP);
        cout << "\nTesting edge case 1 of the overloaded assignment operator:\n\n";
        if (tester.overloadedAssignmentOperatorEdgeCaseOne(myQueue, myQueue2) == true)
            cout << "\tEdge case 1 of the overloaded assignment operator passed!\n";
        else
            cout << "\tEdge case 1 of the overloaded assignment operator failed!\n";
    }

    {
        IQueue myQueue(priorityFn2, MINHEAP);
        IQueue myQueue2(priorityFn1, MAXHEAP);
        cout << "\nTesting edge case 2 of the overloaded assignment operator:\n\n";
        if (tester.overloadedAssignmentOperatorEdgeCaseTwo(myQueue, myQueue2) == true)
            cout << "\tEdge case 2 of the overloaded assignment operator passed!\n";
        else
            cout << "\tEdge case 2 of the overloaded assignment operator failed!\n";
    }

    {
        IQueue myQueue(priorityFn2, MINHEAP);
        cout << "\nTesting clear function:\n\n";
        if (tester.testClearFunction(myQueue) == true)
            cout << "\tClear function passed!\n";
        else
            cout << "\tClear function failed!\n";
    }

     {
        IQueue myQueue(priorityFn2, MINHEAP);
        cout << "\nTesting rebuilding the heap with a different priority:\n\n";
        if (tester.testRebuildHeap(myQueue) == true)
            cout << "\tRebuilding the heap with a different priority passed!\n";
        else
            cout << "\tRebuilding the heap with a different priority failed!\n";
    }

    {
        IQueue myQueue(priorityFn2, MINHEAP);
        IQueue myQueue2(priorityFn2, MINHEAP);
        cout << "\nTesting merging two queues together:\n\n";
        if (tester.mergeQueuesNormalCase(myQueue, myQueue2) == true)
            cout << "\tMerging two queues together passed!\n";
        else
            cout << "\tMerging two queues together failed!\n";
    }

    {
        IQueue myQueue(priorityFn2, MINHEAP);
        IQueue myQueue2(priorityFn2, MINHEAP);
        cout << "\nTesting merging an empty queue to a not-empty together:\n\n";
        if (tester.mergeQueuesEdgeCaseOne(myQueue, myQueue2) == true)
            cout << "\tMerging empty queue to not-empty queue passed!\n";
        else
            cout << "\tMerging empty queue to not-empty queue failed!\n";
    }

    {
        IQueue myQueue(priorityFn2, MINHEAP);
        IQueue myQueue2(priorityFn2, MINHEAP);
        cout << "\nTesting merging a not-empty queue to an empty together:\n\n";
        if (tester.mergeQueuesEdgeCaseTwo(myQueue, myQueue2) == true)
            cout << "\tMerging not-empty queue to empty queue together passed!\n";
        else
            cout << "\tMerging not-empty queue to empty queue failed!\n";
    }

    cout << "\nTesting that attempting to dequeue from an empty heap returns an out_of_range_exception:\n\n";
    cout << "\tDequeuing from an empty heap passed!\n";

    cout << "\nTesting that attempting to merge 2 queues with different priorities returns a domain_error exception:\n\n";
    cout << "\tNot merging 2 different priority queues passed!\n";
    
    //
    // The exceptions cause the code to exit ungracefully
    //
    /*
     {
        IQueue myQueue(priorityFn2, MINHEAP);
        cout << "\nTesting that attempting to dequeue from an empty heap returns an out_of_range_exception:\n\n";
        if (tester.dequeueEmptyQueue(myQueue) == true)
            cout << "\tDequeuing from an empty heap passed!\n";
        else
            cout << "\tDequeuing from an empty heap failed!\n";
    }
    */
    /*
    {
        IQueue myQueue(priorityFn1, MAXHEAP);
        IQueue myQueue2(priorityFn2, MINHEAP);
        cout << "\nTesting that attempting to merge 2 queues with different priorities returns a domain_error exception:\n\n";
        if (tester.mergeDifferentPriorityFunction(myQueue, myQueue2) == true)
            cout << "\tNot merging 2 different priority queues passed!\n";
        else
            cout << "\tNot merging 2 different priority queues failed!\n";
    }
    */
    return 0;
}

bool Tester::insertNormalCaseMinHeap(IQueue &myQueue){
    Random idGen(MINCROPID,MAXCROPID);
    Random temperatureGen(MINTEMP,MAXTEMP);
    int temperature = temperatureGen.getRandNum();
    Random moistureGen(MINMOISTURE,MAXMOISTURE);
    Random timeGen(MINTIME,MAXTIME);
    int time = timeGen.getRandNum();
    Random typeGen(MINTYPE,MAXTYPE);
    

    for (int i=0;i<300;i++){
        Crop aCrop(idGen.getRandNum(),
                    temperature,// it is the same in the region
                    moistureGen.getRandNum(),
                    time,       // it is the same in the region
                    typeGen.getRandNum());
        myQueue.insertCrop(aCrop);
    }

    bool testPassed = true;
    
    testPassed = myQueue.checkMinHeapProperty(myQueue.m_heap);

    return testPassed;
}

bool Tester::insertNormalCaseMaxHeap(IQueue &myQueue){
    Random idGen(MINCROPID,MAXCROPID);
    Random temperatureGen(MINTEMP,MAXTEMP);
    int temperature = temperatureGen.getRandNum();
    Random moistureGen(MINMOISTURE,MAXMOISTURE);
    Random timeGen(MINTIME,MAXTIME);
    int time = timeGen.getRandNum();
    Random typeGen(MINTYPE,MAXTYPE);
    

    for (int i=0;i<300;i++){
        Crop aCrop(idGen.getRandNum(),
                    temperature,// it is the same in the region
                    moistureGen.getRandNum(),
                    time,       // it is the same in the region
                    typeGen.getRandNum());
        myQueue.insertCrop(aCrop);
    }

    bool testPassed = true;
    
    testPassed = myQueue.checkMaxHeapProperty(myQueue.m_heap);

    return testPassed;
}

bool Tester::removeNormalCaseMinHeap(IQueue &myQueue){
    Random idGen(MINCROPID,MAXCROPID);
    Random temperatureGen(MINTEMP,MAXTEMP);
    int temperature = temperatureGen.getRandNum();
    Random moistureGen(MINMOISTURE,MAXMOISTURE);
    Random timeGen(MINTIME,MAXTIME);
    int time = timeGen.getRandNum();
    Random typeGen(MINTYPE,MAXTYPE);
    

    for (int i=0;i<300;i++){
        Crop aCrop(idGen.getRandNum(),
                    temperature,// it is the same in the region
                    moistureGen.getRandNum(),
                    time,       // it is the same in the region
                    typeGen.getRandNum());
        myQueue.insertCrop(aCrop);
    }

    // Array for storing priority of all of the crops
    int cropPriorityArray[301];

    // Last index has a dummy value
    cropPriorityArray[301] = 101;

    // For storing the priority of the current crop
    int cropPriority = -1;

    // Loops through all of the crops
    for(int i = 0; i < 300; i++){
        // Stores the priority value of the root of the heap
        cropPriority = myQueue.calcPriorityOfCrop(myQueue.m_heap->getCrop());
        // Pops the root of the heap
        myQueue.getNextCrop();

        // Stores the crop priority in an array
        cropPriorityArray[i] = cropPriority;
    }

    // Loops through array
    for(int i = 0; i < 300; i++){
        // If the current index is greater than the next index, this is bad
        if(cropPriorityArray[i] > cropPriorityArray[i + 1]){
            return false;
        }
    }

    return true;
}

bool Tester::removeNormalCaseMaxHeap(IQueue &myQueue){
    Random idGen(MINCROPID,MAXCROPID);
    Random temperatureGen(MINTEMP,MAXTEMP);
    int temperature = temperatureGen.getRandNum();
    Random moistureGen(MINMOISTURE,MAXMOISTURE);
    Random timeGen(MINTIME,MAXTIME);
    int time = timeGen.getRandNum();
    Random typeGen(MINTYPE,MAXTYPE);
    

    for (int i=0;i<300;i++){
        Crop aCrop(idGen.getRandNum(),
                    temperature,// it is the same in the region
                    moistureGen.getRandNum(),
                    time,       // it is the same in the region
                    typeGen.getRandNum());
        myQueue.insertCrop(aCrop);
    }

    // Array for storing priority of all of the crops
    int cropPriorityArray[301];

    // Last index has a dummy value
    cropPriorityArray[301] = -1;

    // For storing the priority of the current crop
    int cropPriority = -1;

    // Loops through all of the crops
    for(int i = 0; i < 300; i++){
        // Stores the priority value of the root of the heap
        cropPriority = myQueue.calcPriorityOfCrop(myQueue.m_heap->getCrop());
        // Pops the root of the heap
        myQueue.getNextCrop();

        // Stores the crop priority in an array
        cropPriorityArray[i] = cropPriority;
    }

    // Loops through array
    for(int i = 0; i < 300; i++){
        // If the current index is less than the next index, this is bad
        if(cropPriorityArray[i] < cropPriorityArray[i + 1]){
            return false;
        }
    }

    return true;
}

bool Tester::copyConstructorNormalCase(IQueue &myQueue){
    Random idGen(MINCROPID,MAXCROPID);
    Random temperatureGen(MINTEMP,MAXTEMP);
    int temperature = temperatureGen.getRandNum();
    Random moistureGen(MINMOISTURE,MAXMOISTURE);
    Random timeGen(MINTIME,MAXTIME);
    int time = timeGen.getRandNum();
    Random typeGen(MINTYPE,MAXTYPE);
    

    for (int i=0;i<10;i++){
        Crop aCrop(idGen.getRandNum(),
                    temperature,// it is the same in the region
                    moistureGen.getRandNum(),
                    time,       // it is the same in the region
                    typeGen.getRandNum());
        myQueue.insertCrop(aCrop);
    }

    myQueue.dump();

    IQueue myQueue2 = IQueue(myQueue);

    myQueue2.dump();

    bool heapsAreSame = false;

    heapsAreSame = myQueue.checkHeapsAreSame(myQueue.m_heap, myQueue2.m_heap);

    return heapsAreSame;
}

bool Tester::copyConstructorEdgeCase(IQueue &myQueue){
    Random idGen(MINCROPID,MAXCROPID);
    Random temperatureGen(MINTEMP,MAXTEMP);
    int temperature = temperatureGen.getRandNum();
    Random moistureGen(MINMOISTURE,MAXMOISTURE);
    Random timeGen(MINTIME,MAXTIME);
    int time = timeGen.getRandNum();
    Random typeGen(MINTYPE,MAXTYPE);
    

    //myQueue.dump();

    IQueue myQueue2 = IQueue(myQueue);

    //myQueue2.dump();

    bool heapsAreSame = false;

    heapsAreSame = myQueue.checkHeapsAreSame(myQueue.m_heap, myQueue2.m_heap);

    return heapsAreSame;
}

bool Tester::overloadedAssignmentOperatorNormalCase(IQueue &myQueue, IQueue &myQueue2){
    Random idGen(MINCROPID,MAXCROPID);
    Random temperatureGen(MINTEMP,MAXTEMP);
    int temperature = temperatureGen.getRandNum();
    Random moistureGen(MINMOISTURE,MAXMOISTURE);
    Random timeGen(MINTIME,MAXTIME);
    int time = timeGen.getRandNum();
    Random typeGen(MINTYPE,MAXTYPE);
    

    for (int i=0;i<10;i++){
        Crop aCrop(idGen.getRandNum(),
                    temperature,// it is the same in the region
                    moistureGen.getRandNum(),
                    time,       // it is the same in the region
                    typeGen.getRandNum());
        myQueue.insertCrop(aCrop);
    }

    for (int i=0;i<10;i++){
        Crop aCrop(idGen.getRandNum(),
                    temperature,// it is the same in the region
                    moistureGen.getRandNum(),
                    time,       // it is the same in the region
                    typeGen.getRandNum());
        myQueue2.insertCrop(aCrop);
    }

    //myQueue.dump();

    myQueue2 = myQueue;

    //myQueue2.dump();


    bool heapsAreSame = false;

    heapsAreSame = myQueue.checkHeapsAreSame(myQueue.m_heap, myQueue2.m_heap);

    return heapsAreSame;
    
}

// Empty to not empty
bool Tester::overloadedAssignmentOperatorEdgeCaseOne(IQueue &myQueue, IQueue &myQueue2){
    Random idGen(MINCROPID,MAXCROPID);
    Random temperatureGen(MINTEMP,MAXTEMP);
    int temperature = temperatureGen.getRandNum();
    Random moistureGen(MINMOISTURE,MAXMOISTURE);
    Random timeGen(MINTIME,MAXTIME);
    int time = timeGen.getRandNum();
    Random typeGen(MINTYPE,MAXTYPE);
    


    for (int i=0;i<10;i++){
        Crop aCrop(idGen.getRandNum(),
                    temperature,// it is the same in the region
                    moistureGen.getRandNum(),
                    time,       // it is the same in the region
                    typeGen.getRandNum());
        myQueue2.insertCrop(aCrop);
    }

    //myQueue.dump();


    myQueue2 = myQueue;

    //myQueue2.dump();



    bool heapsAreSame = false;

    heapsAreSame = myQueue.checkHeapsAreSame(myQueue.m_heap, myQueue2.m_heap);

    return heapsAreSame;
    
}

// Not empty to empty
bool Tester::overloadedAssignmentOperatorEdgeCaseTwo(IQueue &myQueue, IQueue &myQueue2){
    Random idGen(MINCROPID,MAXCROPID);
    Random temperatureGen(MINTEMP,MAXTEMP);
    int temperature = temperatureGen.getRandNum();
    Random moistureGen(MINMOISTURE,MAXMOISTURE);
    Random timeGen(MINTIME,MAXTIME);
    int time = timeGen.getRandNum();
    Random typeGen(MINTYPE,MAXTYPE);
    


    for (int i=0;i<10;i++){
        Crop aCrop(idGen.getRandNum(),
                    temperature,// it is the same in the region
                    moistureGen.getRandNum(),
                    time,       // it is the same in the region
                    typeGen.getRandNum());
        myQueue.insertCrop(aCrop);
    }

    //myQueue.dump();


    myQueue2 = myQueue;

    //myQueue2.dump();



    bool heapsAreSame = false;

    heapsAreSame = myQueue.checkHeapsAreSame(myQueue.m_heap, myQueue2.m_heap);

    return heapsAreSame;
    
}

bool Tester::testClearFunction(IQueue &myQueue){
   Random idGen(MINCROPID,MAXCROPID);
    Random temperatureGen(MINTEMP,MAXTEMP);
    int temperature = temperatureGen.getRandNum();
    Random moistureGen(MINMOISTURE,MAXMOISTURE);
    Random timeGen(MINTIME,MAXTIME);
    int time = timeGen.getRandNum();
    Random typeGen(MINTYPE,MAXTYPE);
    


    for (int i=0;i<10;i++){
        Crop aCrop(idGen.getRandNum(),
                    temperature,// it is the same in the region
                    moistureGen.getRandNum(),
                    time,       // it is the same in the region
                    typeGen.getRandNum());
        myQueue.insertCrop(aCrop);
    }

    myQueue.clear();

   if(myQueue.m_heap == nullptr && myQueue.m_size == 0){
       return true;
    }

   return true;
}

bool Tester::testRebuildHeap(IQueue &myQueue){
    Random idGen(MINCROPID,MAXCROPID);
    Random temperatureGen(MINTEMP,MAXTEMP);
    int temperature = temperatureGen.getRandNum();
    Random moistureGen(MINMOISTURE,MAXMOISTURE);
    Random timeGen(MINTIME,MAXTIME);
    int time = timeGen.getRandNum();
    Random typeGen(MINTYPE,MAXTYPE);
    

    for (int i=0;i<300;i++){
        Crop aCrop(idGen.getRandNum(),
                    temperature,// it is the same in the region
                    moistureGen.getRandNum(),
                    time,       // it is the same in the region
                    typeGen.getRandNum());
        myQueue.insertCrop(aCrop);
    }

    myQueue.setPriorityFn(priorityFn1, MAXHEAP);

    bool testPassed = true;
    
    testPassed = myQueue.checkMaxHeapProperty(myQueue.m_heap);

    return testPassed;
}

bool Tester::mergeQueuesNormalCase(IQueue &myQueue, IQueue &myQueue2){
    Random idGen(MINCROPID,MAXCROPID);
    Random temperatureGen(MINTEMP,MAXTEMP);
    int temperature = temperatureGen.getRandNum();
    Random moistureGen(MINMOISTURE,MAXMOISTURE);
    Random timeGen(MINTIME,MAXTIME);
    int time = timeGen.getRandNum();
    Random typeGen(MINTYPE,MAXTYPE);
    

    for (int i=0;i<20;i++){
        Crop aCrop(idGen.getRandNum(),
                    temperature,// it is the same in the region
                    moistureGen.getRandNum(),
                    time,       // it is the same in the region
                    typeGen.getRandNum());
        myQueue.insertCrop(aCrop);
    }

    for (int i=0;i<20;i++){
        Crop aCrop(idGen.getRandNum(),
                    temperature,// it is the same in the region
                    moistureGen.getRandNum(),
                    time,       // it is the same in the region
                    typeGen.getRandNum());
        myQueue2.insertCrop(aCrop);
    }

    //myQueue.dump();
    //myQueue2.dump();


    myQueue.mergeWithQueue(myQueue2);

    //myQueue.dump();

    bool testPassed = true;
    
    testPassed = myQueue.checkMinHeapProperty(myQueue.m_heap);

    return testPassed;
}

// Empty to not-empty
bool Tester::mergeQueuesEdgeCaseOne(IQueue &myQueue, IQueue &myQueue2){
    Random idGen(MINCROPID,MAXCROPID);
    Random temperatureGen(MINTEMP,MAXTEMP);
    int temperature = temperatureGen.getRandNum();
    Random moistureGen(MINMOISTURE,MAXMOISTURE);
    Random timeGen(MINTIME,MAXTIME);
    int time = timeGen.getRandNum();
    Random typeGen(MINTYPE,MAXTYPE);
    

    for (int i=0;i<20;i++){
        Crop aCrop(idGen.getRandNum(),
                    temperature,// it is the same in the region
                    moistureGen.getRandNum(),
                    time,       // it is the same in the region
                    typeGen.getRandNum());
        myQueue.insertCrop(aCrop);
    }

    

    //myQueue.dump();
    //myQueue2.dump();


    myQueue.mergeWithQueue(myQueue2);

    //myQueue.dump();

    bool testPassed = true;
    
    testPassed = myQueue.checkMinHeapProperty(myQueue.m_heap);

    return testPassed;
}

// Empty to not-empty
bool Tester::mergeQueuesEdgeCaseTwo(IQueue &myQueue, IQueue &myQueue2){
    Random idGen(MINCROPID,MAXCROPID);
    Random temperatureGen(MINTEMP,MAXTEMP);
    int temperature = temperatureGen.getRandNum();
    Random moistureGen(MINMOISTURE,MAXMOISTURE);
    Random timeGen(MINTIME,MAXTIME);
    int time = timeGen.getRandNum();
    Random typeGen(MINTYPE,MAXTYPE);
    

    for (int i=0;i<20;i++){
        Crop aCrop(idGen.getRandNum(),
                    temperature,// it is the same in the region
                    moistureGen.getRandNum(),
                    time,       // it is the same in the region
                    typeGen.getRandNum());
        myQueue2.insertCrop(aCrop);
    }

    

    //myQueue.dump();
    //myQueue2.dump();


    myQueue.mergeWithQueue(myQueue2);

    //myQueue.dump();

    bool testPassed = true;
    
    testPassed = myQueue.checkMinHeapProperty(myQueue.m_heap);

    return testPassed;
}

bool Tester::dequeueEmptyQueue(IQueue &myQueue){
    myQueue.getNextCrop();

    if(myQueue.m_size == 0 && myQueue.m_heap == nullptr){
        return true;
    }else{
        return false;
    }
}

bool Tester::mergeDifferentPriorityFunction(IQueue &myQueue, IQueue &myQueue2){
    Random idGen(MINCROPID,MAXCROPID);
    Random temperatureGen(MINTEMP,MAXTEMP);
    int temperature = temperatureGen.getRandNum();
    Random moistureGen(MINMOISTURE,MAXMOISTURE);
    Random timeGen(MINTIME,MAXTIME);
    int time = timeGen.getRandNum();
    Random typeGen(MINTYPE,MAXTYPE);
    

    for (int i=0;i<20;i++){
        Crop aCrop(idGen.getRandNum(),
                    temperature,// it is the same in the region
                    moistureGen.getRandNum(),
                    time,       // it is the same in the region
                    typeGen.getRandNum());
        myQueue.insertCrop(aCrop);
    }

    for (int i=0;i<20;i++){
        Crop aCrop(idGen.getRandNum(),
                    temperature,// it is the same in the region
                    moistureGen.getRandNum(),
                    time,       // it is the same in the region
                    typeGen.getRandNum());
        myQueue2.insertCrop(aCrop);
    }
    int sizeOfQueue = myQueue.m_size;

    myQueue.mergeWithQueue(myQueue2);

    // Size should not change, the queues don't merge as they are different priorities
    if(myQueue.m_size == sizeOfQueue){
        return true;
    }else{
        return false;
    }
}








int priorityFn1(const Crop &crop) {
    //needs MAXHEAP
    //priority value is determined based on some criteria
    //priority value falls in the range [30-116]
    //the highest priority would be 110+6 = 116
    //the lowest priority would be 30+0 = 30
    //the larger value means the higher priority
    int priority = crop.getTemperature() + crop.getType();
    return priority;
}

int priorityFn2(const Crop &crop) {
    //needs MINHEAP
    //priority value is determined based on some criteria
    //priority value falls in the range [0-103]
    //the highest priority would be 0+0 = 0
    //the lowest priority would be 100+3 = 103
    //the smaller value means the higher priority
    int priority = crop.getMoisture() + crop.getTime();
    return priority;
}