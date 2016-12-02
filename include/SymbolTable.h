#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <vector>
#include <string>
#include "Laxer.h"

struct symbolItem
{
    std::string name; // ��ʶ������
    int line;   // ��������
    int kind;   // ���ŵ�����, ����, ����, ����, ����
    int type;   // int or char or void
    int valueoroffset;    // ֵ, ����ǳ����Ļ� or ��Ի���ַƫ��, ����Ǳ���������Ļ�
    int length; // ���鳤��, or ������������
	int scope; // ȫ�ֻ�ֲ�����
};
class SymbolTable
{
    public:
        SymbolTable(int _scope);  // ���캯��
        virtual ~SymbolTable(); // ��������
		struct symbolItem* searchItem(std::string ident);
        struct symbolItem* insertItem(std::string name, int line, int kind, int type, int val = 0, int length = 0);
        struct symbolItem* generateTemp();	// ������ʱ����
		struct symbolItem* generateTempChar();	// ������ʱ�ַ����ͱ���
		struct symbolItem* generateTempConstant(int value, int type);	// ������ʱ����
		int getPosition(struct symbolItem* elem);	// ��ȡԪ�ص��±�, Ϊ�ҵ������Ĳ���
		void clear();	// ��շ��ű�
		
		std::vector<struct symbolItem*> symbolList;
		int offset;

    protected:
    private:
		int scope;
};

// ���ű�
// �������� kind
#define CONSTANT 1
#define VARIABLE 2
#define FUNCTION 3
#define PARAMETER 4

// ������������ type
#define INT_TYPE INT
#define CHAR_TYPE CHAR
#define VOID_TYPE VOID
#define STRING_TYPE STRING

// ����������
#define LOCAL 2
#define GLOBAL 3

#endif // SYMBOLTABLE_H
