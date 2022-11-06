#include <iostream>

using namespace std;

// Y = (5^x + 48*x^4) / (32 - x)
void Task1() {
    long x = 3; // x += 2
    long results[6];
    long oldEcx = 5, power = 5, xForLoop = x - 1;
    const long FIVE = 5;

    _asm {
        mov ecx, 5

        start_loop:

        ; 32 - x
            mov eax, 32
            sub eax, x
            mov edi, eax

            ; 5 ^ x loop
            mov oldEcx, ecx
            mov ecx, x
            mov eax, 1
            power_loop:
        mul FIVE
            loop power_loop

            mov power, eax
            mov ecx, oldEcx

            ; 48 * x ^ 4
            mov eax, 48
            mul x
            mul x
            mul x
            mul x

            add eax, power

            div edi

            mov results[ecx * 4], eax; пересилання результату в пам'ять
            add EBX, 4; збільшення адреси результатів
            add x, 2; збільшення аргументу на 2

            loop start_loop
    }
    int iterator = 1;
    for (int i = 5; i >= 1; --i, ++iterator) {
        std::cout << "Result " << iterator << ": " << results[i] << std::endl;
    }
}

// Y = (450 * x) / (2^x + 31) ; x - ? => Y < 12
void Task2() {
    long x = 1, result = 0, two = 2;
    _asm {
    start_loop:
        ; 2 ^ x operation
            mov ecx, x
            mov eax, 1

            power_iteration:
        mul two
            loop power_iteration

            add eax, 31
            mov edi, eax; edi = 2 ^ x + 31

            mov eax, 450
            mul x

            div edi

            cmp eax, 12
            jl end_loop

            add x, 1
            jmp start_loop

            end_loop :
        mov result, eax
    }

    cout << "X: " << x << "; Result of operation: " << result << endl;
}

void Task3() {
    long index = 0;
    int arr_of_nums[12] = { -1 , -5 , -5, -1, -6 ,1, 34,4, 5, 67, 12, 242 };
    long length1 = 12;
    long negativeSum = 0;

    _asm
    {
        lea ebx, arr_of_nums  //заносимо в регістр ebx адресу масиву arr_of_nums
        mov ecx, length1    //заносимо в регістр esi кількість елементів масиву arr_of_nums

        next_num :        //<-----------------------------------------|
        mov eax, dword ptr[EBX]  //                      |                //
            cmp eax, 0      //                      |  
            jg end_1

            add negativeSum, eax
            inc index
            add ebx, 4        //збільшуємо EBX              |
            loop next_num    //якщо ecx > 0, то--------------------------|

            end_1 :

        mov eax, negativeSum
    }

    for (auto v : arr_of_nums)
        printf("%d ", v);

    printf("\nindex of odd: %d\n", index);
    printf("Negative sum: %d", negativeSum);
}

int main()
{
    cout << "First task: " << endl;
    Task1();

    cout << endl << "Second task: " << endl;
    Task2();

    cout << endl << "Third task: " << endl;
    Task3();
}