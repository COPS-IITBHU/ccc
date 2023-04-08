#ifndef COMPILER_PARSER_H
#define COMPILER_PARSER_H

#include <stddef.h>
#include <error.h>

typedef struct Environment Environment;

typedef struct Token
{
  char *beginning;
  char *end;
} Token;

void print_token(Token t);
Error lex(char *source, Token *token);

typedef enum NodeType
{

  NODE_TYPE_NONE = 0,

  NODE_TYPE_INTEGER,

  NODE_TYPE_SYMBOL,

  NODE_TYPE_FUNCTION,

  NODE_TYPE_FUNCTION_CALL,

  NODE_TYPE_VARIABLE_DECLARATION,

  NODE_TYPE_VARIABLE_DECLARATION_INITIALIZED,

  NODE_TYPE_VARIABLE_REASSIGNMENT,

  NODE_TYPE_BINARY_OPERATOR,

  NODE_TYPE_PROGRAM,

  NODE_TYPE_MAX,
} NodeType;

typedef struct Node
{
  int type;
  union NodeValue
  {
    long long integer;
    char *symbol;
  } value;
  struct Node *children;
  struct Node *next_child;

  int result_register;
} Node;

Node *node_allocate();

#define nonep(node) ((node).type == NODE_TYPE_NONE)
#define integerp(node) ((node).type == NODE_TYPE_INTEGER)
#define symbolp(node) ((node).type == NODE_TYPE_SYMBOL)

void node_add_child(Node *parent, Node *new_child);

int node_compare(Node *a, Node *b);

Node *node_integer(long long value);

Node *node_symbol(char *symbol_string);

Node *node_symbol_from_buffer(char *buffer, size_t length);

void print_node(Node *node, size_t indent_level);

void node_free(Node *root);

void node_copy(Node *a, Node *b);

int token_string_equalp(char *string, Token *token);

int parse_integer(Token *token, Node *node);

typedef struct ParsingStack
{
  struct ParsingStack *parent;
  Node *operator;
  Node *result;
} ParsingStack;

typedef struct ParsingContext
{
  struct ParsingContext *parent;

  Node *operator;
  Node *result;
  Environment *types;

  Environment *variables;

  Environment *functions;

  Environment *binary_operators;
} ParsingContext;

Error define_binary_operator(ParsingContext *context,
                             char *operator,
                             int precedence,
                             char *return_type, char *lhs_type, char *rhs_type);

Error parse_get_type(ParsingContext *context, Node *id, Node *result);

ParsingContext *parse_context_create(ParsingContext *parent);
ParsingContext *parse_context_default_create();

Error parse_program(char *filepath, ParsingContext *context, Node *result);

Error parse_expr(ParsingContext *context,
                 char *source, char **end,
                 Node *result);

#endif /* COMPILER_PARSER_H */
