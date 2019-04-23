#include <vector>
#include <iostream>
#include <fstream>
#include <map>
#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include "Huffman.h"


#define BYTE_LENGTH 8
/*
typedef unsigned char byte;

std::queue<byte> q;


class IOutputStream {
    FILE * F;
    bool file;
 public:
    IOutputStream() {
        file = false
        ;
    }
    IOutputStream(std::string &fname) {
        file = true;
        F = fopen(fname.c_str(), "w");
    }
    void Write(byte b) {
        if (file) {
            fprintf(F, "%c",b);;
        } else {
            q.push(b);
        }
    }
    ~IOutputStream() {
        if (file) {
            fclose(F);
        }
    }
};

class IInputStream {
 private:
    FILE * F;
    bool file;

 public:
    IInputStream() {
        file = false;
    }
    IInputStream(std::string &fname) {
        file = true;
        F = fopen(fname.c_str(), "r");
    }
    bool Read(byte & b) {
        char c = EOF;
        if (file) {
            c = fgetc(F);
            b = c;
            if (feof(F) == 0) {
                return true;
            } else {
                return false;
            }
        } 
        else {
            if (q.empty()) {
                return false;
            } else {
                b = q.front();
                q.pop();
                return true;
            }
        }
    }
    ~IInputStream() {
        if (file) {
            fclose(F);
        }
    }
};


*/

class haf_tree {
 public:
    haf_tree(byte, size_t);
    haf_tree(haf_tree *, haf_tree *);
    ~haf_tree();
    size_t count(){return sum;};
    byte get_symbol(){return symbol;};
    haf_tree * get_left(){return left;};
    haf_tree * get_right(){return right;};
    void alphabet_size(byte *);
 private:
    haf_tree * left;
    haf_tree * right;
    byte symbol;
    size_t sum;
};

void haf_tree::alphabet_size(byte * c) {
    if (left == nullptr || right == nullptr) {
        (*c)++;
        return;
    }
    left->alphabet_size(c);
    right->alphabet_size(c);
}

haf_tree::haf_tree(byte c, size_t n) {
    left = nullptr;
    right = nullptr;
    symbol = c;
    sum = n;
}

haf_tree::haf_tree(haf_tree * a, haf_tree * b) {
    left = a;
    right = b;
    symbol = '\0';
    sum = a->count() + b->count();
}

haf_tree::~haf_tree() {
    if (left != nullptr) {
        delete left;
    }
    if (right != nullptr) {
        delete right;
    }
}

struct cmp {
    bool operator()(haf_tree * a, haf_tree * b) {
        return a->count() > b->count();
    }
};

void read(std::map<byte, size_t> & map, std::vector<byte> & str, IInputStream& original) {
    byte value = 0;
    while (original.Read(value) == true) {
        auto i = map.find(value);
        if (i == map.end()) {
            map.insert(std::pair<byte, size_t>(value, 1));
        } else {
            (i->second)++;
        }
        str.push_back(value);
    }
}

haf_tree * create_tree(std::map<byte, size_t> & map) {
    std::priority_queue<haf_tree *, std::vector<haf_tree *>, cmp > q;
    for (auto i = map.begin(); i != map.end(); i++) {
        haf_tree * new_tree = new haf_tree(i->first, i->second);
        q.push(new_tree);
    }
    while(q.size() > 1) {
        auto left = q.top();
        q.pop();
        auto right = q.top();
        q.pop();
        haf_tree * new_tree = new haf_tree(right, left);
        q.push(new_tree);
    }
    return q.top();
}

byte to_char(std::vector<bool> & bit_str, size_t byte_pos, bool * flag) {
    byte c = 0;
    size_t i = 0;
    for (i = byte_pos * BYTE_LENGTH; i < (byte_pos + 1) * BYTE_LENGTH; i++) {
        if (i >= bit_str.size()) {
            *flag = !(bit_str.back());
            if (*flag) {
                c |= 1 << ((BYTE_LENGTH - 1) - (i % BYTE_LENGTH));
            }
            continue;
        }
        if (bit_str[i]) {
            c |= 1 << ((BYTE_LENGTH - 1) - (i % BYTE_LENGTH));
        }
    }
    *flag = !(bit_str.back());
    return c;
}

void str_to_bit(std::vector<byte> & str, std::vector<bool>& out, std::map<byte, std::vector<bool>> & table) {
    for (auto i = str.begin(); i != str.end(); i++) {
        for (auto j = table[(*i)].begin(); j != table[(*i)].end(); j++) {
            out.push_back(*j);
        }
    }
}

bool print_bool_array(std::vector<bool> & arr, IOutputStream& output) {
    size_t length = arr.size();
    byte symbol = 0;
    bool flag = false;
    int a = 0;
    for (size_t j = 0; j <= (length - 1) / BYTE_LENGTH; j++) {
        symbol = to_char(arr, j, &flag);
        output.Write(byte(symbol));
    }
    if (flag) {
        output.Write(byte(255));
    } else {
        output.Write(byte(0));
    }
    return flag;
}

void compressing(std::vector<byte> & str, std::map<byte, std::vector<bool>> & table, IOutputStream& output) {
    byte alphabet = byte(table.size());
    output.Write(byte(255 - alphabet));
    for (auto i = table.begin(); i != table.end(); i++) {
        output.Write(byte(i->first));
        print_bool_array(i->second, output);
    }
    std::vector<bool> out;
    str_to_bit(str, out, table);
    print_bool_array(out, output);
    output.Write(byte(127));
}


void tree_to_table(haf_tree * tree, std::map<byte, std::vector<bool>> & coding_table, std::vector<bool> &code) {
    if (tree->get_left() == nullptr || tree->get_right() == nullptr) {
        std::vector<bool> insert_vector(code);
        coding_table.insert(std::pair<byte, std::vector<bool>>(tree->get_symbol(), insert_vector));
        return;
    }
    bool flag = false;
    if (code.size() % 8 == 7) {
        flag = true;
        code.push_back(!code.back());
    }
    code.push_back(false);
    tree_to_table(tree->get_left(), coding_table, code);
    code.pop_back();
    code.push_back(true);
    tree_to_table(tree->get_right(), coding_table, code);
    code.pop_back();
    if (flag == true) {
        code.pop_back();
    }
}

void Encode(IInputStream& original, IOutputStream& compressed) {
    std::map<byte, size_t> map;
    std::vector<byte> str;
    read(map, str, original);
    haf_tree * tree = create_tree(map);
    std::map<byte, std::vector<bool>> coding_table;
    std::vector<bool> code;
    tree_to_table(tree, coding_table, code);
    compressing(str, coding_table, compressed);
    delete tree;
}

void push_to_array(std::vector<bool> & in, byte c) {
    for (int j = (BYTE_LENGTH - 1); j >= 0; j--) {
        if ((1 << j ) & c) {
            in.push_back(true);
        } else {
            in.push_back(false);
        }
    }
}

bool get_bit(std::vector<bool> & in, size_t * pos) {
    if (in.size() == *pos) {
        return false;
    }
    (*pos)++;
    return in[*pos - 1];
}

byte get_byte(std::vector<bool> & in, size_t * pos) {
    byte c = 0;
    for (int i = (BYTE_LENGTH - 1); i >= 0; i--) {
        c |= int(get_bit(in, pos)) << i;
    }
    return c;
}

byte top_byte(std::vector<bool> & in, size_t * pos) {
    byte c = get_byte(in, pos);
    (*pos) -= BYTE_LENGTH;
    return c;
}

byte next_byte(std::vector<bool> & in, size_t * pos) {
    (*pos) += BYTE_LENGTH;
    byte c = get_byte(in, pos);
    (*pos) -= BYTE_LENGTH * 2;
    return c;
}

void read_decoder(std::map<std::vector<bool>, byte> & decoder, std::vector<bool> & in, size_t * pos) {
    byte count_symbols = 255 - get_byte(in, pos);
    byte current_symbol = 0;
    std::vector<bool> code;
    for (size_t i = 0; i < size_t(count_symbols); i++) {

        current_symbol = get_byte(in, pos);
        code.clear();
        while (top_byte(in, pos) != 0 && top_byte(in, pos) != 255 && top_byte(in, pos) != -1) {
            for (int j = 0; j < BYTE_LENGTH; j++) {
                code.push_back(get_bit(in, pos));
            }
        }
        for (int j = 0; j < BYTE_LENGTH; j++) {
            code.push_back(get_bit(in, pos));
        }
        if (code.back() == false) {
            while (code.back() == false) {
                code.pop_back();
            }
        } else if (code.back() == true) {
            while (code.back() == true) {
                code.pop_back();
            }
        }
        decoder.insert(std::pair<std::vector<bool>, byte>(code, current_symbol));
    }
}

void delete_end(std::vector<bool> & vec) {
    while (vec.back() == true) {
        vec.pop_back();
    }
    vec.pop_back();
    bool flag = vec.back();
    while (vec.back() == flag) {
        vec.pop_back();
    }
}

void Decode(IInputStream& input, IOutputStream& output) { 
    byte c;
    std::vector<bool> in;
    while (input.Read(c) == true) {
        push_to_array(in, c);
    }
    std::map<std::vector<bool>, byte> decoder;
    size_t pos = 0;
    read_decoder(decoder, in, &pos);
    delete_end(in);
    std::vector<bool> code;
    while(pos < in.size()) {
        code.clear();
        while (decoder.find(code) == decoder.end() && pos < in.size()) {
            code.push_back(get_bit(in, &pos));
        }
        output.Write(byte(decoder[code]));
    }
    return;
}


/*
int main(int argc, char ** argv) {

    if (argv[1][0] == 'c') {
        std::string in_str(argv[2]);
        std::string out_str(argv[3]);
        IInputStream e_in(in_str);
        IOutputStream e_out(out_str);
        Encode(e_in, e_out);

    } else if (argv[1][0] == 'e') {
        std::string in_str(argv[2]);
        std::string out_str(argv[3]);
        IInputStream d_in(in_str);
        IOutputStream d_out(out_str);
        Decode(d_in, d_out);
    }
}*/ 
