
#ifndef HUFFMAN_H
#define HUFFMAN_H

#include<raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct MinHeapNode {
    char data;
    unsigned freq;
    struct MinHeapNode *left, *right;
};

struct MinHeap {
    unsigned size;
    unsigned capacity;
    struct MinHeapNode** array;
};


void minHeapify(struct MinHeap* minHeap, int idx);
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b);
int isSizeOne(struct MinHeap* minHeap) ;
struct MinHeapNode* newNode(char data, unsigned freq);
struct MinHeap* createMinHeap(unsigned capacity);
struct MinHeapNode* extractMin(struct MinHeap* minHeap);
void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode);
void buildMinHeap(struct MinHeap* minHeap);
void printArr(int arr[], int n,FILE*f) ;
int isLeaf(struct MinHeapNode* root) ;
void printCodes(struct MinHeapNode* root, int arr[], int top,FILE*f) ;
void HuffmanCodes(char data[], int freq[], int size,const char* filename);

#endif

