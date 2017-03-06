#include <iostream>
#include <fstream>

#include <sys/time.h>
#include <sys/resource.h>
#include <NBL.h>

#define DEBUG 1

using namespace std;
using namespace NobelLib;

#define PROGRAM_NAME "testing"
#define PROGRAM_VERSION "0.13"

int numFails = 0;
int numTests = 0;
bool btest = true;
int iargc;
char** pargv;

double timeStart, timeDelta;

void get_resource()
{
    ResourceUsage use(Who::useSelf);

    ofstream myfile;
    myfile.open ("nobel.rep", ios::out);
    myfile << "NobelLib report performace:\n" <<
    "Time -> " << Time::Print(Time::Now()) << endl <<
    "Time Elapsed -> " << timeDelta << endl <<
    "Maximum Resident Set Size -> " << use.maxrss() << endl <<
    "Shared Memory Size -> " << use.ixrss() << endl <<
    "Unshared Data Size -> " << use.idrss() << endl <<
    "Unshared Stack Size -> " << use.isrss() << endl <<
    "Page Reclaims -> " << use.minflt() << endl <<
    "Page Faults -> " << use.majflt() << endl <<
    "Swap Memory -> " << use.nswap() << endl <<
    "Input Operation -> " << use.inblock() << endl <<
    "Output Operation -> " << use.oublock() << endl <<
    "Message Sent -> " << use.msgsnd() << endl <<
    "Message Received -> " << use.msgrcv() << endl <<
    "Signals Received -> " << use.nsignals() << endl <<
    "Voluntary Context Switches -> " << use.nvcsw() << endl <<
    "Involuntary Context Switches -> " << use.nivcsw();
    myfile.close();
}


double get_time()
{
    struct timeval t;
    struct timezone tzp;
    gettimeofday(&t, &tzp);
    return t.tv_sec + t.tv_usec*1e-6;
}

static void checkup(char* checkname, bool expression)
{
    numTests++;
    if(expression)
        cout << "[OK] "<< checkname << " test\n";
    else
    {
        cout << "[FAILS]" << checkname << " test\n";
        numFails++;
    }
}
void result()
{
    timeDelta = get_time() - timeStart;
    cout << endl << endl;
    cout << "Number of test Passed: " << numTests - numFails << endl;
    cout << "Number of test Failed: " << numFails << endl;
    cout << "Number of test Executed: " << numTests << endl;
    cout << "Time Elapsed: " << timeDelta << endl;
    get_resource();
    if(numFails == 0)
        cout << "All seems OK... but you can check https://github.com/Nobel3D/Nobel-Library to help me, it would be great! :D" << endl;
}

void testProgram()
{
    Program program(PROGRAM_NAME, PROGRAM_VERSION, iargc, pargv);
    checkup("Program init", program.getName() == PROGRAM_NAME && program.getVersion() == PROGRAM_VERSION);

    ResourceUsage usage(useSelf);
    checkup("Resource Manager",btest);

    Time* now = new Time();
    checkup("Time now: " + now->Print() , true);
}

void testMemory()
{
    Memory mem_int(4,100);
    int* test = (int*)mem_int.getPointer();
    for (int i=0; i< 100; i++) test[i] = i;
    for (int i=0; i< 100 || !btest; i++)  btest = test[i] == i;
    checkup("Memory allocation",btest);

    checkup("Memory space count" , mem_int.getSize() == 4*100);

    Memory pNew(4,200);
    int* pInt = (int*)pNew.getPointer();
    int i = 100;
    int c = 0;
    while (c < 100) pInt[c++] = i--;

    mem_int.Copy(pNew);
    test = (int*)mem_int.getPointer();
    for (int i=0; i< 100 || !btest; i++)  btest = test[i] == c--;
    checkup("Memory copy", btest);

    mem_int.Zero();

    for (int i=0; i< 100 || !btest; i++)  btest = test[i] == 0;
    checkup("Memory zero", btest);

 /*   int x = 100;
    for (int i=0; i < 100; i++) {
        mem_int >> &x;
        btest = x == 0;
    }
    checkup("Memory stream", btest);
*/
    mem_int.Free();
    pNew.Free();

    checkup("Memory clear", mem_int.getSize() == 0 );
}

void testArray()
{
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
    checkup("Array cleaning", numbers.getLength() == 0);

    int* othernumber = new int[10];
    for(int i = 0; i < 10; i++)
        othernumber[i] = i + 10;

    Array<int> copy(othernumber,10);
    checkup("Array copying", copy[3] == 13);

    Array<NString> strings(10);
    strings[0] = "ciao";
    strings[1] = "bello";
    strings[2] = "mondo";
    strings[3] = "hey";
    strings[4] = "xd";
    strings[5] = "lol";

    checkup("Array push stack", strings[0] == "ciao" && strings[1] == "bello" && strings[2] == "mondo" && strings[3] == "hey" && strings[4] == "xd" && strings[5] == "lol");

}

void testList()
{
    List<int> listed;
    for(int i = 0; i < 10 ; i++)
        listed.addItem(i);
    checkup("List allocation", listed[9] == 9);

    listed.findByIndex(9)->setData(99);
    checkup("List modify", listed[9] == 99);

    checkup("List get length", listed.getLength() == 10);

    checkup("List find by object", listed[6] == 6);

//    Array<int>* listarray = listed.toArray();
//    checkup("List to array", (*listarray)[6] = 6);

    listed.Clear();
    checkup("List cleaning", listed.findByIndex(6) == nullptr);

    for(int i = 0; i < 1024; i++)
        listed.addItem(i);

    for(int i = 0; i < 1024; i++)
        cout << listed[i];

    listed.Clear();
}

void testString()
{
    NString hello = "Hello";
    checkup("NString allocation", hello=="Hello");

    hello += " world";
    checkup("NString adding", hello=="Hello world");

    hello.Replace("world", "guys");
    checkup("NString replace", hello == "Hello guys");

    checkup("NString find", hello.Find("guy"));

    Array<NString> space = hello.Split(" ");;
    checkup("NString split", space[0] == "Hello" && space[1] == " guys");

    checkup("NString check Numbers", NString("123").isNumber());

    checkup("NString integer to binary",  NString::toBinary(200) == NString("11001000"));
    checkup("NString integer to hexadecimal",  NString::toHex(200) == NString("C8"));
    checkup("NString integer to string", NString::fromInt(200) == NString("200"));
}

void testTranslate()
{
    Translate<NString,int>* voti = new Translate<NString,int>(10);
    NString read[10] {"pippo","paolo","maria","erika","eleonora","roberto", "matteo", "luca", "francesco", "elisa"};
    for(int i = 0; i<10; i++)
        voti->Add(read[i],i);
    checkup("Translate get destination", (*voti)[read[0]] == 0 && voti->FindBySource(read[9]) == 9);
    checkup("Translate get source", voti->FindByDestination(0) == read[0] && voti->FindByDestination(9) == read[9]);
}
void testFilename()
{
    Filename file("/home/luca/Programmazione/codeblocks.conf");
    checkup("Filename get Path", file.getPath() == "/home/luca/Programmazione/");
    checkup("Filename get Name", file.getName() == "codeblocks.conf");
    checkup("Filename get Extension", file.getExt() == ".conf");
}
void testFile()
{
    NFile writefile("file.txt");
    writefile.Open(Writing);
    writefile << "somethings happened :D";
    writefile.Close();

    NString reading;
    NFile readfile("file.txt");
    readfile.Open(Reading);
    readfile >>  reading;
    readfile.Close();
    checkup("NFile write/read operations", reading == "somethings happened :D\n");


    int num;
    NFile readf("file.txt");
    readf.Open(Reading);
    readf >> num;
    readf.Close();

    std::cout << num << std::endl;
}

void testLog()
{
    Log::Add("user", "checking log", NL_LOGPATH);
}

int main(int argc, char** argv)
{
#if DEBUG == 1
    iargc = argc;
    pargv = argv;

    timeStart = get_time();

    cout << NString("HELLO ") + ":3\n";
    testProgram();
    testMemory();
    testArray();
    testList();
    testString();
    testTranslate();
    testFilename();
    testFile();
    testLog();

    result();
    return 0;

#else // DEBUG

    return 0;
#endif // DEBUG
}

