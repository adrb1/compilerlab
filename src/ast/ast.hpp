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
        std::cout << "CompUnitAST { ";
        func_def->Dump();
        std::cout << " }";
      }
};
   
// FuncDef 也是 BaseAST
class FuncDefAST : public BaseAST {
public:
    unique_ptr<BaseAST> func_type;
    string ident;
    unique_ptr<BaseAST> block;
    void Dump() const override {
        std::cout << "FuncDefAST { ";
        func_type->Dump();
        std::cout << ", " << ident << ", ";
        block->Dump();
        std::cout << " }";
      }
};
   
class FuncTypeAST : public BaseAST {
public:
    string type;
    void Dump() const override {
       std::cout << "FuncTypeAST { " << type << " }";
    }
}

class BlockAST : public BaseAST {
public:
    unique_ptr<BaseAST> stmt;

    void Dump() const override {
        std::cout << "BlockAST { ";
        stmt->Dump();
        std::cout << " }";
    }

};

class StmtAST : public BaseAST {
public:
    int number;
    void Dump() const override {
        std::cout << "StmtAST { " << number << " }";
    }

};