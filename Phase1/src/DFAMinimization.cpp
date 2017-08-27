#include "DFAMinimization.h"

DFAMinimization::DFAMinimization(vector<Node> states)
{
    this->states = states;
}

void DFAMinimization::minimize()
{
    temp = new int*[states];
    for(int i=0;i<states;i++)
    {
        temp[i] = new int[3];
        if(final_states & (1 << i))
            temp[i][1] = 1;
        else
            temp[i][1] = 0;
        temp[i][2] = 0;
    }

    int partitions = 2;
    for(int i = 0; i < 2; i++)
        if(partitioning(partitions))
        {
                i = 0;
                partitions *= 2;
        }
}

bool DFAMinimization::partitioning(int partitions)
{
    int input[10] = {4, 5, 2, 2, 1, 7, 8, 0, 0, 1};

    bool flag_3 = false;
    int increasing = 1 << (partitions % 2);

    for(int i = 0; i < partitions; i++)
    {
        bool flag_1 = false;
        bool flag_2 = false;
        for(int j = 0; j < states; i++)
        {
            if(temp[j][1] == i)
            {
                temp[j][2] = get_state(j, input);
                if(!flag_2 && !flag_1)
                    if(temp[j][2] == 1)
                        flag_1 = true;
                    else
                        flag_2 = true;
                if(temp[j][2] == 1 && flag_2)
                {
                    temp[j][1] += increasing;
                    flag_3 = true;
                }
                else if(temp[j][2] != 1 && flag_1)
                {
                    temp[j][1] += increasing;
                    flag_3 = true;
                }

            }
        }
    }
    return flag_3;
}

Node *DFAMinimization::get_state(string value)
{

}

