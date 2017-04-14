//
//  0316038_Link_List.cpp
//  HW2
//
//  Created by 石瑾旋 on 2017/3/16.
//  Copyright © 2017年 石瑾旋. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include "0316038_Link_List.h"

using namespace std;

//global function
template <typename T>
ostream &operator<<(ostream &output, const Link_List<T> &L)
{
    
    Int_Node<T> *ptr = L.head;
    while(ptr!= NULL){
        output << fixed << setprecision(1) << ptr->value << " ";
        ptr = ptr->next;
    }
    
    return output;
}

template <typename T>
istream &operator>>(istream &input, Link_List<T> &L)
{
    Int_Node<T> *n = new Int_Node<T>;
    input >> n->value;
    
    if(L.size==0){
        L.head=n;
        L.tail=n;
        n->pre=NULL;
        n->next=NULL;
    }
    else{
        L.tail->next = n;
        n->pre = L.tail;
        n->next = NULL;
        L.tail = L.tail->next;
    }
    
    L.size++;
    return input;
}

//default constructor
template <typename T>
Link_List<T>::Link_List()
{
    size = 0;
    head=NULL;
    tail=NULL;
}

//copy constructor
template <typename T>
Link_List<T>::Link_List(const Link_List<T> &LinkListToCopy)
:size(LinkListToCopy.size)
{
    if(size == 0){
        head=NULL;
        tail=NULL;
    }
    
    else{
        Int_Node<T> *ptr = LinkListToCopy.head;
        Int_Node<T> *n;
        
        for(int i=1; i<=size; i++){
            n = new Int_Node<T>;
            n->value = ptr->value;
            if(i == 1){
                head = n;
                tail = n;
                n->pre = NULL;
                n->next = NULL;
            }
            else{
                tail->next = n;
                n->pre = tail;
                n->next = NULL;
                tail = tail->next;
            }
            ptr = ptr->next;
        }
    }
}

//destructor
template<typename T>
Link_List<T>::~Link_List()
{
    while(head != NULL){            //clear Link List
        Int_Node<T> *current = head;
        delete current;
        current = 0;
        head = head -> next;
    }
    tail = NULL;
    size = 0;
}

template<typename T>
int Link_List<T>::getSize() const
{
    return size;
}

//assignment operator
//const return avoids: (L1 = L2) = L3
template<typename T>
const Link_List<T>& Link_List<T>::operator=(const Link_List<T> &Right)
{
    if(&Right != this){                     //avoid self-assignment
        if(size != Right.size){
            while(head != NULL){            //clear Link List
                Int_Node<T> *current = head;
                delete current;
                current = 0;
                head = head -> next;
            }
            
            size = Right.size;
            Int_Node<T> *ptr = Right.head;
            Int_Node<T> *n;
            
            for(int i=1;i<=size;i++){
                n = new Int_Node<T>;
                n->value = ptr->value;
                if(i == 1){
                    head = n;
                    tail = n;
                    n->pre = NULL;
                    n->next = NULL;
                }
                else{
                    tail->next = n;
                    n->pre = tail;
                    n->next = NULL;
                    tail = tail->next;
                }
                ptr = ptr->next;
            }
        }
    }
    return *this;
}

//equality operator
template<typename T>
bool Link_List<T>::operator==(const Link_List<T> &Right) const
{
    if(size != Right.size)
        return false;
    
    Int_Node<T> *left_ptr = head;
    Int_Node<T> *right_ptr = Right.head;
    for(int i=0; i<size; i++){
        if(left_ptr->value != right_ptr->value)
            return false;
        left_ptr = left_ptr->next;
        right_ptr = right_ptr->next;
    }
    return true;
}

// subscript operator for non-const objects
template<typename T>
T &Link_List<T>::operator[](int subscript)
{
    if(subscript <= 0 || subscript > size){
        cerr << "\nError: Subscript " << subscript << "out of range" << endl;
        exit(1);
    }
    
    Int_Node<T> *ptr = head;
    for(int i=1; i<subscript; i++){
        ptr = ptr->next;
    }
    return ptr->value;
}

// subscript operator for const objects
template<typename T>
T Link_List<T>::operator[](int subscript) const
{
    if(subscript <= 0 || subscript > size){
        cerr << "\nError: Subscript " << subscript << "out of range" << endl;
        exit(1);
    }
    
    Int_Node<T> *ptr = head;
    for(int i=1; i<subscript; i++){
        ptr = ptr->next;
    }
    return ptr->value;
}

// insert an integer at the back of link list
template<typename T>
bool Link_List<T>::insert_node(T number)
{
    Int_Node<T> *n = new Int_Node<T>;
    n->value = number;
    
    if(size == 0){
        head = n;
        tail = n;
        n->pre = NULL;
        n->next = NULL;
    }
    else{
        tail->next = n;
        n->pre = tail;
        tail = tail->next;
        n->next = NULL;
    }
    size++;
    
    return 1;
}

// insert an integer after the i_th position
template<typename T>
bool Link_List<T>::insert_node(int index, T number)
{
    if(index < 0)  return 0;
    
    
    Int_Node<T> *ptr = head;
    Int_Node<T> *n = new Int_Node<T>;
    n->value = number;
    
    if(index != 0){
        for(int i=1;i<index;i++){
            ptr = ptr->next;
        }
    }
    
    
    if(index == size){
        n->next = NULL;
        n->pre = ptr;
        ptr->next = n;
        tail = tail->next;
    }
    else if(index == 0){
        n->next = ptr;
        n->pre = NULL;
        ptr->pre = n;
        head = head->pre;
    }
    else{
        n->next = ptr->next;
        ptr->next->pre = n;
        ptr->next = n;
        n->pre = ptr;
    }
    size++;
    return 1;
}

// delete the last node
template<typename T>
bool Link_List<T>::delete_node()
{
    if(size == 0)   return 0;
    
    size--;
    Int_Node<T> *current = tail;
    Int_Node<T> *previous = tail->pre;
    
    if(current == head){
        head = NULL;
        tail = NULL;
        delete current;
        current = NULL;     // 當指標被delete後, 將其指向NULL, 可以避免不必要bug
    }
    else{
        previous->next = NULL;
        tail = previous;
        delete current;
        current = NULL;
        
    }
    
    return 1;
}

// delete the i_th node
template<typename T>
bool Link_List<T>::delete_node(int index)
{
    if(index <= 0 || index > size)  return 0;
    
    
    Int_Node<T> *ptr = head;
    for(int i=1;i<index;i++){
        ptr = ptr->next;
    }
    Int_Node<T> *current = ptr;
    Int_Node<T> *previous = ptr->pre;
    
    if(size == 1 && index == 1){        //刪除第一個，且整個list只有一個element
        head = NULL;
        tail = NULL;
        delete current;
        current = NULL;
    }
    
    else if(index == 1){                //刪除最後一個
        head = current ->next;
        head -> pre = NULL;
        delete current;
        current = NULL;
    }
    else if(index == size && size != 1){//刪除最後一個
        previous->next = NULL;
        tail = previous;
        delete current;
        current = NULL;
    }
    else{
        previous->next = current->next;
        current->next->pre = previous;
        delete current;
        current = NULL;
    }
    
    size--;
    return 1;
}
