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

//----------------------------------------------------------------------//
// NOTE: wikitext_ragel.c is generated from wikitext_ragel.rl, so       //
//       if you make changes to the former they will be overwritten.    //
//       You should perform all your edits in wikitext_ragel.rl.        //
//----------------------------------------------------------------------//

#include "wikitext_ragel.h"
#include "wikitext.h"
#include <stdio.h>
#include <string.h>

#define EMIT(t)     do { out->type = t; out->stop = p + 1; out->column_stop += (out->stop - out->start); } while (0)
#define MARK()      do { mark = p; } while (0)
#define REWIND()    do { p = mark; } while (0)
#define AT_END()    (p + 1 == pe)
#define DISTANCE()  (p + 1 - ts)
#define NEXT_CHAR() (*(p + 1))
#define PRINT_STACK() do {printf("%i %i %i %i\n",token_stack[(*token_stack_size)-1], state_stack[(*state_stack_size)-1], *token_stack_size, *state_stack_size); } while(0)
#define PUSH(type,state) do { token_stack[(*token_stack_size)++] = type; state_stack[(*state_stack_size)++] = state; } while (0)
#define POP()       do { (*token_stack_size)--; (*state_stack_size)--; } while (0)
#define LAST_TYPE() ( token_stack[(*token_stack_size)-1] )
#define TODO()      do { } while (0)
#define ERROR(msg)  do { printf("[31;1m"); printf(msg); printf("[0m: "); strncpy(error_msg,out->start,p-out->start+1); error_msg[p-out->start+1] = 0; printf("%s\n",error_msg);} while (0)
#define GET_STATE() ( state_stack[(*state_stack_size)-1] )
#define DEBUG(msg)  do { printf(msg); printf("\n"); } while (0)


%%{
    machine wikitext;

    action mark
    {
        MARK();
    }

    action non_printable_ascii
    {
        out->code_point = *p & 0x7f;
    }

    action two_byte_utf8_sequence
    {
        out->code_point = ((uint32_t)(*(p - 1)) & 0x1f) << 6 |
            (*p & 0x3f);
    }

    action three_byte_utf8_sequence
    {
        out->code_point = ((uint32_t)(*(p - 2)) & 0x0f) << 12 |
            ((uint32_t)(*(p - 1)) & 0x3f) << 6 |
            (*p & 0x3f);
    }

    action four_byte_utf8_sequence
    {
        out->code_point = ((uint32_t)(*(p - 3)) & 0x07) << 18 |
            ((uint32_t)(*(p - 2)) & 0x3f) << 12 |
            ((uint32_t)(*(p - 1)) & 0x3f) << 6 |
            (*p & 0x3f);
    }

    # simple approximation for matching email addresses; not quite RFC 2822!
    user                = (alnum | [_\.] | '-')+ ;
    tld                 = alpha{2,5} ;
    domain              = (alnum+ '.')+ tld ;
    mail                = user '@' domain ;

    uri_chars           = (alnum | [@$&'(\*\+=%_~/#] | '-')+ ;
    special_uri_chars   = ([!\(\),\.\?])+ ;
    uri                 = ('mailto:'i mail) |
                          (('http'i [sS]? '://' | 'ftp://'i | 'svn://'i) uri_chars (special_uri_chars uri_chars)*) ;
    path                = '/' ([a-zA-Z0-9_\-.]+ '/'?)* ;

    main := |*

        ( '<nowiki>'i ) | ( '</nowiki>'i ) | ( '<blockquote>'i ) | ( '</blockquote>'i ) | 
        ( '<strong>'i ) | ( '</strong>'i ) | ( '<em>'i ) | ( '</em>'i ) | ( '`' ) | 
        ( '<tt>'i ) | ( '</tt>'i ) | uri | mail | '__NOTOC__'
        {
            EMIT(SKIP);
            fbreak;
        };

        ( '<pre>'i ) | ( '<pre lang="' alpha+ '">' ) | ( '<math>'i ) | ( '<timeline>'i ) |
        ( '<ref>'i ) | ( '<ref name=' [^\>]+ '>'i )
        {
            state = GET_STATE(); 
            switch(state){
              case BLIND :
              case BLIND_LINK :
              case INNER_LINK :
              case LINK :
              case DEFAULT :
                PUSH(PRE_START,NOWIKI);
              break;
              default :
                EMIT(SKIP);
                fbreak;
              break;
            }
        };

        ( '</pre>'i ) | ( '</math>'i ) | ( '</timeline>'i ) | ( '</ref>'i )
        {
            state = GET_STATE();
            switch(state){
              case NOWIKI :
                opening = LAST_TYPE();
                if(opening == PRE_START) {
                  POP(); 
                  EMIT(SKIP);
                  fbreak;
                }
              break;
              case BLIND :
              case BLIND_LINK :
              case INNER_LINK :
              case LINK :
              case DEFAULT :
                PRINT_STACK();
                ERROR("Closing token without opening token");
              break;
              default :
                EMIT(SKIP);
                fbreak;
              break;
            }
        };


        "'"{1,5}
        {
            if (DISTANCE() > 1) {
              EMIT(SKIP);
              fbreak;
            } else {
              if(GET_STATE() == DEFAULT) {
                EMIT(PRINTABLE);
                fbreak;
              }
            }
        };


        # shorthand for <blockquote> and </blockquote>
        '>' @mark ' '?
        {
            if (out->column_start == 1 || last_token_type == BLOCKQUOTE) {
              EMIT(SKIP);
              fbreak;
            } else {
              REWIND();
              state = GET_STATE();
              switch(state){
                case DEFAULT :
                  EMIT(PRINTABLE);
                  fbreak;
                break;
                case NOWIKI :
                  opening = LAST_TYPE();
                  if(opening == TAG_START) {
                    POP(); 
                    EMIT(SKIP);
                    fbreak;
                  }
                break;
                default :
                  ERROR("Closing token without opening token");
                  EMIT(SKIP);
                  fbreak;
                break;
              }
            }
        };

        # shorthand for <pre> and </pre>
        ' ' @mark ' '*
        {
            if (out->column_start == 1 || last_token_type == BLOCKQUOTE)
            {
                REWIND();
                EMIT(SKIP);
                fbreak;
            } else {
              state = GET_STATE();
              switch(state){
                case INNER_LINK :
                case LINK :
                  TODO(); // Push token
                  EMIT(SPACE);
                  fbreak;
                break;
                case DEFAULT :
                  EMIT(SPACE);
                  fbreak;
                break;
                default :
                  EMIT(SKIP);
                  fbreak;
                break;
              }
            }
        };

        ('#' | '*' | ';' | ':')+
        {
            if (out->column_start == 1 )
                EMIT(SKIP);
            else
              if(GET_STATE() == DEFAULT)
                EMIT(PRINTABLE);             
              else
                EMIT(SKIP);
            fbreak;
        };

        '='+ @mark ' '*
        {
            if (out->column_start == 1)
            {
                REWIND();
                if (DISTANCE() <= 6) {
                  if (GET_STATE() == DEFAULT){
                    EMIT(CRLF);
                    fbreak;
                  }
                } else {
                    p = ts + 6;
                    EMIT(SKIP);
                    fbreak;
                }
            }
            else if (AT_END() || NEXT_CHAR() == '\n' || NEXT_CHAR() == '\r')
            {
                REWIND();
                if (DISTANCE() <= 6) {
                  if (GET_STATE() == DEFAULT){
                    EMIT(CRLF);
                    fbreak;
                  } else {
                    EMIT(SKIP);
                    fbreak;
                  }
                } else {
                    p -= 6; // will scan the H6 on the next scan
                    if (GET_STATE() == DEFAULT){
                      EMIT(PRINTABLE);
                      fbreak;
                    }
                }
            }
            else
            {
                // note that a H*_END token will never match before a BLOCKQUOTE_END
                REWIND();
                if(GET_STATE() == DEFAULT)
                  EMIT(PRINTABLE);
                else
                  EMIT(SKIP);
                fbreak;
            }
        };

        
        '[[' (alpha | '-')* ':'
        {
            state = GET_STATE();
            switch(state){
              case BLIND :
              case BLIND_LINK :
              case INNER_LINK :
              case LINK :
              case DEFAULT :
                PUSH(SPECIAL_LINK_START,BLIND);
              break;
              default :
                EMIT(SKIP);
                fbreak;
              break;
            }
        };

        '[['
        {
            state = GET_STATE();
            switch(state){
              case BLIND :
              case BLIND_LINK :
                PUSH(LINK_START,BLIND_LINK);
              break;
              case INNER_LINK :
              case LINK :
                PUSH(LINK_START,INNER_LINK);
              break;
              case DEFAULT :
                PUSH(LINK_START,LINK);
                EMIT(LINK_START);
                fbreak;
              break;
              default :
                EMIT(SKIP);
                fbreak;
              break;
            }
        };

        ']]'
        {
            state = GET_STATE();
            switch(state){
              case BLIND :
                if(LAST_TYPE() == SPECIAL_LINK_START) {
                  POP();
                  EMIT(SKIP);
                  fbreak;
                } else
                  ERROR("Non-matching tokens");
              break;
              case BLIND_LINK :
              case INNER_LINK :
                POP();
                EMIT(SKIP);
                fbreak;
              break;
              case LINK :
                POP();
                TODO(); //Close link tag                 
                EMIT(LINK_END);
                fbreak;
              break;
              case DEFAULT :
                PRINT_STACK();
                ERROR("Closing tag without opening");
              break;
              default :
                EMIT(SKIP);
                fbreak;
              break;
            }
        };

        '{|'
        {
            state = GET_STATE();
            switch(state){
              case BLIND :
              case BLIND_LINK :
              case INNER_LINK :
              case LINK :
              case DEFAULT :
                PUSH(TABLE_START,BLIND);
              break;
              default :
                EMIT(SKIP);
                fbreak;
              break;
            }
        };

        '|}}' | '}}'
        {
            state = GET_STATE();
            switch(state){
              case BLIND :
                opening = LAST_TYPE();
                if(opening == IMG_START){
                  POP();
                  EMIT(SKIP);
                  fbreak;
                } else {
                  ERROR("Non-matching tokens");
                  EMIT(SKIP);
                  fbreak;
                }
              break;
              case BLIND_LINK :
              case INNER_LINK :
              case LINK :
                ERROR("Non-matching tokens");
                EMIT(SKIP);
                fbreak;
              break;
              case DEFAULT :
                ERROR("Closing without opening");
                EMIT(SKIP);
                fbreak;
              break;
              default :
                EMIT(SKIP);
                fbreak;
              break;
            }
        };


        '|}'
        {
            state = GET_STATE();
            switch(state){
              case BLIND :
                opening = LAST_TYPE();
                if(opening == TABLE_START){
                  POP();
                } else {
                  ERROR("Non-matching tokens");
                }
              break;
              case BLIND_LINK :
              case INNER_LINK :
              case LINK :
                ERROR("Non-matching tokens");
                EMIT(SKIP);
                fbreak;
              break;
              case DEFAULT :
                ERROR("Closing without opening");
                EMIT(SKIP);
                fbreak;
              break;
              default :
                EMIT(SKIP);
                fbreak;
              break;
            }
        };

        '|'
        {
          if(GET_STATE() == LINK){
            EMIT(SEPARATOR);
            fbreak;
          } else {
            EMIT(SKIP);
            fbreak;
          }
        };

        '['
        {
            state = GET_STATE();
            switch(state){
              case BLIND :
              case BLIND_LINK :
                PUSH(EXT_LINK_START,BLIND_LINK);
              break;
              case INNER_LINK :
              case LINK :
                PUSH(EXT_LINK_START,INNER_LINK);
              break;
              case DEFAULT :
                PUSH(EXT_LINK_START,LINK);
                EMIT(EXT_LINK_START);
                fbreak;
              break;
              default :
                EMIT(SKIP);
                fbreak;
              break;
            }
        };

        ']'
        {
            state = GET_STATE();
            switch(state){
              case BLIND :
                ERROR("Non-matching tokens");
                EMIT(SKIP);
                fbreak;
              break;
              case BLIND_LINK :
              case INNER_LINK :
                POP();
                EMIT(SKIP);
                fbreak;
              break;
              case LINK :
                POP();
                TODO(); //Close link tag                 
                EMIT(EXT_LINK_END);
                fbreak;
              case DEFAULT :
                ERROR("Closing tag without opening");
              break;
              default :
                EMIT(SKIP);
                fbreak;
              break;
            }
        };

        '&quot;'
        {
            EMIT(SKIP);
            fbreak;
        };

        '&amp;'
        {
          EMIT(SKIP);
          fbreak;
        };

        '&' alpha+ digit* ';'
        {
            EMIT(SKIP);
            fbreak;
        };

        '&#' [xX] xdigit+ ';'
        {
            EMIT(SKIP);
            fbreak;
        };

        '&#' digit+ ';'
        {
            EMIT(SKIP);
            fbreak;
        };

        '"'
        {
          if(GET_STATE() == DEFAULT)
            EMIT(PRINTABLE);
          else
            EMIT(SKIP);
          fbreak;
        };

        '&'
        {
          if(GET_STATE() == DEFAULT)
            EMIT(PRINTABLE);
          else
            EMIT(SKIP);
          fbreak;
        };

        ( '<' alpha ) |  '</' | '<!'
        {
            state = GET_STATE();
            switch(state){
              case BLIND :
              case BLIND_LINK :
              case INNER_LINK :
              case LINK :
              case DEFAULT :
                PUSH(TAG_START,NOWIKI);
                EMIT(SKIP);
                fbreak;
              break;
              default :
                EMIT(SKIP);
                fbreak;
              break;
            }
        };
        
        '<'
        {
            state = GET_STATE();
            switch(state){
              case INNER_LINK :
              case LINK :
                TODO(); // Push token
                EMIT(ALNUM);
                fbreak;
              break;
              case DEFAULT :
                EMIT(ALNUM);
                fbreak;
              break;
              default :
                EMIT(SKIP);
                fbreak;
              break;
            }
        };

        '>'
        {
            state = GET_STATE();
            switch(state){
              case DEFAULT :
                EMIT(PRINTABLE);
                fbreak;
              break;
              case NOWIKI :
                opening = LAST_TYPE();
                if(opening == TAG_START) {
                  POP(); 
                  EMIT(SKIP);
                  fbreak;
                }
              break;
              default :
                ERROR("Closing token without opening token");
                EMIT(SKIP);
                fbreak;
              break;
            }
        };

        '{{'
        {
            state = GET_STATE();
            switch(state){
              case BLIND :
              case BLIND_LINK :
              case INNER_LINK :
              case LINK :
              case DEFAULT :
                PUSH(IMG_START,BLIND);
              break;
              default :
                EMIT(SKIP);
                fbreak;
              break;
            }
        };


        '{'
        {
            state = GET_STATE();
            switch(state){
              case INNER_LINK :
              case LINK :
                TODO(); // Push token
                EMIT(PRINTABLE);
                fbreak;
              break;
              case DEFAULT :
                EMIT(PRINTABLE);
                fbreak;
              break;
              default :
                EMIT(SKIP);
                fbreak;
              break;
            }
        };

        '}'
        {
            state = GET_STATE();
            switch(state){
              case INNER_LINK :
              case LINK :
                TODO(); // Push token
                EMIT(PRINTABLE);
                fbreak;
              break;
              case DEFAULT :
                EMIT(PRINTABLE);
                fbreak;
              break;
              default :
                EMIT(SKIP);
                fbreak;
              break;
            }
        };

        ("\r"? "\n") | "\r"
        {
            state = GET_STATE();
            switch(state){
              case INNER_LINK :
              case LINK :
                ERROR("Unclosed link");
                TODO(); // Print tokens
                POP();
                EMIT(CRLF);
              break;
              case DEFAULT :
                EMIT(CRLF);
              break;
              default :
                EMIT(SKIP);
              break;
            }
            out->column_stop = 1;
            out->line_stop++;
            fbreak;
        };

        # must tokenize these separately from the other PRINTABLE characters otherwise a string like:
        #   See http://example.com/.
        # will get greedily tokenized as PRINTABLE, SPACE, PRINTABLE rather than PRINTABLE, SPACE, URI, SPECIAL_URI_CHARS
        # this also applies to MAIL tokenization and input strings like:
        #   Email me (user@example.com) for more info.
        special_uri_chars
        {
            state = GET_STATE();
            switch(state){
              case INNER_LINK :
              case LINK :
                TODO(); // Push token
                EMIT(ALNUM);
                fbreak;
              break;
              case DEFAULT :
                EMIT(ALNUM);
                fbreak;
              break;
              default :
                EMIT(SKIP);
                fbreak;
              break;
            }
        };

        alnum+
        {
            state = GET_STATE();
            switch(state){
              case INNER_LINK :
              case LINK :
                TODO(); // Push token
                EMIT(ALNUM);
                fbreak;
              break;
              case DEFAULT :
                EMIT(ALNUM);
                fbreak;
              break;
              default :
                EMIT(SKIP);
                fbreak;
              break;
            }
        };

        # all the printable ASCII characters (0x20 to 0x7e) excluding those explicitly covered elsewhere:
        # we skip space (0x20), exclamation mark (0x21), quote (0x22), hash (0x23), ampersand (0x26), apostrophe (0x27),
        # left parenthesis (0x28), right parenthesis (0x29), numbers (0x30..0x39), asterisk (0x2a), comma (0x2c), period (0x2e),
        # colon (0x3a), semi-colon (0x3b), less than (0x3c), equals (0x3d), greater than (0x3e), question mark (0x3f), uppercase
        # letters (0x41..0x5a), left bracket (0x5b), right bracket (0x5d), backtick (0x60), lowercase letters (0x61..0x7a), left
        # curly brace (0x7b), vertical bar (0x7c) and right curly brace (0x7d).
        #     one_byte_sequence   = byte begins with zero;
        #     two_byte_sequence   = first byte begins with 110 (0xc0..0xdf), next with 10 (0x80..9xbf);
        #     three_byte_sequence = first byte begins with 1110 (0xe0..0xef), next two with 10 (0x80..9xbf);
        #     four_byte_sequence  = first byte begins with 11110 (0xf0..0xf7), next three with 10 (0x80..9xbf);
        (0x24..0x25 | 0x2b | 0x2d | 0x2f | 0x40 | 0x5c | 0x5e..0x5f | 0x7e |
          (0xc2..0xdf 0x80..0xbf)                         @two_byte_utf8_sequence     |
          (0xe0..0xef 0x80..0xbf 0x80..0xbf)              @three_byte_utf8_sequence   |
          (0xf0..0xf4 0x80..0xbf 0x80..0xbf 0x80..0xbf)   @four_byte_utf8_sequence
        )+
        {
            state = GET_STATE();
            switch(state){
              case INNER_LINK :
              case LINK :
                TODO(); // Push token
                EMIT(ALNUM);
                fbreak;
              break;
              case DEFAULT :
                EMIT(ALNUM);
                fbreak;
              break;
              default :
                EMIT(SKIP);
                fbreak;
              break;
            }
        };

        # here is where we handle everything else
        (0x01..0x1f | 0x7f)                             @non_printable_ascii 
        {
                EMIT(SKIP);
                fbreak;
        };

    *|;

    write data;
}%%

// for now we use the scanner as a tokenizer that returns one token at a time, just like ANTLR
// ultimately we could look at embedding all of the transformation inside the scanner itself (combined scanner/parser)
// pass in the last token because that's useful for the scanner to know
// p data pointer (required by Ragel machine); overriden with contents of last_token if supplied
// pe data end pointer (required by Ragel machine)
void next_token(token_t *out, token_t *last_token, char *p, char *pe,
  int * token_stack, int * state_stack, int * token_stack_size, int * state_stack_size)
{
    int last_token_type = NO_TOKEN;
    if (last_token)
    {
        last_token_type     = last_token->type;
        p = last_token->stop;
        out->line_start     = out->line_stop    = last_token->line_stop;
        out->column_start   = out->column_stop  = last_token->column_stop;
    }
    else
    {
        out->line_start     = 1;
        out->column_start   = 1;
        out->line_stop      = 1;
        out->column_stop    = 1;
    }
    out->type       = NO_TOKEN;
    out->code_point = 0;
    out->start      = p;
    if (p == pe)
    {
        // all done, have reached end of input
        out->stop  = p;
        out->type  = END_OF_FILE;
        return;
    }

    char    *mark;      // for manual backtracking
    char    *eof = pe;  // required for backtracking (longest match determination)
    int     cs;         // current state (standard Ragel)
    char    *ts;        // token start (scanner)
    char    *te;        // token end (scanner)
    int     act;        // identity of last patterned matched (scanner)
    int     state;      // the current state in parser
    int     opening;    // the last opening token type in parser
    char    error_msg[1000];
    %% write init;
    %% write exec;
    if (cs == wikitext_error)
        rb_raise(eWikitextParserError, "failed before finding a token");
    else if (out->type == NO_TOKEN){
        out->stop = p;
        out->type = END_OF_FILE;
        //rb_raise(eWikitextParserError, "failed to produce a token");
    }
}
