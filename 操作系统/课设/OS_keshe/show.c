#include "core.h"

//����ǰ״̬�����ļ�
void saveToFile() {
    FILE* outputFile;
    if (fopen_s(&outputFile, "D:\\Progress\\VS2019\\OS_keshe\\system_state.txt", "w") != 0) {
        printf("�޷���ϵͳ״̬д���ļ���\n");
        return;
    }

    //��ϵͳ״̬д���ļ�
    fprintf(outputFile, "%d %d\n", M, N);
    for (int i = 0; i < N; i++)
        fprintf(outputFile, "%d ", ALL_RESOURCES[i]);
    fprintf(outputFile, "\n");

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++)
            fprintf(outputFile, "%d ", MAX[i][j]);
        fprintf(outputFile, "\n");
    }

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++)
            fprintf(outputFile, "%d ", ALLOCATION[i][j]);
        fprintf(outputFile, "\n");
    }

    for (int j = 0; j < N; j++)
        fprintf(outputFile, "%d ", AVAILABLE[j]);
    fprintf(outputFile, "\n");

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++)
            fprintf(outputFile, "%d ", NEED[i][j]);
        fprintf(outputFile, "\n");
    }

    fclose(outputFile);
    printf("ϵͳ״̬��д��'system_state.txt'\n");
}

//���ļ���ϵͳ״̬�������ڴ�
void loadFromFile() {
    FILE* inputFile;
    if (fopen_s(&inputFile, "D:\\Progress\\VS2019\\OS_keshe\\system_state.txt", "r") != 0) {
        printf("�޷����ļ���ȡϵͳ״̬\n");
        return;
    }

    //���д��ļ���ȡϵͳ״̬
    fscanf_s(inputFile, "%d %d", &M, &N);
    for (int i = 0; i < N; i++)
        fscanf_s(inputFile, "%d", &ALL_RESOURCES[i]);

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++)
            fscanf_s(inputFile, "%d", &MAX[i][j]);
    }

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++)
            fscanf_s(inputFile, "%d", &ALLOCATION[i][j]);
    }

    for (int j = 0; j < N; j++)
        fscanf_s(inputFile, "%d", &AVAILABLE[j]);

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++)
            fscanf_s(inputFile, "%d", &NEED[i][j]);
    }

    fclose(inputFile);
    printf("ϵͳ״̬�Ѵ�'system_state.txt'�������ڴ�\n");
}

//�������Խ��̵���Դ����
void requestResources(int processNumber) {
    printf("����������Դ�Ľ��̺� %d:\n", processNumber);
    for (int i = 0; i < N; i++) {
        printf("��Դ %d�� ", i);
        scanf_s("%d", &Request[i]);
        while (Request[i] > ALL_RESOURCES[i]) {
            printf("���������룺");
            scanf_s("%d", &Request[i]);
        }
            
    }

    //��core������ú�����������
    distributeResources(processNumber);
    if (checkSafety() == -1) {
        printf("�޷�������Դ����Ϊ���ᵼ�²���ȫ״̬��\n");
        restoreResources(processNumber);
    }
    else {
        printf("�����ѱ���׼\n");
    }
}

void displaySystemState() {
    printf("\n������������������������������������\n");
    printf("������Դ��\n");
    for (int j = 0; j < N; j++)
        printf(" ��Դ%d�� %d", j, ALL_RESOURCES[j]);
    printf("\n\n");

    printf("������������������������������������\n");
    printf("������Դ��\n");
    for (int j = 0; j < N; j++)
        printf(" ��Դ%d: %d", j, AVAILABLE[j]);
    printf("\n\n");

    printf("������������������������������������\n");
    printf("��������̵���Դ: \n\n");
    for (int j = 0; j < N; j++)
        printf("       ��Դ%d", j);
    printf("\n");

    for (int i = 0; i < M; i++) {
        printf("����%d��   ", i);
        for (int j = 0; j < N; j++)
            printf("%d           ", ALLOCATION[i][j]);
        printf("\n");
    }
    printf("\n");

    printf("������������������������������������\n");
    printf("������Դ:\n\n");
    for (int j = 0; j < N; j++)
        printf("       ��Դ%d", j);
    printf("\n");

    for (int i = 0; i < M; i++) {
        printf("����%d��   ", i);
        for (int j = 0; j < N; j++)
            printf("%d           ", NEED[i][j]);
        printf("\n");
    }
    printf("\n");
}



int main() {
    // ��ʼ��ϵͳ״̬
    printf("���س�ʼ����Դ��...\n");
    loadFromFile();

    // ��ʾ��ʼϵͳ״̬
    displaySystemState();

    char choice;
    do {
        // �����û��Ƿ�Ҫ������Դ
        printf("\n�Ƿ�Ҫ������Դ? (Y/N): ");
        scanf_s(" %c", &choice);

        if (choice == 'Y' || choice == 'y') {
            int processNumber;
            printf("����������Դ�Ľ��̺�: ");
            scanf_s("%d", &processNumber);

            // ������Դ����
            requestResources(processNumber);

            // ��ʾϵͳ״̬����
            displaySystemState();
        }

        // ѯ���û��Ƿ�Ҫ���浱ǰϵͳ״̬
        printf("\n�Ƿ�Ҫ���浱ǰϵͳ״̬? (Y/N): ");
        scanf_s(" %c", &choice);
        if (choice == 'Y' || choice == 'y') {
            saveToFile();
        }

        // ѯ���û��Ƿ�Ҫ����
        printf("\n�Ƿ����? (Y/N): ");
        scanf_s(" %c", &choice);
    } while (choice == 'Y' || choice == 'y');

    return 0;
}
