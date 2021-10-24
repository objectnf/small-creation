// ������Ҫ��ͷ�ļ�
#include "includeheaders.h"
#include "softio.h"

// ������������
void checkFileStatement();
sqlite3 *connectDB();
int isTableExistCallback(void *, int nCount, char **cValue, char **cName);
void addTeacherToDB(sqlite3 *teacherdb, const teacher *t);
void findTeacherinDB(sqlite3 *teacherdb,void *data,int choice);
int findTeacherCallback(void *ret, int nCount, char **cValue, char **cName);

void checkFileStatement() // ���ڼ�����ݿ��ļ�״̬
{
    if (!access("data.db", 0)) // �Ƿ����
    {
        if (access("data.db", 6)) // �Ƿ�ɶ�д,���ɶ�дֱ���˳���
        {
            printf("���ݿ��ļ��޷���д�������Ƿ��г���ռ�������ļ�������ռ�ý��������������\n"); // ����޷���д��Ϣ
            system("pause"); // ��ͣ
            exit(0); // ǿ���˳�
        }
    }
    else // ��������ʼ�½�
    {
        printf("���ݿ��ļ���ʧ��3����½���\n");
        Sleep(3000); // �ȴ�����
        sqlite3 *teacherdb; // �������ݿ����ָ��
        sqlite3_open("data.db", &teacherdb); // �����ݿ��ļ��������ڵĻ��ͻ��Զ��½�
        sqlite3_close(teacherdb); // �ر����ݿ��ļ����½����
    }
}

sqlite3* connectDB() // �����������ݿ�
{
    sqlite3 *teacherdb; // �������ݿ����ָ��
    sqlite3_open("data.db", &teacherdb); // �����ݿ��ļ�
    string sql = "SELECT COUNT(*) FROM sqlite_master WHERE TYPE='table' AND NAME='teacherdata';";
    char *err; // ����sql���ʹ�����Ϣ����
    int isTableExist = 0; // ����������Ƿ���ڱ�
    int retc = sqlite3_exec(teacherdb, sql.data(), isTableExistCallback, &isTableExist, &err); // ��ѯ���ݿ�
    if (retc != SQLITE_OK) // �����ѯ���ִ��ʧ��
    {
        printf("�������ݿ�ʧ�ܡ������룺%d��������Ϣ��%s\n", retc, err); // �׳�����
        exit(0); //ǿ���˳�
    }
    if (isTableExist == 0) // ������������ݱ�
    {
        printf("δ�ҵ����ݱ��½���...\n"); // �����û�
        // ʹ��sql����ڵ�ǰ�ļ����½�
        string sqlct = "CREATE TABLE teacherdata(" \
                    "teacherID      INT PRIMARY KEY NOT NULL," \
                    "name           TEXT            NOT NULL," \
                    "gender         INT             NOT NULL," \
                    "officeAddr     TEXT            NOT NULL," \
                    "homeAddr       TEXT            NOT NULL," \
                    "phoneNumber    TEXT            NOT NULL," \
                    "basicSalary    REAL            NOT NULL," \
                    "adds           REAL            NOT NULL," \
                    "addsLife       REAL            NOT NULL," \
                    "telephoneFee   REAL            NOT NULL," \
                    "waterElectricityFee REAL       NOT NULL," \
                    "houseFee       REAL            NOT NULL," \
                    "gainTax        REAL            NOT NULL," \
                    "healthFee      REAL            NOT NULL," \
                    "publicFee      REAL            NOT NULL," \
                    "salaryBeforeFee REAL           NOT NULL," \
                    "totalFee       REAL            NOT NULL," \
                    "salaryAfterFee REAL            NOT NULL);";
        int retc2 = sqlite3_exec(teacherdb, sqlct.data(), NULL, NULL, &err); // �������ݱ������
        if (retc2 != SQLITE_OK) // ���sql���ִ��ʧ��
        {
            printf("������ʧ�ܡ������룺%d��������Ϣ��%s\n", retc2, err); // ��ʾ�û�
            exit(0); // ���ݱ����ڣ��޷�ִ�к���������ǿ���˳�
        }
    }
    return teacherdb; // ����sql����ָ�룬�ں���������ʹ��
}

int isTableExistCallback(void *ret, int nCount, char **cValue, char **cName) // �ж����ݱ��Ƿ����ʱ�Ļص�����
{
    int *retint = (int *) ret; // ָ��ǿ������ת��
    if (atoi(cValue[0]) == 0) // ��ȡsql���ķ���ֵ��ִ�в���
        *retint = 0;
    else
        *retint = 1;
    return SQLITE_OK; // �ص�ִ�гɹ�������0
}

void addTeacherToDB(sqlite3 *teacherdb, const teacher *t) // ����ʦ����д�����ݿ�
{
    char sql[500] = "", *err; // ����sql���ʹ���ָ��
    sprintf(sql,
            "INSERT INTO teacherdata VALUES (%d,'%s',%d,'%s','%s','%s',%.5lf,%.5lf,%.5lf,%.5lf,%.5lf,%.5lf,%.5lf,%.5lf,%.5lf,%.5lf,%.5lf,%.5lf);",
            t->teacherID, t->name, t->gender, t->officeAddr, t->homeAddr, t->phoneNumber, t->basicSalary, t->adds,
            t->addsLife, t->telephoneFee, t->waterElectricityFee, t->houseFee, t->gainTax, t->healthFee, t->publicFee,
            t->salaryBeforeFee, t->totalFee, t->salaryAfterFee); // �˴�����sql��䲢printf���ַ�����
    int retc = sqlite3_exec(teacherdb, sql, NULL, NULL, &err); // ִ��sql���
    if (retc != SQLITE_OK) // ��sqlִ��ʧ��
        printf("��ӽ�ʦ����ʧ�ܡ������룺%d��������Ϣ��%s\n", retc, err); // �����û�
    else // ����
        printf("��ӽ�ʦ���ݳɹ���\n"); // ��֪�û��ɹ�
}

int check;

void findTeacherinDB(sqlite3 *teacherdb,void *data,int choice)
{
    char sql[300] = "",*err;
    teacher t;
    check = 0;
    const char col[][15]={"teacherID","name","phoneNumber"};
    if(choice == 1)//��ѡ��ID��ѯ��ʦ��Ϣ
        sprintf(sql, "SELECT * FROM teacherdata WHERE %s=%d", col[choice-1],*(int*)data);
    else
    {
        const char *str=(const char*)data;//��ѡ����ϵ�绰��������ѯ��ʦ��Ϣ
        sprintf(sql, "SELECT * FROM teacherdata WHERE %s=\'%s\'", col[choice-1],str);//��������������
    }
    int retc = sqlite3_exec(teacherdb, sql, findTeacherCallback, &t, &err);//������callback����������check==1����Ϣ��ṹ��t������
    if (retc != SQLITE_OK)
        printf("��ѯ��ʦ����ʧ�ܡ������룺%d��������Ϣ��%s\n", retc, err);
    else
    {
        if(check==1)//callback�ı�check��ֵ
            outputTeacher(&t);
        else
            printf("δ��ѯ��������¼��");//��ѯ���ݲ�����
    }
}

int findTeacherCallback(void *ret, int nCount, char **cValue, char **cName) // ��ѯ��ʦʱ�Ļص�����
{

    teacher *retdata = (teacher *) ret; // ָ������ת��
    // �ṹ�帳ֵ
    retdata->teacherID = atoi(cValue[0]);
    strcpy(retdata->name, cValue[1]);
    retdata->gender = atoi(cValue[2]);
    strcpy(retdata->officeAddr, cValue[3]);
    strcpy(retdata->homeAddr, cValue[4]);
    strcpy(retdata->phoneNumber, cValue[5]);
    retdata->basicSalary = atof(cValue[6]);
    retdata->adds = atof(cValue[7]);
    retdata->addsLife = atof(cValue[8]);
    retdata->telephoneFee = atof(cValue[9]);
    retdata->waterElectricityFee = atof(cValue[10]);
    retdata->houseFee = atof(cValue[11]);
    retdata->gainTax = atof(cValue[12]);
    retdata->healthFee = atof(cValue[13]);
    retdata->publicFee = atof(cValue[14]);
    retdata->salaryBeforeFee = atof(cValue[15]);
    retdata->totalFee = atof(cValue[16]);
    retdata->salaryAfterFee = atof(cValue[17]);
    // check����Ϊ1��֤���Ѿ�����callback
    check=1;
    // ��������
    return SQLITE_OK;
}

void updateTeacherinDB(sqlite3 *teacherdb, int id)
{
    char sql[300] = "", *err , nameAndAddr[300];
    int choice = -1, gen = 0, newID = id;
    double fee;
    teacher t;
    check=0;
    sprintf(sql, "SELECT * FROM teacherdata WHERE teacherID=%d", id); // ����select���
    int retc = sqlite3_exec(teacherdb, sql, findTeacherCallback, &t, &err);//����callback�������ؽṹ��t������
    if (retc != SQLITE_OK)
        printf("��ѯ��ʦ����ʧ�ܡ������룺%d��������Ϣ��%s\n", retc, err);
    else
    {
        if(check==0){
            printf("\n�޸���Ŀ������\n\n");
            return;
        }
        outputTeacher(&t);//���������Ϣ
        while (true)
        {
            printvariables();//ÿ������޸��б���Ϣ
            printf("\n��ѡ����Ҫ�޸ĵ���Ŀ��");
            scanf("%d", &choice);
            switch (choice)
            {
                default:
                    printf("\n����������Ч��2����Զ������ϼ��˵���\n");
                    Sleep(2000);
                    break;//�ص��޸��б�
                case (0):
                    printf("2����˳���\n");
                    Sleep(2000);
                    choice = 0;//��choice��ֵ
                    break;
                case (1):
                    printf("�������µ����ݣ�");
                    scanf("%d", &newID);
                    t.teacherID=newID;//�ڽṹ���и���id
                    sprintf(sql, "UPDATE teacherdata SET teacherID=%d WHERE teacherID=%d", newID, id);
                    retc = sqlite3_exec(teacherdb, sql, NULL, NULL, &err);//�޸�id
                    if (retc != SQLITE_OK) {
                        printf("�޸Ľ�ʦ����ʧ�ܡ������룺%d��������Ϣ��%s\n", retc, err);
                    }
                    break;
                case (2):
                    printf("�������µ����ݣ�");
                    scanf("%s", nameAndAddr);
                    sprintf(sql, "UPDATE teacherdata SET name=\'%s\' WHERE teacherID=%d", nameAndAddr, id);
                    retc = sqlite3_exec(teacherdb, sql, NULL, NULL, &err);//�޸�����
                    if (retc != SQLITE_OK) {
                        printf("�޸Ľ�ʦ����ʧ�ܡ������룺%d��������Ϣ��%s\n", retc, err);
                    }
                    break;
                case (3):
                    printf("�������µ����ݣ�����0����Ů����1�����У�");
                    scanf("%d", &gen);
                    sprintf(sql, "UPDATE teacherdata SET gender=%d WHERE teacherID=%d", gen, id);
                    retc = sqlite3_exec(teacherdb, sql, NULL, NULL, &err);//�޸��Ա�
                    if (retc != SQLITE_OK) {
                        printf("�޸Ľ�ʦ����ʧ�ܡ������룺%d��������Ϣ��%s\n", retc, err);
                    }
                    break;
                case (4):
                    printf("�������µ����ݣ�");
                    scanf("%s", nameAndAddr);
                    sprintf(sql, "UPDATE teacherdata SET officeAddr=\'%s\' WHERE teacherID=%d", nameAndAddr, id);
                    retc = sqlite3_exec(teacherdb, sql, NULL, NULL, &err);//�޸ĵ�ַ
                    if (retc != SQLITE_OK) {
                        printf("�޸Ľ�ʦ����ʧ�ܡ������룺%d��������Ϣ��%s\n", retc, err);
                    }
                    break;
                case (5):
                    printf("�������µ����ݣ�");
                    scanf("%s", nameAndAddr);
                    sprintf(sql, "UPDATE teacherdata SET homeAddr=\'%s\' WHERE teacherID=%d", nameAndAddr, id);
                    retc = sqlite3_exec(teacherdb, sql, NULL, NULL, &err);//�޸ļ�ͥסַ
                    if (retc != SQLITE_OK) {
                        printf("�޸Ľ�ʦ����ʧ�ܡ������룺%d��������Ϣ��%s\n", retc, err);
                    }
                    break;
                case (6):
                    printf("�������µ����ݣ�");
                    scanf("%s", nameAndAddr);
                    sprintf(sql, "UPDATE teacherdata SET phoneNumber=\'%s\' WHERE teacherID=%d", nameAndAddr, id);
                    retc = sqlite3_exec(teacherdb, sql, NULL, NULL, &err);//�޸ĵ绰
                    if (retc != SQLITE_OK) {
                        printf("�޸Ľ�ʦ����ʧ�ܡ������룺%d��������Ϣ��%s\n", retc, err);
                    }
                    break;
                case (7):
                    printf("�������µ����ݣ�");
                    scanf("%lf", &fee);
                    t.basicSalary=fee;//�ṹ���¼�÷���
                    sprintf(sql, "UPDATE teacherdata SET basicSalary=%lf WHERE teacherID=%d", fee, id);
                    retc = sqlite3_exec(teacherdb, sql, NULL, NULL, &err);//�޸ĸ÷���
                    if (retc != SQLITE_OK) {
                        printf("�޸Ľ�ʦ����ʧ�ܡ������룺%d��������Ϣ��%s\n", retc, err);
                    }
                    break;
                case (8):
                    printf("�����룺");
                    scanf("%lf", &fee);
                    t.adds=fee;//�ṹ���¼�÷���
                    sprintf(sql, "UPDATE teacherdata SET adds=%lf WHERE teacherID=%d", fee, id);
                    retc = sqlite3_exec(teacherdb, sql, NULL, NULL, &err);//�޸ĸ÷���
                    if (retc != SQLITE_OK) {
                        printf("�޸Ľ�ʦ����ʧ�ܡ������룺%d��������Ϣ��%s\n", retc, err);
                    }
                    break;
                case (9):
                    printf("�����룺");
                    scanf("%lf", &fee);
                    t.addsLife=fee;//�ṹ���¼�÷���
                    sprintf(sql, "UPDATE teacherdata SET addsLife=%lf WHERE teacherID=%d", fee, id);
                    retc = sqlite3_exec(teacherdb, sql, NULL, NULL, &err);//�޸ĸ÷���
                    if (retc != SQLITE_OK) {
                        printf("�޸Ľ�ʦ����ʧ�ܡ������룺%d��������Ϣ��%s\n", retc, err);
                    }
                    break;
                case (10):
                    printf("�����룺");
                    scanf("%lf", &fee);
                    t.telephoneFee=fee;//�ṹ���¼�÷���
                    sprintf(sql, "UPDATE teacherdata SET telephoneFee=%lf WHERE teacherID=%d", fee, id);
                    retc = sqlite3_exec(teacherdb, sql, NULL, NULL, &err);//�޸ĸ÷���
                    if (retc != SQLITE_OK) {
                        printf("�޸Ľ�ʦ����ʧ�ܡ������룺%d��������Ϣ��%s\n", retc, err);
                    }
                    break;
                case (11):
                    printf("�����룺");
                    scanf("%lf", &fee);
                    t.waterElectricityFee=fee;//�ṹ���¼�÷���
                    sprintf(sql, "UPDATE teacherdata SET waterElectricityFee=%lf WHERE teacherID=%d", fee, id);
                    retc = sqlite3_exec(teacherdb, sql, NULL, NULL, &err);//�޸ĸ÷���
                    if (retc != SQLITE_OK) {
                        printf("�޸Ľ�ʦ����ʧ�ܡ������룺%d��������Ϣ��%s\n", retc, err);
                    }
                    break;
                case (12):
                    printf("�����룺");
                    scanf("%lf", &fee);
                    t.houseFee=fee;//�ṹ���¼�÷���
                    sprintf(sql, "UPDATE teacherdata SET houseFee=%lf WHERE teacherID=%d", fee, id);
                    retc = sqlite3_exec(teacherdb, sql, NULL, NULL, &err);//�޸ĸ÷���
                    if (retc != SQLITE_OK) {
                        printf("�޸Ľ�ʦ����ʧ�ܡ������룺%d��������Ϣ��%s\n", retc, err);
                    }
                    break;
                case (13):
                    printf("�����룺");
                    scanf("%lf", &fee);
                    t.gainTax=fee;//�ṹ���¼�÷���
                    sprintf(sql, "UPDATE teacherdata SET gainTax=%lf WHERE teacherID=%d", fee, id);
                    retc = sqlite3_exec(teacherdb, sql, NULL, NULL, &err);//�޸ĸ÷���
                    if (retc != SQLITE_OK) {
                        printf("�޸Ľ�ʦ����ʧ�ܡ������룺%d��������Ϣ��%s\n", retc, err);
                    }
                    break;
                case (14):
                    printf("�����룺");
                    scanf("%lf", &fee);
                    t.healthFee=fee;//�ṹ���¼�÷���
                    sprintf(sql, "UPDATE teacherdata SET healthFee=%lf WHERE teacherID=%d", fee, id);
                    retc = sqlite3_exec(teacherdb, sql, NULL, NULL, &err);//�޸ĸ÷���
                    if (retc != SQLITE_OK) {
                        printf("�޸Ľ�ʦ����ʧ�ܡ������룺%d��������Ϣ��%s\n", retc, err);
                    }
                    break;
                case (15):
                    printf("�����룺");
                    scanf("%lf", &fee);
                    t.publicFee=fee;//�ṹ���¼�÷���
                    sprintf(sql, "UPDATE teacherdata SET publicFee=%lf WHERE teacherID=%d", fee, id);
                    retc = sqlite3_exec(teacherdb, sql, NULL, NULL, &err);//�޸ĸ÷���
                    if (retc != SQLITE_OK) {
                        printf("�޸Ľ�ʦ����ʧ�ܡ������룺%d��������Ϣ��%s\n", retc, err);
                    }
                    break;
            }
            if (choice == 0)//�����޸�
                break;
            if (choice == 1)//������id��������id�����޸�
                id=newID;
        }
        calcSalaryBeforeFee(&t);
        calcTotalFee(&t);
        calcSalaryAfterFee(&t);//�ڽṹ���иı�����߷��ü���
        sprintf(sql, "UPDATE teacherdata SET salaryBeforeFee = %lf WHERE teacherID = %d", t.salaryBeforeFee, id);
        retc = sqlite3_exec(teacherdb, sql, NULL, NULL, &err);//�޸ĸ÷���
        if (retc != SQLITE_OK) {
            printf("�޸Ľ�ʦ����ʧ�ܡ������룺%d��������Ϣ��%s\n", retc, err);
        }
        sprintf(sql, "UPDATE teacherdata SET totalFee = %lf WHERE teacherID = %d", t.totalFee, id);
        retc = sqlite3_exec(teacherdb, sql, NULL, NULL, &err);//�޸ĸ÷���
        if (retc != SQLITE_OK) {
            printf("�޸Ľ�ʦ����ʧ�ܡ������룺%d��������Ϣ��%s\n", retc, err);
        }
        sprintf(sql, "UPDATE teacherdata SET salaryAfterFee = %lf WHERE teacherID = %d", t.salaryAfterFee, id);
        retc = sqlite3_exec(teacherdb, sql, NULL, NULL, &err);//�޸ĸ÷���
        if (retc != SQLITE_OK) {
            printf("�޸Ľ�ʦ����ʧ�ܡ������룺%d��������Ϣ��%s\n", retc, err);
        }
    }
    sprintf(sql, "SELECT * FROM teacherdata WHERE teacherID=%d", id); // ����select���
    retc = sqlite3_exec(teacherdb, sql, findTeacherCallback, &t, &err);
    if (retc != SQLITE_OK) {
        printf("��ѯ��ʦ����ʧ�ܡ������룺%d��������Ϣ��%s\n", retc, err);
    }
    else
        outputTeacher(&t);//�����޸ĺ����Ϣ
}


void deleteTeacherinDB(sqlite3 *teacherdb, int id) {
    char sql[300] = "", *err;
    sprintf(sql, "DELETE FROM teacherdata WHERE teacherID=%d", id);
    int retc = sqlite3_exec(teacherdb, sql, NULL, NULL, &err);//ɾ��������Ϣ
    if (retc != SQLITE_OK) {
        printf("ɾ����ʦ����ʧ�ܡ������룺%d��������Ϣ��%s\n", retc, err);
        printf("����ȷ�Ͻ�ʦ��Ϣ�Ƿ���ڡ�\n");
    } else
        printf("ɾ����ʦ���ݳɹ���\n");
}
