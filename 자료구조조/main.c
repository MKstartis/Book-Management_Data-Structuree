#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include "구조체.h"
#define BOOK_NAME 50
#define BOOK_AUTHOR 50
#define BOOK_PUBLISHER 50

int count = 1; //전체 조회에서 책의 번호를 나타내기 위한 변수
void deleteBook(Book* root, Book* b) {

}

Book* addBook(char* _BookName, Book* root) {

	Book* b = NULL;
	int isCheck;

	if (root == NULL) {
		Book* b = (Book*)malloc(sizeof(Book));
		b->left = NULL;
		b->right = NULL;

		strcpy_s(b->BookName, BOOK_NAME, _BookName);
		printf("지은이 : \n");
		gets(b->BookAuthor);
		rewind(stdin);
		printf("출판사 : \n");
		gets(b->publisher);
		rewind(stdin);
		printf("책 고유번호 : \n");
		scanf_s("%d", &b->BookNum);
		b->BookRent = 1;//새로 만든 책은 대여 가능으로 고정
		return b;
	}
	else {
		isCheck = strcmp(_BookName, root->BookName);
		if (isCheck < 0) root->left = addBook(_BookName, root->left);
		else if (isCheck > 0) root->right = addBook(_BookName, root->right);
		else { printf("같은 책이 있습니다.\n"); }
		return root;
	}
}

void searchAll(Book* root) {

	if (root) {// 책 첫 글자 자음으로 정렬해서 중위로 해야 같은 글자끼리 출력이 됨
		searchAll(root->left);
		printf("[%d] 책 번호 : %d / 책 이름 : %s / 지은이 : %s / 출판사 : %s\n", ++count, root->BookNum, root->BookName, root->BookAuthor, root->publisher);
		searchAll(root->right);
	}
}

Book* searchBook(Book* root) {

	Book* find = root;
	int num = 0;
	int isCheck;

	while (1) {
		printf("검색 방법\n");
		printf("1. 제목 2. 지은이 3. 출판사\n");
		scanf_s("%d", &num);
		rewind(stdin);
		switch (num) {
		case 1: {
			char* name = (char*)malloc(BOOK_NAME * sizeof(char));
			printf("제목 입력: \n");
			gets(name);
			rewind(stdin);
			while (find != NULL) {
				isCheck = strcmp(name, find->BookName);
				if (isCheck < 0)find = find->left;
				else if (isCheck > 0)find = find->right;
				else { free(name); return find; }
			}
			return find;
		}
		case 2: {
			char* author = (char*)malloc(BOOK_AUTHOR * sizeof(char));
			printf("지은이 입력: \n");
			gets(author);
			rewind(stdin);
			while (find != NULL) {
				isCheck = strcmp(author, find->BookAuthor);
				if (isCheck < 0)find = find->left;
				else if (isCheck > 0)find = find->right;
				else { free(author); return find; }
			}
			return find;
		}
		case 3: {
			char* publisher = (char*)malloc(BOOK_PUBLISHER * sizeof(char));
			printf("출판사 입력: \n");
			gets(publisher);
			rewind(stdin);
			while (find != NULL) {
				isCheck = strcmp(publisher, find->publisher);
				if (isCheck < 0)find = find->left;
				else if (isCheck > 0)find = find->right;
				else { free(publisher); return find; }
			}
			return find;
		}
		default: {printf("다시 입력해주세요.\n"); continue; }
		}
	}
}
void rent_returnBook(Book* root) {

	char chose = '\0';
	int num = 0;
	char check = '\0';

	Book* find = NULL;
	if (root) {
		while (1) {
			find = searchBook(root);
			if (find == NULL) { printf("\n없거나 잘못 입력하셨습니다.\n");  system("pause"); return root; }//예외처리
			printf("\n\t===책 정보===\n");
			printf("책 제목: %s\t/", find->BookName);
			printf("지은이: %s\t/", find->BookAuthor);
			printf("출판사: %s/\t", find->publisher);
			if (find->BookRent == 1)printf("대여 가능 책\n");
			else if (find->BookRent == 0)printf("대여 불가능 책\n");
			printf("1. 대여 2. 반납\n");
			scanf_s("%d", &num);
			getchar();
			switch (num) {
			case 1: {
				if (find->BookRent == 1) {
					printf("대여 가능한 책\n");
					printf("대여 하시겠습니까? (y/n)\n");
					scanf_s("%c", &chose, 1);
					getchar();
					if (chose == 'y') {
						find->BookRent = 0; //대여 불가로 변환
						printf("대여 하셨습니다.\n");
						break;
					}
					else if (chose == 'n') { printf("대여를 취소하셨습니다.\n"); break; }
					else { printf("제대로된 키를 입력해주세요"); continue; }
				}
				else if (find->BookRent == 0) { printf("대여 중인 책입니다.\n"); break; }
			}
			case 2: {
				if (find->BookRent == 0) {
					printf("반납 하시겠습니까? (y/n)\n");
					scanf_s("%c", &chose, 1);
					getchar();
					if (chose == 'y') {
						find->BookRent = 1;// 대여 가능으로 변환
						printf("반납 완료되었습니다.\n");
						break;
					}
					else if (chose == 'n') { printf("취소 하셨습니다.\n"); break; }
					else { printf("제대로된 키를 입력해주세요"); continue; }
				}
				else if (find->BookRent == 1) { printf("대여되지 않은 책입니다.\n"); break; }
			}
			default: {printf("다시 입력하세요\n"); continue; }
			}
			printf("대여를 더 하시겠습니까? (y/n)\n");
			scanf_s("%c", &check, 1);
			getchar();
			if (check == 'y') { continue; }
			else if (check == 'n') { return; }
			else { printf("잘못 입력 하셨습니다.\n"); system("pause"); return; }
		}
	}
	else {
		printf("대여할 책이 없습니다.\n"); system("pause");
	}
}
void modifyBook(Book* root) {

	int num = 0;

	Book* find = root;

	while (1) {
		printf("수정할 부분 선택\n");
		printf("1. 제목 2. 지은이 3. 출판사 \n");
		scanf_s("%d", &num);
		switch (num) {
		case 1: {
			char* _bookname = (char*)malloc(BOOK_NAME * sizeof(char));
			printf("수정할 제목 : \n");
			gets(_bookname);
			addBook(_bookname, root);
			strcpy_s(find->BookName, BOOK_NAME, _bookname);
			printf("수정 완료\n");
			free(_bookname); break; }
		case 2: {
			char* _bookauthor = (char*)malloc(BOOK_AUTHOR * sizeof(char));
			printf("수정할 지은이 : \n");
			gets(_bookauthor);
			addBook(_bookauthor, root);
			strcpy_s(find->BookAuthor, BOOK_AUTHOR, _bookauthor);
			printf("수정 완료\n");
			free(_bookauthor); break; }
		case 3: {
			char* _publisher = (char*)malloc(BOOK_PUBLISHER * sizeof(char));
			printf("수정할 출판사 : \n");
			gets(_publisher);
			addBook(_publisher, root);
			strcpy_s(find->BookAuthor, BOOK_PUBLISHER, _publisher);
			printf("수정 완료\n");
			free(_publisher); break; }
		default: {printf("없는 메뉴\n"); break; }
		}
	}
}

int main(void) {
	// 사용자가 종료할 때 까지 인터페이스 유지
	int num; // 사용자가 메뉴를 사용할 번호
	Book* root = NULL;
	char* _BookName = NULL;

	while (1) {
		system("cls");
		printf("===메뉴선택===\n");
		printf("[1] 책 등록 [2] 전체 조회 [3] 책 검색 [4] 책 정보 수정 [5] 책 삭제 [6] 도서 반납 및 대여 [0] 종료\n");
		scanf_s("%d", &num);
		rewind(stdin);
		switch (num) {
		case 0: return 0;
		case 1: { _BookName = (char*)malloc(BOOK_NAME * sizeof(char)); printf("제목 : \n");
			gets(_BookName); root = addBook(_BookName, root); if (root == NULL) { printf("리스트 추가 안됨\n"); }
			system("pause"); break; }
		case 2: {searchAll(root); system("pause"); break; }
		case 3: {Book* book = searchBook(root);
			if (book != NULL) {
				printf("책 이름 : %s\n", book->BookName);
				printf("지은이 : %s\n", book->BookAuthor);
				printf("책 고유번호 : %d\n", book->BookNum);
				if (book->BookRent == 1)printf("책 대여 가능\n");
				else if (book->BookRent == 0)printf("책 대여 불가\n");
			}
			else { printf("해당 도서가 없습니다.\n"); }
			system("pause"); break; }
		case 4: {modifyBook(root); break; }
			  //case 5: {deleteBook(root, root->key); break; }
		case 6: {rent_returnBook(root); break; }
		default: {printf("====없는 메뉴\n====\n"); printf("다시 입력해주세요.\n"); continue; }
		}
	}
	return 0;
}