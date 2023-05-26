//
// Created by ebrah on 24/05/2023.
//

#ifndef MIVNIIII1_TREE_H
#define MIVNIIII1_TREE_H

#include <iostream>

template <typename T , typename K>
class AVLnode {

    T info;
    int BF;

    AVLnode *Parent;
    int Lheight;
    int Rheight;
    int height;

    void LL_rotation();
    void RR_rotation();
    void LR_rotation();
    void RL_rotation();


public:
    AVLnode *left_son;
    AVLnode *Right_son;
    bool visited;
    int w;
    K key;
    AVLnode();
    AVLnode(K keyy,T& infoo, AVLnode *left_son = nullptr, AVLnode *Right_son = nullptr, AVLnode *Parent = nullptr);
    ~AVLnode();
    AVLnode<T, K> *getLeftSon();
    AVLnode<T, K> *getRightSon();
    AVLnode<T,K> *getParent();
    K& getKey();
    T& getinfo();
    void setParent(AVLnode<T, K> *parent);
    void setLeft(AVLnode<T, K> *Left_son);
    void setRight(AVLnode<T, K> *right_son);
    void setinfo(const T& infoo);
    void setkey(const K keyy);
    int getw()const;
    void updateTotalHeight();
    void updateBF();
    void BFIsOk();
    int getBF()const;
    int getheight()const;
    AVLnode<T,K>* findnextsmallest(AVLnode<T,K> *AVLnode) const;
};



template<typename T, typename K>
AVLnode<T, K>::AVLnode(K keyy,T& infoo, AVLnode *left_son, AVLnode *right_son, AVLnode *parent):key(keyy),info(infoo),BF(0),left_son(
        left_son),Right_son(right_son),Parent(parent),Lheight(0),Rheight(0),height(0),w(1),visited(false){}

template<typename T, typename K>
AVLnode<T, K>::AVLnode(): key(-1), info(nullptr), BF(0), left_son(nullptr), Right_son(nullptr), Parent(nullptr), Lheight(0),
                    Rheight(0), height(0),w(1){}

template<typename T, typename K>
AVLnode<T, K>::~AVLnode() = default;

template<typename T, typename K>
void AVLnode<T, K>::LL_rotation() {
    if(!this)
        return;
    AVLnode<T,K>* high_parent=this->Parent;
    bool root_is_left_son=true;
    if(high_parent!= nullptr){
        if(this==this->Parent->Right_son)
            root_is_left_son=false;
    }
    AVLnode<T,K>* LeftSon=this->left_son;
    AVLnode<T,K>* LeftSonRight=LeftSon->Right_son;
    if(LeftSonRight!= nullptr)
        LeftSonRight->Parent=this;
    this->left_son=LeftSonRight;
    LeftSon->Right_son=this;
    LeftSon->Parent=high_parent;
    this->Parent=LeftSon;
    if(high_parent!= nullptr){
        if(root_is_left_son)
            high_parent->left_son=LeftSon;
        else
            high_parent->Right_son=LeftSon;
    }
    else{
        LeftSon->Parent= nullptr;
    }
    this->updateTotalHeight();
    this->updateBF();
}

template<typename T, typename K>
void AVLnode<T, K>::RR_rotation() {
    if(!this)
        return;
    AVLnode<T,K>* high_parent=this->Parent;
    AVLnode<T,K>* right_son=this->Right_son;
    AVLnode<T,K>*  right_son_left=right_son->left_son;
    bool root_is_left_son=true;
    if(high_parent!= nullptr){
        if(this==this->Parent->Right_son)
            root_is_left_son=false;
    }
    if(right_son_left!= nullptr)
        right_son_left->Parent=this;
    this->Right_son=right_son_left;
    right_son->Parent=high_parent;
    right_son->left_son=this;
    this->Parent=right_son;
    if(high_parent!= nullptr){
        if(root_is_left_son)
            high_parent->left_son=right_son;
        else
            high_parent->Right_son=right_son;
    }
    else{
        right_son->Parent= nullptr;
    }
    this->updateTotalHeight();
    this->updateBF();
}

template<typename T, typename K>
void AVLnode<T, K>::LR_rotation() {
    if (!this)
        return;
    this->left_son->RR_rotation();
    LL_rotation();
}

template<typename T, typename K>
void AVLnode<T, K>::RL_rotation() {
    if (!this)
        return;
    this->Right_son->LL_rotation();
    RR_rotation();
}

template<typename T, typename K>
void AVLnode<T, K>::updateBF() {
    if (!this) {
        return;
    }
    this->BF = (this->Lheight - this->Rheight);
}

template<typename T, typename K>
void AVLnode<T, K>::updateTotalHeight() {
    if(!this){
        return;
    }
    if(this->left_son== nullptr && this->Right_son== nullptr){
        this->Lheight=0;
        this->Rheight=0;
        this->height=1;
        this->w=1;
    }
    if(this->left_son == nullptr && this->Right_son!= nullptr){
        this->Lheight=0;
        this->Rheight=this->Right_son->height;
        this->height=this->Right_son->height+1;
        this->w= 1 + this->Right_son->w;
    }
    if(this->left_son!= nullptr && this->Right_son== nullptr){
        this->Rheight=0;
        this->Lheight=this->left_son->height;
        this->height=this->left_son->height+1;
        this->w= 1 + this->left_son->w;
    }
    if(this->left_son!= nullptr && this->Right_son!= nullptr){
        this->Rheight=this->Right_son->height;
        this->Lheight=this->left_son->height;
        this->height=std::max(this->Right_son->height,this->left_son->height)+1;
        this->w=1+ this->left_son->w + this->Right_son->w;
    }
}

template<typename T, typename K>
void AVLnode<T, K>::BFIsOk() {
    if (!this) {
        return;
    }
    if (this->BF == 2) {
        if (this->left_son->BF >= 0) {
            this->LL_rotation();
        } else {
            this->LR_rotation();
        }
    }
    if (this->BF == -2) {
        if (this->Right_son->BF <= 0) {
            this->RR_rotation();
        } else {
            this->RL_rotation();
        }
    }
}

template<typename T, typename K>
AVLnode<T, K> *AVLnode<T, K>::getLeftSon() {
    if(!this) {
        return nullptr;
    }
    return this->left_son;
}

template<typename T, typename K>
AVLnode<T, K> *AVLnode<T, K>::getRightSon() {
    if(!this) {
        return nullptr;
    }
    return this->Right_son;
}

template<typename T, typename K>
AVLnode<T, K> *AVLnode<T, K>::getParent() {
    if (!this) {
        return nullptr;
    }
    return this->Parent;
}

template<typename T, typename K>
K& AVLnode<T, K>::getKey(){
    return key;
}

template <typename T,typename K>
T& AVLnode<T,K>::getinfo() {
    return info;
}

template<typename T, typename K>
void AVLnode<T, K>::setParent(AVLnode<T, K> *parent) {
    if(!this)
        return;
    this->Parent=parent;
}

template<typename T, typename K>
void AVLnode<T, K>::setLeft(AVLnode<T, K> *Left_son) {
    if (!this)
        return;
    this->left_son = Left_son;
}

template<typename T, typename K>
void AVLnode<T, K>::setRight(AVLnode<T, K> *right_son) {
    if (!this)
        return;
    this->Right_son = right_son;
}

template<typename T, typename K>
void AVLnode<T, K>::setinfo(const T &infoo) {
    if(!this){
        return;
    }
    this->info=infoo;
}

template<typename T, typename K>
void AVLnode<T, K>::setkey(const K keyy) {
    if(!this){
        return;
    }
    this->key=keyy;
}

template<typename T, typename K>
int AVLnode<T, K>::getBF() const{
    return this->BF;
}

template<typename T, typename K>
int AVLnode<T, K>::getheight() const {
    return this->height;
}


template<typename T, typename K>
int AVLnode<T, K>::getw() const{
    if(!this){
        return 0;
    }
    return this->w;
}

template<typename T, typename K>
AVLnode<T, K> *AVLnode<T, K>::findnextsmallest(AVLnode<T, K> *node) const {
    if(node== nullptr){
        return nullptr;
    }
    AVLnode<T,K>* iterator=node;
    while(iterator->getLeftSon()!= nullptr){
        iterator=iterator->getLeftSon();
    }
    return iterator;
}

///END OF THE AVLnode FUNCTIONS

typedef enum {ALLOCATION_FAILED,ALREADY_EXIST,DOES_NOT_EXIST,SUCCESSTREE,NULL_ARGUMENT} Treestatus;

template <typename T,typename K>
class AVLtree {

    AVLnode<T, K> *left_End;
    AVLnode<T, K> *right_End;

    void deletetree(AVLnode<T,K>* root);
    AVLnode<T,K>* findkey(K key,AVLnode<T,K>* Root);
    AVLnode<T,K>* findSpot(K key,AVLnode<T,K>* current)const;
    void fixBFforpath(AVLnode<T,K>* current);
    Treestatus removeAVLnode(AVLnode<T,K>* todelete);
    AVLnode<T,K>* findkeyspot(K key)const;
    K getByrankaux(int rank,AVLnode<T,K>* current)const;
    AVLnode<T,K>* findrightend()const;
    AVLnode<T,K>* findleftend()const;
public:
    AVLnode<T, K> *root;
    int treesize;
    bool isContain(T key){
        AVLnode<T,K> *it = this->root;
        if(this->root == nullptr)
            return false;

        while(it != nullptr){
            if(it->key == key)
                return true;

            else if(key < it->key)
            {
                it=it->getLeftSon();
            }
            else{
                it=it->getRightSon();
            }
        }
        return false;
    }

        T getMaxNode(){
        AVLnode<T,K> *it = this->root;
        if(this->root == nullptr)
            return nullptr;
        while (it->Right_son){
            it=it->Right_son;
        }
        return it->key;
    }
    AVLtree(AVLnode<T,K>* Root= nullptr);
    ~AVLtree();
    Treestatus insert(K key,T info);
    Treestatus deleteKey(K key);
    AVLnode<T,K>* find(K key);
    void treeClear();
    K getByrank(int rank)const;
    bool isEmpty()const;
    bool Contains(K key);
    AVLnode<T,K>* getRoot();
    void setRoot(AVLnode<T,K>* root);
    AVLnode<T,K>* getRightEnd()const;
    AVLnode<T,K>* getLeftEnd()const;
    void updateLeftEnd();
    void updateRightEnd();
};

template<typename T, typename K>
AVLtree<T,K>::AVLtree(AVLnode<T,K>* Root):root(Root),left_End(nullptr),right_End(nullptr),treesize(0) {}

template<typename T, typename K>
AVLtree<T,K>::~AVLtree() {
    if(!this){
        return;
    }
    deletetree(root);
    root = nullptr;
    left_End = right_End = nullptr;
}

template<typename T, typename K>
AVLnode<T,K> *AVLtree<T, K>::findkey(K key,AVLnode<T,K>* current){
    if(!this|| !current){
        return nullptr;
    }
    if(current->getKey()==key){
        return current;
    }
    if(current->getKey()<key){
        return findkey(key,current->getRightSon());
    }
    else{
        return findkey(key,current->getLeftSon());
    }
}

template<typename T, typename K>
Treestatus AVLtree<T, K>::insert(K key, T info) {
    if(!this){
        return NULL_ARGUMENT;
    }
    if(!root){
        AVLnode<T,K>* NewAVLnode=new AVLnode<T,K>(key,info);
        root=NewAVLnode;
        right_End=NewAVLnode;
        left_End=NewAVLnode;
        this->treesize++;
        return SUCCESSTREE;
    }
    if(find(key)){
        return ALREADY_EXIST;
    }
    AVLnode<T,K>* NewAVLnode=new AVLnode<T,K>(key,info);
    AVLnode<T,K>* spot=findkeyspot(key);
    if(key > spot->getKey()){
        spot->setRight(NewAVLnode);
    }
    if(key < spot->getKey()){
        spot->setLeft(NewAVLnode);
    }
    NewAVLnode->setParent(spot);
    this->treesize++;
    this->fixBFforpath(NewAVLnode);
    right_End=findrightend();
    left_End=findleftend();
    return SUCCESSTREE;
}


template<typename T, typename K>
void AVLtree<T, K>::deletetree(AVLnode<T,K> *Root) {
    if(!this || !Root){
        return;
    }
    deletetree(Root->getLeftSon());
    deletetree(Root->getRightSon());
    delete Root;
}

template<typename T, typename K>
AVLnode<T, K> *AVLtree<T,K>::findSpot(K key, AVLnode<T,K> *current) const {
    if(!this||!current){
        return nullptr;
    }

    if(key>current->getKey()){
        if(current->getRightSon() == nullptr){
            return current;
        }
        return findSpot(key,current->getRightSon());
    }
    if (key<current->getKey()){
        if(current->getLeftSon()== nullptr){
            return current;
        }
        return findSpot(key,current->getLeftSon());
    }
    return nullptr;
}

template<typename T, typename K>
AVLnode<T,K>* AVLtree<T, K>::find(K key){
    if(!this){
        return nullptr;
    }
    AVLnode<T,K>* tofind=findkey(key,this->root);
    return tofind ? tofind : nullptr;
}

template<typename T, typename K>
AVLnode<T, K> *AVLtree<T, K>::findkeyspot(K key) const{
    if(!this){
        return nullptr;
    }
    return findSpot(key,this->root);
}

template<typename T, typename K>
void AVLtree<T, K>::fixBFforpath(AVLnode<T, K> *current) {
    if(!current){
        return;
    }
    if(current->getParent()== nullptr){
        root=current;
    }
    current->updateTotalHeight();
    current->updateBF();
    current->BFIsOk();
    fixBFforpath(current->getParent());
}


template<typename T, typename K>
Treestatus AVLtree<T, K>::deleteKey(K key) {
    AVLnode<T,K>* toremove=this->find(key);
    if(!toremove){
        return DOES_NOT_EXIST;
    }
    this->removeAVLnode(toremove);
    right_End=findrightend();
    left_End=findleftend();
    return SUCCESSTREE;
}

template<typename T, typename K>
Treestatus AVLtree<T, K>::removeAVLnode(AVLnode<T, K> *todelete) {
    if(!this || !todelete){
        return NULL_ARGUMENT;
    }
///In this case the AVLnode we want to delete is a leaf
    if(todelete->getRightSon()==nullptr && todelete->getLeftSon()== nullptr){
        AVLnode<T,K>* father=todelete->getParent();
        if(father==nullptr){ ///here is when the tree got one AVLnode which is the root
            this->root= nullptr;
            delete todelete;
            right_End= nullptr;
            left_End= nullptr;
            this->treesize--;
            return SUCCESSTREE;
        }
        else{ ///here is when the we have to delete a leaf that's not the root
            if(father->getLeftSon()==todelete){
                father->setLeft(nullptr);
            }
            else{
                father->setRight(nullptr);
            }
            delete todelete;
            this->treesize--;
            this->fixBFforpath(father);
            return SUCCESSTREE;
        }
    }
///In this case the AVLnode we want to delete a AVLnode that has a left son only
    if(todelete->getLeftSon()!= nullptr && todelete->getRightSon()== nullptr){
        AVLnode<T,K>* father=todelete->getParent();
        if(father== nullptr){ ///in this case we got to remove the root and he has left son
            todelete->getLeftSon()->setParent(nullptr);
            root=todelete->getLeftSon();
            delete todelete;
            this->treesize--;
            return SUCCESSTREE;
        }
        else{
            if(father->getLeftSon()==todelete){
                father->setLeft(todelete->getLeftSon());
            }
            if(father->getRightSon()==todelete){
                father->setRight(todelete->getLeftSon());
            }
            todelete->getLeftSon()->setParent(father);
            delete todelete;
            this->treesize--;
            this->fixBFforpath(father);
            return SUCCESSTREE;
        }
    }
///In this case the AVLnode we want to delete a AVLnode that has a right son only
    if(todelete->getLeftSon()== nullptr && todelete->getRightSon()!= nullptr){
        AVLnode<T,K>* father=todelete->getParent();
        if(father== nullptr){ ///in this case we got to remove the root and he has right son
            todelete->getRightSon()->setParent(nullptr);
            root=todelete->getRightSon();
            delete todelete;
            this->treesize--;
            return SUCCESSTREE;
        }
        else{
            if(father->getLeftSon()==todelete){
                father->setLeft(todelete->getRightSon());
            }
            if(father->getRightSon()==todelete){
                father->setRight(todelete->getRightSon());
            }
            todelete->getRightSon()->setParent(father);
            delete todelete;
            this->treesize--;
            this->fixBFforpath(father);
            return SUCCESSTREE;
        }
    }
///In this case the AVLnode we want to delete has both right and left son
    if(todelete->getRightSon()!= nullptr && todelete->getLeftSon()!= nullptr){
        ///In this case we need to fight the next biggest
        bool left_flag = false;
        AVLnode<T,K>* Thenextbiggest=todelete->getRightSon();
        while(Thenextbiggest->getLeftSon()!=nullptr){
            Thenextbiggest=Thenextbiggest->getLeftSon();
            left_flag = true;
        }
        ///temp -> Thenextbiggest
        ///AVLnode -> todelete
        AVLnode<T,K>* parent = Thenextbiggest->getParent();
        AVLnode<T,K>* right_son = Thenextbiggest->getRightSon();

        Thenextbiggest->setLeft(todelete->getLeftSon());
        Thenextbiggest->setParent(todelete->getParent());
        Thenextbiggest->getLeftSon()->setParent(Thenextbiggest);


        if(todelete->getParent()) {
            if (todelete->getParent()->getRightSon() == todelete)
            { todelete->getParent()->setRight(Thenextbiggest); }
            else todelete->getParent()->setLeft(Thenextbiggest);
        }
        else {this->root = Thenextbiggest;}


        if(left_flag){
            Thenextbiggest->setRight(todelete->getRightSon());
            todelete->getRightSon()->setParent(Thenextbiggest);
            parent->setLeft(right_son);

            if(right_son != nullptr)
                right_son->setParent(parent);
            this->fixBFforpath(parent);
        }
        else{
            this->fixBFforpath(Thenextbiggest);
        }
        todelete->setLeft(nullptr);
        todelete->setRight(nullptr);
        todelete->setParent(nullptr);
        this->treesize--;
        delete todelete;
        ///Find the next biggest in Inorder Visit
        ///we need to swap the two AVLnodes
//    K tmpkey=todelete->getKey();
//    T tmpinfo=todelete->getinfo();
//    todelete->setkey(Thenextbiggest->getKey());
//    todelete->setinfo(Thenextbiggest->getinfo());
//    Thenextbiggest->setkey(tmpkey);
//    Thenextbiggest->setinfo(tmpinfo);
//    return this->removeAVLnode(Thenextbiggest);
    }
    return SUCCESSTREE;
}

template<typename T, typename K>
void AVLtree<T, K>::treeClear() {
    deletetree(this->root);
    this->root= nullptr;
}

template<typename T, typename K>
K AVLtree<T, K>::getByrank(int rank) const {
    return getByrankaux(rank,this->root);
}

template<typename T, typename K>
K AVLtree<T, K>::getByrankaux(int rank, AVLnode<T, K> *current) const {
    int w=current->getLeftSon()->getw();
    if(w==rank-1){
        return current->getinfo();
    }
    if(w>rank-1){
        return getByrankaux(rank,current->getLeftSon());
    }
    if(w<rank-1){
        return getByrankaux(rank-w-1,current->getRightSon());
    }
    return current->getinfo();
}

template<typename T, typename K>
bool AVLtree<T, K>::isEmpty() const {
    return !this || this->treesize==0;
}

template<typename T, typename K>
AVLnode<T, K> *AVLtree<T, K>::getRightEnd() const {
    return right_End;
}

template<typename T, typename K>
AVLnode<T, K> *AVLtree<T, K>::getLeftEnd() const {
    return left_End;
}

template<typename T, typename K>
AVLnode<T, K> *AVLtree<T, K>::findrightend() const {
    AVLnode<T,K>* iterator=this->root;
    while(iterator->getRightSon()!= nullptr){
        iterator=iterator->getRightSon();
    }
    return iterator;
}

template<typename T, typename K>
AVLnode<T, K> *AVLtree<T, K>::findleftend() const {
    AVLnode<T,K>* iterator=this->root;
    while(iterator->getLeftSon()!= nullptr){
        iterator=iterator->getLeftSon();
    }
    return iterator;
}

template<typename T, typename K>
bool AVLtree<T, K>::Contains(K key){
    if(!this){
        return false;
    }
    return find(key) != nullptr;
}

template<typename T, typename K>
AVLnode<T, K> *AVLtree<T, K>::getRoot(){
    if(!this){
        return nullptr;
    }
    return this->root;
}

template<typename T, typename K>
void AVLtree<T, K>::updateLeftEnd() {
    if(!this){
        return ;
    }
    this->left_End = findleftend();
}

template<typename T, typename K>
void AVLtree<T, K>::updateRightEnd() {
    if(!this){
        return ;
    }
    this->right_End = findrightend();
}

template<typename T, typename K>
void AVLtree<T, K>::setRoot(AVLnode<T, K> *Root) {
    if(!this)
        return;
    this->root = Root;
}



//#include <stdio.h>
//
//using namespace std;
//
//
//template <class T>
//class AVLAVLnode {
//public:
//    T key;
//    int balance;
//    AVLnode *left, *right, *parent;
//
//    AVLnode(T k, AVLnode *p) : key(k), balance(0), parent(p),
//                               left(NULL), right(NULL) {}
//
//    ~AVLnode() {
//        delete left;
//        delete right;
//    }
//
//};
//
//
//template <class T>
//class AVLtree {
//public:
//    AVLtree(): root(NULL), size(0) {}
//    ~AVLtree(){
//        delete root;
//    }
//
//
//    bool insert(T key){
//        if (root == NULL) {
//            root = new AVLnode<T>(key, NULL);
//        }
//        else {
//            AVLnode<T>
//                    *n = root,
//                    *parent;
//
//            while (true) {
//                if (n->key == key)
//                    return false;
////                if(root->left ==NULL && root->right == NULL){
////                    if(root->key < key){
////                        root->right=new AVLnode<T>(key, root);
////                    } else{
////                        root->left = new AVLnode<T>(key, root);
////                    }
////                    break;
////                }
//                parent = n;
//
//                bool goLeft = n->key > key;
//                n = goLeft ? n->left : n->right;
//
//                if (n == NULL) {
//                    if (goLeft) {
//                        parent->left = new AVLnode<T>(key, parent);
//                    }
//                    else {
//                        parent->right = new AVLnode<T>(key, parent);
//                    }
//
//                    rebalance(parent);
//                    break;
//                }
//            }
//        }
//        size++;
//        return true;
//    }
//
//    AVLnode<T>* deleteNode(AVLnode<T>* root,T delKey){
//        if (delKey < root->key) {
//            root->left = deleteNode(root->left, delKey);
//        } else if (delKey > root->key) {
//            root->right = deleteNode(root->right, delKey);
//        } else {
//            AVLnode<T> *target;
//            if ((root->left == NULL) || (root->right == NULL)) {
//                target = root->left ? root->left : root->right;
//                /// Did not have childs
//                if (target == NULL) {
//                    delete (root);
//                    return NULL;
//                } else { /// have one child
//                    target->parent = root->parent;
//                    delete (root);
//                    return target;
//                }
//            } else {/// if root has two children
//                AVLnode<T> *tmp = getMin(root->right);
//
//                root->key = tmp->key;
//
//                root->right = deleteNode(root->right, tmp->key);
//            }
//        }
////        if (root != NULL) {
////            root->UpdateHeight();
////        }
//        rebalance(root);
//        size--;
//        return  root;
//    }
//
//    AVLnode<T>* getMin(AVLnode<T>* root){
//        AVLnode<T> *min = root;
//        while (min->left != NULL) {
//            min = min->left;
//        }
//        return min;
//    }
//
//    void deleteKey(T delKey){
//        root= deleteNode(root,delKey);
//    }
//
////    void deleteKey(T delKey){
////        if (root == NULL)
////            return;
////
////        AVLnode<T>
////                *n       = root,
////                *parent  = root,
////                *delNode = NULL,
////                *child   = root;
////
////        while (child != NULL) {
////            parent = n;
////            n = child;
////            child = delKey >= n->key ? n->right : n->left;
////            if (delKey == n->key)
////                delNode = n;
////        }
////
////        if (delNode != NULL) {
////            delNode->key = n->key;
////
////            child = n->left != NULL ? n->left : n->right;
////
////            if (root->key == delKey) {
////                root = child;
////            }
////            else {
////                if (parent->left == n) {
////                    parent->left = child;
////                }
////                else {
////                    parent->right = child;
////                }
////
////                rebalance(parent);
////            }
////        }
////        delete delNode;
////        size--;
////    }
//
//
//
//    bool isContain(T key){
//        AVLnode<T> *it = this->root;
//        if(this->root == nullptr)
//            return false;
//
//        while(it != nullptr){
//            if(it->key == key)
//                return true;
//
//            else if(key < it->key)
//            {
//                it=it->left;
//            }
//            else{
//                it=it->right;
//            }
//        }
//        return false;
//    }
//
//
//    AVLnode<T>* findNode(T key){
//        AVLnode<T> *it = this->root;
//        if(this->root == nullptr)
//            return nullptr;
//
//        while(it != nullptr){
//            if(it->key == key)
//                return it;
//
//            else if(key < it->key)
//            {
//                it=it->left;
//            }
//            else{
//                it=it->right;
//            }
//        }
//        return nullptr;
//    }
//    int getSize(){
//        return this->size;
//    }
//
//
//    AVLnode<T> *root;
//    int size;
//    T getMaxNode(){
//        AVLnode<T> *it = this->root;
//        if(this->root == nullptr)
//            return nullptr;
//        while (it->right){
//            it=it->right;
//        }
//        return it->key;
//    }
//private:
//
//
//    AVLnode<T>* rotateLeft( AVLnode<T> *a ){
//        AVLnode<T> *b = a->right;
//        b->parent = a->parent;
//        a->right = b->left;
//
//        if (a->right != NULL)
//            a->right->parent = a;
//
//        b->left = a;
//        a->parent = b;
//
//        if (b->parent != NULL) {
//            if (b->parent->right == a) {
//                b->parent->right = b;
//            }
//            else {
//                b->parent->left = b;
//            }
//        }
//
//        setBalance(a);
//        setBalance(b);
//        return b;
//    }
//
//
//    AVLnode<T>* rotateRight ( AVLnode<T> *a ){
//        AVLnode<T> *b = a->left;
//        b->parent = a->parent;
//        a->left = b->right;
//
//        if (a->left != NULL)
//            a->left->parent = a;
//
//        b->right = a;
//        a->parent = b;
//
//        if (b->parent != NULL) {
//            if (b->parent->right == a) {
//                b->parent->right = b;
//            }
//            else {
//                b->parent->left = b;
//            }
//        }
//
//        setBalance(a);
//        setBalance(b);
//        return b;
//    }
//
//
//
//    AVLnode<T>* rotateLeftThenRight ( AVLnode<T> *n ){
//        n->left = rotateLeft(n->left);
//        return rotateRight(n);
//    }
//
//
//
//    AVLnode<T>* rotateRightThenLeft ( AVLnode<T> *n ){
//        n->right = rotateRight(n->right);
//        return rotateLeft(n);
//    }
//
//
//
//    void rebalance ( AVLnode<T> *n ){
//        setBalance(n);
//
//        if (n->balance == -2) {
//            if (height(n->left->left) >= height(n->left->right))
//                n = rotateRight(n);
//            else
//                n = rotateLeftThenRight(n);
//        }
//        else if (n->balance == 2) {
//            if (height(n->right->right) >= height(n->right->left))
//                n = rotateLeft(n);
//            else
//                n = rotateRightThenLeft(n);
//        }
//
//        if (n->parent != NULL) {
//            rebalance(n->parent);
//        }
//        else {
//            root = n;
//        }
//    }
//
//
//
//    int height ( AVLnode<T> *n ){
//        if (n == NULL)
//            return -1;
//        return 1 + max(height(n->left), height(n->right));
//    }
//
//
//
//    void setBalance ( AVLnode<T> *n ){
//        n->balance = height(n->right) - height(n->left);
//    }
//};
//

#endif //MIVNIIII1_TREE_H
