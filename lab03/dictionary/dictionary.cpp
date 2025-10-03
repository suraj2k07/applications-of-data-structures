#include "dictionary.h"
#include <cstring>
#include <cmath>
#include <iostream>

#define MOD 1000000007LL
#define P 31LL
#define TOMBSTONE ((char*)-1)

Dictionary::Dictionary() {
    N = DICT_SIZE;
    A = new Entry[N];
    for (int i = 0; i < N; ++i) {
        A[i].key = nullptr; // empty slot
        A[i].value = 0;
    }
}

Dictionary::~Dictionary() {
    for (int i = 0; i < N; ++i) {
        if (A[i].key != nullptr && A[i].key != TOMBSTONE) {
            delete[] A[i].key;
        }
    }
    delete[] A;
}

// Polynomial accumulation + Fibonacci compression
int Dictionary::hashValue(char key[]) {
    long long hash = 0;
    long long factor = 1;

    for (int i = 0; key[i] != '\0'; i++) {
        hash = (hash + factor * (int)key[i]) % MOD;
        factor = (factor * P) % MOD;
    }

    // Fibonacci compression
    const double alpha = 0.6180339887;
    double frac = fmod(hash * alpha, 1.0); // get fractional part
    int index = (int)floor(N * frac);
    return index % N;
}

// Find free index using linear probing (consider TOMBSTONE)
int Dictionary::findFreeIndex(char key[]) {
    int idx = hashValue(key);
    int startIdx = idx;

    do {
        if (A[idx].key == nullptr || A[idx].key == TOMBSTONE || strcmp(A[idx].key, key) == 0) {
            return idx;
        }
        idx = (idx + 1) % N;
    } while (idx != startIdx);

    return -1; // no free slot
}

Entry* Dictionary::get(char key[]) {
    int idx = hashValue(key);
    int startIdx = idx;

    do {
        if (A[idx].key == nullptr) return nullptr;
        if (A[idx].key != TOMBSTONE && strcmp(A[idx].key, key) == 0) return &A[idx];
        idx = (idx + 1) % N;
    } while (idx != startIdx);

    return nullptr;
}

bool Dictionary::put(Entry e) {
    int idx = findFreeIndex(e.key);
    if (idx == -1) return false;

    if (A[idx].key != nullptr && A[idx].key != TOMBSTONE) {
        delete[] A[idx].key; // replace existing key
    }

    A[idx].key = new char[strlen(e.key) + 1];
    strcpy(A[idx].key, e.key);
    A[idx].value = e.value;
    return true;
}

bool Dictionary::remove(char key[]) {
    Entry* entry = get(key);
    if (!entry) return false;
    delete[] entry->key;
    entry->key = TOMBSTONE; // mark as deleted
    entry->value = 0;
    return true;
}
