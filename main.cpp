#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <chrono>

using namespace std;

unordered_map<string, vector<string>> dictionary;
unordered_map<string, vector<string>> postings;

void loadDictionary(const string& dictionaryFile) {
    ifstream file(dictionaryFile);
    string line;
    while (getline(file, line)) {
        transform(line.begin(), line.end(), line.begin(), ::tolower);
        dictionary[line] = vector<string>();
    }
    file.close();
}

void loadPostings(const string& postingsFile) {
    ifstream file(postingsFile);
    string line;
    while (getline(file, line)) {
        istringstream ss(line);
        string word, document;
        ss >> word;
        while (ss >> document) {
            transform(word.begin(), word.end(), word.begin(), ::tolower);
            postings[word].push_back(document);
        }
    }
    file.close();
}

void searchWord(const string& word) {
    string lowerWord = word;
    transform(lowerWord.begin(), lowerWord.end(), lowerWord.begin(), ::tolower);

    if (postings.find(lowerWord) != postings.end()) {
        cout << "Found in the following documents:" << endl;
        for (const auto& doc : postings[lowerWord]) {
            cout << doc << endl;
        }
    } else {
        cout << "No results found for " << word << "." << endl;
    }
}

void logTime(double duration) {
    ofstream logFile("a12_matricula.txt");
    logFile << "Time taken for search: " << duration << " seconds" << endl;
    logFile.close();
}

int main() {
    ifstream inputFile("input.txt");
    if (!inputFile) {
        cout << "Error: Unable to open input file!" << endl;
        return 1;
    }

    auto start = chrono::high_resolution_clock::now();

    loadDictionary("dictionary.txt");
    loadPostings("postings.txt");

    string word;
    while (getline(inputFile, word)) {
        cout << "Searching for: " << word << endl;
        searchWord(word);
    }

    inputFile.close();

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    logTime(duration.count());

    return 0;
}


