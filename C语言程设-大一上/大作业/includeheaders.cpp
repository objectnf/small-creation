#include "includeheaders.h"

// ��������˲�����Ӧ�������ܶ�
void calcSalaryBeforeFee(teacher *tmp)
{
    tmp->salaryBeforeFee = tmp->basicSalary + tmp->adds + tmp->addsLife;
}

// �������������õĿ۳������ܶ�
void calcTotalFee(teacher *tmp)
{
    tmp->totalFee = tmp->gainTax + tmp->healthFee + tmp->houseFee + tmp->publicFee + tmp->telephoneFee + tmp->waterElectricityFee;
}

// ������ʵ�������ܶ�
void calcSalaryAfterFee(teacher *tmp)
{
    tmp->salaryAfterFee = tmp->salaryBeforeFee - tmp->totalFee;
}
