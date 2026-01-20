#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define InitSize 100

//顺序表的定义
typedef struct {
	int* data;//指示动态分配数组的指针
	int length;//顺序表当前已存储的有效元素个数
	int MaxSize;//顺序表的最大容量
}SeqList;

//初始化顺序表
void InitList(SeqList*L) {
	L->data = (int*)malloc(InitSize * sizeof(int));
	L->length = 0;
	L->MaxSize = InitSize;
}

//增加动态数组的长度
void IncreaseSize(SeqList* L, int len) {
	int* p = L->data;
	int* new_data = (int*)realloc(L->data,(L->MaxSize + len) * sizeof(int));
	
	if (new_data == NULL) {
		printf("内存扩容失败！\n");
		return;
	}
	L->data = new_data;
	L->MaxSize += len;
	printf("扩容成功！\n");
	free(p);
}

//顺序表插入元素（布尔类型）
bool ListInsert(SeqList* L, int i, int e) {
	//在i处(此处i是位序而不是数组下标)插入元素e
	if (i<1 || i>L->length+1) {
		return false;
	}
	
	if (L->length >= L->MaxSize) {
		return false;
	}
	int j = 0;
	for (j = L->length; j >= i; j--) {
		L->data[j] = L->data[j - 1];
	}
	L->data[i - 1] = e;
	L->length++;
	printf("插入元素%d成功\n", e);
	return true;
}

//顺序表删除元素
bool ListDelete(SeqList* L, int i, int* e) {
	if (i<1 || i>L->length) {
		return false;
	}
	*e = L->data[i - 1];
	for (int j = i; j < L->length; j++) {
		L->data[j - 1] = L->data[j];
	}
	L->length--;
	return true;
}

//顺序表按位查找
int GetElem(SeqList L, int i) {
	return L.data[i - 1];
}

//顺序表按值查找
int LocateElem(SeqList L, int e) {
	for (int i = 0; i < L.length; i++) {
		if (L.data[i] == e) {
			return i + 1;
		}
	}
	return 0;
}

//测试代码
int main(){
	SeqList L;

	//初始化
	InitList(&L);

	//增加动态存储
	IncreaseSize(&L, 5);

	//插入
	ListInsert(&L, 1, 1);
	ListInsert(&L, 2, 2);
	ListInsert(&L, 3, 3);

	//删除
	int e = -1;
	if (ListDelete(&L, 3, &e)) {
		printf("已删除第三个元素，删除元素为：%d\n", e);
	}
	else {
		printf("位序i不合法，删除失败\n");
	}

	//按位查找
	int ret01 = GetElem(L, 2);
	printf("按位查找成功，找到第二个元素%d\n", ret01);

	//按值查找
	int ret02 = LocateElem(L, 2);
	printf("按值查找成功，找到2的位序是%d\n", ret02);

	return 0;
}