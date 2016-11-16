#ifndef ERROR_H
#define ERROR_H

#include <string>
#include <vector>

class Error
{
    public:
        Error();
        virtual ~Error();

        bool isSuccess();   // 判断是否成功编译
        int getErrorCount();    // 错误信息数量
        void print();   // 打印编译错误信息
        void errorMessage(int errortype, int line, int column);
        void errorMessage(int errortype, int line, int column, std::string message1);
        void errorMessage(int errortype, int line, int column, std::string message1, std::string message2);
    protected:
    private:
        int error_count;
        std::vector<std::string> error_messages;
};

#endif // ERROR_H
