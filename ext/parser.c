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

#include "parser.h"
#include "wikitext.h"
#include "wikitext_ragel.h"

#define IN(type) ary_includes(parser->scope, type)
#define IN_EITHER_OF(type1, type2) ary_includes2(parser->scope, type1, type2)
#define IN_ANY_OF(type1, type2, type3) ary_includes3(parser->scope, type1, type2, type3)

// output styles
enum { HTML_OUTPUT, XML_OUTPUT };

// for testing and debugging only
VALUE Wikitext_parser_tokenize(VALUE self, VALUE string, VALUE file, VALUE doc_id)
{
    if (NIL_P(string))
        return Qnil;

    rb_io_t * file_p_struct;
    Check_Type(file,T_FILE);
    rb_io_binmode(file);
    GetOpenFile(file,file_p_struct);
    rb_io_check_writable(file_p_struct);
    FILE * file_p = rb_io_stdio_file(file_p_struct);


    string = StringValue(string);
    VALUE tokens = rb_ary_new();
    char *p = RSTRING_PTR(string);
    long len = RSTRING_LEN(string);
    char *pe = p + len;
    int ts[100]; //TODO add checks
    int ss[100]; //TODO add checks
    int ts_size = 1 ;
    int ss_size = 1 ;
    ss[0] = 0;
    ts[0] = 0;
    token_t token;
    next_token(&token, NULL, p, pe, ts, ss, &ts_size, &ss_size, file_p, FIX2INT(doc_id));
    if(token.type != SKIP){
      rb_ary_push(tokens, wiki_token(&token));
    }
    while (token.type != END_OF_FILE)
    {
        next_token(&token, &token, NULL, pe, ts, ss, &ts_size, &ss_size, file_p, 
            FIX2INT(doc_id));
        if(token.type != SKIP){
          rb_ary_push(tokens, wiki_token(&token));
        }
    }
    return tokens;
}
