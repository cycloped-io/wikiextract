// Copyright 2007-2012 Wincent Colaiuta. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
//    this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#include <stdbool.h>
#include <ruby.h>
#include <ruby/io.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include "parser.h"
#include "wikitext_ragel.h"

#define IN(type) ary_includes(parser->scope, type)
#define IN_EITHER_OF(type1, type2) ary_includes2(parser->scope, type1, type2)
#define IN_ANY_OF(type1, type2, type3) ary_includes3(parser->scope, type1, type2, type3)


const char * space_type = "space";
const char * printable_type = "print";
const char * num_type = "num";
const char * alnum_type = "alnum";
const char * crlf_type = "crlf";

void finish_link1(int * s1_size,int * s2_size, token_t * stack1, token_t * stack2,
    FILE * file_p1, FILE * file_p2,int doc_id){
  const char * type;
  int offset, buf_size;
  char * buf;
  if(*s1_size == 0 || *s2_size == 0)
    return;
  //printf("%i %i %i\n",*s1_size,stack1[0].start,stack1[*s1_size-1].stop);
  //printf("%i %i %i\n",*s2_size,stack2[0].start,stack2[*s2_size-1].stop);
  fprintf(file_p2,"%i\t%li\t%li\t",
      doc_id,
      (long)stack2[0].start,
      (long)stack1[*s1_size-1].stop);

  offset = 0;
  buf_size = stack2[*s2_size-1].stop-stack2[0].start+1;
  buf = malloc(sizeof(char)*buf_size);
  for(int i = 0; i < *s2_size; i++){
    if(stack2[i].type == CRLF) {
      strncpy(buf+offset,"\\n",2);
      offset += 2;
    } else {
      strncpy(buf+offset,stack2[i].start,stack2[i].stop-stack2[i].start);
      offset += stack2[i].stop-stack2[i].start;
    }
  }
  buf[offset] = 0;
  fprintf(file_p2,"%s\t",buf);
  free(buf);

  buf_size = 1;
  for(int i = 0; i < *s1_size; i++)
    buf_size += stack1[i].stop-stack1[i].start;
  buf = malloc(sizeof(char)*buf_size);
  offset = 0;
  for(int i = 0; i < *s1_size; i++){
    type = NULL;
    switch(stack1[i].type) {
      case SPACE : 
        type = space_type;
      case PRINTABLE :
        if(type == NULL)
          type = printable_type;
      case NUM : 
        if(type == NULL)
          type = num_type;
      case ALNUM :
        if(type == NULL)
          type = alnum_type;
      default :
        if(type == NULL)
          type = alnum_type;
        wikitext_print_token(&(stack1[i]),file_p1,doc_id,type);
        strncpy(buf+offset,stack1[i].start,stack1[i].stop-stack1[i].start);
        offset += stack1[i].stop-stack1[i].start;
      break;
      case CRLF :
        //wikitext_print_crlf(&(stack1[i]),file_p1,doc_id); 
      break;
    }
  }
  buf[offset] = 0;
  fprintf(file_p2,"%s\n",buf);
  free(buf);

  (*s1_size) = 0;
  (*s2_size) = 0;
}

void finish_link(int * s1_size,int * s2_size, token_t * stack1, 
  token_t * stack2, FILE * file_p1, FILE * file_p2,int doc_id, token_t * last_token){
  if(*s1_size <= 0 || *s2_size <= 0 || last_token == 0)
    return;
  char * buf;
  int size1 = stack1[*s1_size-1].stop-stack1[*s1_size-1].start;
  int size2 = last_token->stop-last_token->start;
  buf = malloc(sizeof(char)*(size1 + size2 + 1));
  strncpy(buf,stack1[*s1_size-1].start,size1);
  strncpy(buf + size1,last_token->start,size2);
  buf[size1+size2] = 0;

  stack1[*s1_size-1].start = buf;
  stack1[*s1_size-1].stop = buf + size1 + size2;
  stack1[*s1_size-1].line_stop = last_token->line_stop;
  stack1[*s1_size-1].column_stop = last_token->column_stop;
  finish_link1(s1_size,s2_size,stack1,stack2,file_p1,file_p2,doc_id);
  free(buf);
}

// output styles
enum { HTML_OUTPUT, XML_OUTPUT };

// for testing and debugging only
VALUE Wikitext_parser_tokenize(VALUE self, VALUE string, VALUE file1, VALUE file2,
    VALUE doc_id_v)
{
    if (NIL_P(string))
        return Qnil;
    int doc_id = FIX2INT(doc_id_v);

    rb_io_t * file_p_struct;
    Check_Type(file1,T_FILE);
    rb_io_binmode(file1);
    GetOpenFile(file1,file_p_struct);
    rb_io_check_writable(file_p_struct);
    FILE * file_p1 = rb_io_stdio_file(file_p_struct);

    Check_Type(file2,T_FILE);
    rb_io_binmode(file2);
    GetOpenFile(file2,file_p_struct);
    rb_io_check_writable(file_p_struct);
    FILE * file_p2 = rb_io_stdio_file(file_p_struct);


    string = StringValue(string);
    VALUE tokens = rb_ary_new();
    char *p = RSTRING_PTR(string);
    long len = RSTRING_LEN(string);
    char *pe = p + len;
    const char *type = NULL;
    int state = DEFAULT;
    int ts[1000];
    int ss[1000];
    int ts_size = 1 ;
    int ss_size = 1 ;
    ss[0] = 0;
    ts[0] = 0;
    token_t token;
    token_t stack1[1000]; //tail, TODO add checks 
    token_t stack2[1000]; //head, TODO add checks
    int s1_size = 0;
    int s2_size = 0;
    int start = 1;

    do
    {
        //printf("%i %i\n",s1_size,s2_size);
        if(start) {
          next_token(&token, NULL, p, pe, ts, ss, &ts_size, &ss_size, file_p1, doc_id);
          start = 0;
        } else {
          next_token(&token, &token, NULL, pe, ts, ss, &ts_size, &ss_size, file_p1, doc_id);
        }
        //rb_funcall(rb_mKernel, rb_intern("puts"), 1, wiki_token(&token));
        if(token.type == END_OF_FILE){
          if(state == POST_LINK) {
            finish_link1(&s1_size,&s2_size,stack1,stack2,file_p1,file_p2,doc_id);
          }
          break;
        }
        switch(token.type) {
          case SEPARATOR :
            memcpy(stack2,stack1,sizeof(token_t)*s1_size);
            s2_size = s1_size;
            s1_size = 0;
            state = SEPARATOR;
          break;
          case LINK_START :
            state = LINK;
          break;
          case LINK_END :
            if(state != SEPARATOR) {
              memcpy(stack2,stack1,sizeof(token_t)*s1_size);
              s2_size = s1_size;
            }
            state = POST_LINK;
          break;
          case EXT_LINK_START :
            state = EXT_LINK;
          break;
          case EXT_LINK_END : 
            // TODO print what should be printed
            s1_size = 0;
            s2_size = 0;
          break;
          case ALNUM :
            if(state == POST_LINK){
              finish_link(&s1_size,&s2_size,stack1,stack2,file_p1,file_p2,doc_id,&token);
              state = DEFAULT;
            } else {
              if(s1_size < 1000)
                memcpy(&(stack1[s1_size++]),&token,sizeof(token_t));
              else
                printf("[%i]Token stack overflow\n",doc_id);
            }
          break;
          case SPACE :
            type = space_type;
          case PRINTABLE :
          case DEFAULT :
            if(type == NULL) type = printable_type;
          case NUM :
            if(type == NULL) type = num_type;
            if(state == POST_LINK) {
              finish_link1(&s1_size,&s2_size,stack1,stack2,file_p1,file_p2,doc_id);
              wikitext_print_token(&token,file_p1,doc_id,type);
              state = DEFAULT;
            } else {
              if(s1_size < 1000)
                memcpy(&(stack1[s1_size++]),&token,sizeof(token_t));
              else
                printf("[%i]Token stack overflow\n",doc_id);
            }
          break;
          case CRLF :
            if(state == POST_LINK){
              finish_link1(&s1_size,&s2_size,stack1,stack2,file_p1,file_p2,doc_id);
              wikitext_print_crlf(&token,file_p1,doc_id); 
              state = DEFAULT;
            } else {
              if(s1_size < 1000)
                memcpy(&(stack1[s1_size++]),&token,sizeof(token_t));
              else
                printf("[%i]Token stack overflow\n",doc_id);
            }
          break;
          case SKIP :
            if(state == POST_LINK){
              finish_link1(&s1_size,&s2_size,stack1,stack2,file_p1,file_p2,doc_id);
              state = DEFAULT;
            }
          break;
        }
        type = NULL;
    } while(1);
    return tokens;
}

VALUE Wikitext_parser_flush(VALUE self,VALUE file){
  rb_io_t * file_p_struct;
  FILE * file_p;
  Check_Type(file,T_FILE);
  rb_io_binmode(file);
  GetOpenFile(file,file_p_struct);
  file_p = rb_io_stdio_file(file_p_struct);
  fflush(file_p);
  return Qnil;
}
