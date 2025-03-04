#include <stdio.h>
#include <locale.h>

int main()
{
    setlocale(LC_ALL, "Russian");
    printf("Hello World! My name is Denis Trukhin. I am a student from BSTU \"VOENMEH\".\nMy study group is I914B.\nBye!");
    return 1;
}