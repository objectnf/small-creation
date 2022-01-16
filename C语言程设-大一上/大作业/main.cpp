// ��ʼ��������ͷ�ļ�
#include "includeheaders.h"
#include "dboperation.h"
#include "softio.h"

// ��������
int distribute(int opt);
void showWelcome();
void show();
int searchMenu();
int addMenu();
int updateMenu();
int deleteMenu();

// ���ݿ�����ָ�붨��
sqlite3 *dbaccess = NULL;

void showWelcome() // ����ǰ����ʾ��ӭ��Ϣ
{
    printf("\n                         ��ӭʹ�ý�ʦ���ʹ���ϵͳ\n\n");  // ��ӭ�3�����ʧ��
    printf("         ��ϵͳ�� ObjNF ͬѧ������\n\n");
    printf("                                                    �����£�2018/01/04");
    Sleep(3000);
}

void show() // ���˵�����
{
    system("cls"); // ����
    printf("\n                         ��ʦ���ʹ���ϵͳ - ���˵�\n\n"); // ������˵�
    printf("  ����������Ҫ���еĲ���ǰ����ţ����س���\n\n\n\n");
    printf("  1. ����������ʦ��Ϣ\n\n");
    printf("  2. ���޸ġ���ʦ��Ϣ\n\n");
    printf("  3. ��ɾ������ʦ��Ϣ\n\n");
    printf("  4. ����ѯ����ʦ��Ϣ\n\n");
    printf("  0. ���˳���\n\n\n\n");

    printf("  ������������룺"); // ��ʾ�û������������
}

// ������ڵ�
int main()
{
    int opt = -1;
    checkFileStatement(); // �ȼ�������ļ�״̬
    dbaccess = connectDB(); // �������ݿ⣬���������ݿ�����ָ��
    showWelcome(); // ��ʾ��ӭ��Ϣ
    while (opt <= 4 && opt >= -1)
    {
        if(opt == -1)
        {
            show();
            scanf("%d", &opt);//��Ҫ��������˵���Ҫ������
        }
        opt = distribute(opt);//ѭ��
    }
    return 0;
}

int distribute(int opt) // ���ݲ������ض�����
{
    int ret = 0; // ��ʼ������Ϊ0
    switch(opt) // switch-case��֧�Խ��������ж�
    {
        case (0): // �û�ѡ���˳�
            printf("\n������5���Ӻ��˳���");
            Sleep(5000); // �ȴ�5��
            exit(0); // ǿ���˳�����
        case (1):
            ret = addMenu(); // ��ӽ�ʦ��Ϣ
            break;
        case (2):
            ret = updateMenu();//�޸�
            break;
        case (3):
            ret = deleteMenu();//ɾ��
            break;
        case (4):
            ret = searchMenu();//����
            break;
        default: // ���벻ͬ��������������Ĳ�����
            printf("\n�޷�ʶ��Ĳ��������Զ��������˵���");
            ret = -1;
            Sleep(2000);
            break;
    }
    return ret;//����ֵ����ѭ������һ������
}

int addMenu() {
    teacher tmp;
    int ret=0, choiceAfterAdd = 0;
    inputTeacher(&tmp);//�����ʦ��Ϣ
    addTeacherToDB(dbaccess, &tmp);//�ѽṹ�����뺯�����������ݿ�
    printf("\n��ѡ������һ��Ĳ�����\n��1��.����\n��2��.�޸�\n��3��.��ѯ\n��0��.�������˵�\n\n��������ѡ��");//Ҫ���������
    scanf("%d", &choiceAfterAdd);
    switch (choiceAfterAdd) {
        case (1):
            printf("\n��ʼ������ʦ��Ϣ");
            ret = 1;
            break;
        case (2):
            printf("\n��ʼ�޸Ľ�ʦ��Ϣ");
            ret = 2;
            break;
        case (3):
            printf("\n��ʼ��ѯ��һ����ʦ��Ϣ");
            ret = 4;
            break;
        case (0):
            printf("\n���ڷ������˵�");
            ret = -1;
            Sleep(3000);
            break;
        default:
            printf("\n�޷�ʶ��Ĳ��������Զ��������˵���");
            ret = -1;
            Sleep(2000);
            break;
    }
    return ret;//���ز���Ҫ��
}

int searchMenu() //���ҽ�ʦ��Ϣ
{
    int searchChoice = 0, ret = 0, teacherID = 0;
    char name[10] = "", userPhoneNumber[20] = "";
    system("cls");
    printf("\n��ѡ�������ʦ����Ϣ���ͣ�\n\n��1��.��ʦ���\n��2��.��ʦ����\n��3��.��ϵ�绰\n��4������\n\n\n��������ѡ��");//Ҫ���������
    scanf("%d", &searchChoice);
    switch (searchChoice)
    {
        case (1): //�����ʦ����Բ�ѯ
            printf("\n��ʦ��ţ�");
            scanf("%d", &teacherID);
            findTeacherinDB(dbaccess,(void*)&teacherID,1);
            break;
        case (2): //�����ʦ�����Բ�ѯ
            printf("\n��ʦ������");
            scanf("%s", name);
            findTeacherinDB(dbaccess,(void*)name,2);
            break;
        case (3): //�����ʦ��ϵ�绰�Բ�ѯ
            printf("\n��ϵ�绰��");
            scanf("%s", userPhoneNumber);
            findTeacherinDB(dbaccess,(void*)userPhoneNumber,3);
            break;
        case (4):
            printf("\n2��󷵻����˵���");
            Sleep(2000);
            ret = -1;
            break;
        default:
            printf("\n�޷�ʶ��Ĳ��������Զ��������˵���");
            ret = -1;
            Sleep(2000);
            break;
    }
    if(ret==0)//δ���з������˵�����
    {
        printf("\n��ѡ������һ��Ĳ�����\n\n��1��.�޸�\n��2��.ɾ��\n��3��.��ѯ��һ��\n��0��.�������˵�\n\n��������ѡ��");//Ҫ���������
        scanf("%d", &ret);
        switch (ret)
        {
            case (1):
                printf("\n��ʼ�޸Ľ�ʦ��Ϣ");
                ret = 2;
                break;
            case (2):
                printf("\n��ʼɾ����ʦ��Ϣ");
                ret = 3;
                break;
            case (3):
                printf("\n��ʼ��ѯ��һ����ʦ��Ϣ");
                ret = 4;
                break;
            case (0):
                printf("\n���ڷ������˵�");
                ret = -1;
                Sleep(3000);
                break;
            default:
                printf("\n�޷�ʶ��Ĳ��������Զ��������˵���");
                ret = -1;
                Sleep(2000);
                break;
        }
    }
    return ret;//���ز���Ҫ��
}

int updateMenu()
{
    int teacherID;
    int ret=0;
    int choiceAfterUpdate = 0;
    printf("\n�������ʦ��ţ�");//�����������
    scanf("%d", &teacherID);
    updateTeacherinDB(dbaccess, teacherID);//���²���
    printf("\n��ѡ������һ��Ĳ�����\n��1��.����\n��2��.��ѯ\n��3��.�޸�\n��0��.�������˵�\n\n��������ѡ��");//Ҫ���������
    scanf("%d", &choiceAfterUpdate);
    switch (choiceAfterUpdate)
    {
        case (1):
            printf("\n��ʼ������ʦ��Ϣ");
            ret = 1;
            break;
        case (2):
            printf("\n��ʼ��ѯ��ʦ��Ϣ");
            ret = 4;
            break;
        case (3):
            printf("\n��ʼ�޸Ľ�ʦ��Ϣ");
            ret = 2;
            break;
        case (0):
            printf("\n���ڷ������˵�");
            ret = -1;
            Sleep(2000);
            break;
        default:
            printf("\n�޷�ʶ��Ĳ��������Զ��������˵���");
            ret = -1;
            Sleep(2000);
            break;
    }
    return ret;//���ز���Ҫ��
}

int deleteMenu()
{
    int ret=0;
    int teacherID;
    int choiceAfterDelete = 0;
    printf("\n�������ʦ��ţ�");
    scanf("%d", &teacherID);//Ҫ������ɾ����ʦ����
    deleteTeacherinDB(dbaccess, teacherID);//ɾ������
    printf("\n��ѡ������һ��Ĳ�����\n��1��.����\n��2��.��ѯ\n��0��.�������˵�\n\n��������ѡ��");//Ҫ���������
    scanf("%d", &choiceAfterDelete);
    switch (choiceAfterDelete)
    {
        case (1):
            printf("\n��ʼ������ʦ��Ϣ");
            ret = 1;
            break;
        case (2):
            printf("\n��ʼ��ѯ��ʦ��Ϣ");
            ret = 4;
            break;
        case (0):
            printf("\n���ڷ������˵�");
            ret = -1;
            Sleep(3000);
            break;
        default:
            printf("\n�޷�ʶ��Ĳ��������Զ��������˵���");
            ret = -1;
            Sleep(2000);
            break;
    }
    return ret;//���ز���Ҫ��
}
