
#line 1 "wikitext_ragel.rl"
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
//#define ERROR(msg)  do { printf(msg); printf("\n"); } while (0)
#define ERROR(msg)  do { printf(msg); printf("\n"); } while (0)
#define GET_STATE() ( state_stack[(*state_stack_size)-1] )
#define DEBUG(msg)  do { printf(msg); printf("\n"); } while (0)



#line 55 "wikitext_ragel.c"
static const int wikitext_start = 89;
static const int wikitext_first_final = 89;
static const int wikitext_error = 0;

static const int wikitext_en_main = 89;


#line 823 "wikitext_ragel.rl"


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
    
#line 109 "wikitext_ragel.c"
	{
	cs = wikitext_start;
	ts = 0;
	te = 0;
	act = 0;
	}

#line 868 "wikitext_ragel.rl"
    
#line 119 "wikitext_ragel.c"
	{
	if ( p == pe )
		goto _test_eof;
	switch ( cs )
	{
tr0:
#line 65 "wikitext_ragel.rl"
	{
        out->code_point = ((uint32_t)(*(p - 1)) & 0x1f) << 6 |
            (*p & 0x3f);
    }
#line 799 "wikitext_ragel.rl"
	{te = p+1;{
            state = GET_STATE();
            switch(state){
              case INNER_LINK :
              case LINK :
                TODO(); // Push token
                EMIT(ALNUM);
                {p++; cs = 89; goto _out;}
              break;
              case DEFAULT :
                EMIT(ALNUM);
                {p++; cs = 89; goto _out;}
              break;
              default :
                EMIT(SKIP);
                {p++; cs = 89; goto _out;}
              break;
            }
            out->column_stop = out->column_start + 1;
        }}
	goto st89;
tr3:
#line 71 "wikitext_ragel.rl"
	{
        out->code_point = ((uint32_t)(*(p - 2)) & 0x0f) << 12 |
            ((uint32_t)(*(p - 1)) & 0x3f) << 6 |
            (*p & 0x3f);
    }
#line 799 "wikitext_ragel.rl"
	{te = p+1;{
            state = GET_STATE();
            switch(state){
              case INNER_LINK :
              case LINK :
                TODO(); // Push token
                EMIT(ALNUM);
                {p++; cs = 89; goto _out;}
              break;
              case DEFAULT :
                EMIT(ALNUM);
                {p++; cs = 89; goto _out;}
              break;
              default :
                EMIT(SKIP);
                {p++; cs = 89; goto _out;}
              break;
            }
            out->column_stop = out->column_start + 1;
        }}
	goto st89;
tr6:
#line 78 "wikitext_ragel.rl"
	{
        out->code_point = ((uint32_t)(*(p - 3)) & 0x07) << 18 |
            ((uint32_t)(*(p - 2)) & 0x3f) << 12 |
            ((uint32_t)(*(p - 1)) & 0x3f) << 6 |
            (*p & 0x3f);
    }
#line 799 "wikitext_ragel.rl"
	{te = p+1;{
            state = GET_STATE();
            switch(state){
              case INNER_LINK :
              case LINK :
                TODO(); // Push token
                EMIT(ALNUM);
                {p++; cs = 89; goto _out;}
              break;
              case DEFAULT :
                EMIT(ALNUM);
                {p++; cs = 89; goto _out;}
              break;
              default :
                EMIT(SKIP);
                {p++; cs = 89; goto _out;}
              break;
            }
            out->column_stop = out->column_start + 1;
        }}
	goto st89;
tr7:
#line 556 "wikitext_ragel.rl"
	{{p = ((te))-1;}{
            EMIT(AMP);
            {p++; cs = 89; goto _out;}
        }}
	goto st89;
tr10:
#line 541 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(SKIP);
            {p++; cs = 89; goto _out;}
        }}
	goto st89;
tr12:
#line 535 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(SKIP);
            {p++; cs = 89; goto _out;}
        }}
	goto st89;
tr14:
#line 529 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(SKIP);
            {p++; cs = 89; goto _out;}
        }}
	goto st89;
tr18:
#line 523 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(PRINTABLE);
            {p++; cs = 89; goto _out;}
        }}
	goto st89;
tr22:
#line 517 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(SKIP);
            {p++; cs = 89; goto _out;}
        }}
	goto st89;
tr23:
#line 1 "NONE"
	{	switch( act ) {
	case 1:
	{{p = ((te))-1;}
            EMIT(SKIP);
            {p++; cs = 89; goto _out;}
        }
	break;
	case 14:
	{{p = ((te))-1;}
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
                {p++; cs = 89; goto _out;}
              break;
              case DEFAULT :
                ERROR("Closing without opening");
                EMIT(SKIP);
                {p++; cs = 89; goto _out;}
              break;
              default :
                EMIT(SKIP);
                {p++; cs = 89; goto _out;}
              break;
            }
        }
	break;
	case 30:
	{{p = ((te))-1;}
            state = GET_STATE();
            switch(state){
              case INNER_LINK :
              case LINK :
                TODO(); // Push token
                EMIT(PRINTABLE);
                {p++; cs = 89; goto _out;}
              break;
              case DEFAULT :
                EMIT(PRINTABLE);
                {p++; cs = 89; goto _out;}
              break;
              default :
                EMIT(SKIP);
                {p++; cs = 89; goto _out;}
              break;
            }
        }
	break;
	case 32:
	{{p = ((te))-1;}
            state = GET_STATE();
            switch(state){
              case INNER_LINK :
              case LINK :
                TODO(); // Push token
                EMIT(ALNUM);
                {p++; cs = 89; goto _out;}
              break;
              case DEFAULT :
                EMIT(ALNUM);
                {p++; cs = 89; goto _out;}
              break;
              default :
                EMIT(SKIP);
                {p++; cs = 89; goto _out;}
              break;
            }
        }
	break;
	case 33:
	{{p = ((te))-1;}
            state = GET_STATE();
            switch(state){
              case INNER_LINK :
              case LINK :
                TODO(); // Push token
                EMIT(ALNUM);
                {p++; cs = 89; goto _out;}
              break;
              case DEFAULT :
                EMIT(ALNUM);
                {p++; cs = 89; goto _out;}
              break;
              default :
                EMIT(SKIP);
                {p++; cs = 89; goto _out;}
              break;
            }
        }
	break;
	case 34:
	{{p = ((te))-1;}
            state = GET_STATE();
            switch(state){
              case INNER_LINK :
              case LINK :
                TODO(); // Push token
                EMIT(ALNUM);
                {p++; cs = 89; goto _out;}
              break;
              case DEFAULT :
                EMIT(PRINTABLE);
                {p++; cs = 89; goto _out;}
              break;
              default :
                EMIT(SKIP);
                {p++; cs = 89; goto _out;}
              break;
            }
        }
	break;
	}
	}
	goto st89;
tr30:
#line 562 "wikitext_ragel.rl"
	{{p = ((te))-1;}{
            state = GET_STATE();
            switch(state){
              case BLIND :
              case BLIND_LINK :
              case INNER_LINK :
              case LINK :
              case DEFAULT :
                PUSH(TAG_START,NOWIKI);
                EMIT(SKIP);
                {p++; cs = 89; goto _out;}
              break;
              default :
                EMIT(SKIP);
                {p++; cs = 89; goto _out;}
              break;
            }
        }}
	goto st89;
tr40:
#line 102 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(SKIP);
            {p++; cs = 89; goto _out;}
        }}
	goto st89;
tr44:
#line 126 "wikitext_ragel.rl"
	{te = p+1;{
            state = GET_STATE();
            switch(state){
              case NOWIKI :
                opening = LAST_TYPE();
                if(opening == PRE_START)
                  POP(); 
              break;
              case BLIND :
              case BLIND_LINK :
              case INNER_LINK :
              case LINK :
              case DEFAULT :
                ERROR("Closing token without opening token");
              break;
              default :
                EMIT(SKIP);
                {p++; cs = 89; goto _out;}
              break;
            }
        }}
	goto st89;
tr61:
#line 108 "wikitext_ragel.rl"
	{te = p+1;{
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
                {p++; cs = 89; goto _out;}
              break;
            }
        }}
	goto st89;
tr76:
#line 737 "wikitext_ragel.rl"
	{{p = ((te))-1;}{
            state = GET_STATE();
            switch(state){
              case INNER_LINK :
              case LINK :
                TODO(); // Push token
                EMIT(ALNUM);
                {p++; cs = 89; goto _out;}
              break;
              case DEFAULT :
                EMIT(ALNUM);
                {p++; cs = 89; goto _out;}
              break;
              default :
                EMIT(SKIP);
                {p++; cs = 89; goto _out;}
              break;
            }
        }}
	goto st89;
tr80:
#line 102 "wikitext_ragel.rl"
	{{p = ((te))-1;}{
            EMIT(SKIP);
            {p++; cs = 89; goto _out;}
        }}
	goto st89;
tr82:
#line 308 "wikitext_ragel.rl"
	{{p = ((te))-1;}{
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
                {p++; cs = 89; goto _out;}
              break;
              default :
                EMIT(SKIP);
                {p++; cs = 89; goto _out;}
              break;
            }
        }}
	goto st89;
tr84:
#line 284 "wikitext_ragel.rl"
	{te = p+1;{
            state = GET_STATE();
            switch(state){
              case BLIND :
              case BLIND_LINK :
                PUSH(SPECIAL_LINK_START,BLIND_LINK);
              break;
              case INNER_LINK :
              case LINK :
                PUSH(SPECIAL_LINK_START,INNER_LINK);
              break;
              case DEFAULT :
                PUSH(LINK_START,LINK);
                EMIT(SPECIAL_LINK_START);
                {p++; cs = 89; goto _out;}
              break;
              default :
                EMIT(SKIP);
                {p++; cs = 89; goto _out;}
              break;
            }
        }}
	goto st89;
tr85:
#line 764 "wikitext_ragel.rl"
	{{p = ((te))-1;}{
            state = GET_STATE();
            switch(state){
              case INNER_LINK :
              case LINK :
                TODO(); // Push token
                EMIT(ALNUM);
                {p++; cs = 89; goto _out;}
              break;
              case DEFAULT :
                EMIT(PRINTABLE);
                {p++; cs = 89; goto _out;}
              break;
              default :
                EMIT(SKIP);
                {p++; cs = 89; goto _out;}
              break;
            }
        }}
	goto st89;
tr95:
#line 60 "wikitext_ragel.rl"
	{
        out->code_point = *p & 0x7f;
    }
#line 799 "wikitext_ragel.rl"
	{te = p+1;{
            state = GET_STATE();
            switch(state){
              case INNER_LINK :
              case LINK :
                TODO(); // Push token
                EMIT(ALNUM);
                {p++; cs = 89; goto _out;}
              break;
              case DEFAULT :
                EMIT(ALNUM);
                {p++; cs = 89; goto _out;}
              break;
              default :
                EMIT(SKIP);
                {p++; cs = 89; goto _out;}
              break;
            }
            out->column_stop = out->column_start + 1;
        }}
	goto st89;
tr96:
#line 688 "wikitext_ragel.rl"
	{te = p+1;{
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
            {p++; cs = 89; goto _out;}
        }}
#line 60 "wikitext_ragel.rl"
	{
        out->code_point = *p & 0x7f;
    }
	goto st89;
tr100:
#line 547 "wikitext_ragel.rl"
	{te = p+1;{
          if(GET_STATE() == DEFAULT)
            EMIT(PRINTABLE);
          else
            EMIT(SKIP);
          {p++; cs = 89; goto _out;}
        }}
	goto st89;
tr121:
#line 688 "wikitext_ragel.rl"
	{te = p;p--;{
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
            {p++; cs = 89; goto _out;}
        }}
	goto st89;
tr122:
#line 688 "wikitext_ragel.rl"
	{te = p+1;{
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
            {p++; cs = 89; goto _out;}
        }}
	goto st89;
tr123:
#line 196 "wikitext_ragel.rl"
	{te = p;p--;{
            if (out->column_start == 1 || last_token_type == BLOCKQUOTE)
            {
                REWIND();
                EMIT(SKIP);
                {p++; cs = 89; goto _out;}
            } else {
              state = GET_STATE();
              switch(state){
                case INNER_LINK :
                case LINK :
                  TODO(); // Push token
                  EMIT(SPACE);
                  {p++; cs = 89; goto _out;}
                break;
                case DEFAULT :
                  EMIT(SPACE);
                  {p++; cs = 89; goto _out;}
                break;
                default :
                  EMIT(SKIP);
                  {p++; cs = 89; goto _out;}
                break;
              }
            }
        }}
	goto st89;
tr125:
#line 716 "wikitext_ragel.rl"
	{te = p;p--;{
            state = GET_STATE();
            switch(state){
              case INNER_LINK :
              case LINK :
                TODO(); // Push token
                EMIT(ALNUM);
                {p++; cs = 89; goto _out;}
              break;
              case DEFAULT :
                EMIT(ALNUM);
                {p++; cs = 89; goto _out;}
              break;
              default :
                EMIT(SKIP);
                {p++; cs = 89; goto _out;}
              break;
            }
        }}
	goto st89;
tr126:
#line 224 "wikitext_ragel.rl"
	{te = p;p--;{
            if (out->column_start == 1 )
                EMIT(SKIP);
            else
              if(GET_STATE() == DEFAULT)
                EMIT(PRINTABLE);             
              else
                EMIT(SKIP);
            {p++; cs = 89; goto _out;}
        }}
	goto st89;
tr127:
#line 764 "wikitext_ragel.rl"
	{te = p;p--;{
            state = GET_STATE();
            switch(state){
              case INNER_LINK :
              case LINK :
                TODO(); // Push token
                EMIT(ALNUM);
                {p++; cs = 89; goto _out;}
              break;
              case DEFAULT :
                EMIT(PRINTABLE);
                {p++; cs = 89; goto _out;}
              break;
              default :
                EMIT(SKIP);
                {p++; cs = 89; goto _out;}
              break;
            }
        }}
	goto st89;
tr128:
#line 556 "wikitext_ragel.rl"
	{te = p;p--;{
            EMIT(AMP);
            {p++; cs = 89; goto _out;}
        }}
	goto st89;
tr132:
#line 150 "wikitext_ragel.rl"
	{te = p;p--;{
            if (DISTANCE() > 1) {
              EMIT(SKIP);
              {p++; cs = 89; goto _out;}
            } else {
              if(GET_STATE() == DEFAULT) {
                EMIT(PRINTABLE);
                {p++; cs = 89; goto _out;}
              }
            }
        }}
	goto st89;
tr136:
#line 150 "wikitext_ragel.rl"
	{te = p+1;{
            if (DISTANCE() > 1) {
              EMIT(SKIP);
              {p++; cs = 89; goto _out;}
            } else {
              if(GET_STATE() == DEFAULT) {
                EMIT(PRINTABLE);
                {p++; cs = 89; goto _out;}
              }
            }
        }}
	goto st89;
tr138:
#line 102 "wikitext_ragel.rl"
	{te = p;p--;{
            EMIT(SKIP);
            {p++; cs = 89; goto _out;}
        }}
	goto st89;
tr142:
#line 737 "wikitext_ragel.rl"
	{te = p;p--;{
            state = GET_STATE();
            switch(state){
              case INNER_LINK :
              case LINK :
                TODO(); // Push token
                EMIT(ALNUM);
                {p++; cs = 89; goto _out;}
              break;
              case DEFAULT :
                EMIT(ALNUM);
                {p++; cs = 89; goto _out;}
              break;
              default :
                EMIT(SKIP);
                {p++; cs = 89; goto _out;}
              break;
            }
        }}
	goto st89;
tr143:
#line 582 "wikitext_ragel.rl"
	{te = p;p--;{
            state = GET_STATE();
            switch(state){
              case INNER_LINK :
              case LINK :
                TODO(); // Push token
                EMIT(ALNUM);
                {p++; cs = 89; goto _out;}
              break;
              case DEFAULT :
                EMIT(ALNUM);
                {p++; cs = 89; goto _out;}
              break;
              default :
                EMIT(SKIP);
                {p++; cs = 89; goto _out;}
              break;
            }
        }}
	goto st89;
tr144:
#line 562 "wikitext_ragel.rl"
	{te = p+1;{
            state = GET_STATE();
            switch(state){
              case BLIND :
              case BLIND_LINK :
              case INNER_LINK :
              case LINK :
              case DEFAULT :
                PUSH(TAG_START,NOWIKI);
                EMIT(SKIP);
                {p++; cs = 89; goto _out;}
              break;
              default :
                EMIT(SKIP);
                {p++; cs = 89; goto _out;}
              break;
            }
        }}
	goto st89;
tr154:
#line 562 "wikitext_ragel.rl"
	{te = p;p--;{
            state = GET_STATE();
            switch(state){
              case BLIND :
              case BLIND_LINK :
              case INNER_LINK :
              case LINK :
              case DEFAULT :
                PUSH(TAG_START,NOWIKI);
                EMIT(SKIP);
                {p++; cs = 89; goto _out;}
              break;
              default :
                EMIT(SKIP);
                {p++; cs = 89; goto _out;}
              break;
            }
        }}
	goto st89;
tr165:
#line 236 "wikitext_ragel.rl"
	{te = p;p--;{
            if (out->column_start == 1)
            {
                REWIND();
                if (DISTANCE() <= 6) {
                  if (GET_STATE() == DEFAULT){
                    EMIT(CRLF);
                    {p++; cs = 89; goto _out;}
                  }
                } else {
                    p = ts + 6;
                    EMIT(SKIP);
                    {p++; cs = 89; goto _out;}
                }
            }
            else if (AT_END() || NEXT_CHAR() == '\n' || NEXT_CHAR() == '\r')
            {
                REWIND();
                if (DISTANCE() <= 6) {
                  if (GET_STATE() == DEFAULT){
                    EMIT(CRLF);
                    {p++; cs = 89; goto _out;}
                  } else {
                    EMIT(SKIP);
                    {p++; cs = 89; goto _out;}
                  }
                } else {
                    p -= 6; // will scan the H6 on the next scan
                    if (GET_STATE() == DEFAULT){
                      EMIT(PRINTABLE);
                      {p++; cs = 89; goto _out;}
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
                {p++; cs = 89; goto _out;}
            }
        }}
	goto st89;
tr167:
#line 165 "wikitext_ragel.rl"
	{te = p;p--;{
            if (out->column_start == 1 || last_token_type == BLOCKQUOTE) {
              EMIT(SKIP);
              {p++; cs = 89; goto _out;}
            } else {
              REWIND();
              state = GET_STATE();
              switch(state){
                case DEFAULT :
                  EMIT(PRINTABLE);
                  {p++; cs = 89; goto _out;}
                break;
                case NOWIKI :
                  opening = LAST_TYPE();
                  if(opening == TAG_START) {
                    POP(); 
                    EMIT(SKIP);
                    {p++; cs = 89; goto _out;}
                  }
                break;
                default :
                  ERROR("Closing token without opening token");
                  EMIT(SKIP);
                  {p++; cs = 89; goto _out;}
                break;
              }
            }
        }}
	goto st89;
tr168:
#line 165 "wikitext_ragel.rl"
	{te = p+1;{
            if (out->column_start == 1 || last_token_type == BLOCKQUOTE) {
              EMIT(SKIP);
              {p++; cs = 89; goto _out;}
            } else {
              REWIND();
              state = GET_STATE();
              switch(state){
                case DEFAULT :
                  EMIT(PRINTABLE);
                  {p++; cs = 89; goto _out;}
                break;
                case NOWIKI :
                  opening = LAST_TYPE();
                  if(opening == TAG_START) {
                    POP(); 
                    EMIT(SKIP);
                    {p++; cs = 89; goto _out;}
                  }
                break;
                default :
                  ERROR("Closing token without opening token");
                  EMIT(SKIP);
                  {p++; cs = 89; goto _out;}
                break;
              }
            }
        }}
	goto st89;
tr182:
#line 463 "wikitext_ragel.rl"
	{te = p;p--;{
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
                {p++; cs = 89; goto _out;}
              break;
              default :
                EMIT(SKIP);
                {p++; cs = 89; goto _out;}
              break;
            }
        }}
	goto st89;
tr184:
#line 308 "wikitext_ragel.rl"
	{te = p;p--;{
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
                {p++; cs = 89; goto _out;}
              break;
              default :
                EMIT(SKIP);
                {p++; cs = 89; goto _out;}
              break;
            }
        }}
	goto st89;
tr185:
#line 487 "wikitext_ragel.rl"
	{te = p;p--;{
            state = GET_STATE();
            switch(state){
              case BLIND :
                ERROR("Non-matching tokens");
                EMIT(SKIP);
                {p++; cs = 89; goto _out;}
              break;
              case BLIND_LINK :
              case INNER_LINK :
                POP();
                EMIT(SKIP);
                {p++; cs = 89; goto _out;}
              break;
              case LINK :
                POP();
                TODO(); //Close link tag                 
                EMIT(EXT_LINK_END);
                {p++; cs = 89; goto _out;}
              case DEFAULT :
                ERROR("Closing tag without opening");
              break;
              default :
                EMIT(SKIP);
                {p++; cs = 89; goto _out;}
              break;
            }
        }}
	goto st89;
tr186:
#line 332 "wikitext_ragel.rl"
	{te = p+1;{
            state = GET_STATE();
            switch(state){
              case BLIND :
                if(LAST_TYPE() == SPECIAL_LINK_START) {
                  POP();
                  EMIT(SKIP);
                  {p++; cs = 89; goto _out;}
                } else
                  ERROR("Non-matching tokens");
              break;
              case BLIND_LINK :
              case INNER_LINK :
                POP();
                EMIT(SKIP);
                {p++; cs = 89; goto _out;}
              break;
              case LINK :
                POP();
                TODO(); //Close link tag                 
                EMIT(LINK_END);
                {p++; cs = 89; goto _out;}
              break;
              case DEFAULT :
                PRINT_STACK();
                ERROR("Closing tag without opening");
              break;
              default :
                EMIT(SKIP);
                {p++; cs = 89; goto _out;}
              break;
            }
        }}
	goto st89;
tr189:
#line 646 "wikitext_ragel.rl"
	{te = p;p--;{
            state = GET_STATE();
            switch(state){
              case INNER_LINK :
              case LINK :
                TODO(); // Push token
                EMIT(PRINTABLE);
                {p++; cs = 89; goto _out;}
              break;
              case DEFAULT :
                EMIT(PRINTABLE);
                {p++; cs = 89; goto _out;}
              break;
              default :
                EMIT(SKIP);
                {p++; cs = 89; goto _out;}
              break;
            }
        }}
	goto st89;
tr190:
#line 627 "wikitext_ragel.rl"
	{te = p+1;{
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
                {p++; cs = 89; goto _out;}
              break;
            }
        }}
	goto st89;
tr191:
#line 367 "wikitext_ragel.rl"
	{te = p+1;{
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
                {p++; cs = 89; goto _out;}
              break;
            }
        }}
	goto st89;
tr192:
#line 452 "wikitext_ragel.rl"
	{te = p;p--;{
          if(GET_STATE() == LINK){
            EMIT(SEPARATOR);
            {p++; cs = 89; goto _out;}
          } else {
            EMIT(SKIP);
            {p++; cs = 89; goto _out;}
          }
        }}
	goto st89;
tr194:
#line 385 "wikitext_ragel.rl"
	{te = p+1;{
            state = GET_STATE();
            switch(state){
              case BLIND :
                opening = LAST_TYPE();
                if(opening == IMG_START){
                  POP();
                  EMIT(SKIP);
                  {p++; cs = 89; goto _out;}
                } else {
                  ERROR("Non-matching tokens");
                  EMIT(SKIP);
                  {p++; cs = 89; goto _out;}
                }
              break;
              case BLIND_LINK :
              case INNER_LINK :
              case LINK :
                ERROR("Non-matching tokens");
                EMIT(SKIP);
                {p++; cs = 89; goto _out;}
              break;
              case DEFAULT :
                ERROR("Closing without opening");
                EMIT(SKIP);
                {p++; cs = 89; goto _out;}
              break;
              default :
                EMIT(SKIP);
                {p++; cs = 89; goto _out;}
              break;
            }
        }}
	goto st89;
st89:
#line 1 "NONE"
	{ts = 0;}
	if ( ++p == pe )
		goto _test_eof89;
case 89:
#line 1 "NONE"
	{ts = p;}
#line 1223 "wikitext_ragel.c"
	switch( (*p) ) {
		case 10: goto tr96;
		case 13: goto tr97;
		case 32: goto tr98;
		case 33: goto st92;
		case 34: goto tr100;
		case 35: goto st93;
		case 38: goto tr103;
		case 39: goto st96;
		case 42: goto st93;
		case 43: goto st94;
		case 45: goto tr105;
		case 46: goto tr106;
		case 47: goto st94;
		case 60: goto st108;
		case 61: goto tr109;
		case 62: goto tr110;
		case 63: goto st92;
		case 64: goto st94;
		case 70: goto tr111;
		case 72: goto tr112;
		case 77: goto tr113;
		case 83: goto tr114;
		case 91: goto st137;
		case 92: goto st94;
		case 93: goto st139;
		case 94: goto st94;
		case 95: goto tr117;
		case 96: goto tr40;
		case 102: goto tr111;
		case 104: goto tr112;
		case 109: goto tr113;
		case 115: goto tr114;
		case 123: goto st143;
		case 124: goto st144;
		case 125: goto tr120;
		case 126: goto st94;
		case 127: goto tr95;
	}
	if ( (*p) < 36 ) {
		if ( (*p) < -32 ) {
			if ( -62 <= (*p) && (*p) <= -33 )
				goto st1;
		} else if ( (*p) > -17 ) {
			if ( (*p) > -12 ) {
				if ( 1 <= (*p) && (*p) <= 31 )
					goto tr95;
			} else if ( (*p) >= -16 )
				goto st4;
		} else
			goto st2;
	} else if ( (*p) > 37 ) {
		if ( (*p) < 48 ) {
			if ( 40 <= (*p) && (*p) <= 44 )
				goto st92;
		} else if ( (*p) > 57 ) {
			if ( (*p) > 59 ) {
				if ( 65 <= (*p) && (*p) <= 122 )
					goto tr107;
			} else if ( (*p) >= 58 )
				goto st93;
		} else
			goto tr107;
	} else
		goto st94;
	goto st0;
st0:
cs = 0;
	goto _out;
st1:
	if ( ++p == pe )
		goto _test_eof1;
case 1:
	if ( (*p) <= -65 )
		goto tr0;
	goto st0;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
	if ( (*p) <= -65 )
		goto st3;
	goto st0;
st3:
	if ( ++p == pe )
		goto _test_eof3;
case 3:
	if ( (*p) <= -65 )
		goto tr3;
	goto st0;
st4:
	if ( ++p == pe )
		goto _test_eof4;
case 4:
	if ( (*p) <= -65 )
		goto st5;
	goto st0;
st5:
	if ( ++p == pe )
		goto _test_eof5;
case 5:
	if ( (*p) <= -65 )
		goto st6;
	goto st0;
st6:
	if ( ++p == pe )
		goto _test_eof6;
case 6:
	if ( (*p) <= -65 )
		goto tr6;
	goto st0;
tr97:
#line 60 "wikitext_ragel.rl"
	{
        out->code_point = *p & 0x7f;
    }
	goto st90;
st90:
	if ( ++p == pe )
		goto _test_eof90;
case 90:
#line 1345 "wikitext_ragel.c"
	if ( (*p) == 10 )
		goto tr122;
	goto tr121;
tr98:
#line 55 "wikitext_ragel.rl"
	{
        MARK();
    }
	goto st91;
st91:
	if ( ++p == pe )
		goto _test_eof91;
case 91:
#line 1359 "wikitext_ragel.c"
	if ( (*p) == 32 )
		goto st91;
	goto tr123;
st92:
	if ( ++p == pe )
		goto _test_eof92;
case 92:
	switch( (*p) ) {
		case 33: goto st92;
		case 44: goto st92;
		case 46: goto st92;
		case 63: goto st92;
	}
	if ( 40 <= (*p) && (*p) <= 41 )
		goto st92;
	goto tr125;
st93:
	if ( ++p == pe )
		goto _test_eof93;
case 93:
	switch( (*p) ) {
		case 35: goto st93;
		case 42: goto st93;
	}
	if ( 58 <= (*p) && (*p) <= 59 )
		goto st93;
	goto tr126;
st94:
	if ( ++p == pe )
		goto _test_eof94;
case 94:
	switch( (*p) ) {
		case 43: goto st94;
		case 45: goto st94;
		case 47: goto st94;
		case 64: goto st94;
		case 92: goto st94;
		case 126: goto st94;
	}
	if ( (*p) > 37 ) {
		if ( 94 <= (*p) && (*p) <= 95 )
			goto st94;
	} else if ( (*p) >= 36 )
		goto st94;
	goto tr127;
tr103:
#line 1 "NONE"
	{te = p+1;}
	goto st95;
st95:
	if ( ++p == pe )
		goto _test_eof95;
case 95:
#line 1413 "wikitext_ragel.c"
	switch( (*p) ) {
		case 35: goto st7;
		case 97: goto st13;
		case 113: goto st16;
	}
	if ( (*p) > 90 ) {
		if ( 98 <= (*p) && (*p) <= 122 )
			goto st11;
	} else if ( (*p) >= 65 )
		goto st11;
	goto tr128;
st7:
	if ( ++p == pe )
		goto _test_eof7;
case 7:
	switch( (*p) ) {
		case 88: goto st9;
		case 120: goto st9;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st8;
	goto tr7;
st8:
	if ( ++p == pe )
		goto _test_eof8;
case 8:
	if ( (*p) == 59 )
		goto tr10;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st8;
	goto tr7;
st9:
	if ( ++p == pe )
		goto _test_eof9;
case 9:
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st10;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st10;
	} else
		goto st10;
	goto tr7;
st10:
	if ( ++p == pe )
		goto _test_eof10;
case 10:
	if ( (*p) == 59 )
		goto tr12;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st10;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st10;
	} else
		goto st10;
	goto tr7;
st11:
	if ( ++p == pe )
		goto _test_eof11;
case 11:
	if ( (*p) == 59 )
		goto tr14;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st12;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st11;
	} else
		goto st11;
	goto tr7;
st12:
	if ( ++p == pe )
		goto _test_eof12;
case 12:
	if ( (*p) == 59 )
		goto tr14;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st12;
	goto tr7;
st13:
	if ( ++p == pe )
		goto _test_eof13;
case 13:
	switch( (*p) ) {
		case 59: goto tr14;
		case 109: goto st14;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st12;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st11;
	} else
		goto st11;
	goto tr7;
st14:
	if ( ++p == pe )
		goto _test_eof14;
case 14:
	switch( (*p) ) {
		case 59: goto tr14;
		case 112: goto st15;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st12;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st11;
	} else
		goto st11;
	goto tr7;
st15:
	if ( ++p == pe )
		goto _test_eof15;
case 15:
	if ( (*p) == 59 )
		goto tr18;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st12;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st11;
	} else
		goto st11;
	goto tr7;
st16:
	if ( ++p == pe )
		goto _test_eof16;
case 16:
	switch( (*p) ) {
		case 59: goto tr14;
		case 117: goto st17;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st12;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st11;
	} else
		goto st11;
	goto tr7;
st17:
	if ( ++p == pe )
		goto _test_eof17;
case 17:
	switch( (*p) ) {
		case 59: goto tr14;
		case 111: goto st18;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st12;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st11;
	} else
		goto st11;
	goto tr7;
st18:
	if ( ++p == pe )
		goto _test_eof18;
case 18:
	switch( (*p) ) {
		case 59: goto tr14;
		case 116: goto st19;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st12;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st11;
	} else
		goto st11;
	goto tr7;
st19:
	if ( ++p == pe )
		goto _test_eof19;
case 19:
	if ( (*p) == 59 )
		goto tr22;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st12;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st11;
	} else
		goto st11;
	goto tr7;
st96:
	if ( ++p == pe )
		goto _test_eof96;
case 96:
	if ( (*p) == 39 )
		goto st97;
	goto tr132;
st97:
	if ( ++p == pe )
		goto _test_eof97;
case 97:
	if ( (*p) == 39 )
		goto st98;
	goto tr132;
st98:
	if ( ++p == pe )
		goto _test_eof98;
case 98:
	if ( (*p) == 39 )
		goto st99;
	goto tr132;
st99:
	if ( ++p == pe )
		goto _test_eof99;
case 99:
	if ( (*p) == 39 )
		goto tr136;
	goto tr132;
tr105:
#line 1 "NONE"
	{te = p+1;}
#line 764 "wikitext_ragel.rl"
	{act = 34;}
	goto st100;
st100:
	if ( ++p == pe )
		goto _test_eof100;
case 100:
#line 1650 "wikitext_ragel.c"
	switch( (*p) ) {
		case 43: goto st94;
		case 45: goto tr105;
		case 47: goto st94;
		case 64: goto tr137;
		case 92: goto st94;
		case 94: goto st94;
		case 95: goto tr105;
		case 126: goto st94;
	}
	if ( (*p) < 46 ) {
		if ( 36 <= (*p) && (*p) <= 37 )
			goto st94;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st20;
		} else if ( (*p) >= 65 )
			goto st20;
	} else
		goto st20;
	goto tr127;
st20:
	if ( ++p == pe )
		goto _test_eof20;
case 20:
	switch( (*p) ) {
		case 64: goto st21;
		case 95: goto st20;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st20;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st20;
		} else if ( (*p) >= 65 )
			goto st20;
	} else
		goto st20;
	goto tr23;
st21:
	if ( ++p == pe )
		goto _test_eof21;
case 21:
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st22;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st22;
	} else
		goto st22;
	goto tr23;
st22:
	if ( ++p == pe )
		goto _test_eof22;
case 22:
	if ( (*p) == 46 )
		goto st23;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st22;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st22;
	} else
		goto st22;
	goto tr23;
st23:
	if ( ++p == pe )
		goto _test_eof23;
case 23:
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st22;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st24;
	} else
		goto st24;
	goto tr23;
st24:
	if ( ++p == pe )
		goto _test_eof24;
case 24:
	if ( (*p) == 46 )
		goto st23;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st22;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr29;
	} else
		goto tr29;
	goto tr23;
tr29:
#line 1 "NONE"
	{te = p+1;}
#line 102 "wikitext_ragel.rl"
	{act = 1;}
	goto st101;
st101:
	if ( ++p == pe )
		goto _test_eof101;
case 101:
#line 1759 "wikitext_ragel.c"
	if ( (*p) == 46 )
		goto st23;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st22;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr139;
	} else
		goto tr139;
	goto tr138;
tr139:
#line 1 "NONE"
	{te = p+1;}
#line 102 "wikitext_ragel.rl"
	{act = 1;}
	goto st102;
st102:
	if ( ++p == pe )
		goto _test_eof102;
case 102:
#line 1781 "wikitext_ragel.c"
	if ( (*p) == 46 )
		goto st23;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st22;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr140;
	} else
		goto tr140;
	goto tr138;
tr140:
#line 1 "NONE"
	{te = p+1;}
#line 102 "wikitext_ragel.rl"
	{act = 1;}
	goto st103;
st103:
	if ( ++p == pe )
		goto _test_eof103;
case 103:
#line 1803 "wikitext_ragel.c"
	if ( (*p) == 46 )
		goto st23;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st22;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr141;
	} else
		goto tr141;
	goto tr138;
tr141:
#line 1 "NONE"
	{te = p+1;}
#line 102 "wikitext_ragel.rl"
	{act = 1;}
	goto st104;
st104:
	if ( ++p == pe )
		goto _test_eof104;
case 104:
#line 1825 "wikitext_ragel.c"
	if ( (*p) == 46 )
		goto st23;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st22;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st22;
	} else
		goto st22;
	goto tr138;
tr137:
#line 1 "NONE"
	{te = p+1;}
#line 764 "wikitext_ragel.rl"
	{act = 34;}
	goto st105;
st105:
	if ( ++p == pe )
		goto _test_eof105;
case 105:
#line 1847 "wikitext_ragel.c"
	switch( (*p) ) {
		case 43: goto st94;
		case 45: goto st94;
		case 47: goto st94;
		case 64: goto st94;
		case 92: goto st94;
		case 126: goto st94;
	}
	if ( (*p) < 65 ) {
		if ( (*p) > 37 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st22;
		} else if ( (*p) >= 36 )
			goto st94;
	} else if ( (*p) > 90 ) {
		if ( (*p) > 95 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st22;
		} else if ( (*p) >= 94 )
			goto st94;
	} else
		goto st22;
	goto tr127;
tr106:
#line 1 "NONE"
	{te = p+1;}
#line 716 "wikitext_ragel.rl"
	{act = 32;}
	goto st106;
st106:
	if ( ++p == pe )
		goto _test_eof106;
case 106:
#line 1881 "wikitext_ragel.c"
	switch( (*p) ) {
		case 33: goto st92;
		case 44: goto st92;
		case 45: goto st20;
		case 46: goto tr106;
		case 63: goto st92;
		case 64: goto st21;
		case 95: goto st20;
	}
	if ( (*p) < 48 ) {
		if ( 40 <= (*p) && (*p) <= 41 )
			goto st92;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st20;
		} else if ( (*p) >= 65 )
			goto st20;
	} else
		goto st20;
	goto tr125;
tr107:
#line 1 "NONE"
	{te = p+1;}
#line 737 "wikitext_ragel.rl"
	{act = 33;}
	goto st107;
st107:
	if ( ++p == pe )
		goto _test_eof107;
case 107:
#line 1913 "wikitext_ragel.c"
	switch( (*p) ) {
		case 64: goto st21;
		case 95: goto st20;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st20;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr107;
		} else if ( (*p) >= 65 )
			goto tr107;
	} else
		goto tr107;
	goto tr142;
st108:
	if ( ++p == pe )
		goto _test_eof108;
case 108:
	switch( (*p) ) {
		case 33: goto tr144;
		case 47: goto tr145;
		case 66: goto tr146;
		case 69: goto tr147;
		case 77: goto tr148;
		case 78: goto tr149;
		case 80: goto tr150;
		case 83: goto tr151;
		case 84: goto tr152;
		case 98: goto tr146;
		case 101: goto tr147;
		case 109: goto tr148;
		case 110: goto tr149;
		case 112: goto tr153;
		case 115: goto tr151;
		case 116: goto tr152;
	}
	if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr144;
	} else if ( (*p) >= 65 )
		goto tr144;
	goto tr143;
tr145:
#line 1 "NONE"
	{te = p+1;}
	goto st109;
st109:
	if ( ++p == pe )
		goto _test_eof109;
case 109:
#line 1966 "wikitext_ragel.c"
	switch( (*p) ) {
		case 66: goto st25;
		case 69: goto st35;
		case 77: goto st36;
		case 78: goto st40;
		case 80: goto st45;
		case 83: goto st47;
		case 84: goto st52;
		case 98: goto st25;
		case 101: goto st35;
		case 109: goto st36;
		case 110: goto st40;
		case 112: goto st45;
		case 115: goto st47;
		case 116: goto st52;
	}
	goto tr154;
st25:
	if ( ++p == pe )
		goto _test_eof25;
case 25:
	switch( (*p) ) {
		case 76: goto st26;
		case 108: goto st26;
	}
	goto tr30;
st26:
	if ( ++p == pe )
		goto _test_eof26;
case 26:
	switch( (*p) ) {
		case 79: goto st27;
		case 111: goto st27;
	}
	goto tr30;
st27:
	if ( ++p == pe )
		goto _test_eof27;
case 27:
	switch( (*p) ) {
		case 67: goto st28;
		case 99: goto st28;
	}
	goto tr30;
st28:
	if ( ++p == pe )
		goto _test_eof28;
case 28:
	switch( (*p) ) {
		case 75: goto st29;
		case 107: goto st29;
	}
	goto tr30;
st29:
	if ( ++p == pe )
		goto _test_eof29;
case 29:
	switch( (*p) ) {
		case 81: goto st30;
		case 113: goto st30;
	}
	goto tr30;
st30:
	if ( ++p == pe )
		goto _test_eof30;
case 30:
	switch( (*p) ) {
		case 85: goto st31;
		case 117: goto st31;
	}
	goto tr30;
st31:
	if ( ++p == pe )
		goto _test_eof31;
case 31:
	switch( (*p) ) {
		case 79: goto st32;
		case 111: goto st32;
	}
	goto tr30;
st32:
	if ( ++p == pe )
		goto _test_eof32;
case 32:
	switch( (*p) ) {
		case 84: goto st33;
		case 116: goto st33;
	}
	goto tr30;
st33:
	if ( ++p == pe )
		goto _test_eof33;
case 33:
	switch( (*p) ) {
		case 69: goto st34;
		case 101: goto st34;
	}
	goto tr30;
st34:
	if ( ++p == pe )
		goto _test_eof34;
case 34:
	if ( (*p) == 62 )
		goto tr40;
	goto tr30;
st35:
	if ( ++p == pe )
		goto _test_eof35;
case 35:
	switch( (*p) ) {
		case 77: goto st34;
		case 109: goto st34;
	}
	goto tr30;
st36:
	if ( ++p == pe )
		goto _test_eof36;
case 36:
	switch( (*p) ) {
		case 65: goto st37;
		case 97: goto st37;
	}
	goto tr30;
st37:
	if ( ++p == pe )
		goto _test_eof37;
case 37:
	switch( (*p) ) {
		case 84: goto st38;
		case 116: goto st38;
	}
	goto tr30;
st38:
	if ( ++p == pe )
		goto _test_eof38;
case 38:
	switch( (*p) ) {
		case 72: goto st39;
		case 104: goto st39;
	}
	goto tr30;
st39:
	if ( ++p == pe )
		goto _test_eof39;
case 39:
	if ( (*p) == 62 )
		goto tr44;
	goto tr30;
st40:
	if ( ++p == pe )
		goto _test_eof40;
case 40:
	switch( (*p) ) {
		case 79: goto st41;
		case 111: goto st41;
	}
	goto tr30;
st41:
	if ( ++p == pe )
		goto _test_eof41;
case 41:
	switch( (*p) ) {
		case 87: goto st42;
		case 119: goto st42;
	}
	goto tr30;
st42:
	if ( ++p == pe )
		goto _test_eof42;
case 42:
	switch( (*p) ) {
		case 73: goto st43;
		case 105: goto st43;
	}
	goto tr30;
st43:
	if ( ++p == pe )
		goto _test_eof43;
case 43:
	switch( (*p) ) {
		case 75: goto st44;
		case 107: goto st44;
	}
	goto tr30;
st44:
	if ( ++p == pe )
		goto _test_eof44;
case 44:
	switch( (*p) ) {
		case 73: goto st34;
		case 105: goto st34;
	}
	goto tr30;
st45:
	if ( ++p == pe )
		goto _test_eof45;
case 45:
	switch( (*p) ) {
		case 82: goto st46;
		case 114: goto st46;
	}
	goto tr30;
st46:
	if ( ++p == pe )
		goto _test_eof46;
case 46:
	switch( (*p) ) {
		case 69: goto st39;
		case 101: goto st39;
	}
	goto tr30;
st47:
	if ( ++p == pe )
		goto _test_eof47;
case 47:
	switch( (*p) ) {
		case 84: goto st48;
		case 116: goto st48;
	}
	goto tr30;
st48:
	if ( ++p == pe )
		goto _test_eof48;
case 48:
	switch( (*p) ) {
		case 82: goto st49;
		case 114: goto st49;
	}
	goto tr30;
st49:
	if ( ++p == pe )
		goto _test_eof49;
case 49:
	switch( (*p) ) {
		case 79: goto st50;
		case 111: goto st50;
	}
	goto tr30;
st50:
	if ( ++p == pe )
		goto _test_eof50;
case 50:
	switch( (*p) ) {
		case 78: goto st51;
		case 110: goto st51;
	}
	goto tr30;
st51:
	if ( ++p == pe )
		goto _test_eof51;
case 51:
	switch( (*p) ) {
		case 71: goto st34;
		case 103: goto st34;
	}
	goto tr30;
st52:
	if ( ++p == pe )
		goto _test_eof52;
case 52:
	switch( (*p) ) {
		case 73: goto st53;
		case 84: goto st34;
		case 105: goto st53;
		case 116: goto st34;
	}
	goto tr30;
st53:
	if ( ++p == pe )
		goto _test_eof53;
case 53:
	switch( (*p) ) {
		case 77: goto st54;
		case 109: goto st54;
	}
	goto tr30;
st54:
	if ( ++p == pe )
		goto _test_eof54;
case 54:
	switch( (*p) ) {
		case 69: goto st55;
		case 101: goto st55;
	}
	goto tr30;
st55:
	if ( ++p == pe )
		goto _test_eof55;
case 55:
	switch( (*p) ) {
		case 76: goto st56;
		case 108: goto st56;
	}
	goto tr30;
st56:
	if ( ++p == pe )
		goto _test_eof56;
case 56:
	switch( (*p) ) {
		case 73: goto st57;
		case 105: goto st57;
	}
	goto tr30;
st57:
	if ( ++p == pe )
		goto _test_eof57;
case 57:
	switch( (*p) ) {
		case 78: goto st46;
		case 110: goto st46;
	}
	goto tr30;
tr146:
#line 1 "NONE"
	{te = p+1;}
	goto st110;
st110:
	if ( ++p == pe )
		goto _test_eof110;
case 110:
#line 2287 "wikitext_ragel.c"
	switch( (*p) ) {
		case 76: goto st26;
		case 108: goto st26;
	}
	goto tr154;
tr147:
#line 1 "NONE"
	{te = p+1;}
	goto st111;
st111:
	if ( ++p == pe )
		goto _test_eof111;
case 111:
#line 2301 "wikitext_ragel.c"
	switch( (*p) ) {
		case 77: goto st34;
		case 109: goto st34;
	}
	goto tr154;
tr148:
#line 1 "NONE"
	{te = p+1;}
	goto st112;
st112:
	if ( ++p == pe )
		goto _test_eof112;
case 112:
#line 2315 "wikitext_ragel.c"
	switch( (*p) ) {
		case 65: goto st58;
		case 97: goto st58;
	}
	goto tr154;
st58:
	if ( ++p == pe )
		goto _test_eof58;
case 58:
	switch( (*p) ) {
		case 84: goto st59;
		case 116: goto st59;
	}
	goto tr30;
st59:
	if ( ++p == pe )
		goto _test_eof59;
case 59:
	switch( (*p) ) {
		case 72: goto st60;
		case 104: goto st60;
	}
	goto tr30;
st60:
	if ( ++p == pe )
		goto _test_eof60;
case 60:
	if ( (*p) == 62 )
		goto tr61;
	goto tr30;
tr149:
#line 1 "NONE"
	{te = p+1;}
	goto st113;
st113:
	if ( ++p == pe )
		goto _test_eof113;
case 113:
#line 2354 "wikitext_ragel.c"
	switch( (*p) ) {
		case 79: goto st41;
		case 111: goto st41;
	}
	goto tr154;
tr150:
#line 1 "NONE"
	{te = p+1;}
	goto st114;
st114:
	if ( ++p == pe )
		goto _test_eof114;
case 114:
#line 2368 "wikitext_ragel.c"
	switch( (*p) ) {
		case 82: goto st61;
		case 114: goto st61;
	}
	goto tr154;
st61:
	if ( ++p == pe )
		goto _test_eof61;
case 61:
	switch( (*p) ) {
		case 69: goto st60;
		case 101: goto st60;
	}
	goto tr30;
tr151:
#line 1 "NONE"
	{te = p+1;}
	goto st115;
st115:
	if ( ++p == pe )
		goto _test_eof115;
case 115:
#line 2391 "wikitext_ragel.c"
	switch( (*p) ) {
		case 84: goto st48;
		case 116: goto st48;
	}
	goto tr154;
tr152:
#line 1 "NONE"
	{te = p+1;}
	goto st116;
st116:
	if ( ++p == pe )
		goto _test_eof116;
case 116:
#line 2405 "wikitext_ragel.c"
	switch( (*p) ) {
		case 73: goto st62;
		case 84: goto st34;
		case 105: goto st62;
		case 116: goto st34;
	}
	goto tr154;
st62:
	if ( ++p == pe )
		goto _test_eof62;
case 62:
	switch( (*p) ) {
		case 77: goto st63;
		case 109: goto st63;
	}
	goto tr30;
st63:
	if ( ++p == pe )
		goto _test_eof63;
case 63:
	switch( (*p) ) {
		case 69: goto st64;
		case 101: goto st64;
	}
	goto tr30;
st64:
	if ( ++p == pe )
		goto _test_eof64;
case 64:
	switch( (*p) ) {
		case 76: goto st65;
		case 108: goto st65;
	}
	goto tr30;
st65:
	if ( ++p == pe )
		goto _test_eof65;
case 65:
	switch( (*p) ) {
		case 73: goto st66;
		case 105: goto st66;
	}
	goto tr30;
st66:
	if ( ++p == pe )
		goto _test_eof66;
case 66:
	switch( (*p) ) {
		case 78: goto st61;
		case 110: goto st61;
	}
	goto tr30;
tr153:
#line 1 "NONE"
	{te = p+1;}
	goto st117;
st117:
	if ( ++p == pe )
		goto _test_eof117;
case 117:
#line 2466 "wikitext_ragel.c"
	switch( (*p) ) {
		case 82: goto st61;
		case 114: goto st67;
	}
	goto tr154;
st67:
	if ( ++p == pe )
		goto _test_eof67;
case 67:
	switch( (*p) ) {
		case 69: goto st60;
		case 101: goto st68;
	}
	goto tr30;
st68:
	if ( ++p == pe )
		goto _test_eof68;
case 68:
	switch( (*p) ) {
		case 32: goto st69;
		case 62: goto tr61;
	}
	goto tr30;
st69:
	if ( ++p == pe )
		goto _test_eof69;
case 69:
	if ( (*p) == 108 )
		goto st70;
	goto tr30;
st70:
	if ( ++p == pe )
		goto _test_eof70;
case 70:
	if ( (*p) == 97 )
		goto st71;
	goto tr30;
st71:
	if ( ++p == pe )
		goto _test_eof71;
case 71:
	if ( (*p) == 110 )
		goto st72;
	goto tr30;
st72:
	if ( ++p == pe )
		goto _test_eof72;
case 72:
	if ( (*p) == 103 )
		goto st73;
	goto tr30;
st73:
	if ( ++p == pe )
		goto _test_eof73;
case 73:
	if ( (*p) == 61 )
		goto st74;
	goto tr30;
st74:
	if ( ++p == pe )
		goto _test_eof74;
case 74:
	if ( (*p) == 34 )
		goto st75;
	goto tr30;
st75:
	if ( ++p == pe )
		goto _test_eof75;
case 75:
	if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st76;
	} else if ( (*p) >= 65 )
		goto st76;
	goto tr30;
st76:
	if ( ++p == pe )
		goto _test_eof76;
case 76:
	if ( (*p) == 34 )
		goto st60;
	if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st76;
	} else if ( (*p) >= 65 )
		goto st76;
	goto tr30;
tr109:
#line 55 "wikitext_ragel.rl"
	{
        MARK();
    }
	goto st118;
st118:
	if ( ++p == pe )
		goto _test_eof118;
case 118:
#line 2564 "wikitext_ragel.c"
	switch( (*p) ) {
		case 32: goto st119;
		case 61: goto tr109;
	}
	goto tr165;
st119:
	if ( ++p == pe )
		goto _test_eof119;
case 119:
	if ( (*p) == 32 )
		goto st119;
	goto tr165;
tr110:
#line 55 "wikitext_ragel.rl"
	{
        MARK();
    }
	goto st120;
st120:
	if ( ++p == pe )
		goto _test_eof120;
case 120:
#line 2587 "wikitext_ragel.c"
	if ( (*p) == 32 )
		goto tr168;
	goto tr167;
tr111:
#line 1 "NONE"
	{te = p+1;}
#line 737 "wikitext_ragel.rl"
	{act = 33;}
	goto st121;
st121:
	if ( ++p == pe )
		goto _test_eof121;
case 121:
#line 2601 "wikitext_ragel.c"
	switch( (*p) ) {
		case 64: goto st21;
		case 84: goto tr169;
		case 95: goto st20;
		case 116: goto tr169;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st20;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr107;
		} else if ( (*p) >= 65 )
			goto tr107;
	} else
		goto tr107;
	goto tr142;
tr169:
#line 1 "NONE"
	{te = p+1;}
#line 737 "wikitext_ragel.rl"
	{act = 33;}
	goto st122;
st122:
	if ( ++p == pe )
		goto _test_eof122;
case 122:
#line 2630 "wikitext_ragel.c"
	switch( (*p) ) {
		case 64: goto st21;
		case 80: goto tr170;
		case 95: goto st20;
		case 112: goto tr170;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st20;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr107;
		} else if ( (*p) >= 65 )
			goto tr107;
	} else
		goto tr107;
	goto tr142;
tr170:
#line 1 "NONE"
	{te = p+1;}
#line 737 "wikitext_ragel.rl"
	{act = 33;}
	goto st123;
st123:
	if ( ++p == pe )
		goto _test_eof123;
case 123:
#line 2659 "wikitext_ragel.c"
	switch( (*p) ) {
		case 58: goto st77;
		case 64: goto st21;
		case 95: goto st20;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st20;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr107;
		} else if ( (*p) >= 65 )
			goto tr107;
	} else
		goto tr107;
	goto tr142;
st77:
	if ( ++p == pe )
		goto _test_eof77;
case 77:
	if ( (*p) == 47 )
		goto st78;
	goto tr76;
st78:
	if ( ++p == pe )
		goto _test_eof78;
case 78:
	if ( (*p) == 47 )
		goto st79;
	goto tr76;
st79:
	if ( ++p == pe )
		goto _test_eof79;
case 79:
	switch( (*p) ) {
		case 45: goto tr79;
		case 61: goto tr79;
		case 95: goto tr79;
		case 126: goto tr79;
	}
	if ( (*p) < 47 ) {
		if ( (*p) > 40 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr79;
		} else if ( (*p) >= 35 )
			goto tr79;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr79;
		} else if ( (*p) >= 64 )
			goto tr79;
	} else
		goto tr79;
	goto tr76;
tr79:
#line 1 "NONE"
	{te = p+1;}
	goto st124;
st124:
	if ( ++p == pe )
		goto _test_eof124;
case 124:
#line 2724 "wikitext_ragel.c"
	switch( (*p) ) {
		case 33: goto st80;
		case 41: goto st80;
		case 44: goto st80;
		case 46: goto st80;
		case 61: goto tr79;
		case 63: goto st80;
		case 95: goto tr79;
		case 126: goto tr79;
	}
	if ( (*p) < 64 ) {
		if ( 35 <= (*p) && (*p) <= 57 )
			goto tr79;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr79;
	} else
		goto tr79;
	goto tr138;
st80:
	if ( ++p == pe )
		goto _test_eof80;
case 80:
	switch( (*p) ) {
		case 33: goto st80;
		case 41: goto st80;
		case 44: goto st80;
		case 46: goto st80;
		case 61: goto tr79;
		case 63: goto st80;
		case 95: goto tr79;
		case 126: goto tr79;
	}
	if ( (*p) < 64 ) {
		if ( 35 <= (*p) && (*p) <= 57 )
			goto tr79;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr79;
	} else
		goto tr79;
	goto tr80;
tr112:
#line 1 "NONE"
	{te = p+1;}
#line 737 "wikitext_ragel.rl"
	{act = 33;}
	goto st125;
st125:
	if ( ++p == pe )
		goto _test_eof125;
case 125:
#line 2777 "wikitext_ragel.c"
	switch( (*p) ) {
		case 64: goto st21;
		case 84: goto tr172;
		case 95: goto st20;
		case 116: goto tr172;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st20;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr107;
		} else if ( (*p) >= 65 )
			goto tr107;
	} else
		goto tr107;
	goto tr142;
tr172:
#line 1 "NONE"
	{te = p+1;}
#line 737 "wikitext_ragel.rl"
	{act = 33;}
	goto st126;
st126:
	if ( ++p == pe )
		goto _test_eof126;
case 126:
#line 2806 "wikitext_ragel.c"
	switch( (*p) ) {
		case 64: goto st21;
		case 84: goto tr173;
		case 95: goto st20;
		case 116: goto tr173;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st20;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr107;
		} else if ( (*p) >= 65 )
			goto tr107;
	} else
		goto tr107;
	goto tr142;
tr173:
#line 1 "NONE"
	{te = p+1;}
#line 737 "wikitext_ragel.rl"
	{act = 33;}
	goto st127;
st127:
	if ( ++p == pe )
		goto _test_eof127;
case 127:
#line 2835 "wikitext_ragel.c"
	switch( (*p) ) {
		case 64: goto st21;
		case 80: goto tr174;
		case 95: goto st20;
		case 112: goto tr174;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st20;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr107;
		} else if ( (*p) >= 65 )
			goto tr107;
	} else
		goto tr107;
	goto tr142;
tr174:
#line 1 "NONE"
	{te = p+1;}
#line 737 "wikitext_ragel.rl"
	{act = 33;}
	goto st128;
st128:
	if ( ++p == pe )
		goto _test_eof128;
case 128:
#line 2864 "wikitext_ragel.c"
	switch( (*p) ) {
		case 58: goto st77;
		case 64: goto st21;
		case 83: goto tr170;
		case 95: goto st20;
		case 115: goto tr170;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st20;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr107;
		} else if ( (*p) >= 65 )
			goto tr107;
	} else
		goto tr107;
	goto tr142;
tr113:
#line 1 "NONE"
	{te = p+1;}
#line 737 "wikitext_ragel.rl"
	{act = 33;}
	goto st129;
st129:
	if ( ++p == pe )
		goto _test_eof129;
case 129:
#line 2894 "wikitext_ragel.c"
	switch( (*p) ) {
		case 64: goto st21;
		case 65: goto tr175;
		case 95: goto st20;
		case 97: goto tr175;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st20;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 98 <= (*p) && (*p) <= 122 )
				goto tr107;
		} else if ( (*p) >= 66 )
			goto tr107;
	} else
		goto tr107;
	goto tr142;
tr175:
#line 1 "NONE"
	{te = p+1;}
#line 737 "wikitext_ragel.rl"
	{act = 33;}
	goto st130;
st130:
	if ( ++p == pe )
		goto _test_eof130;
case 130:
#line 2923 "wikitext_ragel.c"
	switch( (*p) ) {
		case 64: goto st21;
		case 73: goto tr176;
		case 95: goto st20;
		case 105: goto tr176;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st20;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr107;
		} else if ( (*p) >= 65 )
			goto tr107;
	} else
		goto tr107;
	goto tr142;
tr176:
#line 1 "NONE"
	{te = p+1;}
#line 737 "wikitext_ragel.rl"
	{act = 33;}
	goto st131;
st131:
	if ( ++p == pe )
		goto _test_eof131;
case 131:
#line 2952 "wikitext_ragel.c"
	switch( (*p) ) {
		case 64: goto st21;
		case 76: goto tr177;
		case 95: goto st20;
		case 108: goto tr177;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st20;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr107;
		} else if ( (*p) >= 65 )
			goto tr107;
	} else
		goto tr107;
	goto tr142;
tr177:
#line 1 "NONE"
	{te = p+1;}
#line 737 "wikitext_ragel.rl"
	{act = 33;}
	goto st132;
st132:
	if ( ++p == pe )
		goto _test_eof132;
case 132:
#line 2981 "wikitext_ragel.c"
	switch( (*p) ) {
		case 64: goto st21;
		case 84: goto tr178;
		case 95: goto st20;
		case 116: goto tr178;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st20;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr107;
		} else if ( (*p) >= 65 )
			goto tr107;
	} else
		goto tr107;
	goto tr142;
tr178:
#line 1 "NONE"
	{te = p+1;}
#line 737 "wikitext_ragel.rl"
	{act = 33;}
	goto st133;
st133:
	if ( ++p == pe )
		goto _test_eof133;
case 133:
#line 3010 "wikitext_ragel.c"
	switch( (*p) ) {
		case 64: goto st21;
		case 79: goto tr179;
		case 95: goto st20;
		case 111: goto tr179;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st20;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr107;
		} else if ( (*p) >= 65 )
			goto tr107;
	} else
		goto tr107;
	goto tr142;
tr179:
#line 1 "NONE"
	{te = p+1;}
#line 737 "wikitext_ragel.rl"
	{act = 33;}
	goto st134;
st134:
	if ( ++p == pe )
		goto _test_eof134;
case 134:
#line 3039 "wikitext_ragel.c"
	switch( (*p) ) {
		case 58: goto st81;
		case 64: goto st21;
		case 95: goto st20;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st20;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr107;
		} else if ( (*p) >= 65 )
			goto tr107;
	} else
		goto tr107;
	goto tr142;
st81:
	if ( ++p == pe )
		goto _test_eof81;
case 81:
	if ( (*p) == 95 )
		goto st20;
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st20;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st20;
		} else if ( (*p) >= 65 )
			goto st20;
	} else
		goto st20;
	goto tr76;
tr114:
#line 1 "NONE"
	{te = p+1;}
#line 737 "wikitext_ragel.rl"
	{act = 33;}
	goto st135;
st135:
	if ( ++p == pe )
		goto _test_eof135;
case 135:
#line 3085 "wikitext_ragel.c"
	switch( (*p) ) {
		case 64: goto st21;
		case 86: goto tr181;
		case 95: goto st20;
		case 118: goto tr181;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st20;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr107;
		} else if ( (*p) >= 65 )
			goto tr107;
	} else
		goto tr107;
	goto tr142;
tr181:
#line 1 "NONE"
	{te = p+1;}
#line 737 "wikitext_ragel.rl"
	{act = 33;}
	goto st136;
st136:
	if ( ++p == pe )
		goto _test_eof136;
case 136:
#line 3114 "wikitext_ragel.c"
	switch( (*p) ) {
		case 64: goto st21;
		case 78: goto tr170;
		case 95: goto st20;
		case 110: goto tr170;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st20;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr107;
		} else if ( (*p) >= 65 )
			goto tr107;
	} else
		goto tr107;
	goto tr142;
st137:
	if ( ++p == pe )
		goto _test_eof137;
case 137:
	if ( (*p) == 91 )
		goto tr183;
	goto tr182;
tr183:
#line 1 "NONE"
	{te = p+1;}
	goto st138;
st138:
	if ( ++p == pe )
		goto _test_eof138;
case 138:
#line 3148 "wikitext_ragel.c"
	switch( (*p) ) {
		case 45: goto st82;
		case 58: goto tr84;
	}
	if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st82;
	} else if ( (*p) >= 65 )
		goto st82;
	goto tr184;
st82:
	if ( ++p == pe )
		goto _test_eof82;
case 82:
	switch( (*p) ) {
		case 45: goto st82;
		case 58: goto tr84;
	}
	if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st82;
	} else if ( (*p) >= 65 )
		goto st82;
	goto tr82;
st139:
	if ( ++p == pe )
		goto _test_eof139;
case 139:
	if ( (*p) == 93 )
		goto tr186;
	goto tr185;
tr117:
#line 1 "NONE"
	{te = p+1;}
#line 764 "wikitext_ragel.rl"
	{act = 34;}
	goto st140;
st140:
	if ( ++p == pe )
		goto _test_eof140;
case 140:
#line 3190 "wikitext_ragel.c"
	switch( (*p) ) {
		case 43: goto st94;
		case 45: goto tr105;
		case 47: goto st94;
		case 64: goto tr137;
		case 92: goto st94;
		case 94: goto st94;
		case 95: goto tr187;
		case 126: goto st94;
	}
	if ( (*p) < 46 ) {
		if ( 36 <= (*p) && (*p) <= 37 )
			goto st94;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st20;
		} else if ( (*p) >= 65 )
			goto st20;
	} else
		goto st20;
	goto tr127;
tr187:
#line 1 "NONE"
	{te = p+1;}
#line 764 "wikitext_ragel.rl"
	{act = 34;}
	goto st141;
st141:
	if ( ++p == pe )
		goto _test_eof141;
case 141:
#line 3223 "wikitext_ragel.c"
	switch( (*p) ) {
		case 43: goto st94;
		case 45: goto tr105;
		case 47: goto st94;
		case 64: goto tr137;
		case 78: goto st83;
		case 92: goto st94;
		case 94: goto st94;
		case 95: goto tr105;
		case 126: goto st94;
	}
	if ( (*p) < 46 ) {
		if ( 36 <= (*p) && (*p) <= 37 )
			goto st94;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st20;
		} else if ( (*p) >= 65 )
			goto st20;
	} else
		goto st20;
	goto tr127;
st83:
	if ( ++p == pe )
		goto _test_eof83;
case 83:
	switch( (*p) ) {
		case 64: goto st21;
		case 79: goto st84;
		case 95: goto st20;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st20;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st20;
		} else if ( (*p) >= 65 )
			goto st20;
	} else
		goto st20;
	goto tr85;
st84:
	if ( ++p == pe )
		goto _test_eof84;
case 84:
	switch( (*p) ) {
		case 64: goto st21;
		case 84: goto st85;
		case 95: goto st20;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st20;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st20;
		} else if ( (*p) >= 65 )
			goto st20;
	} else
		goto st20;
	goto tr85;
st85:
	if ( ++p == pe )
		goto _test_eof85;
case 85:
	switch( (*p) ) {
		case 64: goto st21;
		case 79: goto st86;
		case 95: goto st20;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st20;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st20;
		} else if ( (*p) >= 65 )
			goto st20;
	} else
		goto st20;
	goto tr85;
st86:
	if ( ++p == pe )
		goto _test_eof86;
case 86:
	switch( (*p) ) {
		case 64: goto st21;
		case 67: goto st87;
		case 95: goto st20;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st20;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st20;
		} else if ( (*p) >= 65 )
			goto st20;
	} else
		goto st20;
	goto tr85;
st87:
	if ( ++p == pe )
		goto _test_eof87;
case 87:
	switch( (*p) ) {
		case 64: goto st21;
		case 95: goto st88;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st20;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st20;
		} else if ( (*p) >= 65 )
			goto st20;
	} else
		goto st20;
	goto tr85;
st88:
	if ( ++p == pe )
		goto _test_eof88;
case 88:
	switch( (*p) ) {
		case 64: goto st21;
		case 95: goto tr91;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st20;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st20;
		} else if ( (*p) >= 65 )
			goto st20;
	} else
		goto st20;
	goto tr85;
tr91:
#line 1 "NONE"
	{te = p+1;}
#line 102 "wikitext_ragel.rl"
	{act = 1;}
	goto st142;
st142:
	if ( ++p == pe )
		goto _test_eof142;
case 142:
#line 3381 "wikitext_ragel.c"
	switch( (*p) ) {
		case 64: goto st21;
		case 95: goto st20;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st20;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st20;
		} else if ( (*p) >= 65 )
			goto st20;
	} else
		goto st20;
	goto tr138;
st143:
	if ( ++p == pe )
		goto _test_eof143;
case 143:
	switch( (*p) ) {
		case 123: goto tr190;
		case 124: goto tr191;
	}
	goto tr189;
st144:
	if ( ++p == pe )
		goto _test_eof144;
case 144:
	if ( (*p) == 125 )
		goto tr193;
	goto tr192;
tr120:
#line 1 "NONE"
	{te = p+1;}
#line 667 "wikitext_ragel.rl"
	{act = 30;}
	goto st145;
tr193:
#line 1 "NONE"
	{te = p+1;}
#line 421 "wikitext_ragel.rl"
	{act = 14;}
	goto st145;
st145:
	if ( ++p == pe )
		goto _test_eof145;
case 145:
#line 3430 "wikitext_ragel.c"
	if ( (*p) == 125 )
		goto tr194;
	goto tr23;
	}
	_test_eof89: cs = 89; goto _test_eof; 
	_test_eof1: cs = 1; goto _test_eof; 
	_test_eof2: cs = 2; goto _test_eof; 
	_test_eof3: cs = 3; goto _test_eof; 
	_test_eof4: cs = 4; goto _test_eof; 
	_test_eof5: cs = 5; goto _test_eof; 
	_test_eof6: cs = 6; goto _test_eof; 
	_test_eof90: cs = 90; goto _test_eof; 
	_test_eof91: cs = 91; goto _test_eof; 
	_test_eof92: cs = 92; goto _test_eof; 
	_test_eof93: cs = 93; goto _test_eof; 
	_test_eof94: cs = 94; goto _test_eof; 
	_test_eof95: cs = 95; goto _test_eof; 
	_test_eof7: cs = 7; goto _test_eof; 
	_test_eof8: cs = 8; goto _test_eof; 
	_test_eof9: cs = 9; goto _test_eof; 
	_test_eof10: cs = 10; goto _test_eof; 
	_test_eof11: cs = 11; goto _test_eof; 
	_test_eof12: cs = 12; goto _test_eof; 
	_test_eof13: cs = 13; goto _test_eof; 
	_test_eof14: cs = 14; goto _test_eof; 
	_test_eof15: cs = 15; goto _test_eof; 
	_test_eof16: cs = 16; goto _test_eof; 
	_test_eof17: cs = 17; goto _test_eof; 
	_test_eof18: cs = 18; goto _test_eof; 
	_test_eof19: cs = 19; goto _test_eof; 
	_test_eof96: cs = 96; goto _test_eof; 
	_test_eof97: cs = 97; goto _test_eof; 
	_test_eof98: cs = 98; goto _test_eof; 
	_test_eof99: cs = 99; goto _test_eof; 
	_test_eof100: cs = 100; goto _test_eof; 
	_test_eof20: cs = 20; goto _test_eof; 
	_test_eof21: cs = 21; goto _test_eof; 
	_test_eof22: cs = 22; goto _test_eof; 
	_test_eof23: cs = 23; goto _test_eof; 
	_test_eof24: cs = 24; goto _test_eof; 
	_test_eof101: cs = 101; goto _test_eof; 
	_test_eof102: cs = 102; goto _test_eof; 
	_test_eof103: cs = 103; goto _test_eof; 
	_test_eof104: cs = 104; goto _test_eof; 
	_test_eof105: cs = 105; goto _test_eof; 
	_test_eof106: cs = 106; goto _test_eof; 
	_test_eof107: cs = 107; goto _test_eof; 
	_test_eof108: cs = 108; goto _test_eof; 
	_test_eof109: cs = 109; goto _test_eof; 
	_test_eof25: cs = 25; goto _test_eof; 
	_test_eof26: cs = 26; goto _test_eof; 
	_test_eof27: cs = 27; goto _test_eof; 
	_test_eof28: cs = 28; goto _test_eof; 
	_test_eof29: cs = 29; goto _test_eof; 
	_test_eof30: cs = 30; goto _test_eof; 
	_test_eof31: cs = 31; goto _test_eof; 
	_test_eof32: cs = 32; goto _test_eof; 
	_test_eof33: cs = 33; goto _test_eof; 
	_test_eof34: cs = 34; goto _test_eof; 
	_test_eof35: cs = 35; goto _test_eof; 
	_test_eof36: cs = 36; goto _test_eof; 
	_test_eof37: cs = 37; goto _test_eof; 
	_test_eof38: cs = 38; goto _test_eof; 
	_test_eof39: cs = 39; goto _test_eof; 
	_test_eof40: cs = 40; goto _test_eof; 
	_test_eof41: cs = 41; goto _test_eof; 
	_test_eof42: cs = 42; goto _test_eof; 
	_test_eof43: cs = 43; goto _test_eof; 
	_test_eof44: cs = 44; goto _test_eof; 
	_test_eof45: cs = 45; goto _test_eof; 
	_test_eof46: cs = 46; goto _test_eof; 
	_test_eof47: cs = 47; goto _test_eof; 
	_test_eof48: cs = 48; goto _test_eof; 
	_test_eof49: cs = 49; goto _test_eof; 
	_test_eof50: cs = 50; goto _test_eof; 
	_test_eof51: cs = 51; goto _test_eof; 
	_test_eof52: cs = 52; goto _test_eof; 
	_test_eof53: cs = 53; goto _test_eof; 
	_test_eof54: cs = 54; goto _test_eof; 
	_test_eof55: cs = 55; goto _test_eof; 
	_test_eof56: cs = 56; goto _test_eof; 
	_test_eof57: cs = 57; goto _test_eof; 
	_test_eof110: cs = 110; goto _test_eof; 
	_test_eof111: cs = 111; goto _test_eof; 
	_test_eof112: cs = 112; goto _test_eof; 
	_test_eof58: cs = 58; goto _test_eof; 
	_test_eof59: cs = 59; goto _test_eof; 
	_test_eof60: cs = 60; goto _test_eof; 
	_test_eof113: cs = 113; goto _test_eof; 
	_test_eof114: cs = 114; goto _test_eof; 
	_test_eof61: cs = 61; goto _test_eof; 
	_test_eof115: cs = 115; goto _test_eof; 
	_test_eof116: cs = 116; goto _test_eof; 
	_test_eof62: cs = 62; goto _test_eof; 
	_test_eof63: cs = 63; goto _test_eof; 
	_test_eof64: cs = 64; goto _test_eof; 
	_test_eof65: cs = 65; goto _test_eof; 
	_test_eof66: cs = 66; goto _test_eof; 
	_test_eof117: cs = 117; goto _test_eof; 
	_test_eof67: cs = 67; goto _test_eof; 
	_test_eof68: cs = 68; goto _test_eof; 
	_test_eof69: cs = 69; goto _test_eof; 
	_test_eof70: cs = 70; goto _test_eof; 
	_test_eof71: cs = 71; goto _test_eof; 
	_test_eof72: cs = 72; goto _test_eof; 
	_test_eof73: cs = 73; goto _test_eof; 
	_test_eof74: cs = 74; goto _test_eof; 
	_test_eof75: cs = 75; goto _test_eof; 
	_test_eof76: cs = 76; goto _test_eof; 
	_test_eof118: cs = 118; goto _test_eof; 
	_test_eof119: cs = 119; goto _test_eof; 
	_test_eof120: cs = 120; goto _test_eof; 
	_test_eof121: cs = 121; goto _test_eof; 
	_test_eof122: cs = 122; goto _test_eof; 
	_test_eof123: cs = 123; goto _test_eof; 
	_test_eof77: cs = 77; goto _test_eof; 
	_test_eof78: cs = 78; goto _test_eof; 
	_test_eof79: cs = 79; goto _test_eof; 
	_test_eof124: cs = 124; goto _test_eof; 
	_test_eof80: cs = 80; goto _test_eof; 
	_test_eof125: cs = 125; goto _test_eof; 
	_test_eof126: cs = 126; goto _test_eof; 
	_test_eof127: cs = 127; goto _test_eof; 
	_test_eof128: cs = 128; goto _test_eof; 
	_test_eof129: cs = 129; goto _test_eof; 
	_test_eof130: cs = 130; goto _test_eof; 
	_test_eof131: cs = 131; goto _test_eof; 
	_test_eof132: cs = 132; goto _test_eof; 
	_test_eof133: cs = 133; goto _test_eof; 
	_test_eof134: cs = 134; goto _test_eof; 
	_test_eof81: cs = 81; goto _test_eof; 
	_test_eof135: cs = 135; goto _test_eof; 
	_test_eof136: cs = 136; goto _test_eof; 
	_test_eof137: cs = 137; goto _test_eof; 
	_test_eof138: cs = 138; goto _test_eof; 
	_test_eof82: cs = 82; goto _test_eof; 
	_test_eof139: cs = 139; goto _test_eof; 
	_test_eof140: cs = 140; goto _test_eof; 
	_test_eof141: cs = 141; goto _test_eof; 
	_test_eof83: cs = 83; goto _test_eof; 
	_test_eof84: cs = 84; goto _test_eof; 
	_test_eof85: cs = 85; goto _test_eof; 
	_test_eof86: cs = 86; goto _test_eof; 
	_test_eof87: cs = 87; goto _test_eof; 
	_test_eof88: cs = 88; goto _test_eof; 
	_test_eof142: cs = 142; goto _test_eof; 
	_test_eof143: cs = 143; goto _test_eof; 
	_test_eof144: cs = 144; goto _test_eof; 
	_test_eof145: cs = 145; goto _test_eof; 

	_test_eof: {}
	if ( p == eof )
	{
	switch ( cs ) {
	case 90: goto tr121;
	case 91: goto tr123;
	case 92: goto tr125;
	case 93: goto tr126;
	case 94: goto tr127;
	case 95: goto tr128;
	case 7: goto tr7;
	case 8: goto tr7;
	case 9: goto tr7;
	case 10: goto tr7;
	case 11: goto tr7;
	case 12: goto tr7;
	case 13: goto tr7;
	case 14: goto tr7;
	case 15: goto tr7;
	case 16: goto tr7;
	case 17: goto tr7;
	case 18: goto tr7;
	case 19: goto tr7;
	case 96: goto tr132;
	case 97: goto tr132;
	case 98: goto tr132;
	case 99: goto tr132;
	case 100: goto tr127;
	case 20: goto tr23;
	case 21: goto tr23;
	case 22: goto tr23;
	case 23: goto tr23;
	case 24: goto tr23;
	case 101: goto tr138;
	case 102: goto tr138;
	case 103: goto tr138;
	case 104: goto tr138;
	case 105: goto tr127;
	case 106: goto tr125;
	case 107: goto tr142;
	case 108: goto tr143;
	case 109: goto tr154;
	case 25: goto tr30;
	case 26: goto tr30;
	case 27: goto tr30;
	case 28: goto tr30;
	case 29: goto tr30;
	case 30: goto tr30;
	case 31: goto tr30;
	case 32: goto tr30;
	case 33: goto tr30;
	case 34: goto tr30;
	case 35: goto tr30;
	case 36: goto tr30;
	case 37: goto tr30;
	case 38: goto tr30;
	case 39: goto tr30;
	case 40: goto tr30;
	case 41: goto tr30;
	case 42: goto tr30;
	case 43: goto tr30;
	case 44: goto tr30;
	case 45: goto tr30;
	case 46: goto tr30;
	case 47: goto tr30;
	case 48: goto tr30;
	case 49: goto tr30;
	case 50: goto tr30;
	case 51: goto tr30;
	case 52: goto tr30;
	case 53: goto tr30;
	case 54: goto tr30;
	case 55: goto tr30;
	case 56: goto tr30;
	case 57: goto tr30;
	case 110: goto tr154;
	case 111: goto tr154;
	case 112: goto tr154;
	case 58: goto tr30;
	case 59: goto tr30;
	case 60: goto tr30;
	case 113: goto tr154;
	case 114: goto tr154;
	case 61: goto tr30;
	case 115: goto tr154;
	case 116: goto tr154;
	case 62: goto tr30;
	case 63: goto tr30;
	case 64: goto tr30;
	case 65: goto tr30;
	case 66: goto tr30;
	case 117: goto tr154;
	case 67: goto tr30;
	case 68: goto tr30;
	case 69: goto tr30;
	case 70: goto tr30;
	case 71: goto tr30;
	case 72: goto tr30;
	case 73: goto tr30;
	case 74: goto tr30;
	case 75: goto tr30;
	case 76: goto tr30;
	case 118: goto tr165;
	case 119: goto tr165;
	case 120: goto tr167;
	case 121: goto tr142;
	case 122: goto tr142;
	case 123: goto tr142;
	case 77: goto tr76;
	case 78: goto tr76;
	case 79: goto tr76;
	case 124: goto tr138;
	case 80: goto tr80;
	case 125: goto tr142;
	case 126: goto tr142;
	case 127: goto tr142;
	case 128: goto tr142;
	case 129: goto tr142;
	case 130: goto tr142;
	case 131: goto tr142;
	case 132: goto tr142;
	case 133: goto tr142;
	case 134: goto tr142;
	case 81: goto tr76;
	case 135: goto tr142;
	case 136: goto tr142;
	case 137: goto tr182;
	case 138: goto tr184;
	case 82: goto tr82;
	case 139: goto tr185;
	case 140: goto tr127;
	case 141: goto tr127;
	case 83: goto tr85;
	case 84: goto tr85;
	case 85: goto tr85;
	case 86: goto tr85;
	case 87: goto tr85;
	case 88: goto tr85;
	case 142: goto tr138;
	case 143: goto tr189;
	case 144: goto tr192;
	case 145: goto tr23;
	}
	}

	_out: {}
	}

#line 869 "wikitext_ragel.rl"
    if (cs == wikitext_error)
        rb_raise(eWikitextParserError, "failed before finding a token");
    else if (out->type == NO_TOKEN){
        out->stop = p;
        out->type = END_OF_FILE;
        //rb_raise(eWikitextParserError, "failed to produce a token");
    }
}
