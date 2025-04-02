#pragma once

#include <memory>
#include <string>
#include <iostream>

using namespace std;

extern string mode;

/*
    CompUnit  ::= FuncDef;

    FuncDef   ::= FuncType IDENT "(" ")" Block;
    FuncType  ::= "int";

    Block     ::= "{" Stmt "}";
    Stmt      ::= "return" Number ";";
    Number    ::= INT_CONST;
*/


// 所有 AST 的基类
class BaseAST {
public:
    virtual ~BaseAST() = default;
    virtual void Dump() const = 0;
};
   
// CompUnit 是 BaseAST
class CompUnitAST : public BaseAST {
public:
    // 用智能指针管理对象
    unique_ptr<BaseAST> func_def;
    void Dump() const override {
        if (mode == "-debug") {
            cout << "CompUnitAST { ";
            func_def->Dump();
            cout << " }";
        }
        else if (mode == "-koopa") {
            func_def->Dump();
        }
    }
};
   
// FuncDef 也是 BaseAST
class FuncDefAST : public BaseAST {
public:
    unique_ptr<BaseAST> func_type;
    string ident;
    unique_ptr<BaseAST> block;
    void Dump() const override {
        if (mode == "-debug") {
            cout << "FuncDefAST { ";
            func_type->Dump();
            cout << ", " << ident << ", ";
            block->Dump();
            cout << " }";
        }
        else if (mode == "-koopa") {
            cout << "fun @" << ident << "(): ";
            func_type->Dump();
            cout << " {" << endl;
            block->Dump();
            cout << "}" << endl;
        }
    }
};
   
class FuncTypeAST : public BaseAST {
public:
    string type;
    void Dump() const override {
        if (mode == "-debug") {
            cout << "FuncTypeAST { " << type << " }";
        }
        else if (mode == "-koopa") {
            if (type == "int") {
                cout << "i32";
            }
            else if (type == "void") {
                cout << "void";
            }
        }
    }
};

class BlockAST : public BaseAST {
public:
    unique_ptr<BaseAST> stmt;
    void Dump() const override {
        if (mode == "-debug") {
            cout << "BlockAST { ";
            stmt->Dump();
            cout << " }";
        }
        else if (mode == "-koopa") {
            cout << "%entry:" << endl;
            stmt->Dump();
        }
    }
};

class StmtAST : public BaseAST {
public:
    int number;
    void Dump() const override {
        if (mode == "-debug") {
            cout << "StmtAST { " << number << " }";
        }
        else if (mode == "-koopa") {
            cout << "  ret " << number << endl;
        }
    }
};