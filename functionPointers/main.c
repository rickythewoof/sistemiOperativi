#include <stdio.h>

typedef void (*func_ptr)(char);

int num = 0;
typedef void (*State_ptr)(char);

void S1(char c);
void S2(char c);
void S3(char c);
void S4(char c);
void S5(char c);

State_ptr curr_state = S1;

void S1(char c){
    printf("Entering State1\n");
    if(c == 0xAA){
        curr_state = S2;
    }
    else{

        curr_state = S1;   
    }
}
void S2(char c){
    printf("Entering State2\n");
    if(c == 0x55){
        curr_state = S3;
    } else {
        curr_state = S2;
    }
}
void S3(char c){
    printf("Entering State3\n");
    num = c;
    curr_state = S4;
}
void S4(char c){
    printf("Entering State4\n");
    if(num == 0){
        curr_state = S5;
    }
}
void S5(char c){
    printf("Entering State5\n");
    if(c == 0xAA){
        curr_state = S2;
    } else {
        curr_state = S1;
    }

}

int main(){
    while(1){
        (*curr_state)(getchar());
    }
}