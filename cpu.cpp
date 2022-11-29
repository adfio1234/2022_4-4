#include<stdio.h>
#include<windows.h>
using namespace std;
double Usingcpu();//함수만듦
double arr[10000];//cpuload값을 저장할 배열
int main()
{
    SYSTEMTIME lt;//날짜
    SYSTEM_INFO info;

    GetSystemInfo(&info);

    int index = 0;

    printf("Number of CPUs : %d\n", info.dwNumberOfProcessors);//구조체에 접근하여 프로세서 개수 출력

    for (int i = 0;; i++)
    {
        GetLocalTime(&lt);

        double result = Usingcpu();
        arr[i] = result;
        if (i >= 0)//0일떄는 출력하지않음
        {
            printf("%3d %4d.%02d.%02d %02d:%02d:%02d : ", index++,
                lt.wYear, lt.wMonth, lt.wDay, lt.wHour, lt.wMinute, lt.wSecond);
        }
        if (i >= 1)//1이상 일떄 출력
        {
            printf("[CPU Load: %.2lf%]", result);
        }
        if (i >= 5)//5부터는 평균도출력
        {
            double sum = 0;
            for (int j = i - 5; j < i; j++)//i이 증가함에따라 그전의 인덱스중 맨앞의 것을 제외하고 맨뒤의 새로운 수로 평균을냄
            {
                sum += arr[j];
            }
            printf(" [5sec avg: %.2lf%]", sum / 5);
        }
        if (i >= 10)//i이 증가함에따라 그전의 인덱스중 맨앞의 것을 제외하고 맨뒤의 새로운 수로 평균을냄
        {
            double sum = 0;
            for (int j = i - 10; j < i; j++)
            {
                sum += arr[j];
            }
            printf(" [10sec avg: %.2lf%]", sum / 10);
        }
        if (i >= 15)//i이 증가함에따라 그전의 인덱스중 맨앞의 것을 제외하고 맨뒤의 새로운 수로 평균을냄
        {
            double sum = 0;
            for (int j = i - 15; j < i; j++)
            {
                sum += arr[j];
            }
            printf(" [15sec avg: %.2lf%]", sum / 15);
        }




        printf("\n");


    }
}
double Usingcpu()//cpuloa를 구하는 함수
{
    FILETIME user, kernel, idle;

    GetSystemTimes(&idle, &kernel,&user );//매개변수의 Datetime을 구해준다


    DWORD UserHigh1 = user.dwHighDateTime;
    DWORD UserLow1 = user.dwLowDateTime;
    DWORD KernelHigh1 = kernel.dwHighDateTime;
    DWORD KernelLow1 = kernel.dwLowDateTime;
    DWORD IdleHigh1 = idle.dwHighDateTime;
    DWORD IdleLow1 = idle.dwLowDateTime;

    Sleep(1000);//1초 지남

    GetSystemTimes(&idle, &kernel, &user);//1초가 지난후에 다시 DateTIme을 구해준다

    DWORD UserHigh2 = user.dwHighDateTime;
    DWORD UserLow2 = user.dwLowDateTime;
    DWORD KernelHigh2 = kernel.dwHighDateTime;
    DWORD KernelLow2 = kernel.dwLowDateTime;
    DWORD IdleHigh2 = idle.dwHighDateTime;
    DWORD IdleLow2 = idle.dwLowDateTime;


    double User_num = (UserHigh2 + UserLow2) - (UserHigh1 + UserLow1);//수식을 풀어보면 결국 t2-t1형식이므로 1초동안을 구할수있음
    double Kernel_num = (KernelHigh2 + KernelLow2) - (KernelHigh1 + KernelLow1);//수식을 풀어보면 결국 t2-t1형식이므로 1초동안을 구할수있음
    double Idle_num = (IdleHigh2 + IdleLow2) - (IdleHigh1 + IdleLow1);//수식을 풀어보면 결국 t2-t1형식이므로 1초동안을 구할수있음


    return (User_num + Kernel_num - Idle_num) * 100 / (User_num + Kernel_num);//ppt에 나온수식대로 실제 일을 한 시간/총시간 백분율로나타내기위해 100곱함
}