// Copyright 2008-2009 Wincent Colaiuta. All rights reserved.
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

#include "wikitext_ragel.h"
#include "wikitext.h"
#include "parser.h"

VALUE mWikitext              = 0;   // module Wikitext
VALUE cWikitextParser        = 0;   // class Wikitext::Parser
VALUE eWikitextParserError   = 0;   // class Wikitext::Parser::Error
VALUE cWikitextParserToken   = 0;   // class Wikitext::Parser::Token

void wikitext_print_token(token_t * token,FILE * file_p,int doc_id, const char * type){
  fprintf(file_p,"%i\t%i\t%i\t%i\t%i\t%s\t",doc_id,
      (int)token->line_start, (int)token->line_stop,
      (int)token->column_start,(int)token->column_stop,type); 
  fwrite(token->start,1,token->stop-token->start,file_p); 
  fprintf(file_p,"\n");
}

void wikitext_print_crlf(token_t * token,FILE * file_p, int doc_id){
  fprintf(file_p,"%i\t%i\t%i\t%i\t%i\tcrlft\t\\n",doc_id,
      (int)token->line_start, (int)token->line_stop,
      (int)token->column_start,(int)token->column_stop); 
  fprintf(file_p,"\n");
}

void Init_wikitext()
{
    // Wikitext
    mWikitext = rb_define_module("Wikitext");

    // Wikitext::Parser
    cWikitextParser = rb_define_class_under(mWikitext, "Parser", rb_cObject);
    rb_define_method(cWikitextParser, "tokenize", Wikitext_parser_tokenize, 4);
    rb_define_method(cWikitextParser, "flush_internal", Wikitext_parser_flush, 1);

    // Wikitext::Parser::Error
    eWikitextParserError = rb_define_class_under(cWikitextParser, "Error", rb_eException);

    // Wikitext::Parser::Token
    cWikitextParserToken = rb_define_class_under(cWikitextParser, "Token", rb_cObject);
    rb_define_singleton_method(cWikitextParserToken, "types", Wikitext_parser_token_types, 0);
    rb_define_attr(cWikitextParserToken, "start", Qtrue, Qfalse);
    rb_define_attr(cWikitextParserToken, "stop", Qtrue, Qfalse);
    rb_define_attr(cWikitextParserToken, "line_start", Qtrue, Qfalse);
    rb_define_attr(cWikitextParserToken, "line_stop", Qtrue, Qfalse);
    rb_define_attr(cWikitextParserToken, "column_start", Qtrue, Qfalse);
    rb_define_attr(cWikitextParserToken, "column_stop", Qtrue, Qfalse);
    rb_define_attr(cWikitextParserToken, "code_point", Qtrue, Qfalse);
    rb_define_attr(cWikitextParserToken, "token_type", Qtrue, Qfalse);
    rb_define_attr(cWikitextParserToken, "string_value", Qtrue, Qfalse);
}
