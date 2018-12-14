#include <stdio.h>
#include <stdlib.h>

#define MOVE 0
#define ADD  1
#define SUB  2
#define BRA  3
#define CMP  4
#define BEQ  5
#define BNE  6
#define EXG  7
#define STOP 15

int main()
{
    unsigned short int PC = 0;
    unsigned short int D0 = 0;
    unsigned short int A0 = 0;
    unsigned short int CCR = 0;
    unsigned short int MAR;
    unsigned short int MBR;
    unsigned short int IR;
    unsigned short int operand;
    unsigned short int source;
    unsigned short int destination;
    unsigned short int opcode;
    unsigned short int amode;
    unsigned short int direction;
    unsigned short int memory[256];
    unsigned short int run = 1;

    while (run) {
    /* Take input instruction
     and put it in memory
     at PC Place
    */
        unsigned short int instruction;
        char binaryInstruction[9];
        printf("Enter Instruction : \n");
        scanf("%s", &binaryInstruction);
        instruction = strtol(binaryInstruction, NULL, 2);
        memory[PC] = instruction;

        int userOperand;
        printf("Enter Operand : \n");
        scanf("%d", &userOperand);
        memory[PC + 1] = userOperand;
    /*End of reading Instruction
    from user
    */
        MAR = PC;
        PC = PC + 1;
        MBR = memory[MAR];
        IR = MBR;
        opcode = IR;

        MAR = PC;
        PC = PC + 1;
        MBR = memory[MAR];
        IR = MBR;
        operand = IR;

        amode = opcode & 0x03;
        direction = (opcode & 0x04) >> 2;
        opcode = opcode >> 4;

        switch (amode) {
            case 0:
                source = memory[operand];
                break;
            case 1:
                source = operand;
                break;
            case 2:
                source = memory[A0 + operand];
                break;
            case 3:
                source = memory[PC + operand];
                break;
        }

        switch (opcode) {
            case MOVE: {
                if (direction == 0) destination = D0;
                else D0 = source;
                if (D0 == 0) CCR =1; else CCR = 0;
                break;
            }
            case ADD: {
                if (direction == 0) {
                    destination = D0 + source;
                    if (destination == 0) CCR =1; else CCR = 0;
                } else {
                    D0 = D0 + source;
                    if (D0 == 0) CCR =1; else CCR = 0;
                }
                break;
            }
            case SUB: {
                if (direction == 0) {
                    destination = D0 - source;
                    if (destination == 0) CCR =1; else CCR = 0;
                } else {
                    D0 = D0 - source;
                    if (D0 == 0) CCR =1; else CCR = 0;
                }
                break;
            }
            case BRA: {
                if (amode == 0) PC = operand;
                if (amode == 1) PC = PC + operand;
                break;
            }
            case CMP: {
                MBR = D0 - source;
                if (MBR == 0) CCR =1; else CCR = 0;
                break;
            }
            case BEQ: {
                if (CCR == 1) {
                    if (amode == 0) PC = operand;
                    if (amode == 1) PC = PC + operand;
                }
                break;
            }
            case BNE: {
                if (CCR != 1) {
                    if (amode == 0) PC = operand;
                    if (amode == 1) PC = PC + operand;
                }
                break;
            }
            case EXG: {
                MBR = D0; D0 = A0; A0 = MBR;
                break;
            }
            case STOP: {
                run = 0;
                break;
            }
        }

        if (direction == 0) {
            switch (amode) {
                case 0:
                    memory[operand] = destination;
                    break;
                case 1:
                    break;
                case 2:
                    memory[A0 + operand] = destination;
                    break;
                case 3:
                    memory[PC + operand] = destination;
                    break;
            }

        }
    /*printing values of
    all registers
    */
    printf("PC : %d\n", PC);
    printf("MAR : %d\n", MAR);
    printf("MBR : %d\n", MBR);
    printf("IR : %d\n", IR);
    printf("CCR : %d\n", CCR);
    printf("A0 : %d\n", A0);
    printf("D0 : %d\n", D0);
    run = 0;

    }
    return 0;
}
