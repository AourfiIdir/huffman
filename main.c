#include "include/huffman.h"

int main() {
    //you can use a function to let the user select the array 
    //or make it more advanced by using files directly :/
    char arr[] = {'a', 'b', 'c', 'd', 'e'};//you can write a function that returns all the characters used
    int freq[] = {5, 9, 12, 13, 16};//you can write a function that extracts the freq on a file
    int size = sizeof(arr) / sizeof(arr[0]);
    HuffmanCodes(arr, freq, size);
    return 0;
}