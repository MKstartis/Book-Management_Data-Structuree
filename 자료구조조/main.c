#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include "����ü.h"
#define BOOK_NAME 50
#define BOOK_AUTHOR 50
#define BOOK_PUBLISHER 50

int count = 1; //��ü ��ȸ���� å�� ��ȣ�� ��Ÿ���� ���� ����
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
		printf("������ : \n");
		gets(b->BookAuthor);
		rewind(stdin);
		printf("���ǻ� : \n");
		gets(b->publisher);
		rewind(stdin);
		printf("å ������ȣ : \n");
		scanf_s("%d", &b->BookNum);
		b->BookRent = 1;//���� ���� å�� �뿩 �������� ����
		return b;
	}
	else {
		isCheck = strcmp(_BookName, root->BookName);
		if (isCheck < 0) root->left = addBook(_BookName, root->left);
		else if (isCheck > 0) root->right = addBook(_BookName, root->right);
		else { printf("���� å�� �ֽ��ϴ�.\n"); }
		return root;
	}
}

void searchAll(Book* root) {

	if (root) {// å ù ���� �������� �����ؼ� ������ �ؾ� ���� ���ڳ��� ����� ��
		searchAll(root->left);
		printf("[%d] å ��ȣ : %d / å �̸� : %s / ������ : %s / ���ǻ� : %s\n", ++count, root->BookNum, root->BookName, root->BookAuthor, root->publisher);
		searchAll(root->right);
	}
}

Book* searchBook(Book* root) {

	Book* find = root;
	int num = 0;
	int isCheck;

	while (1) {
		printf("�˻� ���\n");
		printf("1. ���� 2. ������ 3. ���ǻ�\n");
		scanf_s("%d", &num);
		rewind(stdin);
		switch (num) {
		case 1: {
			char* name = (char*)malloc(BOOK_NAME * sizeof(char));
			printf("���� �Է�: \n");
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
			printf("������ �Է�: \n");
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
			printf("���ǻ� �Է�: \n");
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
		default: {printf("�ٽ� �Է����ּ���.\n"); continue; }
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
			if (find == NULL) { printf("\n���ų� �߸� �Է��ϼ̽��ϴ�.\n");  system("pause"); return root; }//����ó��
			printf("\n\t===å ����===\n");
			printf("å ����: %s\t/", find->BookName);
			printf("������: %s\t/", find->BookAuthor);
			printf("���ǻ�: %s/\t", find->publisher);
			if (find->BookRent == 1)printf("�뿩 ���� å\n");
			else if (find->BookRent == 0)printf("�뿩 �Ұ��� å\n");
			printf("1. �뿩 2. �ݳ�\n");
			scanf_s("%d", &num);
			getchar();
			switch (num) {
			case 1: {
				if (find->BookRent == 1) {
					printf("�뿩 ������ å\n");
					printf("�뿩 �Ͻðڽ��ϱ�? (y/n)\n");
					scanf_s("%c", &chose, 1);
					getchar();
					if (chose == 'y') {
						find->BookRent = 0; //�뿩 �Ұ��� ��ȯ
						printf("�뿩 �ϼ̽��ϴ�.\n");
						break;
					}
					else if (chose == 'n') { printf("�뿩�� ����ϼ̽��ϴ�.\n"); break; }
					else { printf("����ε� Ű�� �Է����ּ���"); continue; }
				}
				else if (find->BookRent == 0) { printf("�뿩 ���� å�Դϴ�.\n"); break; }
			}
			case 2: {
				if (find->BookRent == 0) {
					printf("�ݳ� �Ͻðڽ��ϱ�? (y/n)\n");
					scanf_s("%c", &chose, 1);
					getchar();
					if (chose == 'y') {
						find->BookRent = 1;// �뿩 �������� ��ȯ
						printf("�ݳ� �Ϸ�Ǿ����ϴ�.\n");
						break;
					}
					else if (chose == 'n') { printf("��� �ϼ̽��ϴ�.\n"); break; }
					else { printf("����ε� Ű�� �Է����ּ���"); continue; }
				}
				else if (find->BookRent == 1) { printf("�뿩���� ���� å�Դϴ�.\n"); break; }
			}
			default: {printf("�ٽ� �Է��ϼ���\n"); continue; }
			}
			printf("�뿩�� �� �Ͻðڽ��ϱ�? (y/n)\n");
			scanf_s("%c", &check, 1);
			getchar();
			if (check == 'y') { continue; }
			else if (check == 'n') { return; }
			else { printf("�߸� �Է� �ϼ̽��ϴ�.\n"); system("pause"); return; }
		}
	}
	else {
		printf("�뿩�� å�� �����ϴ�.\n"); system("pause");
	}
}
void modifyBook(Book* root) {

	int num = 0;

	Book* find = root;

	while (1) {
		printf("������ �κ� ����\n");
		printf("1. ���� 2. ������ 3. ���ǻ� \n");
		scanf_s("%d", &num);
		switch (num) {
		case 1: {
			char* _bookname = (char*)malloc(BOOK_NAME * sizeof(char));
			printf("������ ���� : \n");
			gets(_bookname);
			addBook(_bookname, root);
			strcpy_s(find->BookName, BOOK_NAME, _bookname);
			printf("���� �Ϸ�\n");
			free(_bookname); break; }
		case 2: {
			char* _bookauthor = (char*)malloc(BOOK_AUTHOR * sizeof(char));
			printf("������ ������ : \n");
			gets(_bookauthor);
			addBook(_bookauthor, root);
			strcpy_s(find->BookAuthor, BOOK_AUTHOR, _bookauthor);
			printf("���� �Ϸ�\n");
			free(_bookauthor); break; }
		case 3: {
			char* _publisher = (char*)malloc(BOOK_PUBLISHER * sizeof(char));
			printf("������ ���ǻ� : \n");
			gets(_publisher);
			addBook(_publisher, root);
			strcpy_s(find->BookAuthor, BOOK_PUBLISHER, _publisher);
			printf("���� �Ϸ�\n");
			free(_publisher); break; }
		default: {printf("���� �޴�\n"); break; }
		}
	}
}

int main(void) {
	// ����ڰ� ������ �� ���� �������̽� ����
	int num; // ����ڰ� �޴��� ����� ��ȣ
	Book* root = NULL;
	char* _BookName = NULL;

	while (1) {
		system("cls");
		printf("===�޴�����===\n");
		printf("[1] å ��� [2] ��ü ��ȸ [3] å �˻� [4] å ���� ���� [5] å ���� [6] ���� �ݳ� �� �뿩 [0] ����\n");
		scanf_s("%d", &num);
		rewind(stdin);
		switch (num) {
		case 0: return 0;
		case 1: { _BookName = (char*)malloc(BOOK_NAME * sizeof(char)); printf("���� : \n");
			gets(_BookName); root = addBook(_BookName, root); if (root == NULL) { printf("����Ʈ �߰� �ȵ�\n"); }
			system("pause"); break; }
		case 2: {searchAll(root); system("pause"); break; }
		case 3: {Book* book = searchBook(root);
			if (book != NULL) {
				printf("å �̸� : %s\n", book->BookName);
				printf("������ : %s\n", book->BookAuthor);
				printf("å ������ȣ : %d\n", book->BookNum);
				if (book->BookRent == 1)printf("å �뿩 ����\n");
				else if (book->BookRent == 0)printf("å �뿩 �Ұ�\n");
			}
			else { printf("�ش� ������ �����ϴ�.\n"); }
			system("pause"); break; }
		case 4: {modifyBook(root); break; }
			  //case 5: {deleteBook(root, root->key); break; }
		case 6: {rent_returnBook(root); break; }
		default: {printf("====���� �޴�\n====\n"); printf("�ٽ� �Է����ּ���.\n"); continue; }
		}
	}
	return 0;
}