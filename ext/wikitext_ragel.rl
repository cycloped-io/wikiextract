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
#include <unistd.h>

#define EMIT(t)     do { out->type = t; out->stop = p + 1; out->column_stop += (out->stop - out->start); out->token_number = ++token_number; } while (0)
#define MARK()      do { mark = p; } while (0)
#define REWIND()    do { p = mark; } while (0)
#define AT_END()    (p + 1 == pe)
#define DISTANCE()  (p + 1 - ts)
#define NEXT_CHAR() (*(p + 1))
#define ERROR(msg)  do { printf("[%i:%i:%i:%i][31;1m",doc_id,(int)out->line_start,(int)out->column_start,GET_STATE()); printf(msg); printf("[0m: "); strncpy(error_msg,out->start,p-out->start+1); error_msg[p-out->start+1] = 0; printf("%s\n",error_msg);} while (0)
#define PRINT_STACK() do {printf("%i %i %i %i\n",token_stack[(*token_stack_size)-1], state_stack[(*state_stack_size)-1], *token_stack_size, *state_stack_size); } while(0)
#define PUSH(type,state) do { if(*token_stack_size == 1000){ERROR("Token stack overflow");}else{ token_stack[(*token_stack_size)++] = type;}  if(*state_stack_size == 1000){ERROR("State stack overflow");}else{state_stack[(*state_stack_size)++] = state;} } while (0)
#define POP()       do { if(*token_stack_size == 0){ERROR("Token stack underflow");}else{(*token_stack_size)--;} if(*state_stack_size == 0){ERROR("State stack underflow");}else{(*state_stack_size)--;} } while (0)
#define LAST_TYPE() ( token_stack[(*token_stack_size)-1] )
#define TODO()      do { } while (0)
#define GET_STATE() ( state_stack[(*state_stack_size)-1] )
#define DEBUG(msg)  do { printf(msg); printf("\n"); } while (0)
#define PRINT(type) do { EMIT(SKIP); wikitext_print_token(out,file_p,doc_id,type); } while (0)
#define PRINT_CRLF() do { EMIT(SKIP); wikitext_print_crlf(out,file_p,doc_id); } while (0)

long token_number = 0;

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

    uri_chars           = (alnum | [@$&'(\*\+=%_~/#] | '-') ;
    special_uri_chars   = (0x21..0x2F | 0x3A..0x40 | 0x5C | 0x5E..0x60 | 0x7E) ;
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
        ( '<ref>'i ) | ( '<ref ' [^\>]+ '>'i )
        {
            state = GET_STATE();
            switch(state){
              case POST_LINK :
                POP();
              case BLIND :
              case BLIND_LINK :
              case INNER_LINK :
              case LINK :
              case DEFAULT :
              case NOWIKI :
                PUSH(PRE_START,NOWIKI);
                EMIT(SKIP);
                fbreak;
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
              case POST_LINK :
                POP();
              case BLIND :
              case BLIND_LINK :
              case INNER_LINK :
              case LINK :
              case DEFAULT :
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
              if(GET_STATE() == POST_LINK)
                POP();
              EMIT(SKIP);
              fbreak;
            } else {
              state = GET_STATE();
              switch(state) {
                case DEFAULT :
                  PRINT("print");
                  fbreak;
                break;
                case INNER_LINK :
                case LINK :
                  TODO(); // Push token
                  EMIT(PRINTABLE);
                  fbreak;
                break;
                case POST_LINK :
                  POP();
                  EMIT(PRINTABLE);
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
                if(GET_STATE() == POST_LINK)
                  POP();
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
                  PRINT("space");
                  fbreak;
                break;
                case POST_LINK :
                  POP();
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
            if (out->column_start == 1 ) {
                if(GET_STATE() == POST_LINK)
                  POP();
                EMIT(SKIP);
            } else {
              state = GET_STATE();
              switch(state){
                case INNER_LINK :
                case LINK :
                  TODO(); // Push token
                  EMIT(PRINTABLE);
                  fbreak;
                break;
                case DEFAULT :
                  PRINT("print");
                  fbreak;
                break;
                case POST_LINK :
                  POP();
                  EMIT(PRINTABLE);
                  fbreak;
                break;
                default :
                  EMIT(SKIP);
                  fbreak;
                break;
              }
            }
        };

        '='+ @mark ' '*
        {
            if (out->column_start == 1)
            {
                REWIND();
                if(GET_STATE() == POST_LINK)
                  POP();
                if (DISTANCE() <= 6) {
                  if (GET_STATE() == DEFAULT){
                    PRINT_CRLF();
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
                if(GET_STATE() == POST_LINK)
                  POP();
                if (DISTANCE() <= 6) {
                  if (GET_STATE() == DEFAULT){
                    PRINT_CRLF();
                    fbreak;
                  } else {
                    EMIT(SKIP);
                    fbreak;
                  }
                } else {
                    p -= 6; // will scan the H6 on the next scan
                    state = GET_STATE();
                    switch(state){
                      case INNER_LINK :
                      case LINK :
                        TODO(); // Push token
                        EMIT(SPACE);
                        fbreak;
                      break;
                      case DEFAULT :
                        PRINT("space");
                        fbreak;
                      break;
                      case POST_LINK :
                        POP();
                        EMIT(SPACE);
                        fbreak;
                      break;
                      default :
                        EMIT(SKIP);
                        fbreak;
                      break;
                    }
                }
            }
            else
            {
                // note that a H*_END token will never match before a BLOCKQUOTE_END
                REWIND();
                state = GET_STATE();
                switch(state){
                  case INNER_LINK :
                  case LINK :
                    TODO(); // Push token
                    EMIT(SPACE);
                    fbreak;
                  break;
                  case DEFAULT :
                    PRINT("space");
                    fbreak;
                  break;
                  case POST_LINK :
                    POP();
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

        
        '[[' (alpha | '-')* ':'
        {
            state = GET_STATE();
            switch(state){
              case POST_LINK :
                POP();
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
              case POST_LINK :
                POP();
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
                // used to combine links such as [[Alan]]owi
                PUSH(SKIP,POST_LINK);
                fbreak;
              break;
              case POST_LINK :
                POP();
              case DEFAULT :
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
              case POST_LINK :
                POP();
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
              case POST_LINK :
                POP();
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
              case POST_LINK :
                POP();
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
          state = GET_STATE();
          switch(state){
              case LINK :
                EMIT(SEPARATOR);
                fbreak;
              break;
              case POST_LINK :
                POP();
              default :
                EMIT(SKIP);
                fbreak;
              break;
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
              case POST_LINK :
                POP();
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
              case POST_LINK :
                POP();
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
            if(GET_STATE() == POST_LINK)
              POP();
            EMIT(SKIP);
            fbreak;
        };

        '&amp;'
        {
          if(GET_STATE() == POST_LINK)
            POP();
          EMIT(SKIP);
          fbreak;
        };

        '&' alpha+ digit* ';'
        {
            if(GET_STATE() == POST_LINK)
              POP();
            EMIT(SKIP);
            fbreak;
        };

        '&#' [xX] xdigit+ ';'
        {
            if(GET_STATE() == POST_LINK)
              POP();
            EMIT(SKIP);
            fbreak;
        };

        '&#' digit+ ';'
        {
            if(GET_STATE() == POST_LINK)
              POP();
            EMIT(SKIP);
            fbreak;
        };

        ( '<' alpha ) |  '</' | '<!'
        {
            state = GET_STATE();
            switch(state){
              case POST_LINK :
                POP();
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
                EMIT(PRINTABLE);
                fbreak;
              break;
              case DEFAULT :
                PRINT("print");
                fbreak;
              break;
              case POST_LINK :
                POP();
                EMIT(PRINTABLE);
                fbreak;
              break;
              default :
                EMIT(SKIP);
                fbreak;
              break;
            }
        };

        '>'+
        {
            if (out->column_start == 1) {
              if(GET_STATE() == POST_LINK)
                POP();
              EMIT(SKIP);
              fbreak;
            } else {
              state = GET_STATE();
              switch(state){
                case DEFAULT :
                  PRINT("print");
                  fbreak;
                break;
                case POST_LINK :
                  POP();
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

        '{{'
        {
            state = GET_STATE();
            switch(state){
              case POST_LINK :
                POP();
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
        
        ("\r"? "\n") | "\r"
        {
            state = GET_STATE();
            switch(state){
              case INNER_LINK :
              case LINK :
                ERROR("Unclosed link");
                TODO(); // Print tokens
                POP();
                EMIT(UNCLOSED);
              break;
              case DEFAULT :
                PRINT_CRLF();
              break;
              case POST_LINK :
                POP();
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

        '"' | '&' | '{' | '}' | special_uri_chars
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
                PRINT("print");
                fbreak;
              break;
              case POST_LINK :
                POP();
                EMIT(PRINTABLE);
                fbreak;
              break;
              default :
                EMIT(SKIP);
                fbreak;
              break;
            }
        };

        digit+ ([:., _/\-] digit+)*
        {
            state = GET_STATE();
            switch(state){
              case INNER_LINK :
              case LINK :
                TODO(); // Push token
                EMIT(NUM);
                fbreak;
              break;
              case DEFAULT :
                PRINT("num");
                fbreak;
              break;
              case POST_LINK :
                POP();
                EMIT(NUM);
                fbreak;
              break;
              default :
                EMIT(SKIP);
                fbreak;
              break;
            }
        };

        (alnum |
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
                PRINT("alnum");
                fbreak;
              break;
              case POST_LINK :
                POP();
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
        (0x01..0x1f | 0x7f)   @non_printable_ascii
        {
                if(GET_STATE() == POST_LINK)
                  POP();
                EMIT(SKIP);
                fbreak;
        };

    *|;

    write data;
}%%

void next_token(token_t *out, token_t *last_token, char *p, char *pe,
  int * token_stack, int * state_stack, int * token_stack_size, int * state_stack_size,
  FILE * file_p, int doc_id)
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
