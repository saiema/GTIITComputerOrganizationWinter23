#include "standard.h"
#include <stdlib.h>

boolean and(const boolean a, const boolean b) {
    //TODO
}

boolean not(const boolean a) {
    //TODO
}

boolean or(const boolean a, const boolean b) {
    //TODO
}

boolean xor(const boolean a, const boolean b) {
    //TODO
}

enum {LEAF, NOT_OP, AND_OP, OR_OP};

struct expression {
    int tag;
    union {
        struct expression* childs[2];
        boolean value;
    } e;
};

struct expression* BOOLEAN_VALUE(boolean value) {
    struct expression* r = malloc(sizeof(struct expression));
    r->tag = LEAF;
    r->e.childs[0] = r->e.childs[1] = 0;
    r->e.value = value;
    return r;
}

struct expression* NOT(struct expression* e) {
    //TODO
}

struct expression* AND(struct expression* left, struct expression* right) {
    struct expression* r = malloc(sizeof(struct expression));
    r->tag = AND_OP;
    r->e.childs[0] = left;
    r->e.childs[1] = right;
    return r;
}

struct expression* OR(struct expression* left, struct expression* right) {
    //TODO
}

boolean eval(struct expression* expr) {
    switch (expr->tag) {
        case LEAF:   return expr->e.value;
        case NOT_OP: return not(eval(expr->e.childs[0]));
        case AND_OP: return and(eval(expr->e.childs[0]), eval(expr->e.childs[1]));
        case OR_OP:  return or(eval(expr->e.childs[0]), eval(expr->e.childs[1]));
        //TODO: add XOR case
    }
}

void drop(struct expression* expr) {
    switch (expr->tag) {
        case LEAF:   free(expr); break;
        case NOT_OP: drop(expr->e.childs[0]); free(expr); break;
        default:     drop(expr->e.childs[0]); drop(expr->e.childs[1]); free(expr);
    }
}