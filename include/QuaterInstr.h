#ifndef QUATERINSTR_H
#define QUATERINSTR_H


class QuaterInstr
{
    public:
        QuaterInstr();
        virtual ~QuaterInstr();
    protected:
    private:
        Opcode op;
        string des;
        string src1;
        string src2;
};

#endif // QUATERINSTR_H
