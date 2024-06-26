#include <iostream>
#include <vector>
#include <stack>

using namespace std;

const int tape_sz = 1e5;

int main()
{
    string program;
    cin >> program;

    vector<char> tape(tape_sz, char(0));
    int tape_id = 0;
    char curr_instruction;

    stack<int> loop_begin_index;

    int prog_len = program.size();
    for (int i = 0; i < prog_len; i++)
    {
        curr_instruction = program[i];
        if (curr_instruction == '+')
        {
            tape[tape_id]++;
            if (tape[tape_id] == 256)
                tape[tape_id] = 0;
        }
        else if (curr_instruction == '-')
        {
            tape[tape_id]--;
            if (tape[tape_id] == -1)
                tape[tape_id] = 255;
        }
        else if (curr_instruction == ',')
        {
            char input_char;
            cin >> input_char;
            tape[tape_id] = input_char;
        }
        else if (curr_instruction == '.')
        {
            cout << tape[tape_id];
        }
        else if (curr_instruction == '>')
        {
            tape_id++;
            if (tape_id == tape_sz)
                tape_id = 0;
        }
        else if (curr_instruction == '<')
        {
            tape_id--;
            if (tape_id == -1)
                tape_id = tape_sz - 1;
        }
        else if (curr_instruction == '[')
        {
            loop_begin_index.push(i);
            int j = i;
            while (j < prog_len && program[j] != ']')
                j++;
            if (tape[tape_id] == 0)
                i = j;
        }
        else if (curr_instruction == ']')
        {
            if (tape[tape_id] > 0)
            {
                i = loop_begin_index.top();
            }
            else
            {
                loop_begin_index.pop();
            }
        }
    }
    return 0;
}