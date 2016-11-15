#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <map>

struct symbolItem
{
    String name; // ��ʶ������
    int line;   // ��������
    int kind;   // ���ŵ�����, ����, ����, ����, ��������, ����
    int type;   // int or char or void
    int valoroffset;    // ֵ, ����ǳ����Ļ�/��Ի���ַƫ��, ����Ǳ���������Ļ�
    int length; // ���鳤��
};
class SymbolTable
{
    public:
        SymbolTable();  // ���캯��
        virtual ~SymbolTable(); // ��������

        struct symbolItem searchItem(string name);
        bool insertItem(string name, int line, int kind, int type, int val = 0, int length = 1)

    protected:
    private:
        std::map<string, struct symbolItem> symbolList;
        int offset = 0;
};

// ���ű�
// �������� kind
#define CONSTANT 1
#define VARIABLE 2
#define FUNCTION 3

// ������������ type
#define INT_TYPE 1
#define CHAR_TYPE 2
#define VOID_TYPE 3

#endif // SYMBOLTABLE_H
