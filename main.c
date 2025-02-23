#include <assert.h>
#include <stdio.h>
#include <string.h>

bool digit(const unsigned int bits, const unsigned int n)
{
    const unsigned int mask = 1 << n;
    const unsigned int result = bits & mask;
    return result >> n;
}

unsigned int short_to_uint(const short bits[5])
{
    return (bits[0] << 4) + (bits[1] << 3) + (bits[2] << 2) + (bits[3] << 1) + (bits[4] << 0);
}

void uint_to_short(short *bits, const unsigned int value)
{
    bits[0] = digit(value, 4);
    bits[1] = digit(value, 3);
    bits[2] = digit(value, 2);
    bits[3] = digit(value, 1);
    bits[4] = digit(value, 0);
}

int main(void) {
    int arr[21] = {0};
    unsigned int occupation = 0;
    short next[24][5];
    memset(next, -1, sizeof next);
    char line[100];
    while (fgets(line, sizeof(line), stdin))
    {
        line[strcspn(line, "\n")] = '\0';
        char cmd[5];
        int stack_num, value;
        if (sscanf(line, "%4s %d %d", cmd, &stack_num, &value) == 3)
        {
            if (strcmp(cmd, "push") != 0) continue;
            unsigned int n = 0;
            while (digit(occupation, n))
            {
                assert(n < 21);
                n++;
            }
            arr[n] = value;
            const unsigned int head_index = short_to_uint(next[21 + stack_num]); 
            if (next[21 + stack_num][0] != -1)
            {
                uint_to_short(next[head_index], n);
            }
            uint_to_short(next[21 + stack_num], n);
            occupation |= 1 << n;
        }
        else if (sscanf(line, "%4s %d", cmd, &stack_num) == 2)
        {
            if (strcmp(cmd, "pop") != 0) continue;
            const unsigned int head_index = short_to_uint(next[21 + stack_num]);
            printf("%d\n", arr[head_index]);
            uint_to_short(next[21 + stack_num], -1);
            for (unsigned int i = 0; i < 21; i++)
            {
                if (short_to_uint(next[i]) == head_index)
                {
                    uint_to_short(next[21 + stack_num], i);
                    uint_to_short(next[i], -1);
                    break;
                }
            }
            occupation &= ~(1 << head_index);
        }
    }
}
