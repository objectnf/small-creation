// ��ֹ���ظ�������ͷ
#ifndef DBOPERATION_H
#define DBOPERATION_H

// ������Ҫ��ͷ�ļ�
#include "includeheaders.h"

void checkFileStatement(); // ������ݿ��Ƿ���Ա�����

sqlite3 *connectDB(); // �������ݿ⣬���ж��Ƿ���ڶ�Ӧ�����ݱ�

int isTableExistCallback(void *, int nCount, char **cValue, char **cName); // �ж����ݱ����ʱ�Ļص�����

void addTeacherToDB(sqlite3 *teacherdb, const teacher *t); // ����������Ľ�ʦ����д�����ݿ�

void findTeacherinDB(sqlite3 *teacherdb,void *data,int choice); // ���ҽ�ʦ��Ϣ

int findTeacherCallback(void *ret, int nCount, char **cValue, char **cName); // ���ҵ���ʦ��Ϣʱ�Ļص�����

void updateTeacherinDB(sqlite3 *teacherdb, int id); // ���½�ʦ��Ϣ����

void deleteTeacherinDB(sqlite3 *teacherdb, int id); // ɾ����ʦ��Ϣ����

#endif