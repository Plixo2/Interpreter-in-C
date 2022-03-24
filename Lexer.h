//
// Created by Mo on 24.03.2022.
//

#ifndef DATA_PROCESSING_INTERMEDIATE_LEXER_H
#define DATA_PROCESSING_INTERMEDIATE_LEXER_H

#include "Tokenizer.h"
#include "IterableStream.h"
#include "DPI_Syntax.h"


struct Node {
    uint8_t lex_type = 0;
    std::string data;
    Node *left = nullptr;
    Node *right = nullptr;
};

#define TOKEN token_stream->current()
#define TYPE token_stream->current().type
#define match(_type) if(token_stream->current().type == (_type).type)
//#define alternative(_type) else if(token_stream->current().type == (_type).type)
#define NEXT next()
#define AS(type) std::string (type) = token_stream->current().raw_string
#define expect(str) else { throw (str);}
#define RET  return new Node
#define THEN(name) Node *name = this->name()
#define ASSERT(_type) if((_type).type != token_stream->current().type) { throw "Failed Assertion"; }
#define WHILE_NOT(_type, to_call , name) \
                  Node * (name) = to_call;       \
while(token_stream->current().type != (_type).type) { \
    (name) = to_call;      \
    NEXT;\
}

class Lexer {
private:
    IterableStream *token_stream;
public:
    Lexer(IterableStream *token_stream) : token_stream(token_stream) {

    }

    void next() {
        token_stream->consume();
    }

    Node *expression() {
        match(Syntax::PARENTHESES_OPEN) {
            NEXT;
            WHILE_NOT(Syntax::PARENTHESES_CLOSED, expression() , exp);
            RET {LexNode::ST};
        } else match(Syntax::NUMBER) {

        } expect("1 or 2");
    }

    Node *statement() {
        match(Syntax::BRACES_OPEN) {
            NEXT;
            THEN(statement);
            match(Syntax::BRACES_CLOSED) {
                return statement;
            }

        } else match(Syntax::IDENTIFIER) {
            AS(ID);
            NEXT;
            match(Syntax::ASSIGN) {
                NEXT;
                THEN(expression);
                RET{LexNode::ASSIGN_STATEMENT, "1", new Node{LexNode::IDENTIFIER, ID}, expression};
            }
        } expect("1 or 2")
    }


};


#endif //DATA_PROCESSING_INTERMEDIATE_LEXER_H
