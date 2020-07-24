// ������Ҫͷ�ļ�
#include "includeheaders.h"

void outputTeacher(const teacher *t) // �����ʦ��Ϣ
{
    printf("��ʦ����\n\n");
    printf("-----������Ϣ-----\n"); // ��Ϊ�ĸ����֣�������Ϣ���������ʺͲ������ۿ���Ϣ�ͺϼ�
    printf("��ʦ��ţ�%d\n��ʦ������%s\n", t->teacherID, t->name);
    if (t->gender == 0) // ͨ��intֵ�ж��Ա�
        printf("��ʦ�Ա�Ů\n");
    else
        printf("��ʦ�Ա���\n");
    printf("��λ���ƣ�%s\n��ͥסַ��%s\n��ϵ�绰��%s\n\n", t->officeAddr, t->homeAddr, t->phoneNumber);
    printf("-----���������벹��-----\n");
    printf("�������ʣ�%.5lf\n������%.5lf\n�������%.5lf\n\n", t->basicSalary, t->adds, t->addsLife);
    printf("-----�ۿ���Ϣ-----\n");
    printf("�绰�ѣ�%.5lf\nˮ��ѣ�%.5lf\n���⣺%.5lf\n����˰��%.5lf\n�����ѣ�%.5lf\n������%.5lf\n\n", t->telephoneFee,
           t->waterElectricityFee, t->houseFee, t->gainTax, t->healthFee, t->publicFee);
    printf("-----�ϼ�-----\n");
    printf("Ӧ�����ʣ�%.5lf\n�ϼƿۿ%.5lf\nʵ�����ʣ�%.5lf\n", t->salaryBeforeFee, t->totalFee, t->salaryAfterFee);
}

void inputTeacher(teacher *t) // �����ʦ��Ϣ����ͨ��ָ���޸Ĵ����tָ��Ľṹ�����
{
    printf("��ʦ��������ҳ\n\n");
    printf("-----������Ϣ-----\n");
    printf("��ʦ��ţ�");
    scanf("%d", &t->teacherID);
    printf("��ʦ������");
    scanf("%s", t->name);
    printf("��ʦ�Ա𣨡�0����Ů����1�����У���");
    scanf("%d", &t->gender);
    printf("��λ���ƣ�");
    scanf("%s", t->officeAddr);
    printf("��ͥסַ��");
    scanf("%s", t->homeAddr);
    printf("��ϵ�绰��");
    scanf("%s", t->phoneNumber);
    printf("\n\n-----���������벹��-----\n");
    printf("�������ʣ�");
    scanf("%lf", &t->basicSalary);
    printf("������");
    scanf("%lf", &t->adds);
    printf("�������");
    scanf("%lf", &t->addsLife);
    printf("\n\n-----�ۿ���Ϣ-----\n");
    printf("�绰�ѣ�");
    scanf("%lf", &t->telephoneFee);
    printf("ˮ��ѣ�");
    scanf("%lf", &t->waterElectricityFee);
    printf("���⣺");
    scanf("%lf", &t->houseFee);
    printf("����˰��");
    scanf("%lf", &t->gainTax);
    printf("�����ѣ�");
    scanf("%lf", &t->healthFee);
    printf("������");
    scanf("%lf", &t->publicFee);
    printf("-----�������-----\n\n");

    calcSalaryBeforeFee(t); // ������Ϻ��������㲢����
    calcTotalFee(t);
    calcSalaryAfterFee(t);
    printf("-----�ϼ�-----\n"); // ������ɺ�����ϼ�
    printf("Ӧ�����ʣ�%.5lf\n�ϼƿۿ%.5lf\nʵ�����ʣ�%.5lf\n\n\n", t->salaryBeforeFee, t->totalFee, t->salaryAfterFee);
}


void printvariables() // ����޸Ĳ���
{
    printf("��1��.��ʦ���\n");
    printf("��2��.��ʦ����\n");
    printf("��3��.��ʦ�Ա�\n");
    printf("��4��.��λ����\n");
    printf("��5��.��ͥסַ\n");
    printf("��6��.��ϵ�绰\n");
    printf("��7��.��������\n");
    printf("��8��.����\n");
    printf("��9��.�����\n");
    printf("��10��.�绰��\n");
    printf("��11��.ˮ���\n");
    printf("��12��.����\n");
    printf("��13��.����˰\n");
    printf("��14��.������\n");
    printf("��15��.������\n\n");
    printf("��0��.�˳��޸�\n");
}
