#ifndef CODEGEN_H
#define CODEGEN_H

#include <environment.h>
#include <error.h>
#include <parser.h>

typedef int RegisterDescriptor;

typedef struct Register
{
  struct Register *next;
  char *name;
  char in_use;
} Register;

Register *register_create(char *name);

void register_add(Register *base, char *name);

void register_free(Register *base);

RegisterDescriptor register_allocate(Register *base);
void register_deallocate(Register *base, RegisterDescriptor register_descriptor);

char *register_name(Register *base, RegisterDescriptor register_descriptor);

char *label_generate();

typedef struct CodegenContext
{
  struct CodegenContext *parent;
  Environment *locals;
} CodegenContext;

enum CodegenOutputFormat
{
  CG_FMT_DEFAULT = 0,
  CG_FMT_x86_64_MSWIN,
};

Error codegen_program(enum CodegenOutputFormat, ParsingContext *context, Node *program);

#endif /* CODEGEN_H */
