#include <iostream>
#include <fstream>
#include <string>
#include <map>

int main(int argc, char *argv[])
{
    using namespace std;
    if (argc == 1)
    {
        cout << "Missing File Path\n";
        return 0;
    }

    ifstream file;
    file.open(argv[1]);

    if (!file.is_open())
    {
        cout << "Invalid File Path\n";
        return 0;
    }

    string line;
    if (!getline(file, line))
    {
        cout << "Empty File\n";
        return 0;
    }

    if (line.size() != 1)
    {
        cout << "Expected single character to denote being revealed by default\n";
        return 0;
    }

    char revealedByDefault = line[0];
    map<char, string> conversions;
    conversions[revealedByDefault] = "";

    int boardWidth = -1;
    string output = "";

    while (getline(file, line))
    {
        if (line.size() == 0)
            break;
        if (conversions.count(line[0]) != 0)
        {
            cout << "Token \'" << line[0] << "\' was assigned multiple times\n";
            return 0;
        }
        if (line[1] != '|')
        {
            cout << "Token \'" << line[0] << "\' is missing its definition\n";
            return 0;
        }
        conversions[line[0]] = line.substr(2);
    }
    while (getline(file, line))
    {
        int tokenNumber = 0;

        for (int i = 0; i < line.size(); i++)
        {
            tokenNumber++;
            if (line[i] == revealedByDefault)
            {
                i++;
                if (i == line.size())
                {
                    cout << "Default revealing indicator at end of line\n";
                    return 0;
                }
                if (line[i] == revealedByDefault)
                {
                    cout << "Duplicate default revealing indicators\n";
                    return 0;
                }
                if (conversions.count(line[i]) == 0)
                {
                    cout << "Unknown token  \'" << line[i] << "\'\n";
                    return 0;
                }
                output += conversions.at(line[i]);
            }
            else
            {
                output += "||";
                if (conversions.count(line[i]) == 0)
                {
                    cout << "Unknown token  \'" << line[i] << "\'\n";
                    return 0;
                }
                output += conversions.at(line[i]);
                output += "||";
            }
        }

        if (boardWidth == -1)
        {
            boardWidth = tokenNumber;
        }
        if (boardWidth != tokenNumber)
        {
            cout << "Inconsistent line length, expected " << to_string(boardWidth) << " tokens but found " << to_string(tokenNumber) << "\n";
            return 0;
        }
        output += "\n";
    }

    cout << "\n" << output << "\n";
}