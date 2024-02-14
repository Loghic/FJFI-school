#ifndef RANDOM_ARRAY_H
#define RANDOM_ARRAY_H


class array {
    int *buff;
    int size{};
    int Iterator;
public:
    array();
    ~array();
    array(int capacity);
    array(const array& number);

    int *getBuff() const;

    void setBuff(int *buff);

    int getSize() const;

    void setSize(int size);

    int getNumberOnIteratorPossition(int it){return *(buff + it);}

};


#endif
