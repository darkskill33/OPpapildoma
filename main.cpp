#include "functions.h"


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
