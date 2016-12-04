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
		void printErrors();   // 打印编译错误信息
		void printWarnings();   // 打印编译警告信息
        void errorMessage(int errortype, int line, int column);
        void errorMessage(int errortype, int line, int column, std::string message1);
        void errorMessage(int errortype, int line, int column, std::string message1, std::string message2);
		void warningMessage(int warningtype, int line, int column, std::string message1);

		int warning_count = 0;
		int error_count;
		std::vector<std::string> error_messages;
		std::vector<std::string> warning_messages;

    protected:
    private:
        
};

#endif // ERROR_H
