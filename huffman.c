#include "include/huffman.h"


#define MAX_TREE_HT 256

// -------------------- Node and MinHeap --------------------
struct MinHeapNode* newNode(char data, unsigned freq) {
    struct MinHeapNode* temp = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;
    return temp;
}

struct MinHeap* createMinHeap(unsigned capacity) {
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHeapNode**)malloc(capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}

void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b) {
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(struct MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx) {
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

int isSizeOne(struct MinHeap* minHeap) {
    return (minHeap->size == 1);
}

struct MinHeapNode* extractMin(struct MinHeap* minHeap) {
    struct MinHeapNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}

void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode) {
    ++minHeap->size;
    int i = minHeap->size - 1;
    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = minHeapNode;
}

void buildMinHeap(struct MinHeap* minHeap) {
    int n = minHeap->size - 1;
    for (int i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}

// -------------------- Huffman Tree --------------------
int isLeaf(struct MinHeapNode* root) {
    return !(root->left) && !(root->right);
}

void printArr(int arr[], int n, FILE* f) {
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        fprintf(f, "%d", arr[i]);
    }
    printf("\n");
}

void printCodes(struct MinHeapNode* root, int arr[], int top, FILE* f) {
    if (root->left) {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1, f);
    }
    if (root->right) {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1, f);
    }
    if (isLeaf(root)) {
        printf("%c: ", root->data);
        printArr(arr, top, f);
    }
}

// -------------------- Memory Cleanup --------------------
void freeTree(struct MinHeapNode* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

// -------------------- Huffman Codes --------------------
void HuffmanCodes(char data[], int freq[], int size, const char* filename) {
    struct MinHeapNode *left, *right, *top;
    struct MinHeap* minHeap = createMinHeap(size);
    int codes[MAX_TREE_HT];

    for (int i = 0; i < size; ++i)
        minHeap->array[i] = newNode(data[i], freq[i]);
    minHeap->size = size;
    buildMinHeap(minHeap);

    while (!isSizeOne(minHeap)) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);
        top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        insertMinHeap(minHeap, top);
    }

    FILE *f = fopen(filename, "w");
    if (!f) {
        perror("Cannot open file");
        exit(1);
    }

    printCodes(minHeap->array[0], codes, 0, f);
    fclose(f);

    // Free memory
    freeTree(minHeap->array[0]);
    free(minHeap->array);
    free(minHeap);
}

