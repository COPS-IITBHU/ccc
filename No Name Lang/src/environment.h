#ifndef COMPILER_ENVIRONMENT_H
#define COMPILER_ENVIRONMENT_H

typedef struct Node Node;

typedef struct Binding
{
  Node *id;
  Node *value;
  struct Binding *next;
} Binding;

typedef struct Environment
{
  struct Environment *parent;
  Binding *bind;
} Environment;

Environment *environment_create(Environment *parent);

int environment_set(Environment *env, Node *id, Node *value);

int environment_get(Environment env, Node *id, Node *result);

int environment_get_by_symbol(Environment env, char *symbol, Node *result);

#endif /* COMPILER_ENVIRONMENT_H */
