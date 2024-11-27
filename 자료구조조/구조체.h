#pragma once
#define BOOK_NAME 50
#define BOOK_AUTHOR 50
#define BOOK_PUBLISHER 50

typedef struct Book {
    char BookName[BOOK_NAME]; //책 제목
    char BookAuthor[BOOK_AUTHOR]; // 지은이
    char publisher[BOOK_PUBLISHER]; // 출판사
    int BookRent; // 대여가능 여부 (1 or 0) 1:가능 0:불가능
    int BookNum;
    struct Book* left;
    struct Book* right;
} Book;