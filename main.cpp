
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

    vector<pair<string, int>> wordFrequencyVec(wordFrequency.begin(), wordFrequency.end());
    sort(wordFrequencyVec.begin(), wordFrequencyVec.end(), compareFrequency);

    ofstream outputFile(outputFilePath);

    for (const auto& pair : wordFrequencyVec) 
    {
        const string& word = pair.first;
        int frequency = pair.second;

        if (frequency > 1) {
            outputFile << "Word: " << word << " (Frequency: " << frequency << ")" << endl;
            outputFile << "Found in lines: ";
            for (int line : wordLines[word]) 
            {
                outputFile << line << " ";
            }
            outputFile << endl << endl;
        }
    }

    inputFile.close();
    outputFile.close();

    cout << "Word frequency count completed. Results saved in " << outputFilePath << endl;
}


void FindURL(const string& inputFilePath, const string& outputFilePath) 
{
    ifstream inputFile(inputFilePath);

    string line;
    regex urlRegex(R"(\b(?:https?|ftp):\/\/[\w-]+(?:\.[\w-]+)+(?:[\w.,@?^=%&:/~+#-]*[\w@?^=%&/~+#-])?\b|\bwww\.[\w-]+(?:\.[\w-]+)+(?:[\w.,@?^=%&:/~+#-]*[\w@?^=%&/~+#-])?\b)");

    ofstream outputFile(outputFilePath);

    while (getline(inputFile, line)) {
        std::smatch match;
        string::const_iterator searchStart(line.cbegin());

        while (regex_search(searchStart, line.cend(), match, urlRegex)) {
            for (const auto& url : match) {
                outputFile << "URL found: " << url << endl;
            }
            searchStart = match.suffix().first;
        }
    }

    inputFile.close();
    outputFile.close();

    cout << "URL search completed. Results saved in " << outputFilePath << endl;
}

int main() 
{
    string inputFilePath = "skaitymas.txt";  // Input file name
    string outputFilePath = "spausdinimas.txt";  // Output file name
    char kint;

    cout << "Sveiki! Paisirinkite, ką norite daryti: " <<endl;
    cout << "Įrašykite F, jei norite gauti failo žodžių dažnį;" <<endl;
    cout << "Įrašykite U, jei norite gauti faile esančius URL." <<endl;
    cin >> kint;

    if(kint == 'F' || kint == 'f')
    {
        ReadWriteFrequency(inputFilePath, outputFilePath);
    } else 
        if(kint == 'U' || kint == 'u')
        {
            FindURL("url_skaitymas.txt", "url_rasymas.txt");
        }

    
    return 0;
}
