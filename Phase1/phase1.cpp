#include<iostream>
#include<fstream>
using namespace std;

class program
{
    char M[100][4]; // main memory
    char IR[4]; //instruction register
    char R[4]; // register
    int IC ;// instruction counter;
    int SI ; // service interrupt;
    char buffer[40];
    bool C ;// flag for CR;
    int flag;
    int m;

public:
    void init();
    void load();
    int getloc(); 
    void startExecution();
    void executeUserProgram();
    void MOS();
    void read();
    void write();
    void terminate();
    fstream Input;
    fstream Output;
};

void program::init()
{
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            M[i][j] = '\0';
        }
    }
    
    C = false;
    IR[4] = {' '};

    R[4] = {' '};
    flag = 0;
    m = 0;
}

int program::getloc()
{
    int mem = ((IR[2] - '0') * 10) + (IR[3] - '0');
    return mem;
}

void program::load()
{

     while (!Input.eof())
    {
        // initialising buffer
        for (int i = 0; i < 40; i++)
        {
            buffer[i] = '\0';
        }

        // reading from input file line by line
        Input.getline(buffer, 41);

        if (buffer[0] == '$' && buffer[1] == 'A' && buffer[2] == 'M' && buffer[3] == 'J')
        {
            init();
        }
        else if (buffer[0] == '$' && buffer[1] == 'D' && buffer[2] == 'T' && buffer[3] == 'A')
        {
            startExecution();
        }
        else if (buffer[0] == '$' && buffer[1] == 'E' && buffer[2] == 'N' && buffer[3] == 'D')
        {
            int x = 0;
            for (int i = 0; i < 100; i++)
            {
                cout << "M" << x << ":" << M[i][0] << M[i][1] << M[i][2] << M[i][3] << endl;
                x++;
            }

            break;
        }
        else
        {
            // reading from the program card
            int k = 0;
            for (; m < 100; m++)
            {
                for (int j = 0; j < 4; j++)
                {
                    // error handling for when the OP_CODE is 'H'
                    if (buffer[k] == 'H')
                    {
                        M[m][j] = buffer[k];
                        k++;
                        break;
                    }
                    else
                    {
                        M[m][j] = buffer[k];
                        k++;
                    }
                }
                if (k == 40 || buffer[k] == ' ' || buffer[k] == '\0')
                {
                    m++;
                    break;
                }
            }
        }
    }
}

void program::startExecution()
{
    IC = 00;
    executeUserProgram();
}

void program::executeUserProgram()
{

    while (true)
    {
        // reading next instruction
        IR[0] = M[IC][0];
        IR[1] = M[IC][1];
        IR[2] = M[IC][2];
        IR[3] = M[IC][3];

        IC++;

        if (IR[0] == 'P' && IR[1] == 'D')
        {
            SI = 2;
            MOS();
        }
        else if (IR[0] == 'G' && IR[1] == 'D')
        {
            SI = 1;
            MOS();
        }
        else if (IR[0] == 'L' && IR[1] == 'R')
        {
            int loc = getloc();

            for (int i = 0; i < 4; i++)
            {
                R[i] = M[loc][i];
            }
        }
        else if (IR[0] == 'S' && IR[1] == 'R')
        {
            int loc = getloc();
            for (int i = 0; i < 4; i++)
            {
                M[loc][i] = R[i];
            }
        }
        else if (IR[0] == 'B' && IR[1]== 'T')
        {
            if (C)
            {
                int loc = getloc();
                IC = loc;
            }
        }
        else if (IR[0] == 'C' && IR[1] == 'R')
        {

            int loc = getloc();

            if (R[0] == M[loc][0] && R[1] == M[loc][1] && R[2] == M[loc][2] && R[3] == M[loc][3])
            {
                C = true;
            }
            else
            {
                C = false;
            }
        }
        else if (IR[0] == 'H')
        {
            SI = 3;
            MOS();
            break;
        }
    }
}

void program::MOS()
{
    switch (SI)
    {
    case 1:
        read();
        break;
    case 2:
        write();
        break;
    case 3:
        terminate();
        break;
    default:
        break;
    }
}

void program::read()
{
    for (int i = 0; i < 40; i++)
    {
        buffer[i] = '\0';
    }
    // reading data from data card and putting it into buffer
    Input.getline(buffer, 41);

    if (buffer[0] == '$' && buffer[1] == 'E' && buffer[2] == 'N' && buffer[3] == 'D')
    {
        return;
    }


    int loc = getloc();

    int k = 0;
    for (int l = loc; l < loc + 10; l++)
    {
        for (int j = 0; j < 4; j++)
        {
            M[l][j] = buffer[k];
            k++;
        }
    }
    SI = 0;
}

void program::write()
{
    for (int i = 0; i < 40; i++)
    {
        buffer[i] = '\0';
    }

    int loc = getloc();
    // reading data from Memory and putting it into buffer
    int k = 0;
    for (int l = loc; l < loc + 10; l++)
    {
        for (int j = 0; j < 4; j++)
        {
            buffer[k] = M[l][j];
            k++;
        }
    }

    // printing buffer data to output.txt
    string output = "";
    for (int i = 0; i < 40; i++)
    {
        if (buffer[i] != '\0')
        {
            output += buffer[i];
        }
    }

    cout << "output: " << output << endl;

    Output << output;
    Output << "\n";
    SI = 0;
}

void program::terminate()
{
    cout << "terminate\n";
    Output << "\n\n";
    load();
}

int main()
{

    program prog;

    prog.Input.open("input.txt", ios::in);
    prog.Output.open("output.txt", ios::app);

    if (!prog.Input)
    {
        cout << "File cannot open\n";
    }
    else
    {
        cout << "File Exist \n";
    }
    prog.load();
    prog.Input.close();
    prog.Output.close();
    return 0;
}

