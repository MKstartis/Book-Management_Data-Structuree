#pragma once
#define BOOK_NAME 50
#define BOOK_AUTHOR 50
#define BOOK_PUBLISHER 50

typedef struct Book {
    char BookName[BOOK_NAME]; //å ����
    char BookAuthor[BOOK_AUTHOR]; // ������
    char publisher[BOOK_PUBLISHER]; // ���ǻ�
    int BookRent; // �뿩���� ���� (1 or 0) 1:���� 0:�Ұ���
    int BookNum;
    struct Book* left;
    struct Book* right;
} Book;