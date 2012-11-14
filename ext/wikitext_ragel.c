
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



#line 55 "wikitext_ragel.c"
static const int wikitext_start = 101;
static const int wikitext_first_final = 101;
static const int wikitext_error = 0;

static const int wikitext_en_main = 101;


#line 804 "wikitext_ragel.rl"


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
    
#line 110 "wikitext_ragel.c"
	{
	cs = wikitext_start;
	ts = 0;
	te = 0;
	act = 0;
	}

#line 850 "wikitext_ragel.rl"
    
#line 120 "wikitext_ragel.c"
	{
	if ( p == pe )
		goto _test_eof;
	switch ( cs )
	{
tr0:
#line 1 "NONE"
	{	switch( act ) {
	case 0:
	{{goto st0;}}
	break;
	case 1:
	{{p = ((te))-1;}
            EMIT(SKIP);
            {p++; cs = 101; goto _out;}
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
                {p++; cs = 101; goto _out;}
              break;
              case DEFAULT :
                ERROR("Closing without opening");
                EMIT(SKIP);
                {p++; cs = 101; goto _out;}
              break;
              default :
                EMIT(SKIP);
                {p++; cs = 101; goto _out;}
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
                {p++; cs = 101; goto _out;}
              break;
              case DEFAULT :
                EMIT(PRINTABLE);
                {p++; cs = 101; goto _out;}
              break;
              default :
                EMIT(SKIP);
                {p++; cs = 101; goto _out;}
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
                {p++; cs = 101; goto _out;}
              break;
              case DEFAULT :
                EMIT(ALNUM);
                {p++; cs = 101; goto _out;}
              break;
              default :
                EMIT(SKIP);
                {p++; cs = 101; goto _out;}
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
                {p++; cs = 101; goto _out;}
              break;
              case DEFAULT :
                EMIT(ALNUM);
                {p++; cs = 101; goto _out;}
              break;
              default :
                EMIT(SKIP);
                {p++; cs = 101; goto _out;}
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
                {p++; cs = 101; goto _out;}
              break;
              case DEFAULT :
                EMIT(PRINTABLE);
                {p++; cs = 101; goto _out;}
              break;
              default :
                EMIT(SKIP);
                {p++; cs = 101; goto _out;}
              break;
            }
        }
	break;
	}
	}
	goto st101;
tr7:
#line 555 "wikitext_ragel.rl"
	{{p = ((te))-1;}{
          if(GET_STATE() == DEFAULT)
            EMIT(PRINTABLE);
          else
            EMIT(SKIP);
          {p++; cs = 101; goto _out;}
        }}
	goto st101;
tr10:
#line 540 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(SKIP);
            {p++; cs = 101; goto _out;}
        }}
	goto st101;
tr12:
#line 534 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(SKIP);
            {p++; cs = 101; goto _out;}
        }}
	goto st101;
tr14:
#line 528 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(SKIP);
            {p++; cs = 101; goto _out;}
        }}
	goto st101;
tr18:
#line 522 "wikitext_ragel.rl"
	{te = p+1;{
          EMIT(SKIP);
          {p++; cs = 101; goto _out;}
        }}
	goto st101;
tr22:
#line 516 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(SKIP);
            {p++; cs = 101; goto _out;}
        }}
	goto st101;
tr29:
#line 564 "wikitext_ragel.rl"
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
                {p++; cs = 101; goto _out;}
              break;
              default :
                EMIT(SKIP);
                {p++; cs = 101; goto _out;}
              break;
            }
        }}
	goto st101;
tr39:
#line 102 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(SKIP);
            {p++; cs = 101; goto _out;}
        }}
	goto st101;
tr43:
#line 127 "wikitext_ragel.rl"
	{te = p+1;{
            state = GET_STATE();
            switch(state){
              case NOWIKI :
                opening = LAST_TYPE();
                if(opening == PRE_START) {
                  POP(); 
                  EMIT(SKIP);
                  {p++; cs = 101; goto _out;}
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
                {p++; cs = 101; goto _out;}
              break;
            }
        }}
	goto st101;
tr61:
#line 109 "wikitext_ragel.rl"
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
                {p++; cs = 101; goto _out;}
              break;
            }
        }}
	goto st101;
tr84:
#line 739 "wikitext_ragel.rl"
	{{p = ((te))-1;}{
            state = GET_STATE();
            switch(state){
              case INNER_LINK :
              case LINK :
                TODO(); // Push token
                EMIT(ALNUM);
                {p++; cs = 101; goto _out;}
              break;
              case DEFAULT :
                EMIT(ALNUM);
                {p++; cs = 101; goto _out;}
              break;
              default :
                EMIT(SKIP);
                {p++; cs = 101; goto _out;}
              break;
            }
        }}
	goto st101;
tr88:
#line 102 "wikitext_ragel.rl"
	{{p = ((te))-1;}{
            EMIT(SKIP);
            {p++; cs = 101; goto _out;}
        }}
	goto st101;
tr90:
#line 307 "wikitext_ragel.rl"
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
                {p++; cs = 101; goto _out;}
              break;
              default :
                EMIT(SKIP);
                {p++; cs = 101; goto _out;}
              break;
            }
        }}
	goto st101;
tr92:
#line 289 "wikitext_ragel.rl"
	{te = p+1;{
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
                {p++; cs = 101; goto _out;}
              break;
            }
        }}
	goto st101;
tr93:
#line 774 "wikitext_ragel.rl"
	{{p = ((te))-1;}{
            state = GET_STATE();
            switch(state){
              case INNER_LINK :
              case LINK :
                TODO(); // Push token
                EMIT(ALNUM);
                {p++; cs = 101; goto _out;}
              break;
              case DEFAULT :
                EMIT(PRINTABLE);
                {p++; cs = 101; goto _out;}
              break;
              default :
                EMIT(SKIP);
                {p++; cs = 101; goto _out;}
              break;
            }
        }}
	goto st101;
tr104:
#line 60 "wikitext_ragel.rl"
	{
        out->code_point = *p & 0x7f;
    }
#line 796 "wikitext_ragel.rl"
	{te = p+1;{
                EMIT(SKIP);
                {p++; cs = 101; goto _out;}
        }}
	goto st101;
tr105:
#line 690 "wikitext_ragel.rl"
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
            {p++; cs = 101; goto _out;}
        }}
#line 60 "wikitext_ragel.rl"
	{
        out->code_point = *p & 0x7f;
    }
	goto st101;
tr109:
#line 546 "wikitext_ragel.rl"
	{te = p+1;{
          if(GET_STATE() == DEFAULT)
            EMIT(PRINTABLE);
          else
            EMIT(SKIP);
          {p++; cs = 101; goto _out;}
        }}
	goto st101;
tr130:
#line 774 "wikitext_ragel.rl"
	{te = p;p--;{
            state = GET_STATE();
            switch(state){
              case INNER_LINK :
              case LINK :
                TODO(); // Push token
                EMIT(ALNUM);
                {p++; cs = 101; goto _out;}
              break;
              case DEFAULT :
                EMIT(PRINTABLE);
                {p++; cs = 101; goto _out;}
              break;
              default :
                EMIT(SKIP);
                {p++; cs = 101; goto _out;}
              break;
            }
        }}
	goto st101;
tr131:
#line 690 "wikitext_ragel.rl"
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
            {p++; cs = 101; goto _out;}
        }}
	goto st101;
tr132:
#line 690 "wikitext_ragel.rl"
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
            {p++; cs = 101; goto _out;}
        }}
	goto st101;
tr133:
#line 201 "wikitext_ragel.rl"
	{te = p;p--;{
            if (out->column_start == 1 || last_token_type == BLOCKQUOTE)
            {
                REWIND();
                EMIT(SKIP);
                {p++; cs = 101; goto _out;}
            } else {
              state = GET_STATE();
              switch(state){
                case INNER_LINK :
                case LINK :
                  TODO(); // Push token
                  EMIT(SPACE);
                  {p++; cs = 101; goto _out;}
                break;
                case DEFAULT :
                  EMIT(SPACE);
                  {p++; cs = 101; goto _out;}
                break;
                default :
                  EMIT(SKIP);
                  {p++; cs = 101; goto _out;}
                break;
              }
            }
        }}
	goto st101;
tr135:
#line 718 "wikitext_ragel.rl"
	{te = p;p--;{
            state = GET_STATE();
            switch(state){
              case INNER_LINK :
              case LINK :
                TODO(); // Push token
                EMIT(ALNUM);
                {p++; cs = 101; goto _out;}
              break;
              case DEFAULT :
                EMIT(ALNUM);
                {p++; cs = 101; goto _out;}
              break;
              default :
                EMIT(SKIP);
                {p++; cs = 101; goto _out;}
              break;
            }
        }}
	goto st101;
tr136:
#line 229 "wikitext_ragel.rl"
	{te = p;p--;{
            if (out->column_start == 1 )
                EMIT(SKIP);
            else
              if(GET_STATE() == DEFAULT)
                EMIT(PRINTABLE);             
              else
                EMIT(SKIP);
            {p++; cs = 101; goto _out;}
        }}
	goto st101;
tr137:
#line 555 "wikitext_ragel.rl"
	{te = p;p--;{
          if(GET_STATE() == DEFAULT)
            EMIT(PRINTABLE);
          else
            EMIT(SKIP);
          {p++; cs = 101; goto _out;}
        }}
	goto st101;
tr141:
#line 155 "wikitext_ragel.rl"
	{te = p;p--;{
            if (DISTANCE() > 1) {
              EMIT(SKIP);
              {p++; cs = 101; goto _out;}
            } else {
              if(GET_STATE() == DEFAULT) {
                EMIT(PRINTABLE);
                {p++; cs = 101; goto _out;}
              }
            }
        }}
	goto st101;
tr145:
#line 155 "wikitext_ragel.rl"
	{te = p+1;{
            if (DISTANCE() > 1) {
              EMIT(SKIP);
              {p++; cs = 101; goto _out;}
            } else {
              if(GET_STATE() == DEFAULT) {
                EMIT(PRINTABLE);
                {p++; cs = 101; goto _out;}
              }
            }
        }}
	goto st101;
tr147:
#line 102 "wikitext_ragel.rl"
	{te = p;p--;{
            EMIT(SKIP);
            {p++; cs = 101; goto _out;}
        }}
	goto st101;
tr151:
#line 739 "wikitext_ragel.rl"
	{te = p;p--;{
            state = GET_STATE();
            switch(state){
              case INNER_LINK :
              case LINK :
                TODO(); // Push token
                EMIT(ALNUM);
                {p++; cs = 101; goto _out;}
              break;
              case DEFAULT :
                EMIT(ALNUM);
                {p++; cs = 101; goto _out;}
              break;
              default :
                EMIT(SKIP);
                {p++; cs = 101; goto _out;}
              break;
            }
        }}
	goto st101;
tr152:
#line 584 "wikitext_ragel.rl"
	{te = p;p--;{
            state = GET_STATE();
            switch(state){
              case INNER_LINK :
              case LINK :
                TODO(); // Push token
                EMIT(ALNUM);
                {p++; cs = 101; goto _out;}
              break;
              case DEFAULT :
                EMIT(ALNUM);
                {p++; cs = 101; goto _out;}
              break;
              default :
                EMIT(SKIP);
                {p++; cs = 101; goto _out;}
              break;
            }
        }}
	goto st101;
tr153:
#line 564 "wikitext_ragel.rl"
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
                {p++; cs = 101; goto _out;}
              break;
              default :
                EMIT(SKIP);
                {p++; cs = 101; goto _out;}
              break;
            }
        }}
	goto st101;
tr165:
#line 564 "wikitext_ragel.rl"
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
                {p++; cs = 101; goto _out;}
              break;
              default :
                EMIT(SKIP);
                {p++; cs = 101; goto _out;}
              break;
            }
        }}
	goto st101;
tr179:
#line 241 "wikitext_ragel.rl"
	{te = p;p--;{
            if (out->column_start == 1)
            {
                REWIND();
                if (DISTANCE() <= 6) {
                  if (GET_STATE() == DEFAULT){
                    EMIT(CRLF);
                    {p++; cs = 101; goto _out;}
                  }
                } else {
                    p = ts + 6;
                    EMIT(SKIP);
                    {p++; cs = 101; goto _out;}
                }
            }
            else if (AT_END() || NEXT_CHAR() == '\n' || NEXT_CHAR() == '\r')
            {
                REWIND();
                if (DISTANCE() <= 6) {
                  if (GET_STATE() == DEFAULT){
                    EMIT(CRLF);
                    {p++; cs = 101; goto _out;}
                  } else {
                    EMIT(SKIP);
                    {p++; cs = 101; goto _out;}
                  }
                } else {
                    p -= 6; // will scan the H6 on the next scan
                    if (GET_STATE() == DEFAULT){
                      EMIT(PRINTABLE);
                      {p++; cs = 101; goto _out;}
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
                {p++; cs = 101; goto _out;}
            }
        }}
	goto st101;
tr181:
#line 170 "wikitext_ragel.rl"
	{te = p;p--;{
            if (out->column_start == 1 || last_token_type == BLOCKQUOTE) {
              EMIT(SKIP);
              {p++; cs = 101; goto _out;}
            } else {
              REWIND();
              state = GET_STATE();
              switch(state){
                case DEFAULT :
                  EMIT(PRINTABLE);
                  {p++; cs = 101; goto _out;}
                break;
                case NOWIKI :
                  opening = LAST_TYPE();
                  if(opening == TAG_START) {
                    POP(); 
                    EMIT(SKIP);
                    {p++; cs = 101; goto _out;}
                  }
                break;
                default :
                  ERROR("Closing token without opening token");
                  EMIT(SKIP);
                  {p++; cs = 101; goto _out;}
                break;
              }
            }
        }}
	goto st101;
tr182:
#line 170 "wikitext_ragel.rl"
	{te = p+1;{
            if (out->column_start == 1 || last_token_type == BLOCKQUOTE) {
              EMIT(SKIP);
              {p++; cs = 101; goto _out;}
            } else {
              REWIND();
              state = GET_STATE();
              switch(state){
                case DEFAULT :
                  EMIT(PRINTABLE);
                  {p++; cs = 101; goto _out;}
                break;
                case NOWIKI :
                  opening = LAST_TYPE();
                  if(opening == TAG_START) {
                    POP(); 
                    EMIT(SKIP);
                    {p++; cs = 101; goto _out;}
                  }
                break;
                default :
                  ERROR("Closing token without opening token");
                  EMIT(SKIP);
                  {p++; cs = 101; goto _out;}
                break;
              }
            }
        }}
	goto st101;
tr196:
#line 462 "wikitext_ragel.rl"
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
                {p++; cs = 101; goto _out;}
              break;
              default :
                EMIT(SKIP);
                {p++; cs = 101; goto _out;}
              break;
            }
        }}
	goto st101;
tr198:
#line 307 "wikitext_ragel.rl"
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
                {p++; cs = 101; goto _out;}
              break;
              default :
                EMIT(SKIP);
                {p++; cs = 101; goto _out;}
              break;
            }
        }}
	goto st101;
tr199:
#line 486 "wikitext_ragel.rl"
	{te = p;p--;{
            state = GET_STATE();
            switch(state){
              case BLIND :
                ERROR("Non-matching tokens");
                EMIT(SKIP);
                {p++; cs = 101; goto _out;}
              break;
              case BLIND_LINK :
              case INNER_LINK :
                POP();
                EMIT(SKIP);
                {p++; cs = 101; goto _out;}
              break;
              case LINK :
                POP();
                TODO(); //Close link tag                 
                EMIT(EXT_LINK_END);
                {p++; cs = 101; goto _out;}
              case DEFAULT :
                ERROR("Closing tag without opening");
              break;
              default :
                EMIT(SKIP);
                {p++; cs = 101; goto _out;}
              break;
            }
        }}
	goto st101;
tr200:
#line 331 "wikitext_ragel.rl"
	{te = p+1;{
            state = GET_STATE();
            switch(state){
              case BLIND :
                if(LAST_TYPE() == SPECIAL_LINK_START) {
                  POP();
                  EMIT(SKIP);
                  {p++; cs = 101; goto _out;}
                } else
                  ERROR("Non-matching tokens");
              break;
              case BLIND_LINK :
              case INNER_LINK :
                POP();
                EMIT(SKIP);
                {p++; cs = 101; goto _out;}
              break;
              case LINK :
                POP();
                TODO(); //Close link tag                 
                EMIT(LINK_END);
                {p++; cs = 101; goto _out;}
              break;
              case DEFAULT :
                PRINT_STACK();
                ERROR("Closing tag without opening");
              break;
              default :
                EMIT(SKIP);
                {p++; cs = 101; goto _out;}
              break;
            }
        }}
	goto st101;
tr203:
#line 648 "wikitext_ragel.rl"
	{te = p;p--;{
            state = GET_STATE();
            switch(state){
              case INNER_LINK :
              case LINK :
                TODO(); // Push token
                EMIT(PRINTABLE);
                {p++; cs = 101; goto _out;}
              break;
              case DEFAULT :
                EMIT(PRINTABLE);
                {p++; cs = 101; goto _out;}
              break;
              default :
                EMIT(SKIP);
                {p++; cs = 101; goto _out;}
              break;
            }
        }}
	goto st101;
tr204:
#line 629 "wikitext_ragel.rl"
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
                {p++; cs = 101; goto _out;}
              break;
            }
        }}
	goto st101;
tr205:
#line 366 "wikitext_ragel.rl"
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
                {p++; cs = 101; goto _out;}
              break;
            }
        }}
	goto st101;
tr206:
#line 451 "wikitext_ragel.rl"
	{te = p;p--;{
          if(GET_STATE() == LINK){
            EMIT(SEPARATOR);
            {p++; cs = 101; goto _out;}
          } else {
            EMIT(SKIP);
            {p++; cs = 101; goto _out;}
          }
        }}
	goto st101;
tr208:
#line 384 "wikitext_ragel.rl"
	{te = p+1;{
            state = GET_STATE();
            switch(state){
              case BLIND :
                opening = LAST_TYPE();
                if(opening == IMG_START){
                  POP();
                  EMIT(SKIP);
                  {p++; cs = 101; goto _out;}
                } else {
                  ERROR("Non-matching tokens");
                  EMIT(SKIP);
                  {p++; cs = 101; goto _out;}
                }
              break;
              case BLIND_LINK :
              case INNER_LINK :
              case LINK :
                ERROR("Non-matching tokens");
                EMIT(SKIP);
                {p++; cs = 101; goto _out;}
              break;
              case DEFAULT :
                ERROR("Closing without opening");
                EMIT(SKIP);
                {p++; cs = 101; goto _out;}
              break;
              default :
                EMIT(SKIP);
                {p++; cs = 101; goto _out;}
              break;
            }
        }}
	goto st101;
st101:
#line 1 "NONE"
	{ts = 0;}
#line 1 "NONE"
	{act = 0;}
	if ( ++p == pe )
		goto _test_eof101;
case 101:
#line 1 "NONE"
	{ts = p;}
#line 1130 "wikitext_ragel.c"
	switch( (*p) ) {
		case 10: goto tr105;
		case 13: goto tr106;
		case 32: goto tr107;
		case 33: goto st105;
		case 34: goto tr109;
		case 35: goto st106;
		case 38: goto tr112;
		case 39: goto st108;
		case 42: goto st106;
		case 43: goto tr111;
		case 45: goto tr114;
		case 46: goto tr115;
		case 47: goto tr111;
		case 60: goto st120;
		case 61: goto tr118;
		case 62: goto tr119;
		case 63: goto st105;
		case 64: goto tr111;
		case 70: goto tr120;
		case 72: goto tr121;
		case 77: goto tr122;
		case 83: goto tr123;
		case 91: goto st151;
		case 92: goto tr111;
		case 93: goto st153;
		case 94: goto tr111;
		case 95: goto tr126;
		case 96: goto tr39;
		case 102: goto tr120;
		case 104: goto tr121;
		case 109: goto tr122;
		case 115: goto tr123;
		case 123: goto st157;
		case 124: goto st158;
		case 125: goto tr129;
		case 126: goto tr111;
		case 127: goto tr104;
	}
	if ( (*p) < 36 ) {
		if ( (*p) < -32 ) {
			if ( -62 <= (*p) && (*p) <= -33 )
				goto st1;
		} else if ( (*p) > -17 ) {
			if ( (*p) > -12 ) {
				if ( 1 <= (*p) && (*p) <= 31 )
					goto tr104;
			} else if ( (*p) >= -16 )
				goto st4;
		} else
			goto st2;
	} else if ( (*p) > 37 ) {
		if ( (*p) < 48 ) {
			if ( 40 <= (*p) && (*p) <= 44 )
				goto st105;
		} else if ( (*p) > 57 ) {
			if ( (*p) > 59 ) {
				if ( 65 <= (*p) && (*p) <= 122 )
					goto tr116;
			} else if ( (*p) >= 58 )
				goto st106;
		} else
			goto tr116;
	} else
		goto tr111;
	goto st0;
st0:
cs = 0;
	goto _out;
st1:
	if ( ++p == pe )
		goto _test_eof1;
case 1:
	if ( (*p) <= -65 )
		goto tr1;
	goto tr0;
tr1:
#line 1 "NONE"
	{te = p+1;}
#line 65 "wikitext_ragel.rl"
	{
        out->code_point = ((uint32_t)(*(p - 1)) & 0x1f) << 6 |
            (*p & 0x3f);
    }
#line 774 "wikitext_ragel.rl"
	{act = 34;}
	goto st102;
tr3:
#line 1 "NONE"
	{te = p+1;}
#line 71 "wikitext_ragel.rl"
	{
        out->code_point = ((uint32_t)(*(p - 2)) & 0x0f) << 12 |
            ((uint32_t)(*(p - 1)) & 0x3f) << 6 |
            (*p & 0x3f);
    }
#line 774 "wikitext_ragel.rl"
	{act = 34;}
	goto st102;
tr6:
#line 1 "NONE"
	{te = p+1;}
#line 78 "wikitext_ragel.rl"
	{
        out->code_point = ((uint32_t)(*(p - 3)) & 0x07) << 18 |
            ((uint32_t)(*(p - 2)) & 0x3f) << 12 |
            ((uint32_t)(*(p - 1)) & 0x3f) << 6 |
            (*p & 0x3f);
    }
#line 774 "wikitext_ragel.rl"
	{act = 34;}
	goto st102;
tr111:
#line 1 "NONE"
	{te = p+1;}
#line 774 "wikitext_ragel.rl"
	{act = 34;}
	goto st102;
st102:
	if ( ++p == pe )
		goto _test_eof102;
case 102:
#line 1253 "wikitext_ragel.c"
	switch( (*p) ) {
		case 43: goto tr111;
		case 45: goto tr111;
		case 47: goto tr111;
		case 64: goto tr111;
		case 92: goto tr111;
		case 126: goto tr111;
	}
	if ( (*p) < -16 ) {
		if ( (*p) > -33 ) {
			if ( -32 <= (*p) && (*p) <= -17 )
				goto st2;
		} else if ( (*p) >= -62 )
			goto st1;
	} else if ( (*p) > -12 ) {
		if ( (*p) > 37 ) {
			if ( 94 <= (*p) && (*p) <= 95 )
				goto tr111;
		} else if ( (*p) >= 36 )
			goto tr111;
	} else
		goto st4;
	goto tr130;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
	if ( (*p) <= -65 )
		goto st3;
	goto tr0;
st3:
	if ( ++p == pe )
		goto _test_eof3;
case 3:
	if ( (*p) <= -65 )
		goto tr3;
	goto tr0;
st4:
	if ( ++p == pe )
		goto _test_eof4;
case 4:
	if ( (*p) <= -65 )
		goto st5;
	goto tr0;
st5:
	if ( ++p == pe )
		goto _test_eof5;
case 5:
	if ( (*p) <= -65 )
		goto st6;
	goto tr0;
st6:
	if ( ++p == pe )
		goto _test_eof6;
case 6:
	if ( (*p) <= -65 )
		goto tr6;
	goto tr0;
tr106:
#line 60 "wikitext_ragel.rl"
	{
        out->code_point = *p & 0x7f;
    }
	goto st103;
st103:
	if ( ++p == pe )
		goto _test_eof103;
case 103:
#line 1322 "wikitext_ragel.c"
	if ( (*p) == 10 )
		goto tr132;
	goto tr131;
tr107:
#line 55 "wikitext_ragel.rl"
	{
        MARK();
    }
	goto st104;
st104:
	if ( ++p == pe )
		goto _test_eof104;
case 104:
#line 1336 "wikitext_ragel.c"
	if ( (*p) == 32 )
		goto st104;
	goto tr133;
st105:
	if ( ++p == pe )
		goto _test_eof105;
case 105:
	switch( (*p) ) {
		case 33: goto st105;
		case 44: goto st105;
		case 46: goto st105;
		case 63: goto st105;
	}
	if ( 40 <= (*p) && (*p) <= 41 )
		goto st105;
	goto tr135;
st106:
	if ( ++p == pe )
		goto _test_eof106;
case 106:
	switch( (*p) ) {
		case 35: goto st106;
		case 42: goto st106;
	}
	if ( 58 <= (*p) && (*p) <= 59 )
		goto st106;
	goto tr136;
tr112:
#line 1 "NONE"
	{te = p+1;}
	goto st107;
st107:
	if ( ++p == pe )
		goto _test_eof107;
case 107:
#line 1372 "wikitext_ragel.c"
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
	goto tr137;
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
st108:
	if ( ++p == pe )
		goto _test_eof108;
case 108:
	if ( (*p) == 39 )
		goto st109;
	goto tr141;
st109:
	if ( ++p == pe )
		goto _test_eof109;
case 109:
	if ( (*p) == 39 )
		goto st110;
	goto tr141;
st110:
	if ( ++p == pe )
		goto _test_eof110;
case 110:
	if ( (*p) == 39 )
		goto st111;
	goto tr141;
st111:
	if ( ++p == pe )
		goto _test_eof111;
case 111:
	if ( (*p) == 39 )
		goto tr145;
	goto tr141;
tr114:
#line 1 "NONE"
	{te = p+1;}
#line 774 "wikitext_ragel.rl"
	{act = 34;}
	goto st112;
st112:
	if ( ++p == pe )
		goto _test_eof112;
case 112:
#line 1609 "wikitext_ragel.c"
	switch( (*p) ) {
		case 43: goto tr111;
		case 45: goto tr114;
		case 47: goto tr111;
		case 64: goto tr146;
		case 92: goto tr111;
		case 94: goto tr111;
		case 95: goto tr114;
		case 126: goto tr111;
	}
	if ( (*p) < 36 ) {
		if ( (*p) < -32 ) {
			if ( -62 <= (*p) && (*p) <= -33 )
				goto st1;
		} else if ( (*p) > -17 ) {
			if ( -16 <= (*p) && (*p) <= -12 )
				goto st4;
		} else
			goto st2;
	} else if ( (*p) > 37 ) {
		if ( (*p) < 65 ) {
			if ( 46 <= (*p) && (*p) <= 57 )
				goto st20;
		} else if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st20;
		} else
			goto st20;
	} else
		goto tr111;
	goto tr130;
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
	goto tr0;
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
	goto tr0;
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
	goto tr0;
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
	goto tr0;
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
			goto tr28;
	} else
		goto tr28;
	goto tr0;
tr28:
#line 1 "NONE"
	{te = p+1;}
#line 102 "wikitext_ragel.rl"
	{act = 1;}
	goto st113;
st113:
	if ( ++p == pe )
		goto _test_eof113;
case 113:
#line 1727 "wikitext_ragel.c"
	if ( (*p) == 46 )
		goto st23;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st22;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr148;
	} else
		goto tr148;
	goto tr147;
tr148:
#line 1 "NONE"
	{te = p+1;}
#line 102 "wikitext_ragel.rl"
	{act = 1;}
	goto st114;
st114:
	if ( ++p == pe )
		goto _test_eof114;
case 114:
#line 1749 "wikitext_ragel.c"
	if ( (*p) == 46 )
		goto st23;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st22;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr149;
	} else
		goto tr149;
	goto tr147;
tr149:
#line 1 "NONE"
	{te = p+1;}
#line 102 "wikitext_ragel.rl"
	{act = 1;}
	goto st115;
st115:
	if ( ++p == pe )
		goto _test_eof115;
case 115:
#line 1771 "wikitext_ragel.c"
	if ( (*p) == 46 )
		goto st23;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st22;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr150;
	} else
		goto tr150;
	goto tr147;
tr150:
#line 1 "NONE"
	{te = p+1;}
#line 102 "wikitext_ragel.rl"
	{act = 1;}
	goto st116;
st116:
	if ( ++p == pe )
		goto _test_eof116;
case 116:
#line 1793 "wikitext_ragel.c"
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
	goto tr147;
tr146:
#line 1 "NONE"
	{te = p+1;}
#line 774 "wikitext_ragel.rl"
	{act = 34;}
	goto st117;
st117:
	if ( ++p == pe )
		goto _test_eof117;
case 117:
#line 1815 "wikitext_ragel.c"
	switch( (*p) ) {
		case 43: goto tr111;
		case 45: goto tr111;
		case 47: goto tr111;
		case 64: goto tr111;
		case 92: goto tr111;
		case 126: goto tr111;
	}
	if ( (*p) < 36 ) {
		if ( (*p) < -32 ) {
			if ( -62 <= (*p) && (*p) <= -33 )
				goto st1;
		} else if ( (*p) > -17 ) {
			if ( -16 <= (*p) && (*p) <= -12 )
				goto st4;
		} else
			goto st2;
	} else if ( (*p) > 37 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st22;
		} else if ( (*p) > 90 ) {
			if ( (*p) > 95 ) {
				if ( 97 <= (*p) && (*p) <= 122 )
					goto st22;
			} else if ( (*p) >= 94 )
				goto tr111;
		} else
			goto st22;
	} else
		goto tr111;
	goto tr130;
tr115:
#line 1 "NONE"
	{te = p+1;}
#line 718 "wikitext_ragel.rl"
	{act = 32;}
	goto st118;
st118:
	if ( ++p == pe )
		goto _test_eof118;
case 118:
#line 1858 "wikitext_ragel.c"
	switch( (*p) ) {
		case 33: goto st105;
		case 44: goto st105;
		case 45: goto st20;
		case 46: goto tr115;
		case 63: goto st105;
		case 64: goto st21;
		case 95: goto st20;
	}
	if ( (*p) < 48 ) {
		if ( 40 <= (*p) && (*p) <= 41 )
			goto st105;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st20;
		} else if ( (*p) >= 65 )
			goto st20;
	} else
		goto st20;
	goto tr135;
tr116:
#line 1 "NONE"
	{te = p+1;}
#line 739 "wikitext_ragel.rl"
	{act = 33;}
	goto st119;
st119:
	if ( ++p == pe )
		goto _test_eof119;
case 119:
#line 1890 "wikitext_ragel.c"
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
				goto tr116;
		} else if ( (*p) >= 65 )
			goto tr116;
	} else
		goto tr116;
	goto tr151;
st120:
	if ( ++p == pe )
		goto _test_eof120;
case 120:
	switch( (*p) ) {
		case 33: goto tr153;
		case 47: goto tr154;
		case 66: goto tr155;
		case 69: goto tr156;
		case 77: goto tr157;
		case 78: goto tr158;
		case 80: goto tr159;
		case 82: goto tr160;
		case 83: goto tr161;
		case 84: goto tr162;
		case 98: goto tr155;
		case 101: goto tr156;
		case 109: goto tr157;
		case 110: goto tr158;
		case 112: goto tr163;
		case 114: goto tr164;
		case 115: goto tr161;
		case 116: goto tr162;
	}
	if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr153;
	} else if ( (*p) >= 65 )
		goto tr153;
	goto tr152;
tr154:
#line 1 "NONE"
	{te = p+1;}
	goto st121;
st121:
	if ( ++p == pe )
		goto _test_eof121;
case 121:
#line 1945 "wikitext_ragel.c"
	switch( (*p) ) {
		case 66: goto st25;
		case 69: goto st35;
		case 77: goto st36;
		case 78: goto st40;
		case 80: goto st45;
		case 82: goto st47;
		case 83: goto st49;
		case 84: goto st54;
		case 98: goto st25;
		case 101: goto st35;
		case 109: goto st36;
		case 110: goto st40;
		case 112: goto st45;
		case 114: goto st47;
		case 115: goto st49;
		case 116: goto st54;
	}
	goto tr165;
st25:
	if ( ++p == pe )
		goto _test_eof25;
case 25:
	switch( (*p) ) {
		case 76: goto st26;
		case 108: goto st26;
	}
	goto tr29;
st26:
	if ( ++p == pe )
		goto _test_eof26;
case 26:
	switch( (*p) ) {
		case 79: goto st27;
		case 111: goto st27;
	}
	goto tr29;
st27:
	if ( ++p == pe )
		goto _test_eof27;
case 27:
	switch( (*p) ) {
		case 67: goto st28;
		case 99: goto st28;
	}
	goto tr29;
st28:
	if ( ++p == pe )
		goto _test_eof28;
case 28:
	switch( (*p) ) {
		case 75: goto st29;
		case 107: goto st29;
	}
	goto tr29;
st29:
	if ( ++p == pe )
		goto _test_eof29;
case 29:
	switch( (*p) ) {
		case 81: goto st30;
		case 113: goto st30;
	}
	goto tr29;
st30:
	if ( ++p == pe )
		goto _test_eof30;
case 30:
	switch( (*p) ) {
		case 85: goto st31;
		case 117: goto st31;
	}
	goto tr29;
st31:
	if ( ++p == pe )
		goto _test_eof31;
case 31:
	switch( (*p) ) {
		case 79: goto st32;
		case 111: goto st32;
	}
	goto tr29;
st32:
	if ( ++p == pe )
		goto _test_eof32;
case 32:
	switch( (*p) ) {
		case 84: goto st33;
		case 116: goto st33;
	}
	goto tr29;
st33:
	if ( ++p == pe )
		goto _test_eof33;
case 33:
	switch( (*p) ) {
		case 69: goto st34;
		case 101: goto st34;
	}
	goto tr29;
st34:
	if ( ++p == pe )
		goto _test_eof34;
case 34:
	if ( (*p) == 62 )
		goto tr39;
	goto tr29;
st35:
	if ( ++p == pe )
		goto _test_eof35;
case 35:
	switch( (*p) ) {
		case 77: goto st34;
		case 109: goto st34;
	}
	goto tr29;
st36:
	if ( ++p == pe )
		goto _test_eof36;
case 36:
	switch( (*p) ) {
		case 65: goto st37;
		case 97: goto st37;
	}
	goto tr29;
st37:
	if ( ++p == pe )
		goto _test_eof37;
case 37:
	switch( (*p) ) {
		case 84: goto st38;
		case 116: goto st38;
	}
	goto tr29;
st38:
	if ( ++p == pe )
		goto _test_eof38;
case 38:
	switch( (*p) ) {
		case 72: goto st39;
		case 104: goto st39;
	}
	goto tr29;
st39:
	if ( ++p == pe )
		goto _test_eof39;
case 39:
	if ( (*p) == 62 )
		goto tr43;
	goto tr29;
st40:
	if ( ++p == pe )
		goto _test_eof40;
case 40:
	switch( (*p) ) {
		case 79: goto st41;
		case 111: goto st41;
	}
	goto tr29;
st41:
	if ( ++p == pe )
		goto _test_eof41;
case 41:
	switch( (*p) ) {
		case 87: goto st42;
		case 119: goto st42;
	}
	goto tr29;
st42:
	if ( ++p == pe )
		goto _test_eof42;
case 42:
	switch( (*p) ) {
		case 73: goto st43;
		case 105: goto st43;
	}
	goto tr29;
st43:
	if ( ++p == pe )
		goto _test_eof43;
case 43:
	switch( (*p) ) {
		case 75: goto st44;
		case 107: goto st44;
	}
	goto tr29;
st44:
	if ( ++p == pe )
		goto _test_eof44;
case 44:
	switch( (*p) ) {
		case 73: goto st34;
		case 105: goto st34;
	}
	goto tr29;
st45:
	if ( ++p == pe )
		goto _test_eof45;
case 45:
	switch( (*p) ) {
		case 82: goto st46;
		case 114: goto st46;
	}
	goto tr29;
st46:
	if ( ++p == pe )
		goto _test_eof46;
case 46:
	switch( (*p) ) {
		case 69: goto st39;
		case 101: goto st39;
	}
	goto tr29;
st47:
	if ( ++p == pe )
		goto _test_eof47;
case 47:
	switch( (*p) ) {
		case 69: goto st48;
		case 101: goto st48;
	}
	goto tr29;
st48:
	if ( ++p == pe )
		goto _test_eof48;
case 48:
	switch( (*p) ) {
		case 70: goto st39;
		case 102: goto st39;
	}
	goto tr29;
st49:
	if ( ++p == pe )
		goto _test_eof49;
case 49:
	switch( (*p) ) {
		case 84: goto st50;
		case 116: goto st50;
	}
	goto tr29;
st50:
	if ( ++p == pe )
		goto _test_eof50;
case 50:
	switch( (*p) ) {
		case 82: goto st51;
		case 114: goto st51;
	}
	goto tr29;
st51:
	if ( ++p == pe )
		goto _test_eof51;
case 51:
	switch( (*p) ) {
		case 79: goto st52;
		case 111: goto st52;
	}
	goto tr29;
st52:
	if ( ++p == pe )
		goto _test_eof52;
case 52:
	switch( (*p) ) {
		case 78: goto st53;
		case 110: goto st53;
	}
	goto tr29;
st53:
	if ( ++p == pe )
		goto _test_eof53;
case 53:
	switch( (*p) ) {
		case 71: goto st34;
		case 103: goto st34;
	}
	goto tr29;
st54:
	if ( ++p == pe )
		goto _test_eof54;
case 54:
	switch( (*p) ) {
		case 73: goto st55;
		case 84: goto st34;
		case 105: goto st55;
		case 116: goto st34;
	}
	goto tr29;
st55:
	if ( ++p == pe )
		goto _test_eof55;
case 55:
	switch( (*p) ) {
		case 77: goto st56;
		case 109: goto st56;
	}
	goto tr29;
st56:
	if ( ++p == pe )
		goto _test_eof56;
case 56:
	switch( (*p) ) {
		case 69: goto st57;
		case 101: goto st57;
	}
	goto tr29;
st57:
	if ( ++p == pe )
		goto _test_eof57;
case 57:
	switch( (*p) ) {
		case 76: goto st58;
		case 108: goto st58;
	}
	goto tr29;
st58:
	if ( ++p == pe )
		goto _test_eof58;
case 58:
	switch( (*p) ) {
		case 73: goto st59;
		case 105: goto st59;
	}
	goto tr29;
st59:
	if ( ++p == pe )
		goto _test_eof59;
case 59:
	switch( (*p) ) {
		case 78: goto st46;
		case 110: goto st46;
	}
	goto tr29;
tr155:
#line 1 "NONE"
	{te = p+1;}
	goto st122;
st122:
	if ( ++p == pe )
		goto _test_eof122;
case 122:
#line 2286 "wikitext_ragel.c"
	switch( (*p) ) {
		case 76: goto st26;
		case 108: goto st26;
	}
	goto tr165;
tr156:
#line 1 "NONE"
	{te = p+1;}
	goto st123;
st123:
	if ( ++p == pe )
		goto _test_eof123;
case 123:
#line 2300 "wikitext_ragel.c"
	switch( (*p) ) {
		case 77: goto st34;
		case 109: goto st34;
	}
	goto tr165;
tr157:
#line 1 "NONE"
	{te = p+1;}
	goto st124;
st124:
	if ( ++p == pe )
		goto _test_eof124;
case 124:
#line 2314 "wikitext_ragel.c"
	switch( (*p) ) {
		case 65: goto st60;
		case 97: goto st60;
	}
	goto tr165;
st60:
	if ( ++p == pe )
		goto _test_eof60;
case 60:
	switch( (*p) ) {
		case 84: goto st61;
		case 116: goto st61;
	}
	goto tr29;
st61:
	if ( ++p == pe )
		goto _test_eof61;
case 61:
	switch( (*p) ) {
		case 72: goto st62;
		case 104: goto st62;
	}
	goto tr29;
st62:
	if ( ++p == pe )
		goto _test_eof62;
case 62:
	if ( (*p) == 62 )
		goto tr61;
	goto tr29;
tr158:
#line 1 "NONE"
	{te = p+1;}
	goto st125;
st125:
	if ( ++p == pe )
		goto _test_eof125;
case 125:
#line 2353 "wikitext_ragel.c"
	switch( (*p) ) {
		case 79: goto st41;
		case 111: goto st41;
	}
	goto tr165;
tr159:
#line 1 "NONE"
	{te = p+1;}
	goto st126;
st126:
	if ( ++p == pe )
		goto _test_eof126;
case 126:
#line 2367 "wikitext_ragel.c"
	switch( (*p) ) {
		case 82: goto st63;
		case 114: goto st63;
	}
	goto tr165;
st63:
	if ( ++p == pe )
		goto _test_eof63;
case 63:
	switch( (*p) ) {
		case 69: goto st62;
		case 101: goto st62;
	}
	goto tr29;
tr160:
#line 1 "NONE"
	{te = p+1;}
	goto st127;
st127:
	if ( ++p == pe )
		goto _test_eof127;
case 127:
#line 2390 "wikitext_ragel.c"
	switch( (*p) ) {
		case 69: goto st64;
		case 101: goto st64;
	}
	goto tr165;
st64:
	if ( ++p == pe )
		goto _test_eof64;
case 64:
	switch( (*p) ) {
		case 70: goto st62;
		case 102: goto st62;
	}
	goto tr29;
tr161:
#line 1 "NONE"
	{te = p+1;}
	goto st128;
st128:
	if ( ++p == pe )
		goto _test_eof128;
case 128:
#line 2413 "wikitext_ragel.c"
	switch( (*p) ) {
		case 84: goto st50;
		case 116: goto st50;
	}
	goto tr165;
tr162:
#line 1 "NONE"
	{te = p+1;}
	goto st129;
st129:
	if ( ++p == pe )
		goto _test_eof129;
case 129:
#line 2427 "wikitext_ragel.c"
	switch( (*p) ) {
		case 73: goto st65;
		case 84: goto st34;
		case 105: goto st65;
		case 116: goto st34;
	}
	goto tr165;
st65:
	if ( ++p == pe )
		goto _test_eof65;
case 65:
	switch( (*p) ) {
		case 77: goto st66;
		case 109: goto st66;
	}
	goto tr29;
st66:
	if ( ++p == pe )
		goto _test_eof66;
case 66:
	switch( (*p) ) {
		case 69: goto st67;
		case 101: goto st67;
	}
	goto tr29;
st67:
	if ( ++p == pe )
		goto _test_eof67;
case 67:
	switch( (*p) ) {
		case 76: goto st68;
		case 108: goto st68;
	}
	goto tr29;
st68:
	if ( ++p == pe )
		goto _test_eof68;
case 68:
	switch( (*p) ) {
		case 73: goto st69;
		case 105: goto st69;
	}
	goto tr29;
st69:
	if ( ++p == pe )
		goto _test_eof69;
case 69:
	switch( (*p) ) {
		case 78: goto st63;
		case 110: goto st63;
	}
	goto tr29;
tr163:
#line 1 "NONE"
	{te = p+1;}
	goto st130;
st130:
	if ( ++p == pe )
		goto _test_eof130;
case 130:
#line 2488 "wikitext_ragel.c"
	switch( (*p) ) {
		case 82: goto st63;
		case 114: goto st70;
	}
	goto tr165;
st70:
	if ( ++p == pe )
		goto _test_eof70;
case 70:
	switch( (*p) ) {
		case 69: goto st62;
		case 101: goto st71;
	}
	goto tr29;
st71:
	if ( ++p == pe )
		goto _test_eof71;
case 71:
	switch( (*p) ) {
		case 32: goto st72;
		case 62: goto tr61;
	}
	goto tr29;
st72:
	if ( ++p == pe )
		goto _test_eof72;
case 72:
	if ( (*p) == 108 )
		goto st73;
	goto tr29;
st73:
	if ( ++p == pe )
		goto _test_eof73;
case 73:
	if ( (*p) == 97 )
		goto st74;
	goto tr29;
st74:
	if ( ++p == pe )
		goto _test_eof74;
case 74:
	if ( (*p) == 110 )
		goto st75;
	goto tr29;
st75:
	if ( ++p == pe )
		goto _test_eof75;
case 75:
	if ( (*p) == 103 )
		goto st76;
	goto tr29;
st76:
	if ( ++p == pe )
		goto _test_eof76;
case 76:
	if ( (*p) == 61 )
		goto st77;
	goto tr29;
st77:
	if ( ++p == pe )
		goto _test_eof77;
case 77:
	if ( (*p) == 34 )
		goto st78;
	goto tr29;
st78:
	if ( ++p == pe )
		goto _test_eof78;
case 78:
	if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st79;
	} else if ( (*p) >= 65 )
		goto st79;
	goto tr29;
st79:
	if ( ++p == pe )
		goto _test_eof79;
case 79:
	if ( (*p) == 34 )
		goto st62;
	if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st79;
	} else if ( (*p) >= 65 )
		goto st79;
	goto tr29;
tr164:
#line 1 "NONE"
	{te = p+1;}
	goto st131;
st131:
	if ( ++p == pe )
		goto _test_eof131;
case 131:
#line 2584 "wikitext_ragel.c"
	switch( (*p) ) {
		case 69: goto st64;
		case 101: goto st80;
	}
	goto tr165;
st80:
	if ( ++p == pe )
		goto _test_eof80;
case 80:
	switch( (*p) ) {
		case 70: goto st62;
		case 102: goto st81;
	}
	goto tr29;
st81:
	if ( ++p == pe )
		goto _test_eof81;
case 81:
	switch( (*p) ) {
		case 32: goto st82;
		case 62: goto tr61;
	}
	goto tr29;
st82:
	if ( ++p == pe )
		goto _test_eof82;
case 82:
	if ( (*p) == 110 )
		goto st83;
	goto tr29;
st83:
	if ( ++p == pe )
		goto _test_eof83;
case 83:
	if ( (*p) == 97 )
		goto st84;
	goto tr29;
st84:
	if ( ++p == pe )
		goto _test_eof84;
case 84:
	if ( (*p) == 109 )
		goto st85;
	goto tr29;
st85:
	if ( ++p == pe )
		goto _test_eof85;
case 85:
	if ( (*p) == 101 )
		goto st86;
	goto tr29;
st86:
	if ( ++p == pe )
		goto _test_eof86;
case 86:
	if ( (*p) == 61 )
		goto st87;
	goto tr29;
st87:
	if ( ++p == pe )
		goto _test_eof87;
case 87:
	if ( (*p) == 62 )
		goto tr29;
	goto st88;
st88:
	if ( ++p == pe )
		goto _test_eof88;
case 88:
	if ( (*p) == 62 )
		goto tr61;
	goto st88;
tr118:
#line 55 "wikitext_ragel.rl"
	{
        MARK();
    }
	goto st132;
st132:
	if ( ++p == pe )
		goto _test_eof132;
case 132:
#line 2667 "wikitext_ragel.c"
	switch( (*p) ) {
		case 32: goto st133;
		case 61: goto tr118;
	}
	goto tr179;
st133:
	if ( ++p == pe )
		goto _test_eof133;
case 133:
	if ( (*p) == 32 )
		goto st133;
	goto tr179;
tr119:
#line 55 "wikitext_ragel.rl"
	{
        MARK();
    }
	goto st134;
st134:
	if ( ++p == pe )
		goto _test_eof134;
case 134:
#line 2690 "wikitext_ragel.c"
	if ( (*p) == 32 )
		goto tr182;
	goto tr181;
tr120:
#line 1 "NONE"
	{te = p+1;}
#line 739 "wikitext_ragel.rl"
	{act = 33;}
	goto st135;
st135:
	if ( ++p == pe )
		goto _test_eof135;
case 135:
#line 2704 "wikitext_ragel.c"
	switch( (*p) ) {
		case 64: goto st21;
		case 84: goto tr183;
		case 95: goto st20;
		case 116: goto tr183;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st20;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr116;
		} else if ( (*p) >= 65 )
			goto tr116;
	} else
		goto tr116;
	goto tr151;
tr183:
#line 1 "NONE"
	{te = p+1;}
#line 739 "wikitext_ragel.rl"
	{act = 33;}
	goto st136;
st136:
	if ( ++p == pe )
		goto _test_eof136;
case 136:
#line 2733 "wikitext_ragel.c"
	switch( (*p) ) {
		case 64: goto st21;
		case 80: goto tr184;
		case 95: goto st20;
		case 112: goto tr184;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st20;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr116;
		} else if ( (*p) >= 65 )
			goto tr116;
	} else
		goto tr116;
	goto tr151;
tr184:
#line 1 "NONE"
	{te = p+1;}
#line 739 "wikitext_ragel.rl"
	{act = 33;}
	goto st137;
st137:
	if ( ++p == pe )
		goto _test_eof137;
case 137:
#line 2762 "wikitext_ragel.c"
	switch( (*p) ) {
		case 58: goto st89;
		case 64: goto st21;
		case 95: goto st20;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st20;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr116;
		} else if ( (*p) >= 65 )
			goto tr116;
	} else
		goto tr116;
	goto tr151;
st89:
	if ( ++p == pe )
		goto _test_eof89;
case 89:
	if ( (*p) == 47 )
		goto st90;
	goto tr84;
st90:
	if ( ++p == pe )
		goto _test_eof90;
case 90:
	if ( (*p) == 47 )
		goto st91;
	goto tr84;
st91:
	if ( ++p == pe )
		goto _test_eof91;
case 91:
	switch( (*p) ) {
		case 45: goto tr87;
		case 61: goto tr87;
		case 95: goto tr87;
		case 126: goto tr87;
	}
	if ( (*p) < 47 ) {
		if ( (*p) > 40 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr87;
		} else if ( (*p) >= 35 )
			goto tr87;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr87;
		} else if ( (*p) >= 64 )
			goto tr87;
	} else
		goto tr87;
	goto tr84;
tr87:
#line 1 "NONE"
	{te = p+1;}
	goto st138;
st138:
	if ( ++p == pe )
		goto _test_eof138;
case 138:
#line 2827 "wikitext_ragel.c"
	switch( (*p) ) {
		case 33: goto st92;
		case 41: goto st92;
		case 44: goto st92;
		case 46: goto st92;
		case 61: goto tr87;
		case 63: goto st92;
		case 95: goto tr87;
		case 126: goto tr87;
	}
	if ( (*p) < 64 ) {
		if ( 35 <= (*p) && (*p) <= 57 )
			goto tr87;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr87;
	} else
		goto tr87;
	goto tr147;
st92:
	if ( ++p == pe )
		goto _test_eof92;
case 92:
	switch( (*p) ) {
		case 33: goto st92;
		case 41: goto st92;
		case 44: goto st92;
		case 46: goto st92;
		case 61: goto tr87;
		case 63: goto st92;
		case 95: goto tr87;
		case 126: goto tr87;
	}
	if ( (*p) < 64 ) {
		if ( 35 <= (*p) && (*p) <= 57 )
			goto tr87;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr87;
	} else
		goto tr87;
	goto tr88;
tr121:
#line 1 "NONE"
	{te = p+1;}
#line 739 "wikitext_ragel.rl"
	{act = 33;}
	goto st139;
st139:
	if ( ++p == pe )
		goto _test_eof139;
case 139:
#line 2880 "wikitext_ragel.c"
	switch( (*p) ) {
		case 64: goto st21;
		case 84: goto tr186;
		case 95: goto st20;
		case 116: goto tr186;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st20;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr116;
		} else if ( (*p) >= 65 )
			goto tr116;
	} else
		goto tr116;
	goto tr151;
tr186:
#line 1 "NONE"
	{te = p+1;}
#line 739 "wikitext_ragel.rl"
	{act = 33;}
	goto st140;
st140:
	if ( ++p == pe )
		goto _test_eof140;
case 140:
#line 2909 "wikitext_ragel.c"
	switch( (*p) ) {
		case 64: goto st21;
		case 84: goto tr187;
		case 95: goto st20;
		case 116: goto tr187;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st20;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr116;
		} else if ( (*p) >= 65 )
			goto tr116;
	} else
		goto tr116;
	goto tr151;
tr187:
#line 1 "NONE"
	{te = p+1;}
#line 739 "wikitext_ragel.rl"
	{act = 33;}
	goto st141;
st141:
	if ( ++p == pe )
		goto _test_eof141;
case 141:
#line 2938 "wikitext_ragel.c"
	switch( (*p) ) {
		case 64: goto st21;
		case 80: goto tr188;
		case 95: goto st20;
		case 112: goto tr188;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st20;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr116;
		} else if ( (*p) >= 65 )
			goto tr116;
	} else
		goto tr116;
	goto tr151;
tr188:
#line 1 "NONE"
	{te = p+1;}
#line 739 "wikitext_ragel.rl"
	{act = 33;}
	goto st142;
st142:
	if ( ++p == pe )
		goto _test_eof142;
case 142:
#line 2967 "wikitext_ragel.c"
	switch( (*p) ) {
		case 58: goto st89;
		case 64: goto st21;
		case 83: goto tr184;
		case 95: goto st20;
		case 115: goto tr184;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st20;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr116;
		} else if ( (*p) >= 65 )
			goto tr116;
	} else
		goto tr116;
	goto tr151;
tr122:
#line 1 "NONE"
	{te = p+1;}
#line 739 "wikitext_ragel.rl"
	{act = 33;}
	goto st143;
st143:
	if ( ++p == pe )
		goto _test_eof143;
case 143:
#line 2997 "wikitext_ragel.c"
	switch( (*p) ) {
		case 64: goto st21;
		case 65: goto tr189;
		case 95: goto st20;
		case 97: goto tr189;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st20;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 98 <= (*p) && (*p) <= 122 )
				goto tr116;
		} else if ( (*p) >= 66 )
			goto tr116;
	} else
		goto tr116;
	goto tr151;
tr189:
#line 1 "NONE"
	{te = p+1;}
#line 739 "wikitext_ragel.rl"
	{act = 33;}
	goto st144;
st144:
	if ( ++p == pe )
		goto _test_eof144;
case 144:
#line 3026 "wikitext_ragel.c"
	switch( (*p) ) {
		case 64: goto st21;
		case 73: goto tr190;
		case 95: goto st20;
		case 105: goto tr190;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st20;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr116;
		} else if ( (*p) >= 65 )
			goto tr116;
	} else
		goto tr116;
	goto tr151;
tr190:
#line 1 "NONE"
	{te = p+1;}
#line 739 "wikitext_ragel.rl"
	{act = 33;}
	goto st145;
st145:
	if ( ++p == pe )
		goto _test_eof145;
case 145:
#line 3055 "wikitext_ragel.c"
	switch( (*p) ) {
		case 64: goto st21;
		case 76: goto tr191;
		case 95: goto st20;
		case 108: goto tr191;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st20;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr116;
		} else if ( (*p) >= 65 )
			goto tr116;
	} else
		goto tr116;
	goto tr151;
tr191:
#line 1 "NONE"
	{te = p+1;}
#line 739 "wikitext_ragel.rl"
	{act = 33;}
	goto st146;
st146:
	if ( ++p == pe )
		goto _test_eof146;
case 146:
#line 3084 "wikitext_ragel.c"
	switch( (*p) ) {
		case 64: goto st21;
		case 84: goto tr192;
		case 95: goto st20;
		case 116: goto tr192;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st20;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr116;
		} else if ( (*p) >= 65 )
			goto tr116;
	} else
		goto tr116;
	goto tr151;
tr192:
#line 1 "NONE"
	{te = p+1;}
#line 739 "wikitext_ragel.rl"
	{act = 33;}
	goto st147;
st147:
	if ( ++p == pe )
		goto _test_eof147;
case 147:
#line 3113 "wikitext_ragel.c"
	switch( (*p) ) {
		case 64: goto st21;
		case 79: goto tr193;
		case 95: goto st20;
		case 111: goto tr193;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st20;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr116;
		} else if ( (*p) >= 65 )
			goto tr116;
	} else
		goto tr116;
	goto tr151;
tr193:
#line 1 "NONE"
	{te = p+1;}
#line 739 "wikitext_ragel.rl"
	{act = 33;}
	goto st148;
st148:
	if ( ++p == pe )
		goto _test_eof148;
case 148:
#line 3142 "wikitext_ragel.c"
	switch( (*p) ) {
		case 58: goto st93;
		case 64: goto st21;
		case 95: goto st20;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st20;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr116;
		} else if ( (*p) >= 65 )
			goto tr116;
	} else
		goto tr116;
	goto tr151;
st93:
	if ( ++p == pe )
		goto _test_eof93;
case 93:
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
	goto tr84;
tr123:
#line 1 "NONE"
	{te = p+1;}
#line 739 "wikitext_ragel.rl"
	{act = 33;}
	goto st149;
st149:
	if ( ++p == pe )
		goto _test_eof149;
case 149:
#line 3188 "wikitext_ragel.c"
	switch( (*p) ) {
		case 64: goto st21;
		case 86: goto tr195;
		case 95: goto st20;
		case 118: goto tr195;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st20;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr116;
		} else if ( (*p) >= 65 )
			goto tr116;
	} else
		goto tr116;
	goto tr151;
tr195:
#line 1 "NONE"
	{te = p+1;}
#line 739 "wikitext_ragel.rl"
	{act = 33;}
	goto st150;
st150:
	if ( ++p == pe )
		goto _test_eof150;
case 150:
#line 3217 "wikitext_ragel.c"
	switch( (*p) ) {
		case 64: goto st21;
		case 78: goto tr184;
		case 95: goto st20;
		case 110: goto tr184;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st20;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr116;
		} else if ( (*p) >= 65 )
			goto tr116;
	} else
		goto tr116;
	goto tr151;
st151:
	if ( ++p == pe )
		goto _test_eof151;
case 151:
	if ( (*p) == 91 )
		goto tr197;
	goto tr196;
tr197:
#line 1 "NONE"
	{te = p+1;}
	goto st152;
st152:
	if ( ++p == pe )
		goto _test_eof152;
case 152:
#line 3251 "wikitext_ragel.c"
	switch( (*p) ) {
		case 45: goto st94;
		case 58: goto tr92;
	}
	if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st94;
	} else if ( (*p) >= 65 )
		goto st94;
	goto tr198;
st94:
	if ( ++p == pe )
		goto _test_eof94;
case 94:
	switch( (*p) ) {
		case 45: goto st94;
		case 58: goto tr92;
	}
	if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st94;
	} else if ( (*p) >= 65 )
		goto st94;
	goto tr90;
st153:
	if ( ++p == pe )
		goto _test_eof153;
case 153:
	if ( (*p) == 93 )
		goto tr200;
	goto tr199;
tr126:
#line 1 "NONE"
	{te = p+1;}
#line 774 "wikitext_ragel.rl"
	{act = 34;}
	goto st154;
st154:
	if ( ++p == pe )
		goto _test_eof154;
case 154:
#line 3293 "wikitext_ragel.c"
	switch( (*p) ) {
		case 43: goto tr111;
		case 45: goto tr114;
		case 47: goto tr111;
		case 64: goto tr146;
		case 92: goto tr111;
		case 94: goto tr111;
		case 95: goto tr201;
		case 126: goto tr111;
	}
	if ( (*p) < 36 ) {
		if ( (*p) < -32 ) {
			if ( -62 <= (*p) && (*p) <= -33 )
				goto st1;
		} else if ( (*p) > -17 ) {
			if ( -16 <= (*p) && (*p) <= -12 )
				goto st4;
		} else
			goto st2;
	} else if ( (*p) > 37 ) {
		if ( (*p) < 65 ) {
			if ( 46 <= (*p) && (*p) <= 57 )
				goto st20;
		} else if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st20;
		} else
			goto st20;
	} else
		goto tr111;
	goto tr130;
tr201:
#line 1 "NONE"
	{te = p+1;}
#line 774 "wikitext_ragel.rl"
	{act = 34;}
	goto st155;
st155:
	if ( ++p == pe )
		goto _test_eof155;
case 155:
#line 3335 "wikitext_ragel.c"
	switch( (*p) ) {
		case 43: goto tr111;
		case 45: goto tr114;
		case 47: goto tr111;
		case 64: goto tr146;
		case 78: goto st95;
		case 92: goto tr111;
		case 94: goto tr111;
		case 95: goto tr114;
		case 126: goto tr111;
	}
	if ( (*p) < 36 ) {
		if ( (*p) < -32 ) {
			if ( -62 <= (*p) && (*p) <= -33 )
				goto st1;
		} else if ( (*p) > -17 ) {
			if ( -16 <= (*p) && (*p) <= -12 )
				goto st4;
		} else
			goto st2;
	} else if ( (*p) > 37 ) {
		if ( (*p) < 65 ) {
			if ( 46 <= (*p) && (*p) <= 57 )
				goto st20;
		} else if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st20;
		} else
			goto st20;
	} else
		goto tr111;
	goto tr130;
st95:
	if ( ++p == pe )
		goto _test_eof95;
case 95:
	switch( (*p) ) {
		case 64: goto st21;
		case 79: goto st96;
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
	goto tr93;
st96:
	if ( ++p == pe )
		goto _test_eof96;
case 96:
	switch( (*p) ) {
		case 64: goto st21;
		case 84: goto st97;
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
	goto tr93;
st97:
	if ( ++p == pe )
		goto _test_eof97;
case 97:
	switch( (*p) ) {
		case 64: goto st21;
		case 79: goto st98;
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
	goto tr93;
st98:
	if ( ++p == pe )
		goto _test_eof98;
case 98:
	switch( (*p) ) {
		case 64: goto st21;
		case 67: goto st99;
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
	goto tr93;
st99:
	if ( ++p == pe )
		goto _test_eof99;
case 99:
	switch( (*p) ) {
		case 64: goto st21;
		case 95: goto st100;
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
	goto tr93;
st100:
	if ( ++p == pe )
		goto _test_eof100;
case 100:
	switch( (*p) ) {
		case 64: goto st21;
		case 95: goto tr99;
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
	goto tr93;
tr99:
#line 1 "NONE"
	{te = p+1;}
#line 102 "wikitext_ragel.rl"
	{act = 1;}
	goto st156;
st156:
	if ( ++p == pe )
		goto _test_eof156;
case 156:
#line 3502 "wikitext_ragel.c"
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
	goto tr147;
st157:
	if ( ++p == pe )
		goto _test_eof157;
case 157:
	switch( (*p) ) {
		case 123: goto tr204;
		case 124: goto tr205;
	}
	goto tr203;
st158:
	if ( ++p == pe )
		goto _test_eof158;
case 158:
	if ( (*p) == 125 )
		goto tr207;
	goto tr206;
tr129:
#line 1 "NONE"
	{te = p+1;}
#line 669 "wikitext_ragel.rl"
	{act = 30;}
	goto st159;
tr207:
#line 1 "NONE"
	{te = p+1;}
#line 420 "wikitext_ragel.rl"
	{act = 14;}
	goto st159;
st159:
	if ( ++p == pe )
		goto _test_eof159;
case 159:
#line 3551 "wikitext_ragel.c"
	if ( (*p) == 125 )
		goto tr208;
	goto tr0;
	}
	_test_eof101: cs = 101; goto _test_eof; 
	_test_eof1: cs = 1; goto _test_eof; 
	_test_eof102: cs = 102; goto _test_eof; 
	_test_eof2: cs = 2; goto _test_eof; 
	_test_eof3: cs = 3; goto _test_eof; 
	_test_eof4: cs = 4; goto _test_eof; 
	_test_eof5: cs = 5; goto _test_eof; 
	_test_eof6: cs = 6; goto _test_eof; 
	_test_eof103: cs = 103; goto _test_eof; 
	_test_eof104: cs = 104; goto _test_eof; 
	_test_eof105: cs = 105; goto _test_eof; 
	_test_eof106: cs = 106; goto _test_eof; 
	_test_eof107: cs = 107; goto _test_eof; 
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
	_test_eof108: cs = 108; goto _test_eof; 
	_test_eof109: cs = 109; goto _test_eof; 
	_test_eof110: cs = 110; goto _test_eof; 
	_test_eof111: cs = 111; goto _test_eof; 
	_test_eof112: cs = 112; goto _test_eof; 
	_test_eof20: cs = 20; goto _test_eof; 
	_test_eof21: cs = 21; goto _test_eof; 
	_test_eof22: cs = 22; goto _test_eof; 
	_test_eof23: cs = 23; goto _test_eof; 
	_test_eof24: cs = 24; goto _test_eof; 
	_test_eof113: cs = 113; goto _test_eof; 
	_test_eof114: cs = 114; goto _test_eof; 
	_test_eof115: cs = 115; goto _test_eof; 
	_test_eof116: cs = 116; goto _test_eof; 
	_test_eof117: cs = 117; goto _test_eof; 
	_test_eof118: cs = 118; goto _test_eof; 
	_test_eof119: cs = 119; goto _test_eof; 
	_test_eof120: cs = 120; goto _test_eof; 
	_test_eof121: cs = 121; goto _test_eof; 
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
	_test_eof58: cs = 58; goto _test_eof; 
	_test_eof59: cs = 59; goto _test_eof; 
	_test_eof122: cs = 122; goto _test_eof; 
	_test_eof123: cs = 123; goto _test_eof; 
	_test_eof124: cs = 124; goto _test_eof; 
	_test_eof60: cs = 60; goto _test_eof; 
	_test_eof61: cs = 61; goto _test_eof; 
	_test_eof62: cs = 62; goto _test_eof; 
	_test_eof125: cs = 125; goto _test_eof; 
	_test_eof126: cs = 126; goto _test_eof; 
	_test_eof63: cs = 63; goto _test_eof; 
	_test_eof127: cs = 127; goto _test_eof; 
	_test_eof64: cs = 64; goto _test_eof; 
	_test_eof128: cs = 128; goto _test_eof; 
	_test_eof129: cs = 129; goto _test_eof; 
	_test_eof65: cs = 65; goto _test_eof; 
	_test_eof66: cs = 66; goto _test_eof; 
	_test_eof67: cs = 67; goto _test_eof; 
	_test_eof68: cs = 68; goto _test_eof; 
	_test_eof69: cs = 69; goto _test_eof; 
	_test_eof130: cs = 130; goto _test_eof; 
	_test_eof70: cs = 70; goto _test_eof; 
	_test_eof71: cs = 71; goto _test_eof; 
	_test_eof72: cs = 72; goto _test_eof; 
	_test_eof73: cs = 73; goto _test_eof; 
	_test_eof74: cs = 74; goto _test_eof; 
	_test_eof75: cs = 75; goto _test_eof; 
	_test_eof76: cs = 76; goto _test_eof; 
	_test_eof77: cs = 77; goto _test_eof; 
	_test_eof78: cs = 78; goto _test_eof; 
	_test_eof79: cs = 79; goto _test_eof; 
	_test_eof131: cs = 131; goto _test_eof; 
	_test_eof80: cs = 80; goto _test_eof; 
	_test_eof81: cs = 81; goto _test_eof; 
	_test_eof82: cs = 82; goto _test_eof; 
	_test_eof83: cs = 83; goto _test_eof; 
	_test_eof84: cs = 84; goto _test_eof; 
	_test_eof85: cs = 85; goto _test_eof; 
	_test_eof86: cs = 86; goto _test_eof; 
	_test_eof87: cs = 87; goto _test_eof; 
	_test_eof88: cs = 88; goto _test_eof; 
	_test_eof132: cs = 132; goto _test_eof; 
	_test_eof133: cs = 133; goto _test_eof; 
	_test_eof134: cs = 134; goto _test_eof; 
	_test_eof135: cs = 135; goto _test_eof; 
	_test_eof136: cs = 136; goto _test_eof; 
	_test_eof137: cs = 137; goto _test_eof; 
	_test_eof89: cs = 89; goto _test_eof; 
	_test_eof90: cs = 90; goto _test_eof; 
	_test_eof91: cs = 91; goto _test_eof; 
	_test_eof138: cs = 138; goto _test_eof; 
	_test_eof92: cs = 92; goto _test_eof; 
	_test_eof139: cs = 139; goto _test_eof; 
	_test_eof140: cs = 140; goto _test_eof; 
	_test_eof141: cs = 141; goto _test_eof; 
	_test_eof142: cs = 142; goto _test_eof; 
	_test_eof143: cs = 143; goto _test_eof; 
	_test_eof144: cs = 144; goto _test_eof; 
	_test_eof145: cs = 145; goto _test_eof; 
	_test_eof146: cs = 146; goto _test_eof; 
	_test_eof147: cs = 147; goto _test_eof; 
	_test_eof148: cs = 148; goto _test_eof; 
	_test_eof93: cs = 93; goto _test_eof; 
	_test_eof149: cs = 149; goto _test_eof; 
	_test_eof150: cs = 150; goto _test_eof; 
	_test_eof151: cs = 151; goto _test_eof; 
	_test_eof152: cs = 152; goto _test_eof; 
	_test_eof94: cs = 94; goto _test_eof; 
	_test_eof153: cs = 153; goto _test_eof; 
	_test_eof154: cs = 154; goto _test_eof; 
	_test_eof155: cs = 155; goto _test_eof; 
	_test_eof95: cs = 95; goto _test_eof; 
	_test_eof96: cs = 96; goto _test_eof; 
	_test_eof97: cs = 97; goto _test_eof; 
	_test_eof98: cs = 98; goto _test_eof; 
	_test_eof99: cs = 99; goto _test_eof; 
	_test_eof100: cs = 100; goto _test_eof; 
	_test_eof156: cs = 156; goto _test_eof; 
	_test_eof157: cs = 157; goto _test_eof; 
	_test_eof158: cs = 158; goto _test_eof; 
	_test_eof159: cs = 159; goto _test_eof; 

	_test_eof: {}
	if ( p == eof )
	{
	switch ( cs ) {
	case 1: goto tr0;
	case 102: goto tr130;
	case 2: goto tr0;
	case 3: goto tr0;
	case 4: goto tr0;
	case 5: goto tr0;
	case 6: goto tr0;
	case 103: goto tr131;
	case 104: goto tr133;
	case 105: goto tr135;
	case 106: goto tr136;
	case 107: goto tr137;
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
	case 108: goto tr141;
	case 109: goto tr141;
	case 110: goto tr141;
	case 111: goto tr141;
	case 112: goto tr130;
	case 20: goto tr0;
	case 21: goto tr0;
	case 22: goto tr0;
	case 23: goto tr0;
	case 24: goto tr0;
	case 113: goto tr147;
	case 114: goto tr147;
	case 115: goto tr147;
	case 116: goto tr147;
	case 117: goto tr130;
	case 118: goto tr135;
	case 119: goto tr151;
	case 120: goto tr152;
	case 121: goto tr165;
	case 25: goto tr29;
	case 26: goto tr29;
	case 27: goto tr29;
	case 28: goto tr29;
	case 29: goto tr29;
	case 30: goto tr29;
	case 31: goto tr29;
	case 32: goto tr29;
	case 33: goto tr29;
	case 34: goto tr29;
	case 35: goto tr29;
	case 36: goto tr29;
	case 37: goto tr29;
	case 38: goto tr29;
	case 39: goto tr29;
	case 40: goto tr29;
	case 41: goto tr29;
	case 42: goto tr29;
	case 43: goto tr29;
	case 44: goto tr29;
	case 45: goto tr29;
	case 46: goto tr29;
	case 47: goto tr29;
	case 48: goto tr29;
	case 49: goto tr29;
	case 50: goto tr29;
	case 51: goto tr29;
	case 52: goto tr29;
	case 53: goto tr29;
	case 54: goto tr29;
	case 55: goto tr29;
	case 56: goto tr29;
	case 57: goto tr29;
	case 58: goto tr29;
	case 59: goto tr29;
	case 122: goto tr165;
	case 123: goto tr165;
	case 124: goto tr165;
	case 60: goto tr29;
	case 61: goto tr29;
	case 62: goto tr29;
	case 125: goto tr165;
	case 126: goto tr165;
	case 63: goto tr29;
	case 127: goto tr165;
	case 64: goto tr29;
	case 128: goto tr165;
	case 129: goto tr165;
	case 65: goto tr29;
	case 66: goto tr29;
	case 67: goto tr29;
	case 68: goto tr29;
	case 69: goto tr29;
	case 130: goto tr165;
	case 70: goto tr29;
	case 71: goto tr29;
	case 72: goto tr29;
	case 73: goto tr29;
	case 74: goto tr29;
	case 75: goto tr29;
	case 76: goto tr29;
	case 77: goto tr29;
	case 78: goto tr29;
	case 79: goto tr29;
	case 131: goto tr165;
	case 80: goto tr29;
	case 81: goto tr29;
	case 82: goto tr29;
	case 83: goto tr29;
	case 84: goto tr29;
	case 85: goto tr29;
	case 86: goto tr29;
	case 87: goto tr29;
	case 88: goto tr29;
	case 132: goto tr179;
	case 133: goto tr179;
	case 134: goto tr181;
	case 135: goto tr151;
	case 136: goto tr151;
	case 137: goto tr151;
	case 89: goto tr84;
	case 90: goto tr84;
	case 91: goto tr84;
	case 138: goto tr147;
	case 92: goto tr88;
	case 139: goto tr151;
	case 140: goto tr151;
	case 141: goto tr151;
	case 142: goto tr151;
	case 143: goto tr151;
	case 144: goto tr151;
	case 145: goto tr151;
	case 146: goto tr151;
	case 147: goto tr151;
	case 148: goto tr151;
	case 93: goto tr84;
	case 149: goto tr151;
	case 150: goto tr151;
	case 151: goto tr196;
	case 152: goto tr198;
	case 94: goto tr90;
	case 153: goto tr199;
	case 154: goto tr130;
	case 155: goto tr130;
	case 95: goto tr93;
	case 96: goto tr93;
	case 97: goto tr93;
	case 98: goto tr93;
	case 99: goto tr93;
	case 100: goto tr93;
	case 156: goto tr147;
	case 157: goto tr203;
	case 158: goto tr206;
	case 159: goto tr0;
	}
	}

	_out: {}
	}

#line 851 "wikitext_ragel.rl"
    if (cs == wikitext_error)
        rb_raise(eWikitextParserError, "failed before finding a token");
    else if (out->type == NO_TOKEN){
        out->stop = p;
        out->type = END_OF_FILE;
        //rb_raise(eWikitextParserError, "failed to produce a token");
    }
}
