#include "dictionary.h"
#include <cmath>
#include <iostream>

#define MOD 1000000007LL
#define P 31LL
#define TOMBSTONE "__TOMBSTONE__"

// ---------------- Constructors ----------------
Dictionary::Dictionary() {
    N = DICT_SIZE;
    A = new Entry[N];
    for (int i = 0; i < N; ++i) {
        A[i].key = ""; 
        A[i].value = 0;
    }
}

Dictionary::Dictionary(int n) {
    N = n;
    A = new Entry[N];
    for (int i = 0; i < N; ++i) {
        A[i].key = "";
        A[i].value = 0;
    }
}

// ---------------- Hash Function ----------------
int Dictionary::hashValue(std::string key) {
    long long hash = 0;
    long long factor = 1;
    for (char c : key) {
        hash = (hash + factor * (int)c) % MOD;
        factor = (factor * P) % MOD;
    }
    const double alpha = 0.6180339887;
    double frac = fmod(hash * alpha, 1.0);
    int index = (int)floor(N * frac);
    return index % N;
}

// ---------------- Find Free Index ----------------
int Dictionary::findFreeIndex(std::string key) {
    int idx = hashValue(key);
    int startIdx = idx;

    do {
        if (A[idx].key == "" || A[idx].key == TOMBSTONE || A[idx].key == key) return idx;
        idx = (idx + 1) % N;
    } while (idx != startIdx);

    return -1;
}

// ---------------- Get Entry ----------------
Entry* Dictionary::get(std::string key) {
    int idx = hashValue(key);
    int startIdx = idx;

    do {
        if (A[idx].key == "") return nullptr;
        if (A[idx].key != TOMBSTONE && A[idx].key == key) return &A[idx];
        idx = (idx + 1) % N;
    } while (idx != startIdx);

    return nullptr;
}

// ---------------- Put Entry ----------------
bool Dictionary::put(Entry e) {
    int idx = findFreeIndex(e.key);
    if (idx == -1) return false;

    A[idx].key = e.key;
    A[idx].value = e.value;
    return true;
}

// ---------------- Remove Entry ----------------
bool Dictionary::remove(std::string key) {
    Entry* entry = get(key);
    if (!entry) return false;

    entry->key = TOMBSTONE;
    entry->value = 0;
    return true;
}

// ---------------- Dump Table ----------------
std::vector<std::tuple<std::string,int,int>> Dictionary::dumpTable() {
    std::vector<std::tuple<std::string,int,int>> res;
    for (int i = 0; i < N; ++i) {
        if (A[i].key != "" && A[i].key != TOMBSTONE) {
            res.push_back(std::make_tuple(A[i].key, A[i].value, i));
        }
    }
    return res;
}
