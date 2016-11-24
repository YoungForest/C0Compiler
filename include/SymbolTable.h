#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <map>
#include <string>
#include "Laxer.h"

struct symbolItem
{
    std::string name; // ��ʶ������
    int line;   // ��������
    int kind;   // ���ŵ�����, ����, ����, ����, ��������, ����
    int type;   // int or char or void
    int valueoroffset;    // ֵ, ����ǳ����Ļ�/��Ի���ַƫ��, ����Ǳ���������Ļ�
    int length; // ���鳤��
};
class SymbolTable
{
    public:
        SymbolTable();  // ���캯��
        virtual ~SymbolTable(); // ��������

        struct symbolItem *searchItem(std::string name);
        struct symbolItem *insertItem(std::string name, int line, int kind, int type, int val = 0, int length = 0);
        struct symbolItem *generateTemp();
		struct symbolItem* SymbolTable::generateTempConstant(int value);

    protected:
    private:
        std::map<std::string, struct symbolItem*> symbolList;
        int offset;
};

// ���ű�
// �������� kind
#define CONSTANT 1
#define VARIABLE 2
#define FUNCTION 3

// ������������ type
#define INT_TYPE INT
#define CHAR_TYPE CHAR
#define VOID_TYPE VOID
#define STRING_TYPE 30

#endif // SYMBOLTABLE_H
