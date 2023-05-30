
#include "Mylib.h"


bool isPunctuation(char c) 
{
    static const string punctuation = "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~–";
    return punctuation.find(c) != string::npos;
}

bool compareFrequency(const pair<string, int>& a, const pair<string, int>& b) // Sort in descending order of frequency
{
    return a.second > b.second;  
}

void ReadWriteFrequency(const string& inputFilePath, const string& outputFilePath) 
{
    unordered_map<string, int> wordFrequency;
    unordered_map<string, vector<int>> wordLines;

    ifstream inputFile(inputFilePath);
    if (!inputFile.is_open()) 
    {
        cout << "Failed to open the input file." << endl;
        return;
    }

    string line;
    int lineNum = 1;
    while (getline(inputFile, line)) 
    {
        std::istringstream iss(line);
        string word;
        while (iss >> word) 
        {
            word.erase(remove_if(word.begin(), word.end(), isPunctuation), word.end()); // Remove punctuation from word
            transform(word.begin(), word.end(), word.begin(), [](unsigned char c) { return tolower(c); }); // Convert word to lowercase

            if (!word.empty()) 
            {
                ++wordFrequency[word];
                wordLines[word].push_back(lineNum);
            }
        }
        ++lineNum;
    }

    inputFile.close();

    vector<pair<string, int>> wordFrequencyVec(wordFrequency.begin(), wordFrequency.end());
    sort(wordFrequencyVec.begin(), wordFrequencyVec.end(), compareFrequency);

    ofstream outputFile(outputFilePath);
    if (!outputFile.is_open()) 
    {
        cout << "Failed to open the output file." << endl;
        return;
    }

    for (const auto& pair : wordFrequencyVec) 
    {
        const string& word = pair.first;
        int frequency = pair.second;

        if (frequency > 1) {
            outputFile << "Word: " << word << " (Frequency: " << frequency << ")" << endl;
            outputFile << "Found in lines: ";
            for (int line : wordLines[word]) 
            {
                outputFile << line << ", ";
            }
            outputFile << endl << endl;
        }
    }

    outputFile.close();

    cout << "Word frequency count completed. Results saved in " << outputFilePath << endl;
}

int main() 
{
    string inputFilePath = "skaitymas.txt";  // Input file name
    string outputFilePath = "spausdinimas.txt";  // Output file name

    ReadWriteFrequency(inputFilePath, outputFilePath);

    return 0;
}
