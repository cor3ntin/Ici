#ifndef _ICIAST_H
#define _ICIAST_H

#include "iciast_fwd.h"
#include <QString>
#include <QStringList>

namespace ICI{

struct Node
{
    enum Type {
        Type_Node,
        Type_Source,
        Type_Statements,
        Type_Statement,
        Type_IfStatement,

        Type_Assignement,
        Type_Operator,

        Type_Expression,
        Type_NumericLiteral,
        Type_StringLiteral,
        Type_List,
        Type_Identifier,

        Type_FunctionCall,
        Type_LogicalExpression
    };
    enum Operator {
        AssignementOperator,
        AssignementAdditionOperator,
        AssignementSubstractionOperator,
        AndOperator,
        OrOperator,
        NotOperator,
        OperatorNone,
    };

    inline Node()
        :line(0), pos(0){
    }
    virtual ~Node(){}

    int  line,pos;
    Type type;
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
    virtual ~StatementListNode(){}

    StatementNode  *node;
    StatementListNode *next;
};

struct StatementNode : public Node {
    StatementNode(){
        type = Type_Statement;
    }
    virtual ~StatementNode(){}
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

struct IdentifierNode : public ExpressionNode {
    IdentifierNode(IdentifierNode* previous){
        type = Type_Identifier;
        this->next = previous->next;
        previous->next = this;
        this->name = previous->name;
        previous->name.clear();
    }
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
    QStringList keys() const {
        QStringList k;
        keys(k);
        return k;
    }
    void keys(QStringList & k) const {
        k << name;
        if(next && next !=this)
            next->keys(k);
    }

    IdentifierNode* next;
    QString name;
};

struct AssignementNode : public StatementNode {
    AssignementNode(IdentifierNode* id, OperatorNode* op, ExpressionNode* value)
        :id(id), op(op), value(value){
        type = Type_Assignement;
    }
    IdentifierNode* id;
    OperatorNode* op;
    ExpressionNode* value;
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

struct ListElementNode : public Node {
    ListElementNode(ListElementNode* previous, ExpressionNode* value){
        this->next  = previous->next;
        previous->next = this;
        this->value = value;
        type = Type_List;
    }
    ListElementNode(ExpressionNode* value){
        this->next  = this;
        this->value = value;
        type = Type_List;
    }

    ListElementNode* next;
    ExpressionNode* value;
};
struct ListNode : public ExpressionNode {
    ListNode(ListElementNode* node = 0){
        nodes = node;
        type = Type_List;
    }
    ListElementNode* nodes;
};

struct FunctionCallNode : public ExpressionNode {
    FunctionCallNode(const QString & name, ListElementNode* parameters = 0)
        :name(name), parameters(parameters){
         type = Type_FunctionCall;
    }
    QString name;
    ListElementNode* parameters;
};

struct LogicalExpressionNode : public ExpressionNode {
    LogicalExpressionNode(ExpressionNode* node, LogicalExpressionNode* next = 0, Node::Operator op = OperatorNone)
        :condition(node), next(next), op(op){
        type = Type_LogicalExpression;

    }
    ExpressionNode* condition;
    LogicalExpressionNode* next;
    Operator op;
};

struct IfStatementNode : public StatementNode {
    IfStatementNode(LogicalExpressionNode* condition, StatementListNode* block, StatementListNode* alternative_block = 0)
        :condition(condition), block(block), alternative_block(alternative_block){
         type = Type_IfStatement;

    }
    LogicalExpressionNode* condition;
    StatementListNode* block;
    StatementListNode* alternative_block;
};

struct RootNode : public Node {

    RootNode(StatementListNode* nodes):
        nodes(nodes){
        type = Type_Source;
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
