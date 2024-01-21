#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1
#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int M; //��������
int N; //��Դ����
int ALL_RESOURCES[MAX_RESOURCES]; //������Դ����Ŀ�ܺ�
int MAX[MAX_PROCESSES][MAX_RESOURCES]; //M�����̶�N����Դ�����Դ������
int AVAILABLE[MAX_RESOURCES]; //ϵͳ������Դ��
int ALLOCATION[MAX_PROCESSES][MAX_RESOURCES]; //M�������ѵõ�N����Դ����Դ��
int NEED[MAX_PROCESSES][MAX_RESOURCES]; //M�����̻���ҪN����Դ����Դ��
int Request[MAX_RESOURCES]; //������Դ����

int safeSequence[MAX_PROCESSES]; // ���ڴ洢��ȫִ�����е�����

// ���ϵͳ�Ƿ��ڰ�ȫ״̬�ĺ���
int checkSafety() {
    int work[MAX_RESOURCES];
    int finish[MAX_PROCESSES];
    int find, p;

    // ��ʼ�������������������
    for (int i = 0; i < N; i++)
        work[i] = AVAILABLE[i];  //������֮�������Դ

    for (int i = 0; i < M; i++)
        finish[i] = FALSE;

    // ��ѭ���Լ�鰲ȫ����
    int count = 0; // ����ɽ��̼���
    while (count < M) {
        find = FALSE;
        for (p = 0; p < M; p++) {  //ѭ������
            if (finish[p] == FALSE) {
                int j;
                for (j = 0; j < N; j++) //ѭ����Դ
                    if (NEED[p][j] > work[j])//ĳ�����̵�������Դ��Ȼ�������������Դ��������ѭ��������һ�������ж�
                        break;

                if (j == N) {  //������������Ҫ�ļ�����Դ�������㣬�ͷ�����ԴȻ������ж���һ������
                    for (int k = 0; k < N; k++)   //������Դ
                        work[k] += ALLOCATION[p][k];
                    finish[p] = TRUE;
                    safeSequence[count++] = p; // ������ p ���밲ȫ����
                    find = TRUE;
                }
            }
        }

        if (find == FALSE)
            break;
    }

    // ������н��̶���ɣ���ӡ��ȫ����
    if (count == M) {
        printf("��ȫ���У�");
        for (int i = 0; i < M; i++) {
            printf("%d", safeSequence[i]);
            if (i < M - 1)
                printf(" -> ");
        }
        printf("\n");
    }
    else {
        printf("ϵͳ���ڲ���ȫ״̬\n");
        return -1; // ���� -1 ��ʾ����ȫ״̬
    }

    return 0; // ���� 0 ��ʾ��ȫ״̬
}
//����Դ���������
void distributeResources(int processNumber) {
    for (int j = 0; j < N; j++) {
        AVAILABLE[j] -= Request[j];
        ALLOCATION[processNumber][j] += Request[j];
        NEED[processNumber][j] -= Request[j];
    }
}

//�ӽ����лָ���Դ
void restoreResources(int processNumber) {
    for (int j = 0; j < N; j++) {
        AVAILABLE[j] += Request[j];
        ALLOCATION[processNumber][j] -= Request[j];
        NEED[processNumber][j] += Request[j];
    }
}
