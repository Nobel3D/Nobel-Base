#include <iostream>
#include <time.h>
#include <NBL.h>

#define DEBUG 1

using namespace std;
using namespace NobelLib;

int numFails = 0;
int numTests = 0;

void checkup(char* checkname, bool expression)
{
    numTests++;
    if(expression)
        cout << checkname << " test: [OK]\n";
    else
    {
        cout << checkname << " test: [FAILS]\n";
        numFails++;
    }
}

void result()
{
    cout << endl << endl;
    cout << "Number of test Passed: " << numTests - numFails << endl;
    cout << "Number of test Failed: " << numFails << endl;
    cout << "Number of test Executed: " << numTests << endl;
    if(numFails == 0)
        cout << "All seems OK... but you can check https://github.com/Nobel3D/Nobel-Library to help me, it would be great! :D" << endl;
}


int main()
{
#if DEBUG == 1
    Array<int> numbers(10);
    for(int i = 0; i < 10 ; i++)
        numbers[i] = i;
    checkup("Array allocation", numbers[0] == 0 && numbers[5] == 5 && numbers[9] == 9);

    numbers.Expand(12);
    numbers[10] = 10;
    numbers[11] = 11;
    checkup("Array adding", numbers[10] == 10 && numbers[11] == 11);

    numbers[1] = 99;
    checkup("Array replace", numbers[1] == 99);

    numbers.Clear();
    checkup("Array cleaning", numbers[2] != 2);

    int* othernumber = new int[10];
    for(int i = 0; i < 10 ; i++)
        othernumber[i] = i + 10;
    numbers.Copy(othernumber);
    checkup("Array copying", numbers[3] == 13);
    List<int> listed;
    for(int i = 0; i < 10 ; i++)
        listed.addItem(i);
    checkup("List allocation", listed[9] == 9);

    listed[9] = 99;
    checkup("List modify", listed[9] == 99);

    checkup("List get length", listed.getLength() == 10);

    checkup("List find by object", listed.findByObject(6) == 6);

    Array<int>* listarray = listed.toArray();
    checkup("List to array", (*listarray)[6] = 6);

    listed.Clear();
    checkup("List cleaning", listed[0] != 0);

    NString hello = "Hello";
    checkup("NString allocation", hello=="Hello");

    hello += " world";
    checkup("NString adding", hello=="Hello world");

    checkup("NString replace", hello.Replace("world", "guys") == "Hello guys");

    checkup("NString find", hello.Find("wor"));

    List<NString>* strList = hello.Split(" ");
    Array<NString>* space = strList->toArray();
    checkup("NString split", (*space)[0] == "Hello" && (*space)[1] == "world");

    checkup("NString check Numbers", NString("123").chk_Number());

    checkup("NString integer to binary",  NString::toBinary(200) == NString("11001000"));
    checkup("NString integer to hexadecimal",  NString::toHex(200) == NString("C8"));
    checkup("NString integer to string", NString::fromInt(200) == NString("200"));

    Translate<NString,int> voti(10);
    const NString read[10] {"pippo","paolo","maria","erika","eleonora","roberto", "matteo", "luca", "francesco", "elisa"};
    for(int i = 0; i<10; i++)
        voti.Add(read[i],i);
    checkup("Translate get destination", voti[read[0]] == 0 && voti.FindBySource(read[9]) == 9);
    checkup("Translate get source", voti.FindByDestination(0) == read[0] && voti.FindByDestination(9) == read[9]);

    Time* now = new Time();
    checkup("Time now: " + now->Print() , true);

    NFile writefile("file.txt");
    writefile.Open(Writing);
    writefile << "somethings happened :D";
    writefile.Close();

    NString reading;
    NFile readfile("file.txt");
    readfile.Open(Reading);
    readfile >>  reading;
    readfile.Close();
    checkup("NFile write/read operations", reading == "somethings happened :D");

    Log::Add("user", "checking log", NL_LOGPATH);

    result();
    return 0;
#else // DEBUG

    Translate<NString,int> voti(10);
    const NString read[10] {"pippo","paolo","maria","erika","eleonora","roberto", "matteo", "luca", "francesco", "elisa"};
    int i=0;
    while (i<10)
    {
        voti.Add(read[i],i);
        cout << voti.FindBySource(read[i]) << " ";
        cout << voti.FindByDestination(i)<< endl;
        i++;
    }

    return 0;
#endif // DEBUG
}

