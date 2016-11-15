#include "Error.h"
#include <sstream>

Error::Error()
{
    //ctor
    error_count = 0;
}

Error::~Error()
{
    //dtor
}

int Error::getErrorCount() {
    return error_count;
}

bool Error::IsSuccess() {
    return error_count == 0;
}

void Error::errorMessage(int errortype,int line, int column) {
    stringstream Message;
    Message << "�����ڵ� " << line << "��, �� " << column << "�� :";
    error_count++;
    switch (errortype)
    {
        //the function have defined before.
    case 3: Message << "Find ! which is not followed by =." << endl; break;
    case 14: Message << "���������ж�" << endl; break;
    case 15:Message << "������г������������ַ���" << endl; break;
    case 24: Message << "for����г����˷�to��downto��ʶ" << endl; break;
    case 26: Message << "�������ַǷ���ϵ�����" << endl; break;
    case 27: Message << "�����в����Գ����ַ�����" << endl; break;
    case 41: Message << "��������ȱ�ٱ�ʶ��" << endl; break;
    case 50: Message << "����û����.��β" << endl; break;
    case 42: Message << "�� = �� := ʹ��" << endl; break;
    case 60: Message << "�ֳ���û����������" << endl; break;
    case 61: Message << "���������ʽ����ȷ" << endl; break;
    case 62: Message << "��ͷ�����쳣�ַ���" << endl; break;
    //case 63: Message << "factor����ǰ�����岻��ȷ���ַ���" << endl; break;
    //case 64: Message << "const����ǰ�����岻��ȷ���ַ���" << endl; break;
    //case 65: Message << "var����ǰ�����岻��ȷ���ַ���" << endl; break;
    //case 66: Message << "��������ǰ�����岻��ȷ���ַ���" << endl; break;
    //case 67: Message << "����ǰ�����岻��ȷ���ַ���" << endl; break;
    default: Message << "Unhandled error " << errortype << " !" << endl;
        break;
    }
    error_messages.push_back(Message.str());
}

void Error::errorMessage(int errortype, int line, int column, string message1) {
    stringstream Message;
    Message << "�����ڵ� " << line << "��, �� " << column << "�� :";
    error_count++;
    switch (errortype)
    {
        //the function have defined before.
    case 101: Message << "Parse error " << message1 << " !" << endl; break;
    case 2: Message << "Can't recongnize this token" << message1 << endl; break;
    case 6: Message << "���������޷�ʶ����ַ�" << message1 << endl; break;
    case 10: Message << message1 << "����һ���Ϸ��ĺ���������" << endl; break;
    case 11: Message << message1 << "����һ���Ϸ��Ĺ���������" << endl; break;
    case 12: Message << message1 << "����һ���Ϸ��Ļ������ͣ�" << endl; break;
    case 13: Message << "�ں���" << message1 << "������ȱ�ٷֺţ�" << endl; break;
    case 16: Message << message1 << "����һ���Ϸ��ĳ������ͣ�" << endl; break;
    case 9: Message << "��Ӧ�����ַ�" << message1 << endl; break;
    case 18: Message << message1 << "�ǳ�����������ֵ�����������и��ģ�" << endl; break;
    case 19: Message << message1 << "��Ӧ���ڴ˴����֣�" << endl; break ;
    case 20: Message << "�����ڷ�" << message1 << "��������Ϊ����ָ������ֵ��" << endl; break;
    case 39: Message << message1 << "����/�������޲����ģ�����ʱ���ô�()" << endl; break;
    case 40: Message << "��ʶ��" << message1 << "δ���壡" << endl; break;
    case 41: Message << "����" << message1 << "��ʹ�õı�ʶ���Ѿ��������!" << endl; break;
    case 42: Message << "����" << message1 << "��ʹ�õı�ʶ���Ѿ��������!" << endl; break;
    case 43: Message << "����" << message1 << "��ʹ�õı�ʶ���Ѿ�������ˣ�" << endl; break;
    case 44: Message << "����" << message1 << "��ʹ�õı�ʶ���Ѿ�������ˣ�" << endl; break;
    case 45: Message << "�����ķ�������" << message1 << "���ǻ������ͣ�" << endl; break;
    case 46: Message << message1 << "�������飡" << endl; break;
    case 47: Message << message1 << "����/���� ���޲����ģ�����ʱ��Ӧ��ʹ��()!" << endl; break;
    case 54: Message << "���ܴ���Ǳ�����Ϊ" << message1 << " �д��� var ���βε�ʵ�Σ�" << endl; break;
    case 55: Message << message1 << "�β���ʵ�θ�����ƥ�䣡" << endl; break;
    case 56: Message << message1 << "�β���ʵ�ε����Ͳ�ƥ�䣡" << endl; break;
    case 57: Message << message1 << "���ǹ��̣�" << endl; break;
    case 58: Message << message1 << "�±겻��ȷ��" << endl; break;
    default: Message << "Unhandled error " << errortype << " !" << endl;
        break;
    }
    error_messages.push_back(Message.str());
}

void Error::errorMessage(int errortype, int line, int column, string message1, string message2) {
    stringstream Message;
    Message << "�����ڵ� " << line << "��, �� " << column << "�� :  ";
    error_count++;
    switch (errortype)
    {
        //the function have defined before.
    case 47: Message << message1 << "�� int,����ֱ�Ӹ�ֵ�� char ����" << message2 << "��" << endl; break;
    case 48: Message << message1 << "��" << message2 << "���Ͳ���int �� char�����ܲ������㣡" << endl; break;
    case 9: Message << "������" << message1 << " �ڳ�����ȴ��" << message2 << endl; break;
    default: Message << "Unhandled error " << errortype << " !" << endl;
        break;
    }
    error_messages.push_back(Message.str());
}

void Error::print() {
    vector<string>::iterator it = error_messages.begin();
    while (it != error_messages.end()) {
        cout << (*it);
        it++;
    }
}