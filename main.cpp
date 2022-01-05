#include <iostream>
#include <map>
#include <vector>
#include <cstring>

#define VERSION "1.0.3"

using namespace std;

struct FLAG {
    char shortN;
    const char* longN;
    int argRequire;
};

typedef vector<FLAG>::const_iterator iter;
class ERRORINPUT {};

void error(const char*);
int define(int, char* [], vector<FLAG>);
int defineShort(char*, vector<FLAG>);
int onlyShort(char*&, vector<FLAG>, int&);
int defineLong(int, char* [], vector<FLAG>);
int argI = 1;

void help();
void list(const char*);
void version(const char*);

map<char, char*> Flags;
vector<char> queue;

vector<FLAG> allFlags;

int main(int argc, char* argv[])
{
    if (argc == 1) return 0;

    allFlags.push_back(FLAG{ 'h', "help", 0 });
    allFlags.push_back(FLAG{ 'v', "version", 1 });


    try
    {
        while (define(argc, argv, allFlags) != -1);

        for (unsigned long int i = 0; i < queue.size(); i++)
        {
            switch (queue[i])
            {
            case 'h':
                help();
                break;
            case 'v':
                version(Flags[queue[i]]);
                break;
            default:
                break;
            }
        }
    }
    catch (...)
    {
        cerr << "Invalid input\n";
        return -1;
    }

    return 0;
}

void help()
{
    cout << "This is demo help. Try -h or --help.\n";
}

void version(const char* v)
{
    if (!*v)
    {
    VER:
        cout << "Version: " << VERSION << '\n';
    }
    else
    {
        const char* check = v;
        while (*check++)
        {
            if (*check != '.' && (*check > 57 || *check < 48))
            {
                goto VER;
            }
        }
        cout << "Version: " << v << '\n';
    }
}

int define(int argc, char* argv[], vector<FLAG> flags)
{
    int rez = -1;

    if (argI >= argc) return -1;

    char* arg = argv[argI];

    if (strlen(arg) > 3 && *arg == '-' && *(arg + 1) == '-' && *(arg + 2) >= 65)
        rez = defineLong(argc, argv, flags);
    else if (strlen(arg) >= 2 && *arg == '-' && *(arg + 1) >= 65)
        rez = defineShort(arg + 1, flags);
    else throw new ERRORINPUT();

    return rez;
}

int defineShort(char* arg, vector<FLAG> flags)
{
    int rez = -1;

    int f;
    if ((rez = onlyShort(arg, flags, f)) == -1) error(arg);

    if (Flags.find(rez) == Flags.end())
        queue.push_back(rez);

    int r;
    if (onlyShort(arg, flags, r) == -1)
    {
        if (flags[f].argRequire > 0)
        {
            if (!*arg)
                if (flags[f].argRequire == 2)
                {
                    error(arg - 1);
                    Flags[rez] = (char*)"???";
                }
                else Flags[rez] = (char*)"";
            else
            {
                int l = strlen(arg) + 1;
                Flags[rez] = new char[l];
                copy(arg, arg + l, Flags[rez]);
            }
        }
        else
        {
            Flags[rez] = (char*)"";
        }
        argI++;
    }
    else
    {
        arg--;
        Flags[rez] = (char*)"";
        rez = defineShort(arg, flags);
    }
    return rez;
}

int onlyShort(char*& arg, vector<FLAG> flags, int& flag)
{
    int rez = -1;

    for (long unsigned int i = 0; i < flags.size(); i++)
    {
        if (flags[i].shortN == *arg)
        {
            rez = *arg++;
            flag = i;
            break;
        }
    }

    return rez;
}

int defineLong(int argc, char* argv[], vector<FLAG> flags)
{
    int rez = -1;

    if (argI >= argc) return -1;

    char* arg = argv[argI] + 2;

    iter f;
    for (f = flags.begin(); f != flags.end(); f++)
    {
        if (!(rez = strcmp(arg, (*f).longN)))
            break;
    }
    if (rez) return -1;

    rez = (*f).shortN;

    if (Flags.find(rez) == Flags.end())
        queue.push_back(rez);

    argI++;
    if ((*f).argRequire > 0)
    {
        if (argI >= argc)
            if ((*f).argRequire == 2) error(argv[argI - 1]);
            else Flags[rez] = (char*)"";
        else if (!strcmp(argv[argI], "="))
        {
            argI++;
            arg = argv[argI];
            int l = strlen(arg) + 1;
            Flags[rez] = new char[l];
            copy(arg, arg + l, Flags[rez]);
            argI++;
        }
        else if ((*f).argRequire == 2) error(argv[argI]);
        else Flags[rez] = (char*)"";
    }
    else Flags[rez] = (char*)"";

    return rez;
}

void error(const char* err)
{
    cerr << "Invalid option -- " << err << '\n';
    throw new ERRORINPUT();
}