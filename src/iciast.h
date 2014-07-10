/****************************************************************************
**
** Copyright (C) 2012 Corentin Jabot
** Contact: https://github.com/cor3ntin/Ici
**
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
****************************************************************************/


#ifndef _ICIAST_H
#define _ICIAST_H

#include "iciast_fwd.h"
#include <QString>
#include <QStringList>

namespace ICI{

struct Node
{
    enum Type {
        Type_Node = 0,
        Type_Source,
        Type_Statements,
        Type_Statement,
        Type_IfStatement,
        Type_Include,
        Type_Unset,

        Type_Assignement,
        Type_Operator,

        Type_Expression,
        Type_NumericLiteral = 10,
        Type_BooleanLiteral,
        Type_StringLiteral,
        Type_Null,
        Type_List,
        Type_Map,
        Type_Identifier,
        Type_IdentifierString = 17,

        Type_FunctionCall,
        Type_LogicalExpression
    };
    enum Operator {
        AssignementOperator,
        AssignementAdditionOperator,
        AssignementSubstractionOperator,
        AssignementUniqueAdditionOperator,
        AndOperator,
        OrOperator,
        NotOperator,
        OperatorNone
    };

    inline Node()
        :line(0), pos(0){
    }

    virtual ~Node(){
    }

    int  line,pos;
    Type type;
    QString file;
};

struct StatementNode : public Node {
    StatementNode(){
        type = Type_Statement;
    }
    virtual ~StatementNode(){}
};

struct IncludeStatementNode : public StatementNode {
    IncludeStatementNode(const QString & path)
        :path(path), executed(false){
        type = Type_Include;
    }
    virtual ~IncludeStatementNode(){}
    QString path;
    bool executed;
};

struct StatementListNode : public Node {
    StatementListNode(StatementNode* node = 0){
        this->node = node;
        next = this;
        type = Type_Statements;
    }

    StatementListNode(StatementListNode* previous, StatementNode* node){
           this->node = node;
           type = Type_Statements;
           next = previous->next;
           previous->next = this;
    }

    virtual ~StatementListNode(){
        delete node;
        if(this->next != this)
            delete next;
    }

    StatementNode  *node;
    StatementListNode *next;
};

struct ExpressionNode : public Node {
};

struct OperatorNode : public Node {
    OperatorNode(Operator op){
        type = Type_Operator;
        this->op = op;
    }

    Operator op;
};

struct LExprepressionNode : public ExpressionNode {

};

struct IdentifierNode : public LExprepressionNode {
    IdentifierNode(IdentifierNode* previous, const QString & name){
        type = Type_Identifier;
        this->name = name;
        this->next = previous->next;
        previous->next = this;
    }

    IdentifierNode(const QString & name){
        type = Type_Identifier;
        this->name = name;
        this->next = this;
    }

    virtual ~IdentifierNode(){
        if(next!=this)
            delete next;
    }

    IdentifierNode* next;
    QString name;
};

struct IdentifierStringNode : IdentifierNode {
public:
    IdentifierStringNode(IdentifierNode* previous, const QString & name)
        :IdentifierNode(previous, name) {

        type = Type_IdentifierString;
    }

    IdentifierStringNode(const QString & name)
        :IdentifierNode(name) {

        type = Type_IdentifierString;
    }
};

struct UnsetStatementNode : public StatementNode {
    UnsetStatementNode(IdentifierNode* identifier)
        :identifier(identifier){
        type = Type_Unset;
    }
    virtual ~UnsetStatementNode(){
        delete identifier;
    }
    IdentifierNode* identifier;
};

struct AssignementNode : public ExpressionNode {
    AssignementNode(IdentifierNode* id, OperatorNode* op, ExpressionNode* value)
        :id(id), op(op), value(value){
        type = Type_Assignement;
    }

    virtual ~AssignementNode(){
        delete id;
        delete op;
        delete value;
    }

    IdentifierNode* id;
    OperatorNode* op;
    ExpressionNode* value;
};

struct AssignementStatementNode : public StatementNode {
    AssignementStatementNode(AssignementNode* node)
        :node(node){
         type = Type_Assignement;
    }
    virtual ~AssignementStatementNode(){
        delete node;
    }
    AssignementNode* node;
};

struct StringLiteralNode : public ExpressionNode {
    StringLiteralNode(const QString & s):
        value(s){
        type = Type_StringLiteral;
    }

    QString value;
};

struct NumericLiteralNode : public ExpressionNode {
    NumericLiteralNode(double d):
        value(d){
        type = Type_NumericLiteral;
    }

    double value;
};

struct BooleanLiteralNode : public ExpressionNode {
    BooleanLiteralNode(bool b):
        value(b){
        type = Type_BooleanLiteral;
    }

    bool value;
};

struct NullNode : public ExpressionNode {
    NullNode(){
        type = Type_Null;
    }
};
struct ListElementNode : public Node {
    ListElementNode(ListElementNode* previous, ExpressionNode* value){
        this->next  = previous->next;
        previous->next = this;
        this->value = value;
        type = Type_List;
    }

    ListElementNode(ExpressionNode* value){
        if(this->next != this)
            this->next  = this;

        this->value = value;
        type = Type_List;
    }

    virtual ~ListElementNode(){
        delete next;
        delete value;
    }

    ListElementNode* next;
    ExpressionNode* value;
};
struct ListNode : public ExpressionNode {
    ListNode(ListElementNode* node = 0){
        nodes = node;
        type = Type_List;
    }

    virtual ~ListNode(){
        delete nodes;
    }

    ListElementNode* nodes;
};

struct MapElementNode : public Node {
    MapElementNode(MapElementNode* previous, IdentifierNode* key, ExpressionNode* value){
        this->next  = previous->next;
        previous->next = this;
        this->key = key;
        this->value = value;
        type = Type_Map;
    }

    MapElementNode(IdentifierNode* key, ExpressionNode* value){
        this->next  = this;
        this->key   = key;
        this->value = value;
        type = Type_Map;
    }

    virtual ~MapElementNode(){
        if(next != this)
            delete next;
        delete value;
        delete key;
    }

    MapElementNode* next;
    ExpressionNode* value;
    IdentifierNode* key;
};

struct MapNode : public ExpressionNode {
    MapNode(MapElementNode* node = 0){
        nodes = node;
        type = Type_Map;
    }

    virtual ~MapNode(){
        delete nodes;
    }

    MapElementNode* nodes;
};

struct MapStatementNode : public StatementNode {
    MapStatementNode(MapNode* map)
        :map(map){
        type = Type_Map;
    }
    virtual ~MapStatementNode(){
        delete map;
    }
    MapNode* map;
};

struct FunctionCallNode : public ExpressionNode {
    FunctionCallNode(const QString & name, ListElementNode* parameters = 0)
        :name(name), parameters(parameters){
         type = Type_FunctionCall;
    }

    virtual ~FunctionCallNode(){
        delete parameters;
    }

    QString name;
    ListElementNode* parameters;
};

struct FunctionCallStatementNode : public StatementNode {
    FunctionCallStatementNode(FunctionCallNode* funct)
        :funct(funct){
         type = Type_FunctionCall;
    }
    virtual ~FunctionCallStatementNode(){
        delete funct;
    }
    FunctionCallNode* funct;
};

struct LogicalExpressionNode : public ExpressionNode {
    LogicalExpressionNode(ExpressionNode* node, ExpressionNode* next = 0, Node::Operator op = OperatorNone)
        :condition(node), next(next), op(op){
        type = Type_LogicalExpression;
    }

    virtual ~LogicalExpressionNode(){
        delete condition;
        delete next;
    }

    ExpressionNode* condition;
    ExpressionNode* next;
    Operator op;
};

struct IfStatementNode : public StatementNode {
    IfStatementNode(ExpressionNode* condition, StatementListNode* block, StatementListNode* alternative_block = 0)
        :condition(condition), block(block), alternative_block(alternative_block){
         type = Type_IfStatement;
    }

    virtual ~IfStatementNode(){
        delete condition;
        delete block;
        delete alternative_block;
    }

    ExpressionNode* condition;
    StatementListNode* block;
    StatementListNode* alternative_block;
};

struct RootNode : public Node {

    RootNode(StatementListNode* nodes):
        nodes(nodes){
        type = Type_Source;
    }

    virtual ~RootNode(){
        delete nodes;
    }

    StatementListNode* nodes;
};


template <typename NodeType> NodeType* makeAstNode(){
    return new NodeType();
}
template <typename NodeType, typename Arg1> NodeType* makeAstNode(Arg1 arg1){
    return new NodeType(arg1);
}
template <typename NodeType, typename Arg1, typename Arg2> NodeType* makeAstNode(Arg1 arg1, Arg2 arg2){
    return new NodeType(arg1, arg2);
}
template <typename NodeType, typename Arg1,typename Arg2, typename Arg3> NodeType* makeAstNode(Arg1 arg1, Arg2 arg2, Arg3 arg3){
    return new NodeType(arg1, arg2, arg3);
}

template <typename NodeType> NodeType* finish(NodeType* node){
    if(!node)
        return 0;
    NodeType* front = node->next;
    node->next = 0;
    return front;
}
}

#endif // CONFIGURATIONPARSERAST_H
