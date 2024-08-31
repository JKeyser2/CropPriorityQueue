// CMSC 341 - Fall 2022 - Project 3
#include "iqueue.h"
#include <stdexcept>

class OutOfRangeException: public out_of_range{
public:
    OutOfRangeException(): out_of_range("Attempted to dequeue an already empty heap!\n"){}
};

class DomainErrorException: public domain_error{
public:
    DomainErrorException(): domain_error("Attempted to merge 2 queues with different priority functions!\n"){}
};

IQueue::IQueue(prifn_t priFn, HEAPTYPE heapType)
{
    m_priorFunc = priFn;
    m_heapType = heapType;

    m_heap = nullptr;

    m_size = 0;
}

IQueue::~IQueue()
{  
    //delete m_heap;
    // Call clear on the root of the heap
  clear(m_heap);
  // Set the root of the heap to nullptr
  //m_heap = nullptr;
  // Resets the size of the queue
  m_size = 0;
  
}

IQueue::IQueue(const IQueue& rhs)
{
    //cout << "COPY" << endl;

    m_priorFunc = rhs.m_priorFunc;
    m_heapType = rhs.m_heapType;

    //m_heap = rhs.m_heap;

    m_size = rhs.m_size;

    // Copy over the other heap using helper function
    // This does not make it identical however
    //copyHeap(m_heap, rhs.m_heap);

    copySubtree(rhs.m_heap, 0);
}

IQueue& IQueue::operator=(const IQueue& rhs)
{
    //cout << "OVERLOAD" << endl;

    // We are looking to make sure that the memory address of other is not equal to the memory address...
    // ... of the thing we are working on.
    if(this != &rhs){
        // Clear the old heap
        clear(m_heap);

        m_priorFunc = rhs.m_priorFunc;
        m_heapType = rhs.m_heapType;

        //m_heap = rhs.m_heap;


        // Copy over the other heap using helper function
        copySubtree(rhs.m_heap, 0);

        m_size = rhs.m_size;

  }
    return *this;
}

void IQueue::insertCrop(const Crop& crop) {
    // Creating new node, and store the crop into it
   // Node * newNode = new Node(crop);

    Node * newNode = new Node(crop);

    // Increment size of heap by 1
    m_size++;


    // Merge the new node
    // m_heap on left
    m_heap = merge(m_heap, newNode);

}

Crop IQueue::getNextCrop() {
    // If heap is empty
    if(m_heap == nullptr){
        throw OutOfRangeException();
    }

    // Storing the old highest priority node
    Node * old_root = m_heap;
    // Storing the old highest priority crop
    Crop highestPriorityCrop = old_root->getCrop();

    // Merging the new heap
    m_heap = merge(m_heap->m_left, m_heap->m_right);
    // Deleting the old highest priority node
    delete old_root;
    // Returning the old highest priority crop
    return highestPriorityCrop;
}

void IQueue::mergeWithQueue(IQueue& rhs) {
    // Priority functions are not the same
    if(m_priorFunc != rhs.m_priorFunc){
        throw DomainErrorException();
    }else{
    // Not merging the same heap to itself
    if(this != &rhs){
        // Merge 2 heaps together
        m_heap = merge(m_heap, rhs.m_heap);
        m_size = m_size + rhs.m_size;
    }
    // Setting the other heap's root to nullptr
    rhs.m_heap = nullptr;
    }
}

void IQueue::clear() {
    // Calling "clear helper fuction" that has a parameter for storing the current node that will be cleared
    clear(m_heap);

    m_heap = nullptr;

    m_size = 0;
}

int IQueue::numCrops() const
{
  return m_size;
}

void IQueue::printCropsQueue() const {
    // Call a preorder traversal starting at the root
    preorderTraversal(m_heap);
}

prifn_t IQueue::getPriorityFn() const {
  return m_priorFunc;
}

void IQueue::setPriorityFn(prifn_t priFn, HEAPTYPE heapType) {
    m_priorFunc = priFn;
    m_heapType = heapType; 

    // To store the crops
    vector<Crop> theCrop;

    // Helper function for inserting crops into an array that will be used for grabbing the crops...
    // ... and inserting them into a new heap
    storeCrops(m_heap, theCrop);  

    // Clear the old heap
    clear(m_heap);

    m_heap = nullptr;
    m_size = 0;

    // Insert crops into new heap
    for(unsigned int i = 0; i < theCrop.size(); i++){
        insertCrop(theCrop.at(i));
    }

}

void IQueue::dump() const
{
  if (m_size == 0) {
    cout << "Empty skew heap.\n" ;
  } else {
    dump(m_heap);
    cout << endl;
  }
}

void IQueue::dump(Node *pos) const {
  if ( pos != nullptr ) {
    cout << "(";
    dump(pos->m_left);
    cout << m_priorFunc(pos->m_crop) << ":" << pos->m_crop.getCropID();
    dump(pos->m_right);
    cout << ")";
  }
}

ostream& operator<<(ostream& sout, const Crop& crop) {
  sout << "Crop ID: " << crop.getCropID() 
        << ", current temperature: " << crop.getTemperature()
        << ", current soil moisture: " << crop.getMoisture() << "%"
        << ", current time: " << crop.getTimeString()
        << ", plant type: " << crop.getTypeString();
  return sout;
}

ostream& operator<<(ostream& sout, const Node& node) {
  sout << node.getCrop();
  return sout;
}

void IQueue::clear(Node * curr){
    // While we have not reached a nullptr
    if(curr != nullptr){
        // Use recursion to clear all of the nodes
        clear(curr->m_right);
        clear(curr->m_left);
        delete curr;
    }
}

void IQueue::copyHeap(Node * currTreeNode, Node * otherTreeNode){
    // While we have not reached a nullptr
    if(otherTreeNode != nullptr){
       m_size++;

       // Store all information of the copied over crop 
       int theCropId = otherTreeNode->getCrop().getCropID();
       int theCropTemperature = otherTreeNode->getCrop().getTemperature();
       int theCropMoisture= otherTreeNode->getCrop().getMoisture();
       int theCropTime= otherTreeNode->getCrop().getTime();
       int theCropType = otherTreeNode->getCrop().getType();

       // Make the crop object
       Crop newCrop = Crop(theCropId, theCropTemperature, theCropMoisture, theCropTime, theCropType);

       // Store the crop object in a node
       Node * newCropNode = new Node(newCrop);


        // Merging in the new crop
        if(m_heap != nullptr){
            cout << m_heap->getCrop().getCropID() << endl;
        }
        cout << newCropNode->getCrop().getCropID() << endl;
        m_heap = merge(m_heap, newCropNode);

        // Use recursion to copy over all of the nodes from the other tree
        //copyHeap(currTreeNode->m_right, otherTreeNode->m_right);
        //copyHeap(currTreeNode->m_right, otherTreeNode->m_left);

        copyHeap(currTreeNode, otherTreeNode->m_right);
        copyHeap(currTreeNode, otherTreeNode->m_left);

    // Have reached a nullptr
    }else{
        currTreeNode = nullptr;
    }
}

Node * IQueue::copySubtree(Node * currNode, int counter){
    if(counter == 0){
        m_heap = currNode;
        counter++;
    }

    if(currNode != nullptr){

        Node * newNode = new Node(currNode->getCrop());


        m_size++;

        newNode->m_left = copySubtree(currNode->m_left, counter); 
        
        newNode->m_right = copySubtree(currNode->m_right, counter);
        
    }
    return nullptr;
}

void IQueue::preorderTraversal(Node * currNode) const{
    // Reached an end
    if (currNode == nullptr){
        return;
    }

    cout << "[" << calcPriorityOfCrop(currNode->getCrop()) << "]" << currNode->getCrop() << endl;
 
    // Left recursive
    preorderTraversal(currNode->m_left);
 
    // Right recursive
    preorderTraversal(currNode->m_right);
}

Node * IQueue::merge(Node * left, Node * right){

    // MAX HEAP
    if(m_heapType == 1){
        Node * new_sub_root = nullptr;


        // Both left and right are not nullptr
        if(left && right){
            // If the left value is greater than the right value
            if(calcPriorityOfCrop(left->getCrop()) >= calcPriorityOfCrop(right->getCrop())){
                left->m_right = merge(left->m_right, right);
                new_sub_root = left;
            // If the right value is greater than the left value
            }else{
                right->m_right = merge(right->m_right, left);
                new_sub_root = right;
            }
        }
        // Only a left
        else if(left){
            new_sub_root = left;
        }
        // Only a right
        else if(right){
            new_sub_root = right;
        }
        // If new_sub_root is not nullptr
        if(new_sub_root){
            // This makes it a skew heap
            swap(new_sub_root->m_left, new_sub_root->m_right);
        }
        return new_sub_root;
    // MIN HEAP
    }else{
        Node * new_sub_root = nullptr;


        // Both left and right are not nullptr
        if(left != nullptr && right != nullptr){
            // If the right value is greater than the left value
            if(calcPriorityOfCrop(left->getCrop()) <= calcPriorityOfCrop(right->getCrop())){
                left->m_right = merge(left->m_right, right);
                new_sub_root = left;
            // If the right value is greater than the left value
            }else{
                right->m_right = merge(right->m_right, left);
                new_sub_root = right;
            }
        }
        // Only a left
        else if(left){
            new_sub_root = left;
        }
        // Only a right
        else if(right){
            new_sub_root = right;
        }
        // If new_sub_root is not nullptr
        if(new_sub_root){
            // This makes it a skew heap
            swap(new_sub_root->m_left, new_sub_root->m_right);
        }
        return new_sub_root;
    }
}

int IQueue::calcPriorityOfCrop(Crop crop) const{
    return m_priorFunc(crop);
}

void IQueue::storeCrops(Node * curr, vector<Crop> &theCrop){

    // Reached an end
    if (curr == nullptr){
        return;
    }else{
       // Store crop
       theCrop.push_back(curr->getCrop());
    }
 
    // Left recursive
    storeCrops(curr->m_left, theCrop);
 
    // Right recursive
    storeCrops(curr->m_right, theCrop);

}

bool IQueue::checkMinHeapProperty(Node * currNode) const{
    // Reached an end
    if (currNode == nullptr){
        return true;
    }

    // If the current node has a left child
    if(currNode->m_left){
        // If the left child is smaller, this is bad
        if(calcPriorityOfCrop(currNode->getCrop()) > calcPriorityOfCrop(currNode->m_left->getCrop())){
            return false;
        }
    }
    
    // If the current node has a right child
    if(currNode->m_right){
        // If the right child is smaller, this is bad
        if(calcPriorityOfCrop(currNode->getCrop()) > calcPriorityOfCrop(currNode->m_right->getCrop())){
            return false;
        }
    }
 
    // Left recursive
    checkMinHeapProperty(currNode->m_left);
 
    // Right recursive
    checkMinHeapProperty(currNode->m_right);

    return true;
}

bool IQueue::checkMaxHeapProperty(Node * currNode) const{
    // Reached an end
    if (currNode == nullptr){
        return true;
    }

    // If the current node has a left child
    if(currNode->m_left){
        // If the left child is bigger, this is bad
        if(calcPriorityOfCrop(currNode->getCrop()) < calcPriorityOfCrop(currNode->m_left->getCrop())){
            return false;
        }
    }
    
    // If the current node has a right child
    if(currNode->m_right){
        // If the right child is bigger, this is bad
        if(calcPriorityOfCrop(currNode->getCrop()) < calcPriorityOfCrop(currNode->m_right->getCrop())){
            return false;
        }
    }
 
    // Left recursive
    checkMaxHeapProperty(currNode->m_left);
 
    // Right recursive
    checkMaxHeapProperty(currNode->m_right);

    return true;
}

bool IQueue::checkHeapsAreSame(Node * heapOne, Node * heapTwo) const{
    // Both nodes hold a crop
    if(heapOne != nullptr && heapTwo != nullptr){
        // If the IDs are different, that is bad
        if(heapOne->getCrop().getCropID() != heapTwo->getCrop().getCropID()){
            return false;
        }
        // Left and right recursion
        checkHeapsAreSame(heapOne->getLeft(), heapTwo->getLeft());
        checkHeapsAreSame(heapOne->getRight(), heapTwo->getRight());
    // If one node has a crop, and one node does not, that is bad
    }else if(heapOne == nullptr && heapTwo != nullptr){
        return false;
    }else if(heapOne != nullptr && heapTwo == nullptr){
        return false;
    // Both nodes are nullptrs, that is good
    }else{
        return true;
    }
    
    return true;
}