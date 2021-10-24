// ��ֹ���ظ�������ͷ
#ifndef INCLUDEHEADERS_H
#define INCLUDEHEADERS_H

// ��Ҫ���û���ͷ�ļ�
#include <cstdio>       // C��׼�������
#include <cstdlib>      // C��׼�⺯��
#include <cstring>      // C�ַ�������
#include <string>

// ʹ��C��ʽ����ʣ��ͷ�ļ�
extern "C"
{
#include <io.h>         // C��չ�������
#include <windows.h>    // C����
#include "sqlite3.h"    // SQLite3�Ŀ�
}

// ʹ�ñ�׼�����ռ�
using namespace std;

// ���� teacher �ṹ��
typedef struct Teacher {
    int teacherID;
    char name[10];
    int gender;
    char officeAddr[100];
    char homeAddr[100];
    char phoneNumber[20]; // �绰����λ������int��ʾ��Χ�������ַ�����ʾ
    double basicSalary;
    double adds;
    double addsLife;
    double telephoneFee;
    double waterElectricityFee;
    double houseFee;
    double gainTax;
    double healthFee;
    double publicFee;
    double salaryBeforeFee;
    double totalFee;
    double salaryAfterFee;
} teacher;

// �ֱ��Ǽ���ʵ�����ʡ�Ӧ�����ʺͺϼƿۿ�ĺ�������
void calcSalaryAfterFee(teacher *tmp);

void calcSalaryBeforeFee(teacher *tmp);

void calcTotalFee(teacher *tmp);

#endif