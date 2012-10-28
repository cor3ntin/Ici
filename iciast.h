#ifndef _ICIAST_H
#define _ICIAST_H

namespace ICI{
namespace AST{

class Node
{
public:
    enum Type {
        Type_Node,
        Type_Expression,

        Type_Numeric,
        Type_String,
        Type_List,
        Type_Identifier,
        Type_ArgumentList
    };
    inline Node()
        :m_line(0), m_pos(0), m_left(0), m_right(0){
    }
private:
    int m_line,m_pos;
    Node* m_left;
    Node* m_right;
};


}
}
#endif // CONFIGURATIONPARSERAST_H
