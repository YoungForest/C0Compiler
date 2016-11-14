#ifndef LAXER_H
#define LAXER_H


class Laxer
{
    public:
        Laxer();
        virtual ~Laxer();
    protected:
    private:
        int num;                          // 存放最近一次识别出来的数字
        int cc;                           // 字母计数（列指针）
        int err;                            // 记录编译出错次数
};

#endif // LAXER_H
