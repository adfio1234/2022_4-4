#include<stdio.h>
#include<windows.h>
using namespace std;
double Usingcpu();//�Լ�����
double arr[10000];//cpuload���� ������ �迭
int main()
{
    SYSTEMTIME lt;//��¥
    SYSTEM_INFO info;

    GetSystemInfo(&info);

    int index = 0;

    printf("Number of CPUs : %d\n", info.dwNumberOfProcessors);//����ü�� �����Ͽ� ���μ��� ���� ���

    for (int i = 0;; i++)
    {
        GetLocalTime(&lt);

        double result = Usingcpu();
        arr[i] = result;
        if (i >= 0)//0�ϋ��� �����������
        {
            printf("%3d %4d.%02d.%02d %02d:%02d:%02d : ", index++,
                lt.wYear, lt.wMonth, lt.wDay, lt.wHour, lt.wMinute, lt.wSecond);
        }
        if (i >= 1)//1�̻� �ϋ� ���
        {
            printf("[CPU Load: %.2lf%]", result);
        }
        if (i >= 5)//5���ʹ� ��յ����
        {
            double sum = 0;
            for (int j = i - 5; j < i; j++)//i�� �����Կ����� ������ �ε����� �Ǿ��� ���� �����ϰ� �ǵ��� ���ο� ���� �������
            {
                sum += arr[j];
            }
            printf(" [5sec avg: %.2lf%]", sum / 5);
        }
        if (i >= 10)//i�� �����Կ����� ������ �ε����� �Ǿ��� ���� �����ϰ� �ǵ��� ���ο� ���� �������
        {
            double sum = 0;
            for (int j = i - 10; j < i; j++)
            {
                sum += arr[j];
            }
            printf(" [10sec avg: %.2lf%]", sum / 10);
        }
        if (i >= 15)//i�� �����Կ����� ������ �ε����� �Ǿ��� ���� �����ϰ� �ǵ��� ���ο� ���� �������
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
double Usingcpu()//cpuloa�� ���ϴ� �Լ�
{
    FILETIME user, kernel, idle;

    GetSystemTimes(&idle, &kernel,&user );//�Ű������� Datetime�� �����ش�


    DWORD UserHigh1 = user.dwHighDateTime;
    DWORD UserLow1 = user.dwLowDateTime;
    DWORD KernelHigh1 = kernel.dwHighDateTime;
    DWORD KernelLow1 = kernel.dwLowDateTime;
    DWORD IdleHigh1 = idle.dwHighDateTime;
    DWORD IdleLow1 = idle.dwLowDateTime;

    Sleep(1000);//1�� ����

    GetSystemTimes(&idle, &kernel, &user);//1�ʰ� �����Ŀ� �ٽ� DateTIme�� �����ش�

    DWORD UserHigh2 = user.dwHighDateTime;
    DWORD UserLow2 = user.dwLowDateTime;
    DWORD KernelHigh2 = kernel.dwHighDateTime;
    DWORD KernelLow2 = kernel.dwLowDateTime;
    DWORD IdleHigh2 = idle.dwHighDateTime;
    DWORD IdleLow2 = idle.dwLowDateTime;


    double User_num = (UserHigh2 + UserLow2) - (UserHigh1 + UserLow1);//������ Ǯ��� �ᱹ t2-t1�����̹Ƿ� 1�ʵ����� ���Ҽ�����
    double Kernel_num = (KernelHigh2 + KernelLow2) - (KernelHigh1 + KernelLow1);//������ Ǯ��� �ᱹ t2-t1�����̹Ƿ� 1�ʵ����� ���Ҽ�����
    double Idle_num = (IdleHigh2 + IdleLow2) - (IdleHigh1 + IdleLow1);//������ Ǯ��� �ᱹ t2-t1�����̹Ƿ� 1�ʵ����� ���Ҽ�����


    return (User_num + Kernel_num - Idle_num) * 100 / (User_num + Kernel_num);//ppt�� ���¼��Ĵ�� ���� ���� �� �ð�/�ѽð� ������γ�Ÿ�������� 100����
}