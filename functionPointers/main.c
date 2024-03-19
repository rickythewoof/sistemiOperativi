#include <stdio.h>

int num = 0;
typedef void (*State_ptr)(unsigned char);

void S1(unsigned char c);
void S2(unsigned char c);
void S3(unsigned char c);
void S4(unsigned char c);
void S5(unsigned char c);

State_ptr curr_state = S1;

void S1(unsigned char c)
{
    printf("State1\n");
    if (c == 0xAA)
    {
        
        curr_state = S2;
    }
    else
    {

        curr_state = S1;
    }
}
void S2(unsigned char c)
{
    printf("Entering State2\n");
    if (c == 0x55)
    {
        curr_state = S3;
    }
    else
    {
        curr_state = S2;
    }
}
void S3(unsigned char c)
{
    printf("Entering State3\n");
    num = c;
    curr_state = S4;
}
void S4(unsigned char c)
{
    printf("Entering State4\n");
    if (num == 0)
    {
        curr_state = S5;
    } num--;
}
void S5(unsigned char c)
{
    printf("Entering State5\n");
    if (c == 0xAA)
    {
        curr_state = S2;
    }
    else
    {
        curr_state = S1;
    }
}

int main()
{
    unsigned char c;
    while (1)
    {
        scanf("%hhx", &c);
        (*curr_state)(c);
    }
}