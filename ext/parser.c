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

#include "parser.h"
#include "wikitext.h"
#include "wikitext_ragel.h"

#define IN(type) ary_includes(parser->scope, type)
#define IN_EITHER_OF(type1, type2) ary_includes2(parser->scope, type1, type2)
#define IN_ANY_OF(type1, type2, type3) ary_includes3(parser->scope, type1, type2, type3)

// output styles
enum { HTML_OUTPUT, XML_OUTPUT };

const char null_str[]                   = { 0 };
const char escaped_no_wiki_start[]      = "&lt;nowiki&gt;";
const char escaped_no_wiki_end[]        = "&lt;/nowiki&gt;";
const char literal_strong_em[]          = "'''''";
const char literal_strong[]             = "'''";
const char literal_em[]                 = "''";
const char escaped_em_start[]           = "&lt;em&gt;";
const char escaped_em_end[]             = "&lt;/em&gt;";
const char escaped_strong_start[]       = "&lt;strong&gt;";
const char escaped_strong_end[]         = "&lt;/strong&gt;";
const char escaped_tt_start[]           = "&lt;tt&gt;";
const char escaped_tt_end[]             = "&lt;/tt&gt;";
const char pre_start[]                  = "<pre>";
const char pre_end[]                    = "</pre>";
const char escaped_pre_start[]          = "&lt;pre&gt;";
const char escaped_pre_end[]            = "&lt;/pre&gt;";
const char blockquote_start[]           = "<blockquote>";
const char blockquote_end[]             = "</blockquote>";
const char escaped_blockquote_start[]   = "&lt;blockquote&gt;";
const char escaped_blockquote_end[]     = "&lt;/blockquote&gt;";
const char strong_em_start[]            = "<strong><em>";
const char strong_start[]               = "<strong>";
const char strong_end[]                 = "</strong>";
const char em_start[]                   = "<em>";
const char em_end[]                     = "</em>";
const char code_start[]                 = "<code>";
const char code_end[]                   = "</code>";
const char ol_start[]                   = "<ol>";
const char ol_end[]                     = "</ol>";
const char ul_start[]                   = "<ul>";
const char ul_end[]                     = "</ul>";
const char li_start[]                   = "<li>";
const char li_end[]                     = "</li>";
const char h6_start[]                   = "<h6>";
const char h6_end[]                     = "</h6>";
const char h5_start[]                   = "<h5>";
const char h5_end[]                     = "</h5>";
const char h4_start[]                   = "<h4>";
const char h4_end[]                     = "</h4>";
const char h3_start[]                   = "<h3>";
const char h3_end[]                     = "</h3>";
const char h2_start[]                   = "<h2>";
const char h2_end[]                     = "</h2>";
const char h1_start[]                   = "<h1>";
const char h1_end[]                     = "</h1>";
const char p_start[]                    = "<p>";
const char p_end[]                      = "</p>";
const char space[]                      = " ";
const char a_start[]                    = "<a href=\"";
const char a_class[]                    = "\" class=\"";
const char a_rel[]                      = "\" rel=\"";
const char a_start_close[]              = "\">";
const char a_end[]                      = "</a>";
const char link_start[]                 = "[[";
const char link_end[]                   = "]]";
const char separator[]                  = "|";
const char ext_link_start[]             = "[";
const char backtick[]                   = "`";
const char quote[]                      = "\"";
const char ampersand[]                  = "&";
const char quot_entity[]                = "&quot;";
const char amp_entity[]                 = "&amp;";
const char lt_entity[]                  = "&lt;";
const char gt_entity[]                  = "&gt;";
const char escaped_blockquote[]         = "&gt; ";
const char ext_link_end[]               = "]";
const char literal_img_start[]          = "{{";
const char img_start[]                  = "<img src=\"";
const char img_end_xml[]                = "\" />";
const char img_end_html[]               = "\">";
const char img_alt[]                    = "\" alt=\"";
const char pre_class_start[]            = "<pre class=\"";
const char pre_class_end[]              = "-syntax\">";

// for testing and debugging only
VALUE Wikitext_parser_tokenize(VALUE self, VALUE string)
{
    if (NIL_P(string))
        return Qnil;
    string = StringValue(string);
    VALUE tokens = rb_ary_new();
    char *p = RSTRING_PTR(string);
    long len = RSTRING_LEN(string);
    char *pe = p + len;
    token_t token;
    next_token(&token, NULL, p, pe);
    rb_ary_push(tokens, wiki_token(&token));
    while (token.type != END_OF_FILE)
    {
        next_token(&token, &token, NULL, pe);
        rb_ary_push(tokens, wiki_token(&token));
    }
    return tokens;
}
