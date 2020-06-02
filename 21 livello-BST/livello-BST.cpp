#include <iostream>
#include <fstream>

using namespace std;

template <typename T>
class Node{
    private:
    T * pKey;
    Node<T> * pLeft;
    Node<T> * pRight;

    public:
    Node(T value){
        pKey = new T(value);
        pLeft = pRight = NULL;
    }

    //metodi getter e setter
    void setKey(T value){
        *pKey = value;
    }

    void setLeft(Node<T> * pNode){
        pLeft = pNode;
    }

    void setRight(Node<T> * pNode){
        pRight = pNode;
    }

    T getKey(){
        return * pKey;
    }

    Node<T> * getLeft(){
        return pLeft;
    }

    Node<T> * getRight(){
        return pRight;
    }
};

template<typename T>
class BST{
    private:
    Node<T> * pRoot;
    int iLevel;     //contatore livello

    //metodi di servizio
    Node<T> * _insert(T value, Node<T> * pLastRoot){
        if(pLastRoot == NULL){  //caso base
            pLastRoot = new Node<T>(value);
            return pLastRoot;
        }

        if(value > pLastRoot->getKey())
            pLastRoot->setRight(_insert(value,pLastRoot->getRight()));
        else 
            pLastRoot->setLeft(_insert(value,pLastRoot->getLeft()));
    }

    Node<T> * _canc(T value, Node<T> * pLastRoot){
        if(pLastRoot->getKey() == value){   //caso base
            //ha entrambi i figli
            if(pLastRoot->getLeft() && pLastRoot->getRight()){
                Node<T> * pTemp = pLastRoot->getRight();
                //minimo dei maggioranti
                while(pTemp->getLeft())
                    pTemp = pTemp->getLeft();
                pLastRoot->setKey(pTemp->getKey());
                pLastRoot->setRight(_canc(pTemp->getKey(),pLastRoot->getRight()));
            }
            else if(pLastRoot->getRight() == NULL)  //manca il figlio destro
                pLastRoot = pLastRoot->getLeft();
            else 
                pLastRoot = pLastRoot->getRight();  //manca il sinistro o entrambi

            return pLastRoot;
        }

        if(value > pLastRoot->getKey())
            pLastRoot->setRight(_canc(value,pLastRoot->getRight()));
        else 
            pLastRoot->setLeft(_canc(value,pLastRoot->getLeft()));
    }

    void _getLevel(T value, Node<T> * pLastRoot){

        if(pLastRoot->getKey() == value){
            return;
        }
        
        iLevel++;

        if(value > pLastRoot->getKey())
            _getLevel(value,pLastRoot->getRight());
        else 
            _getLevel(value, pLastRoot->getLeft());

    }

    public:
    BST(){
        pRoot = NULL;
        iLevel = 0;
    }

    //metodi innescanti
    void insert(T value){
        pRoot = _insert(value,pRoot);
    }

    void canc(T value){
        pRoot = _canc(value, pRoot);
    }

    int getLevel(T value){
        iLevel = 0;
        _getLevel(value, pRoot);
        return iLevel;
    }
};

template<typename T>
void parsing(ifstream &inFile, ofstream &outFile){

    BST<T> * pBST = new BST<T>();

    int iN;
    T tmp;
    char cOpType;
    char cIgnore;
    int iLevel;

    inFile >> iN;
    inFile >> iLevel;

    for(int i=0;i<iN;i++){
        inFile >> cOpType;

        inFile >> cIgnore;
        inFile >> cIgnore;
        inFile >> cIgnore;

        switch(cOpType){
            case 'i':
            inFile >> tmp;
            pBST->insert(tmp);
            break;

            case 'c':
            inFile >> cIgnore;
            inFile >> tmp;
            pBST->canc(tmp);
            break;
        }
    }    

    
    for(int i=0;i<iLevel;i++){
        inFile >> tmp;
        outFile << pBST->getLevel(tmp)<<" ";
    }
    outFile<<endl;
}

int main(){

   ifstream inFile("input.txt");
   ofstream outFile("output.txt");

   string strType;

   while(inFile >> strType){
       switch (strType[0])
       {
           case 'i':
           parsing<int>(inFile,outFile);
           break;

           case 'c':
           parsing<char>(inFile,outFile);
           break;

           case 'd':
           parsing<double>(inFile,outFile);
           break;

           case 'b':
           parsing<bool>(inFile,outFile);
           break;
       }
   }
}