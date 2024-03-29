
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


#line 59 "wikitext_ragel.c"
static const int wikitext_start = 98;
static const int wikitext_first_final = 98;
static const int wikitext_error = 0;

static const int wikitext_en_main = 98;


#line 864 "wikitext_ragel.rl"


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
    
#line 110 "wikitext_ragel.c"
	{
	cs = wikitext_start;
	ts = 0;
	te = 0;
	act = 0;
	}

#line 906 "wikitext_ragel.rl"
    
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
            {p++; cs = 98; goto _out;}
        }
	break;
	case 13:
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
                {p++; cs = 98; goto _out;}
              break;
              case POST_LINK :
                POP();
              case DEFAULT :
                ERROR("Closing without opening");
                EMIT(SKIP);
                {p++; cs = 98; goto _out;}
              break;
              default :
                EMIT(SKIP);
                {p++; cs = 98; goto _out;}
              break;
            }
        }
	break;
	case 27:
	{{p = ((te))-1;}
            state = GET_STATE();
            switch(state){
              case INNER_LINK :
              case LINK :
                TODO(); // Push token
                EMIT(PRINTABLE);
                {p++; cs = 98; goto _out;}
              break;
              case DEFAULT :
                PRINT("print");
                {p++; cs = 98; goto _out;}
              break;
              case POST_LINK :
                POP();
                EMIT(PRINTABLE);
                {p++; cs = 98; goto _out;}
              break;
              default :
                EMIT(SKIP);
                {p++; cs = 98; goto _out;}
              break;
            }
        }
	break;
	case 28:
	{{p = ((te))-1;}
            state = GET_STATE();
            switch(state){
              case INNER_LINK :
              case LINK :
                TODO(); // Push token
                EMIT(NUM);
                {p++; cs = 98; goto _out;}
              break;
              case DEFAULT :
                PRINT("num");
                {p++; cs = 98; goto _out;}
              break;
              case POST_LINK :
                POP();
                EMIT(NUM);
                {p++; cs = 98; goto _out;}
              break;
              default :
                EMIT(SKIP);
                {p++; cs = 98; goto _out;}
              break;
            }
        }
	break;
	case 29:
	{{p = ((te))-1;}
            state = GET_STATE();
            switch(state){
              case INNER_LINK :
              case LINK :
                TODO(); // Push token
                EMIT(ALNUM);
                {p++; cs = 98; goto _out;}
              break;
              case DEFAULT :
                PRINT("alnum");
                {p++; cs = 98; goto _out;}
              break;
              case POST_LINK :
                POP();
                EMIT(ALNUM);
                {p++; cs = 98; goto _out;}
              break;
              default :
                EMIT(SKIP);
                {p++; cs = 98; goto _out;}
              break;
            }
        }
	break;
	}
	}
	goto st98;
tr7:
#line 771 "wikitext_ragel.rl"
	{{p = ((te))-1;}{
            state = GET_STATE();
            switch(state){
              case INNER_LINK :
              case LINK :
                TODO(); // Push token
                EMIT(PRINTABLE);
                {p++; cs = 98; goto _out;}
              break;
              case DEFAULT :
                PRINT("print");
                {p++; cs = 98; goto _out;}
              break;
              case POST_LINK :
                POP();
                EMIT(PRINTABLE);
                {p++; cs = 98; goto _out;}
              break;
              default :
                EMIT(SKIP);
                {p++; cs = 98; goto _out;}
              break;
            }
        }}
	goto st98;
tr10:
#line 632 "wikitext_ragel.rl"
	{te = p+1;{
            if(GET_STATE() == POST_LINK)
              POP();
            EMIT(SKIP);
            {p++; cs = 98; goto _out;}
        }}
	goto st98;
tr12:
#line 624 "wikitext_ragel.rl"
	{te = p+1;{
            if(GET_STATE() == POST_LINK)
              POP();
            EMIT(SKIP);
            {p++; cs = 98; goto _out;}
        }}
	goto st98;
tr14:
#line 616 "wikitext_ragel.rl"
	{te = p+1;{
            if(GET_STATE() == POST_LINK)
              POP();
            EMIT(SKIP);
            {p++; cs = 98; goto _out;}
        }}
	goto st98;
tr18:
#line 608 "wikitext_ragel.rl"
	{te = p+1;{
          if(GET_STATE() == POST_LINK)
            POP();
          EMIT(SKIP);
          {p++; cs = 98; goto _out;}
        }}
	goto st98;
tr22:
#line 600 "wikitext_ragel.rl"
	{te = p+1;{
            if(GET_STATE() == POST_LINK)
              POP();
            EMIT(SKIP);
            {p++; cs = 98; goto _out;}
        }}
	goto st98;
tr29:
#line 797 "wikitext_ragel.rl"
	{{p = ((te))-1;}{
            state = GET_STATE();
            switch(state){
              case INNER_LINK :
              case LINK :
                TODO(); // Push token
                EMIT(NUM);
                {p++; cs = 98; goto _out;}
              break;
              case DEFAULT :
                PRINT("num");
                {p++; cs = 98; goto _out;}
              break;
              case POST_LINK :
                POP();
                EMIT(NUM);
                {p++; cs = 98; goto _out;}
              break;
              default :
                EMIT(SKIP);
                {p++; cs = 98; goto _out;}
              break;
            }
        }}
	goto st98;
tr32:
#line 640 "wikitext_ragel.rl"
	{{p = ((te))-1;}{
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
                {p++; cs = 98; goto _out;}
              break;
              default :
                EMIT(SKIP);
                {p++; cs = 98; goto _out;}
              break;
            }
        }}
	goto st98;
tr42:
#line 106 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(SKIP);
            {p++; cs = 98; goto _out;}
        }}
	goto st98;
tr46:
#line 136 "wikitext_ragel.rl"
	{te = p+1;{
            state = GET_STATE();
            switch(state){
              case NOWIKI :
                opening = LAST_TYPE();
                if(opening == PRE_START) {
                  POP();
                  EMIT(SKIP);
                  {p++; cs = 98; goto _out;}
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
                {p++; cs = 98; goto _out;}
              break;
            }
        }}
	goto st98;
tr64:
#line 113 "wikitext_ragel.rl"
	{te = p+1;{
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
                {p++; cs = 98; goto _out;}
              break;
              default :
                EMIT(SKIP);
                {p++; cs = 98; goto _out;}
              break;
            }
        }}
	goto st98;
tr82:
#line 827 "wikitext_ragel.rl"
	{{p = ((te))-1;}{
            state = GET_STATE();
            switch(state){
              case INNER_LINK :
              case LINK :
                TODO(); // Push token
                EMIT(ALNUM);
                {p++; cs = 98; goto _out;}
              break;
              case DEFAULT :
                PRINT("alnum");
                {p++; cs = 98; goto _out;}
              break;
              case POST_LINK :
                POP();
                EMIT(ALNUM);
                {p++; cs = 98; goto _out;}
              break;
              default :
                EMIT(SKIP);
                {p++; cs = 98; goto _out;}
              break;
            }
        }}
	goto st98;
tr86:
#line 370 "wikitext_ragel.rl"
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
              case POST_LINK :
                POP();
              case DEFAULT :
                PUSH(LINK_START,LINK);
                EMIT(LINK_START);
                {p++; cs = 98; goto _out;}
              break;
              default :
                EMIT(SKIP);
                {p++; cs = 98; goto _out;}
              break;
            }
        }}
	goto st98;
tr88:
#line 350 "wikitext_ragel.rl"
	{te = p+1;{
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
                {p++; cs = 98; goto _out;}
              break;
            }
        }}
	goto st98;
tr100:
#line 64 "wikitext_ragel.rl"
	{
        out->code_point = *p & 0x7f;
    }
#line 854 "wikitext_ragel.rl"
	{te = p+1;{
                if(GET_STATE() == POST_LINK)
                  POP();
                EMIT(SKIP);
                {p++; cs = 98; goto _out;}
        }}
	goto st98;
tr101:
#line 744 "wikitext_ragel.rl"
	{te = p+1;{
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
            {p++; cs = 98; goto _out;}
        }}
#line 64 "wikitext_ragel.rl"
	{
        out->code_point = *p & 0x7f;
    }
	goto st98;
tr104:
#line 771 "wikitext_ragel.rl"
	{te = p+1;{
            state = GET_STATE();
            switch(state){
              case INNER_LINK :
              case LINK :
                TODO(); // Push token
                EMIT(PRINTABLE);
                {p++; cs = 98; goto _out;}
              break;
              case DEFAULT :
                PRINT("print");
                {p++; cs = 98; goto _out;}
              break;
              case POST_LINK :
                POP();
                EMIT(PRINTABLE);
                {p++; cs = 98; goto _out;}
              break;
              default :
                EMIT(SKIP);
                {p++; cs = 98; goto _out;}
              break;
            }
        }}
	goto st98;
tr124:
#line 827 "wikitext_ragel.rl"
	{te = p;p--;{
            state = GET_STATE();
            switch(state){
              case INNER_LINK :
              case LINK :
                TODO(); // Push token
                EMIT(ALNUM);
                {p++; cs = 98; goto _out;}
              break;
              case DEFAULT :
                PRINT("alnum");
                {p++; cs = 98; goto _out;}
              break;
              case POST_LINK :
                POP();
                EMIT(ALNUM);
                {p++; cs = 98; goto _out;}
              break;
              default :
                EMIT(SKIP);
                {p++; cs = 98; goto _out;}
              break;
            }
        }}
	goto st98;
tr126:
#line 744 "wikitext_ragel.rl"
	{te = p;p--;{
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
            {p++; cs = 98; goto _out;}
        }}
	goto st98;
tr127:
#line 744 "wikitext_ragel.rl"
	{te = p+1;{
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
            {p++; cs = 98; goto _out;}
        }}
	goto st98;
tr128:
#line 196 "wikitext_ragel.rl"
	{te = p;p--;{
            if (out->column_start == 1 || last_token_type == BLOCKQUOTE)
            {
                if(GET_STATE() == POST_LINK)
                  POP();
                REWIND();
                EMIT(SKIP);
                {p++; cs = 98; goto _out;}
            } else {
              state = GET_STATE();
              switch(state){
                case INNER_LINK :
                case LINK :
                  TODO(); // Push token
                  EMIT(SPACE);
                  {p++; cs = 98; goto _out;}
                break;
                case DEFAULT :
                  PRINT("space");
                  {p++; cs = 98; goto _out;}
                break;
                case POST_LINK :
                  POP();
                  EMIT(SPACE);
                  {p++; cs = 98; goto _out;}
                break;
                default :
                  EMIT(SKIP);
                  {p++; cs = 98; goto _out;}
                break;
              }
            }
        }}
	goto st98;
tr130:
#line 231 "wikitext_ragel.rl"
	{te = p;p--;{
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
                  {p++; cs = 98; goto _out;}
                break;
                case DEFAULT :
                  PRINT("print");
                  {p++; cs = 98; goto _out;}
                break;
                case POST_LINK :
                  POP();
                  EMIT(PRINTABLE);
                  {p++; cs = 98; goto _out;}
                break;
                default :
                  EMIT(SKIP);
                  {p++; cs = 98; goto _out;}
                break;
              }
            }
        }}
	goto st98;
tr131:
#line 771 "wikitext_ragel.rl"
	{te = p;p--;{
            state = GET_STATE();
            switch(state){
              case INNER_LINK :
              case LINK :
                TODO(); // Push token
                EMIT(PRINTABLE);
                {p++; cs = 98; goto _out;}
              break;
              case DEFAULT :
                PRINT("print");
                {p++; cs = 98; goto _out;}
              break;
              case POST_LINK :
                POP();
                EMIT(PRINTABLE);
                {p++; cs = 98; goto _out;}
              break;
              default :
                EMIT(SKIP);
                {p++; cs = 98; goto _out;}
              break;
            }
        }}
	goto st98;
tr135:
#line 165 "wikitext_ragel.rl"
	{te = p;p--;{
            if (DISTANCE() > 1) {
              if(GET_STATE() == POST_LINK)
                POP();
              EMIT(SKIP);
              {p++; cs = 98; goto _out;}
            } else {
              state = GET_STATE();
              switch(state) {
                case DEFAULT :
                  PRINT("print");
                  {p++; cs = 98; goto _out;}
                break;
                case INNER_LINK :
                case LINK :
                  TODO(); // Push token
                  EMIT(PRINTABLE);
                  {p++; cs = 98; goto _out;}
                break;
                case POST_LINK :
                  POP();
                  EMIT(PRINTABLE);
                  {p++; cs = 98; goto _out;}
                break;
              }
            }
        }}
	goto st98;
tr139:
#line 165 "wikitext_ragel.rl"
	{te = p+1;{
            if (DISTANCE() > 1) {
              if(GET_STATE() == POST_LINK)
                POP();
              EMIT(SKIP);
              {p++; cs = 98; goto _out;}
            } else {
              state = GET_STATE();
              switch(state) {
                case DEFAULT :
                  PRINT("print");
                  {p++; cs = 98; goto _out;}
                break;
                case INNER_LINK :
                case LINK :
                  TODO(); // Push token
                  EMIT(PRINTABLE);
                  {p++; cs = 98; goto _out;}
                break;
                case POST_LINK :
                  POP();
                  EMIT(PRINTABLE);
                  {p++; cs = 98; goto _out;}
                break;
              }
            }
        }}
	goto st98;
tr140:
#line 106 "wikitext_ragel.rl"
	{te = p;p--;{
            EMIT(SKIP);
            {p++; cs = 98; goto _out;}
        }}
	goto st98;
tr144:
#line 797 "wikitext_ragel.rl"
	{te = p;p--;{
            state = GET_STATE();
            switch(state){
              case INNER_LINK :
              case LINK :
                TODO(); // Push token
                EMIT(NUM);
                {p++; cs = 98; goto _out;}
              break;
              case DEFAULT :
                PRINT("num");
                {p++; cs = 98; goto _out;}
              break;
              case POST_LINK :
                POP();
                EMIT(NUM);
                {p++; cs = 98; goto _out;}
              break;
              default :
                EMIT(SKIP);
                {p++; cs = 98; goto _out;}
              break;
            }
        }}
	goto st98;
tr147:
#line 662 "wikitext_ragel.rl"
	{te = p;p--;{
            state = GET_STATE();
            switch(state){
              case INNER_LINK :
              case LINK :
                TODO(); // Push token
                EMIT(PRINTABLE);
                {p++; cs = 98; goto _out;}
              break;
              case DEFAULT :
                PRINT("print");
                {p++; cs = 98; goto _out;}
              break;
              case POST_LINK :
                POP();
                EMIT(PRINTABLE);
                {p++; cs = 98; goto _out;}
              break;
              default :
                EMIT(SKIP);
                {p++; cs = 98; goto _out;}
              break;
            }
        }}
	goto st98;
tr148:
#line 640 "wikitext_ragel.rl"
	{te = p+1;{
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
                {p++; cs = 98; goto _out;}
              break;
              default :
                EMIT(SKIP);
                {p++; cs = 98; goto _out;}
              break;
            }
        }}
	goto st98;
tr160:
#line 640 "wikitext_ragel.rl"
	{te = p;p--;{
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
                {p++; cs = 98; goto _out;}
              break;
              default :
                EMIT(SKIP);
                {p++; cs = 98; goto _out;}
              break;
            }
        }}
	goto st98;
tr174:
#line 263 "wikitext_ragel.rl"
	{te = p;p--;{
            if (out->column_start == 1)
            {
                REWIND();
                if(GET_STATE() == POST_LINK)
                  POP();
                if (DISTANCE() <= 6) {
                  if (GET_STATE() == DEFAULT){
                    PRINT_CRLF();
                    {p++; cs = 98; goto _out;}
                  }
                } else {
                    p = ts + 6;
                    EMIT(SKIP);
                    {p++; cs = 98; goto _out;}
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
                    {p++; cs = 98; goto _out;}
                  } else {
                    EMIT(SKIP);
                    {p++; cs = 98; goto _out;}
                  }
                } else {
                    p -= 6; // will scan the H6 on the next scan
                    state = GET_STATE();
                    switch(state){
                      case INNER_LINK :
                      case LINK :
                        TODO(); // Push token
                        EMIT(SPACE);
                        {p++; cs = 98; goto _out;}
                      break;
                      case DEFAULT :
                        PRINT("space");
                        {p++; cs = 98; goto _out;}
                      break;
                      case POST_LINK :
                        POP();
                        EMIT(SPACE);
                        {p++; cs = 98; goto _out;}
                      break;
                      default :
                        EMIT(SKIP);
                        {p++; cs = 98; goto _out;}
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
                    {p++; cs = 98; goto _out;}
                  break;
                  case DEFAULT :
                    PRINT("space");
                    {p++; cs = 98; goto _out;}
                  break;
                  case POST_LINK :
                    POP();
                    EMIT(SPACE);
                    {p++; cs = 98; goto _out;}
                  break;
                  default :
                    EMIT(SKIP);
                    {p++; cs = 98; goto _out;}
                  break;
                }
            }
        }}
	goto st98;
tr176:
#line 688 "wikitext_ragel.rl"
	{te = p;p--;{
            if (out->column_start == 1) {
              if(GET_STATE() == POST_LINK)
                POP();
              EMIT(SKIP);
              {p++; cs = 98; goto _out;}
            } else {
              state = GET_STATE();
              switch(state){
                case DEFAULT :
                  PRINT("print");
                  {p++; cs = 98; goto _out;}
                break;
                case POST_LINK :
                  POP();
                  EMIT(PRINTABLE);
                  {p++; cs = 98; goto _out;}
                break;
                case NOWIKI :
                  opening = LAST_TYPE();
                  if(opening == TAG_START) {
                    POP();
                    EMIT(SKIP);
                    {p++; cs = 98; goto _out;}
                  }
                break;
                default :
                  ERROR("Closing token without opening token");
                  EMIT(SKIP);
                  {p++; cs = 98; goto _out;}
                break;
              }
            }
        }}
	goto st98;
tr190:
#line 542 "wikitext_ragel.rl"
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
              case POST_LINK :
                POP();
              case DEFAULT :
                PUSH(EXT_LINK_START,LINK);
                EMIT(EXT_LINK_START);
                {p++; cs = 98; goto _out;}
              break;
              default :
                EMIT(SKIP);
                {p++; cs = 98; goto _out;}
              break;
            }
        }}
	goto st98;
tr192:
#line 370 "wikitext_ragel.rl"
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
              case POST_LINK :
                POP();
              case DEFAULT :
                PUSH(LINK_START,LINK);
                EMIT(LINK_START);
                {p++; cs = 98; goto _out;}
              break;
              default :
                EMIT(SKIP);
                {p++; cs = 98; goto _out;}
              break;
            }
        }}
	goto st98;
tr193:
#line 568 "wikitext_ragel.rl"
	{te = p;p--;{
            state = GET_STATE();
            switch(state){
              case BLIND :
                ERROR("Non-matching tokens");
                EMIT(SKIP);
                {p++; cs = 98; goto _out;}
              break;
              case BLIND_LINK :
              case INNER_LINK :
                POP();
                EMIT(SKIP);
                {p++; cs = 98; goto _out;}
              break;
              case LINK :
                POP();
                TODO(); //Close link tag
                EMIT(EXT_LINK_END);
                {p++; cs = 98; goto _out;}
              case POST_LINK :
                POP();
              case DEFAULT :
                ERROR("Closing tag without opening");
              break;
              default :
                EMIT(SKIP);
                {p++; cs = 98; goto _out;}
              break;
            }
        }}
	goto st98;
tr194:
#line 396 "wikitext_ragel.rl"
	{te = p+1;{
            state = GET_STATE();
            switch(state){
              case BLIND :
                if(LAST_TYPE() == SPECIAL_LINK_START) {
                  POP();
                  EMIT(SKIP);
                  {p++; cs = 98; goto _out;}
                } else
                  ERROR("Non-matching tokens");
              break;
              case BLIND_LINK :
              case INNER_LINK :
                POP();
                EMIT(SKIP);
                {p++; cs = 98; goto _out;}
              break;
              case LINK :
                POP();
                TODO(); //Close link tag
                EMIT(LINK_END);
                // used to combine links such as [[Alan]]owi
                PUSH(SKIP,POST_LINK);
                {p++; cs = 98; goto _out;}
              break;
              case POST_LINK :
                POP();
              case DEFAULT :
                ERROR("Closing tag without opening");
              break;
              default :
                EMIT(SKIP);
                {p++; cs = 98; goto _out;}
              break;
            }
        }}
	goto st98;
tr196:
#line 724 "wikitext_ragel.rl"
	{te = p+1;{
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
                {p++; cs = 98; goto _out;}
              break;
            }
        }}
	goto st98;
tr197:
#line 434 "wikitext_ragel.rl"
	{te = p+1;{
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
                {p++; cs = 98; goto _out;}
              break;
            }
        }}
	goto st98;
tr198:
#line 525 "wikitext_ragel.rl"
	{te = p;p--;{
          state = GET_STATE();
          switch(state){
              case LINK :
                EMIT(SEPARATOR);
                {p++; cs = 98; goto _out;}
              break;
              case POST_LINK :
                POP();
              default :
                EMIT(SKIP);
                {p++; cs = 98; goto _out;}
              break;
          }
        }}
	goto st98;
tr200:
#line 454 "wikitext_ragel.rl"
	{te = p+1;{
            state = GET_STATE();
            switch(state){
              case BLIND :
                opening = LAST_TYPE();
                if(opening == IMG_START){
                  POP();
                  EMIT(SKIP);
                  {p++; cs = 98; goto _out;}
                } else {
                  ERROR("Non-matching tokens");
                  EMIT(SKIP);
                  {p++; cs = 98; goto _out;}
                }
              break;
              case BLIND_LINK :
              case INNER_LINK :
              case LINK :
                ERROR("Non-matching tokens");
                EMIT(SKIP);
                {p++; cs = 98; goto _out;}
              break;
              case POST_LINK :
                POP();
              case DEFAULT :
                ERROR("Closing without opening");
                EMIT(SKIP);
                {p++; cs = 98; goto _out;}
              break;
              default :
                EMIT(SKIP);
                {p++; cs = 98; goto _out;}
              break;
            }
        }}
	goto st98;
st98:
#line 1 "NONE"
	{ts = 0;}
#line 1 "NONE"
	{act = 0;}
	if ( ++p == pe )
		goto _test_eof98;
case 98:
#line 1 "NONE"
	{ts = p;}
#line 1285 "wikitext_ragel.c"
	switch( (*p) ) {
		case 10: goto tr101;
		case 13: goto tr102;
		case 32: goto tr103;
		case 35: goto st102;
		case 38: goto tr106;
		case 39: goto st104;
		case 42: goto st102;
		case 47: goto tr104;
		case 60: goto st117;
		case 61: goto tr111;
		case 62: goto st131;
		case 70: goto tr114;
		case 72: goto tr115;
		case 77: goto tr116;
		case 83: goto tr117;
		case 91: goto st148;
		case 92: goto tr104;
		case 93: goto st150;
		case 94: goto tr104;
		case 95: goto tr120;
		case 96: goto tr42;
		case 102: goto tr114;
		case 104: goto tr115;
		case 109: goto tr116;
		case 115: goto tr117;
		case 123: goto st152;
		case 124: goto st153;
		case 125: goto tr123;
		case 126: goto tr104;
		case 127: goto tr100;
	}
	if ( (*p) < 33 ) {
		if ( (*p) < -32 ) {
			if ( -62 <= (*p) && (*p) <= -33 )
				goto st1;
		} else if ( (*p) > -17 ) {
			if ( (*p) > -12 ) {
				if ( 1 <= (*p) && (*p) <= 31 )
					goto tr100;
			} else if ( (*p) >= -16 )
				goto st4;
		} else
			goto st2;
	} else if ( (*p) > 44 ) {
		if ( (*p) < 58 ) {
			if ( (*p) > 46 ) {
				if ( 48 <= (*p) && (*p) <= 57 )
					goto tr109;
			} else if ( (*p) >= 45 )
				goto tr108;
		} else if ( (*p) > 59 ) {
			if ( (*p) > 64 ) {
				if ( 65 <= (*p) && (*p) <= 122 )
					goto tr113;
			} else if ( (*p) >= 63 )
				goto tr104;
		} else
			goto st102;
	} else
		goto tr104;
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
#line 69 "wikitext_ragel.rl"
	{
        out->code_point = ((uint32_t)(*(p - 1)) & 0x1f) << 6 |
            (*p & 0x3f);
    }
#line 827 "wikitext_ragel.rl"
	{act = 29;}
	goto st99;
tr3:
#line 1 "NONE"
	{te = p+1;}
#line 75 "wikitext_ragel.rl"
	{
        out->code_point = ((uint32_t)(*(p - 2)) & 0x0f) << 12 |
            ((uint32_t)(*(p - 1)) & 0x3f) << 6 |
            (*p & 0x3f);
    }
#line 827 "wikitext_ragel.rl"
	{act = 29;}
	goto st99;
tr6:
#line 1 "NONE"
	{te = p+1;}
#line 82 "wikitext_ragel.rl"
	{
        out->code_point = ((uint32_t)(*(p - 3)) & 0x07) << 18 |
            ((uint32_t)(*(p - 2)) & 0x3f) << 12 |
            ((uint32_t)(*(p - 1)) & 0x3f) << 6 |
            (*p & 0x3f);
    }
#line 827 "wikitext_ragel.rl"
	{act = 29;}
	goto st99;
tr125:
#line 1 "NONE"
	{te = p+1;}
#line 827 "wikitext_ragel.rl"
	{act = 29;}
	goto st99;
st99:
	if ( ++p == pe )
		goto _test_eof99;
case 99:
#line 1404 "wikitext_ragel.c"
	if ( (*p) < -16 ) {
		if ( (*p) > -33 ) {
			if ( -32 <= (*p) && (*p) <= -17 )
				goto st2;
		} else if ( (*p) >= -62 )
			goto st1;
	} else if ( (*p) > -12 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr125;
		} else if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr125;
		} else
			goto tr125;
	} else
		goto st4;
	goto tr124;
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
tr102:
#line 64 "wikitext_ragel.rl"
	{
        out->code_point = *p & 0x7f;
    }
	goto st100;
st100:
	if ( ++p == pe )
		goto _test_eof100;
case 100:
#line 1468 "wikitext_ragel.c"
	if ( (*p) == 10 )
		goto tr127;
	goto tr126;
tr103:
#line 59 "wikitext_ragel.rl"
	{
        MARK();
    }
	goto st101;
st101:
	if ( ++p == pe )
		goto _test_eof101;
case 101:
#line 1482 "wikitext_ragel.c"
	if ( (*p) == 32 )
		goto st101;
	goto tr128;
st102:
	if ( ++p == pe )
		goto _test_eof102;
case 102:
	switch( (*p) ) {
		case 35: goto st102;
		case 42: goto st102;
	}
	if ( 58 <= (*p) && (*p) <= 59 )
		goto st102;
	goto tr130;
tr106:
#line 1 "NONE"
	{te = p+1;}
	goto st103;
st103:
	if ( ++p == pe )
		goto _test_eof103;
case 103:
#line 1505 "wikitext_ragel.c"
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
	goto tr131;
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
st104:
	if ( ++p == pe )
		goto _test_eof104;
case 104:
	if ( (*p) == 39 )
		goto st105;
	goto tr135;
st105:
	if ( ++p == pe )
		goto _test_eof105;
case 105:
	if ( (*p) == 39 )
		goto st106;
	goto tr135;
st106:
	if ( ++p == pe )
		goto _test_eof106;
case 106:
	if ( (*p) == 39 )
		goto st107;
	goto tr135;
st107:
	if ( ++p == pe )
		goto _test_eof107;
case 107:
	if ( (*p) == 39 )
		goto tr139;
	goto tr135;
tr95:
#line 1 "NONE"
	{te = p+1;}
#line 106 "wikitext_ragel.rl"
	{act = 1;}
	goto st108;
tr108:
#line 1 "NONE"
	{te = p+1;}
#line 771 "wikitext_ragel.rl"
	{act = 27;}
	goto st108;
st108:
	if ( ++p == pe )
		goto _test_eof108;
case 108:
#line 1748 "wikitext_ragel.c"
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
#line 106 "wikitext_ragel.rl"
	{act = 1;}
	goto st109;
st109:
	if ( ++p == pe )
		goto _test_eof109;
case 109:
#line 1851 "wikitext_ragel.c"
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
	goto tr140;
tr141:
#line 1 "NONE"
	{te = p+1;}
#line 106 "wikitext_ragel.rl"
	{act = 1;}
	goto st110;
st110:
	if ( ++p == pe )
		goto _test_eof110;
case 110:
#line 1873 "wikitext_ragel.c"
	if ( (*p) == 46 )
		goto st23;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st22;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr142;
	} else
		goto tr142;
	goto tr140;
tr142:
#line 1 "NONE"
	{te = p+1;}
#line 106 "wikitext_ragel.rl"
	{act = 1;}
	goto st111;
st111:
	if ( ++p == pe )
		goto _test_eof111;
case 111:
#line 1895 "wikitext_ragel.c"
	if ( (*p) == 46 )
		goto st23;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st22;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr143;
	} else
		goto tr143;
	goto tr140;
tr143:
#line 1 "NONE"
	{te = p+1;}
#line 106 "wikitext_ragel.rl"
	{act = 1;}
	goto st112;
st112:
	if ( ++p == pe )
		goto _test_eof112;
case 112:
#line 1917 "wikitext_ragel.c"
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
	goto tr140;
tr109:
#line 1 "NONE"
	{te = p+1;}
#line 797 "wikitext_ragel.rl"
	{act = 28;}
	goto st113;
st113:
	if ( ++p == pe )
		goto _test_eof113;
case 113:
#line 1939 "wikitext_ragel.c"
	switch( (*p) ) {
		case 32: goto st25;
		case 44: goto st25;
		case 47: goto st25;
		case 58: goto st25;
		case 64: goto st21;
		case 95: goto st26;
	}
	if ( (*p) < 45 ) {
		if ( (*p) < -32 ) {
			if ( -62 <= (*p) && (*p) <= -33 )
				goto st1;
		} else if ( (*p) > -17 ) {
			if ( -16 <= (*p) && (*p) <= -12 )
				goto st4;
		} else
			goto st2;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr109;
		} else if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr113;
		} else
			goto tr113;
	} else
		goto st26;
	goto tr144;
st25:
	if ( ++p == pe )
		goto _test_eof25;
case 25:
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr30;
	goto tr29;
tr30:
#line 1 "NONE"
	{te = p+1;}
	goto st114;
st114:
	if ( ++p == pe )
		goto _test_eof114;
case 114:
#line 1984 "wikitext_ragel.c"
	switch( (*p) ) {
		case 32: goto st25;
		case 58: goto st25;
		case 95: goto st25;
	}
	if ( (*p) > 47 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr30;
	} else if ( (*p) >= 44 )
		goto st25;
	goto tr144;
st26:
	if ( ++p == pe )
		goto _test_eof26;
case 26:
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
		goto tr31;
	goto tr29;
tr31:
#line 1 "NONE"
	{te = p+1;}
#line 797 "wikitext_ragel.rl"
	{act = 28;}
	goto st115;
st115:
	if ( ++p == pe )
		goto _test_eof115;
case 115:
#line 2026 "wikitext_ragel.c"
	switch( (*p) ) {
		case 32: goto st25;
		case 44: goto st25;
		case 47: goto st25;
		case 58: goto st25;
		case 64: goto st21;
		case 95: goto st26;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st26;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st20;
		} else if ( (*p) >= 65 )
			goto st20;
	} else
		goto tr31;
	goto tr144;
tr113:
#line 1 "NONE"
	{te = p+1;}
#line 827 "wikitext_ragel.rl"
	{act = 29;}
	goto st116;
st116:
	if ( ++p == pe )
		goto _test_eof116;
case 116:
#line 2057 "wikitext_ragel.c"
	switch( (*p) ) {
		case 64: goto st21;
		case 95: goto st20;
	}
	if ( (*p) < 45 ) {
		if ( (*p) < -32 ) {
			if ( -62 <= (*p) && (*p) <= -33 )
				goto st1;
		} else if ( (*p) > -17 ) {
			if ( -16 <= (*p) && (*p) <= -12 )
				goto st4;
		} else
			goto st2;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr113;
		} else if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr113;
		} else
			goto tr113;
	} else
		goto st20;
	goto tr124;
st117:
	if ( ++p == pe )
		goto _test_eof117;
case 117:
	switch( (*p) ) {
		case 33: goto tr148;
		case 47: goto tr149;
		case 66: goto tr150;
		case 69: goto tr151;
		case 77: goto tr152;
		case 78: goto tr153;
		case 80: goto tr154;
		case 82: goto tr155;
		case 83: goto tr156;
		case 84: goto tr157;
		case 98: goto tr150;
		case 101: goto tr151;
		case 109: goto tr152;
		case 110: goto tr153;
		case 112: goto tr158;
		case 114: goto tr159;
		case 115: goto tr156;
		case 116: goto tr157;
	}
	if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr148;
	} else if ( (*p) >= 65 )
		goto tr148;
	goto tr147;
tr149:
#line 1 "NONE"
	{te = p+1;}
	goto st118;
st118:
	if ( ++p == pe )
		goto _test_eof118;
case 118:
#line 2121 "wikitext_ragel.c"
	switch( (*p) ) {
		case 66: goto st27;
		case 69: goto st37;
		case 77: goto st38;
		case 78: goto st42;
		case 80: goto st47;
		case 82: goto st49;
		case 83: goto st51;
		case 84: goto st56;
		case 98: goto st27;
		case 101: goto st37;
		case 109: goto st38;
		case 110: goto st42;
		case 112: goto st47;
		case 114: goto st49;
		case 115: goto st51;
		case 116: goto st56;
	}
	goto tr160;
st27:
	if ( ++p == pe )
		goto _test_eof27;
case 27:
	switch( (*p) ) {
		case 76: goto st28;
		case 108: goto st28;
	}
	goto tr32;
st28:
	if ( ++p == pe )
		goto _test_eof28;
case 28:
	switch( (*p) ) {
		case 79: goto st29;
		case 111: goto st29;
	}
	goto tr32;
st29:
	if ( ++p == pe )
		goto _test_eof29;
case 29:
	switch( (*p) ) {
		case 67: goto st30;
		case 99: goto st30;
	}
	goto tr32;
st30:
	if ( ++p == pe )
		goto _test_eof30;
case 30:
	switch( (*p) ) {
		case 75: goto st31;
		case 107: goto st31;
	}
	goto tr32;
st31:
	if ( ++p == pe )
		goto _test_eof31;
case 31:
	switch( (*p) ) {
		case 81: goto st32;
		case 113: goto st32;
	}
	goto tr32;
st32:
	if ( ++p == pe )
		goto _test_eof32;
case 32:
	switch( (*p) ) {
		case 85: goto st33;
		case 117: goto st33;
	}
	goto tr32;
st33:
	if ( ++p == pe )
		goto _test_eof33;
case 33:
	switch( (*p) ) {
		case 79: goto st34;
		case 111: goto st34;
	}
	goto tr32;
st34:
	if ( ++p == pe )
		goto _test_eof34;
case 34:
	switch( (*p) ) {
		case 84: goto st35;
		case 116: goto st35;
	}
	goto tr32;
st35:
	if ( ++p == pe )
		goto _test_eof35;
case 35:
	switch( (*p) ) {
		case 69: goto st36;
		case 101: goto st36;
	}
	goto tr32;
st36:
	if ( ++p == pe )
		goto _test_eof36;
case 36:
	if ( (*p) == 62 )
		goto tr42;
	goto tr32;
st37:
	if ( ++p == pe )
		goto _test_eof37;
case 37:
	switch( (*p) ) {
		case 77: goto st36;
		case 109: goto st36;
	}
	goto tr32;
st38:
	if ( ++p == pe )
		goto _test_eof38;
case 38:
	switch( (*p) ) {
		case 65: goto st39;
		case 97: goto st39;
	}
	goto tr32;
st39:
	if ( ++p == pe )
		goto _test_eof39;
case 39:
	switch( (*p) ) {
		case 84: goto st40;
		case 116: goto st40;
	}
	goto tr32;
st40:
	if ( ++p == pe )
		goto _test_eof40;
case 40:
	switch( (*p) ) {
		case 72: goto st41;
		case 104: goto st41;
	}
	goto tr32;
st41:
	if ( ++p == pe )
		goto _test_eof41;
case 41:
	if ( (*p) == 62 )
		goto tr46;
	goto tr32;
st42:
	if ( ++p == pe )
		goto _test_eof42;
case 42:
	switch( (*p) ) {
		case 79: goto st43;
		case 111: goto st43;
	}
	goto tr32;
st43:
	if ( ++p == pe )
		goto _test_eof43;
case 43:
	switch( (*p) ) {
		case 87: goto st44;
		case 119: goto st44;
	}
	goto tr32;
st44:
	if ( ++p == pe )
		goto _test_eof44;
case 44:
	switch( (*p) ) {
		case 73: goto st45;
		case 105: goto st45;
	}
	goto tr32;
st45:
	if ( ++p == pe )
		goto _test_eof45;
case 45:
	switch( (*p) ) {
		case 75: goto st46;
		case 107: goto st46;
	}
	goto tr32;
st46:
	if ( ++p == pe )
		goto _test_eof46;
case 46:
	switch( (*p) ) {
		case 73: goto st36;
		case 105: goto st36;
	}
	goto tr32;
st47:
	if ( ++p == pe )
		goto _test_eof47;
case 47:
	switch( (*p) ) {
		case 82: goto st48;
		case 114: goto st48;
	}
	goto tr32;
st48:
	if ( ++p == pe )
		goto _test_eof48;
case 48:
	switch( (*p) ) {
		case 69: goto st41;
		case 101: goto st41;
	}
	goto tr32;
st49:
	if ( ++p == pe )
		goto _test_eof49;
case 49:
	switch( (*p) ) {
		case 69: goto st50;
		case 101: goto st50;
	}
	goto tr32;
st50:
	if ( ++p == pe )
		goto _test_eof50;
case 50:
	switch( (*p) ) {
		case 70: goto st41;
		case 102: goto st41;
	}
	goto tr32;
st51:
	if ( ++p == pe )
		goto _test_eof51;
case 51:
	switch( (*p) ) {
		case 84: goto st52;
		case 116: goto st52;
	}
	goto tr32;
st52:
	if ( ++p == pe )
		goto _test_eof52;
case 52:
	switch( (*p) ) {
		case 82: goto st53;
		case 114: goto st53;
	}
	goto tr32;
st53:
	if ( ++p == pe )
		goto _test_eof53;
case 53:
	switch( (*p) ) {
		case 79: goto st54;
		case 111: goto st54;
	}
	goto tr32;
st54:
	if ( ++p == pe )
		goto _test_eof54;
case 54:
	switch( (*p) ) {
		case 78: goto st55;
		case 110: goto st55;
	}
	goto tr32;
st55:
	if ( ++p == pe )
		goto _test_eof55;
case 55:
	switch( (*p) ) {
		case 71: goto st36;
		case 103: goto st36;
	}
	goto tr32;
st56:
	if ( ++p == pe )
		goto _test_eof56;
case 56:
	switch( (*p) ) {
		case 73: goto st57;
		case 84: goto st36;
		case 105: goto st57;
		case 116: goto st36;
	}
	goto tr32;
st57:
	if ( ++p == pe )
		goto _test_eof57;
case 57:
	switch( (*p) ) {
		case 77: goto st58;
		case 109: goto st58;
	}
	goto tr32;
st58:
	if ( ++p == pe )
		goto _test_eof58;
case 58:
	switch( (*p) ) {
		case 69: goto st59;
		case 101: goto st59;
	}
	goto tr32;
st59:
	if ( ++p == pe )
		goto _test_eof59;
case 59:
	switch( (*p) ) {
		case 76: goto st60;
		case 108: goto st60;
	}
	goto tr32;
st60:
	if ( ++p == pe )
		goto _test_eof60;
case 60:
	switch( (*p) ) {
		case 73: goto st61;
		case 105: goto st61;
	}
	goto tr32;
st61:
	if ( ++p == pe )
		goto _test_eof61;
case 61:
	switch( (*p) ) {
		case 78: goto st48;
		case 110: goto st48;
	}
	goto tr32;
tr150:
#line 1 "NONE"
	{te = p+1;}
	goto st119;
st119:
	if ( ++p == pe )
		goto _test_eof119;
case 119:
#line 2462 "wikitext_ragel.c"
	switch( (*p) ) {
		case 76: goto st28;
		case 108: goto st28;
	}
	goto tr160;
tr151:
#line 1 "NONE"
	{te = p+1;}
	goto st120;
st120:
	if ( ++p == pe )
		goto _test_eof120;
case 120:
#line 2476 "wikitext_ragel.c"
	switch( (*p) ) {
		case 77: goto st36;
		case 109: goto st36;
	}
	goto tr160;
tr152:
#line 1 "NONE"
	{te = p+1;}
	goto st121;
st121:
	if ( ++p == pe )
		goto _test_eof121;
case 121:
#line 2490 "wikitext_ragel.c"
	switch( (*p) ) {
		case 65: goto st62;
		case 97: goto st62;
	}
	goto tr160;
st62:
	if ( ++p == pe )
		goto _test_eof62;
case 62:
	switch( (*p) ) {
		case 84: goto st63;
		case 116: goto st63;
	}
	goto tr32;
st63:
	if ( ++p == pe )
		goto _test_eof63;
case 63:
	switch( (*p) ) {
		case 72: goto st64;
		case 104: goto st64;
	}
	goto tr32;
st64:
	if ( ++p == pe )
		goto _test_eof64;
case 64:
	if ( (*p) == 62 )
		goto tr64;
	goto tr32;
tr153:
#line 1 "NONE"
	{te = p+1;}
	goto st122;
st122:
	if ( ++p == pe )
		goto _test_eof122;
case 122:
#line 2529 "wikitext_ragel.c"
	switch( (*p) ) {
		case 79: goto st43;
		case 111: goto st43;
	}
	goto tr160;
tr154:
#line 1 "NONE"
	{te = p+1;}
	goto st123;
st123:
	if ( ++p == pe )
		goto _test_eof123;
case 123:
#line 2543 "wikitext_ragel.c"
	switch( (*p) ) {
		case 82: goto st65;
		case 114: goto st65;
	}
	goto tr160;
st65:
	if ( ++p == pe )
		goto _test_eof65;
case 65:
	switch( (*p) ) {
		case 69: goto st64;
		case 101: goto st64;
	}
	goto tr32;
tr155:
#line 1 "NONE"
	{te = p+1;}
	goto st124;
st124:
	if ( ++p == pe )
		goto _test_eof124;
case 124:
#line 2566 "wikitext_ragel.c"
	switch( (*p) ) {
		case 69: goto st66;
		case 101: goto st66;
	}
	goto tr160;
st66:
	if ( ++p == pe )
		goto _test_eof66;
case 66:
	switch( (*p) ) {
		case 70: goto st64;
		case 102: goto st64;
	}
	goto tr32;
tr156:
#line 1 "NONE"
	{te = p+1;}
	goto st125;
st125:
	if ( ++p == pe )
		goto _test_eof125;
case 125:
#line 2589 "wikitext_ragel.c"
	switch( (*p) ) {
		case 84: goto st52;
		case 116: goto st52;
	}
	goto tr160;
tr157:
#line 1 "NONE"
	{te = p+1;}
	goto st126;
st126:
	if ( ++p == pe )
		goto _test_eof126;
case 126:
#line 2603 "wikitext_ragel.c"
	switch( (*p) ) {
		case 73: goto st67;
		case 84: goto st36;
		case 105: goto st67;
		case 116: goto st36;
	}
	goto tr160;
st67:
	if ( ++p == pe )
		goto _test_eof67;
case 67:
	switch( (*p) ) {
		case 77: goto st68;
		case 109: goto st68;
	}
	goto tr32;
st68:
	if ( ++p == pe )
		goto _test_eof68;
case 68:
	switch( (*p) ) {
		case 69: goto st69;
		case 101: goto st69;
	}
	goto tr32;
st69:
	if ( ++p == pe )
		goto _test_eof69;
case 69:
	switch( (*p) ) {
		case 76: goto st70;
		case 108: goto st70;
	}
	goto tr32;
st70:
	if ( ++p == pe )
		goto _test_eof70;
case 70:
	switch( (*p) ) {
		case 73: goto st71;
		case 105: goto st71;
	}
	goto tr32;
st71:
	if ( ++p == pe )
		goto _test_eof71;
case 71:
	switch( (*p) ) {
		case 78: goto st65;
		case 110: goto st65;
	}
	goto tr32;
tr158:
#line 1 "NONE"
	{te = p+1;}
	goto st127;
st127:
	if ( ++p == pe )
		goto _test_eof127;
case 127:
#line 2664 "wikitext_ragel.c"
	switch( (*p) ) {
		case 82: goto st65;
		case 114: goto st72;
	}
	goto tr160;
st72:
	if ( ++p == pe )
		goto _test_eof72;
case 72:
	switch( (*p) ) {
		case 69: goto st64;
		case 101: goto st73;
	}
	goto tr32;
st73:
	if ( ++p == pe )
		goto _test_eof73;
case 73:
	switch( (*p) ) {
		case 32: goto st74;
		case 62: goto tr64;
	}
	goto tr32;
st74:
	if ( ++p == pe )
		goto _test_eof74;
case 74:
	if ( (*p) == 108 )
		goto st75;
	goto tr32;
st75:
	if ( ++p == pe )
		goto _test_eof75;
case 75:
	if ( (*p) == 97 )
		goto st76;
	goto tr32;
st76:
	if ( ++p == pe )
		goto _test_eof76;
case 76:
	if ( (*p) == 110 )
		goto st77;
	goto tr32;
st77:
	if ( ++p == pe )
		goto _test_eof77;
case 77:
	if ( (*p) == 103 )
		goto st78;
	goto tr32;
st78:
	if ( ++p == pe )
		goto _test_eof78;
case 78:
	if ( (*p) == 61 )
		goto st79;
	goto tr32;
st79:
	if ( ++p == pe )
		goto _test_eof79;
case 79:
	if ( (*p) == 34 )
		goto st80;
	goto tr32;
st80:
	if ( ++p == pe )
		goto _test_eof80;
case 80:
	if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st81;
	} else if ( (*p) >= 65 )
		goto st81;
	goto tr32;
st81:
	if ( ++p == pe )
		goto _test_eof81;
case 81:
	if ( (*p) == 34 )
		goto st64;
	if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st81;
	} else if ( (*p) >= 65 )
		goto st81;
	goto tr32;
tr159:
#line 1 "NONE"
	{te = p+1;}
	goto st128;
st128:
	if ( ++p == pe )
		goto _test_eof128;
case 128:
#line 2760 "wikitext_ragel.c"
	switch( (*p) ) {
		case 69: goto st66;
		case 101: goto st82;
	}
	goto tr160;
st82:
	if ( ++p == pe )
		goto _test_eof82;
case 82:
	switch( (*p) ) {
		case 70: goto st64;
		case 102: goto st83;
	}
	goto tr32;
st83:
	if ( ++p == pe )
		goto _test_eof83;
case 83:
	switch( (*p) ) {
		case 32: goto st84;
		case 62: goto tr64;
	}
	goto tr32;
st84:
	if ( ++p == pe )
		goto _test_eof84;
case 84:
	if ( (*p) == 62 )
		goto tr32;
	goto st85;
st85:
	if ( ++p == pe )
		goto _test_eof85;
case 85:
	if ( (*p) == 62 )
		goto tr64;
	goto st85;
tr111:
#line 59 "wikitext_ragel.rl"
	{
        MARK();
    }
	goto st129;
st129:
	if ( ++p == pe )
		goto _test_eof129;
case 129:
#line 2808 "wikitext_ragel.c"
	switch( (*p) ) {
		case 32: goto st130;
		case 61: goto tr111;
	}
	goto tr174;
st130:
	if ( ++p == pe )
		goto _test_eof130;
case 130:
	if ( (*p) == 32 )
		goto st130;
	goto tr174;
st131:
	if ( ++p == pe )
		goto _test_eof131;
case 131:
	if ( (*p) == 62 )
		goto st131;
	goto tr176;
tr114:
#line 1 "NONE"
	{te = p+1;}
#line 827 "wikitext_ragel.rl"
	{act = 29;}
	goto st132;
st132:
	if ( ++p == pe )
		goto _test_eof132;
case 132:
#line 2838 "wikitext_ragel.c"
	switch( (*p) ) {
		case 64: goto st21;
		case 84: goto tr177;
		case 95: goto st20;
		case 116: goto tr177;
	}
	if ( (*p) < 45 ) {
		if ( (*p) < -32 ) {
			if ( -62 <= (*p) && (*p) <= -33 )
				goto st1;
		} else if ( (*p) > -17 ) {
			if ( -16 <= (*p) && (*p) <= -12 )
				goto st4;
		} else
			goto st2;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr113;
		} else if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr113;
		} else
			goto tr113;
	} else
		goto st20;
	goto tr124;
tr177:
#line 1 "NONE"
	{te = p+1;}
#line 827 "wikitext_ragel.rl"
	{act = 29;}
	goto st133;
st133:
	if ( ++p == pe )
		goto _test_eof133;
case 133:
#line 2876 "wikitext_ragel.c"
	switch( (*p) ) {
		case 64: goto st21;
		case 80: goto tr178;
		case 95: goto st20;
		case 112: goto tr178;
	}
	if ( (*p) < 45 ) {
		if ( (*p) < -32 ) {
			if ( -62 <= (*p) && (*p) <= -33 )
				goto st1;
		} else if ( (*p) > -17 ) {
			if ( -16 <= (*p) && (*p) <= -12 )
				goto st4;
		} else
			goto st2;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr113;
		} else if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr113;
		} else
			goto tr113;
	} else
		goto st20;
	goto tr124;
tr178:
#line 1 "NONE"
	{te = p+1;}
#line 827 "wikitext_ragel.rl"
	{act = 29;}
	goto st134;
st134:
	if ( ++p == pe )
		goto _test_eof134;
case 134:
#line 2914 "wikitext_ragel.c"
	switch( (*p) ) {
		case 58: goto st86;
		case 64: goto st21;
		case 95: goto st20;
	}
	if ( (*p) < 45 ) {
		if ( (*p) < -32 ) {
			if ( -62 <= (*p) && (*p) <= -33 )
				goto st1;
		} else if ( (*p) > -17 ) {
			if ( -16 <= (*p) && (*p) <= -12 )
				goto st4;
		} else
			goto st2;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr113;
		} else if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr113;
		} else
			goto tr113;
	} else
		goto st20;
	goto tr124;
st86:
	if ( ++p == pe )
		goto _test_eof86;
case 86:
	if ( (*p) == 47 )
		goto st87;
	goto tr82;
st87:
	if ( ++p == pe )
		goto _test_eof87;
case 87:
	if ( (*p) == 47 )
		goto st88;
	goto tr82;
st88:
	if ( ++p == pe )
		goto _test_eof88;
case 88:
	switch( (*p) ) {
		case 45: goto tr85;
		case 61: goto tr85;
		case 95: goto tr85;
		case 126: goto tr85;
	}
	if ( (*p) < 47 ) {
		if ( (*p) > 40 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr85;
		} else if ( (*p) >= 35 )
			goto tr85;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr85;
		} else if ( (*p) >= 64 )
			goto tr85;
	} else
		goto tr85;
	goto tr0;
tr85:
#line 1 "NONE"
	{te = p+1;}
#line 106 "wikitext_ragel.rl"
	{act = 1;}
	goto st135;
st135:
	if ( ++p == pe )
		goto _test_eof135;
case 135:
#line 2990 "wikitext_ragel.c"
	switch( (*p) ) {
		case 92: goto st88;
		case 126: goto st88;
	}
	if ( (*p) < 58 ) {
		if ( 33 <= (*p) && (*p) <= 47 )
			goto st88;
	} else if ( (*p) > 64 ) {
		if ( 94 <= (*p) && (*p) <= 96 )
			goto st88;
	} else
		goto st88;
	goto tr140;
tr115:
#line 1 "NONE"
	{te = p+1;}
#line 827 "wikitext_ragel.rl"
	{act = 29;}
	goto st136;
st136:
	if ( ++p == pe )
		goto _test_eof136;
case 136:
#line 3014 "wikitext_ragel.c"
	switch( (*p) ) {
		case 64: goto st21;
		case 84: goto tr180;
		case 95: goto st20;
		case 116: goto tr180;
	}
	if ( (*p) < 45 ) {
		if ( (*p) < -32 ) {
			if ( -62 <= (*p) && (*p) <= -33 )
				goto st1;
		} else if ( (*p) > -17 ) {
			if ( -16 <= (*p) && (*p) <= -12 )
				goto st4;
		} else
			goto st2;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr113;
		} else if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr113;
		} else
			goto tr113;
	} else
		goto st20;
	goto tr124;
tr180:
#line 1 "NONE"
	{te = p+1;}
#line 827 "wikitext_ragel.rl"
	{act = 29;}
	goto st137;
st137:
	if ( ++p == pe )
		goto _test_eof137;
case 137:
#line 3052 "wikitext_ragel.c"
	switch( (*p) ) {
		case 64: goto st21;
		case 84: goto tr181;
		case 95: goto st20;
		case 116: goto tr181;
	}
	if ( (*p) < 45 ) {
		if ( (*p) < -32 ) {
			if ( -62 <= (*p) && (*p) <= -33 )
				goto st1;
		} else if ( (*p) > -17 ) {
			if ( -16 <= (*p) && (*p) <= -12 )
				goto st4;
		} else
			goto st2;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr113;
		} else if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr113;
		} else
			goto tr113;
	} else
		goto st20;
	goto tr124;
tr181:
#line 1 "NONE"
	{te = p+1;}
#line 827 "wikitext_ragel.rl"
	{act = 29;}
	goto st138;
st138:
	if ( ++p == pe )
		goto _test_eof138;
case 138:
#line 3090 "wikitext_ragel.c"
	switch( (*p) ) {
		case 64: goto st21;
		case 80: goto tr182;
		case 95: goto st20;
		case 112: goto tr182;
	}
	if ( (*p) < 45 ) {
		if ( (*p) < -32 ) {
			if ( -62 <= (*p) && (*p) <= -33 )
				goto st1;
		} else if ( (*p) > -17 ) {
			if ( -16 <= (*p) && (*p) <= -12 )
				goto st4;
		} else
			goto st2;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr113;
		} else if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr113;
		} else
			goto tr113;
	} else
		goto st20;
	goto tr124;
tr182:
#line 1 "NONE"
	{te = p+1;}
#line 827 "wikitext_ragel.rl"
	{act = 29;}
	goto st139;
st139:
	if ( ++p == pe )
		goto _test_eof139;
case 139:
#line 3128 "wikitext_ragel.c"
	switch( (*p) ) {
		case 58: goto st86;
		case 64: goto st21;
		case 83: goto tr178;
		case 95: goto st20;
		case 115: goto tr178;
	}
	if ( (*p) < 45 ) {
		if ( (*p) < -32 ) {
			if ( -62 <= (*p) && (*p) <= -33 )
				goto st1;
		} else if ( (*p) > -17 ) {
			if ( -16 <= (*p) && (*p) <= -12 )
				goto st4;
		} else
			goto st2;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr113;
		} else if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr113;
		} else
			goto tr113;
	} else
		goto st20;
	goto tr124;
tr116:
#line 1 "NONE"
	{te = p+1;}
#line 827 "wikitext_ragel.rl"
	{act = 29;}
	goto st140;
st140:
	if ( ++p == pe )
		goto _test_eof140;
case 140:
#line 3167 "wikitext_ragel.c"
	switch( (*p) ) {
		case 64: goto st21;
		case 65: goto tr183;
		case 95: goto st20;
		case 97: goto tr183;
	}
	if ( (*p) < 45 ) {
		if ( (*p) < -32 ) {
			if ( -62 <= (*p) && (*p) <= -33 )
				goto st1;
		} else if ( (*p) > -17 ) {
			if ( -16 <= (*p) && (*p) <= -12 )
				goto st4;
		} else
			goto st2;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 66 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr113;
		} else if ( (*p) > 90 ) {
			if ( 98 <= (*p) && (*p) <= 122 )
				goto tr113;
		} else
			goto tr113;
	} else
		goto st20;
	goto tr124;
tr183:
#line 1 "NONE"
	{te = p+1;}
#line 827 "wikitext_ragel.rl"
	{act = 29;}
	goto st141;
st141:
	if ( ++p == pe )
		goto _test_eof141;
case 141:
#line 3205 "wikitext_ragel.c"
	switch( (*p) ) {
		case 64: goto st21;
		case 73: goto tr184;
		case 95: goto st20;
		case 105: goto tr184;
	}
	if ( (*p) < 45 ) {
		if ( (*p) < -32 ) {
			if ( -62 <= (*p) && (*p) <= -33 )
				goto st1;
		} else if ( (*p) > -17 ) {
			if ( -16 <= (*p) && (*p) <= -12 )
				goto st4;
		} else
			goto st2;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr113;
		} else if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr113;
		} else
			goto tr113;
	} else
		goto st20;
	goto tr124;
tr184:
#line 1 "NONE"
	{te = p+1;}
#line 827 "wikitext_ragel.rl"
	{act = 29;}
	goto st142;
st142:
	if ( ++p == pe )
		goto _test_eof142;
case 142:
#line 3243 "wikitext_ragel.c"
	switch( (*p) ) {
		case 64: goto st21;
		case 76: goto tr185;
		case 95: goto st20;
		case 108: goto tr185;
	}
	if ( (*p) < 45 ) {
		if ( (*p) < -32 ) {
			if ( -62 <= (*p) && (*p) <= -33 )
				goto st1;
		} else if ( (*p) > -17 ) {
			if ( -16 <= (*p) && (*p) <= -12 )
				goto st4;
		} else
			goto st2;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr113;
		} else if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr113;
		} else
			goto tr113;
	} else
		goto st20;
	goto tr124;
tr185:
#line 1 "NONE"
	{te = p+1;}
#line 827 "wikitext_ragel.rl"
	{act = 29;}
	goto st143;
st143:
	if ( ++p == pe )
		goto _test_eof143;
case 143:
#line 3281 "wikitext_ragel.c"
	switch( (*p) ) {
		case 64: goto st21;
		case 84: goto tr186;
		case 95: goto st20;
		case 116: goto tr186;
	}
	if ( (*p) < 45 ) {
		if ( (*p) < -32 ) {
			if ( -62 <= (*p) && (*p) <= -33 )
				goto st1;
		} else if ( (*p) > -17 ) {
			if ( -16 <= (*p) && (*p) <= -12 )
				goto st4;
		} else
			goto st2;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr113;
		} else if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr113;
		} else
			goto tr113;
	} else
		goto st20;
	goto tr124;
tr186:
#line 1 "NONE"
	{te = p+1;}
#line 827 "wikitext_ragel.rl"
	{act = 29;}
	goto st144;
st144:
	if ( ++p == pe )
		goto _test_eof144;
case 144:
#line 3319 "wikitext_ragel.c"
	switch( (*p) ) {
		case 64: goto st21;
		case 79: goto tr187;
		case 95: goto st20;
		case 111: goto tr187;
	}
	if ( (*p) < 45 ) {
		if ( (*p) < -32 ) {
			if ( -62 <= (*p) && (*p) <= -33 )
				goto st1;
		} else if ( (*p) > -17 ) {
			if ( -16 <= (*p) && (*p) <= -12 )
				goto st4;
		} else
			goto st2;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr113;
		} else if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr113;
		} else
			goto tr113;
	} else
		goto st20;
	goto tr124;
tr187:
#line 1 "NONE"
	{te = p+1;}
#line 827 "wikitext_ragel.rl"
	{act = 29;}
	goto st145;
st145:
	if ( ++p == pe )
		goto _test_eof145;
case 145:
#line 3357 "wikitext_ragel.c"
	switch( (*p) ) {
		case 58: goto st89;
		case 64: goto st21;
		case 95: goto st20;
	}
	if ( (*p) < 45 ) {
		if ( (*p) < -32 ) {
			if ( -62 <= (*p) && (*p) <= -33 )
				goto st1;
		} else if ( (*p) > -17 ) {
			if ( -16 <= (*p) && (*p) <= -12 )
				goto st4;
		} else
			goto st2;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr113;
		} else if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr113;
		} else
			goto tr113;
	} else
		goto st20;
	goto tr124;
st89:
	if ( ++p == pe )
		goto _test_eof89;
case 89:
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
	goto tr82;
tr117:
#line 1 "NONE"
	{te = p+1;}
#line 827 "wikitext_ragel.rl"
	{act = 29;}
	goto st146;
st146:
	if ( ++p == pe )
		goto _test_eof146;
case 146:
#line 3412 "wikitext_ragel.c"
	switch( (*p) ) {
		case 64: goto st21;
		case 86: goto tr189;
		case 95: goto st20;
		case 118: goto tr189;
	}
	if ( (*p) < 45 ) {
		if ( (*p) < -32 ) {
			if ( -62 <= (*p) && (*p) <= -33 )
				goto st1;
		} else if ( (*p) > -17 ) {
			if ( -16 <= (*p) && (*p) <= -12 )
				goto st4;
		} else
			goto st2;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr113;
		} else if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr113;
		} else
			goto tr113;
	} else
		goto st20;
	goto tr124;
tr189:
#line 1 "NONE"
	{te = p+1;}
#line 827 "wikitext_ragel.rl"
	{act = 29;}
	goto st147;
st147:
	if ( ++p == pe )
		goto _test_eof147;
case 147:
#line 3450 "wikitext_ragel.c"
	switch( (*p) ) {
		case 64: goto st21;
		case 78: goto tr178;
		case 95: goto st20;
		case 110: goto tr178;
	}
	if ( (*p) < 45 ) {
		if ( (*p) < -32 ) {
			if ( -62 <= (*p) && (*p) <= -33 )
				goto st1;
		} else if ( (*p) > -17 ) {
			if ( -16 <= (*p) && (*p) <= -12 )
				goto st4;
		} else
			goto st2;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr113;
		} else if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr113;
		} else
			goto tr113;
	} else
		goto st20;
	goto tr124;
st148:
	if ( ++p == pe )
		goto _test_eof148;
case 148:
	if ( (*p) == 91 )
		goto tr191;
	goto tr190;
tr191:
#line 1 "NONE"
	{te = p+1;}
	goto st149;
st149:
	if ( ++p == pe )
		goto _test_eof149;
case 149:
#line 3493 "wikitext_ragel.c"
	switch( (*p) ) {
		case 45: goto st90;
		case 58: goto tr88;
	}
	if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st90;
	} else if ( (*p) >= 65 )
		goto st90;
	goto tr192;
st90:
	if ( ++p == pe )
		goto _test_eof90;
case 90:
	switch( (*p) ) {
		case 45: goto st90;
		case 58: goto tr88;
	}
	if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st90;
	} else if ( (*p) >= 65 )
		goto st90;
	goto tr86;
st150:
	if ( ++p == pe )
		goto _test_eof150;
case 150:
	if ( (*p) == 93 )
		goto tr194;
	goto tr193;
tr120:
#line 1 "NONE"
	{te = p+1;}
#line 771 "wikitext_ragel.rl"
	{act = 27;}
	goto st151;
st151:
	if ( ++p == pe )
		goto _test_eof151;
case 151:
#line 3535 "wikitext_ragel.c"
	switch( (*p) ) {
		case 64: goto st21;
		case 95: goto st91;
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
	goto tr131;
st91:
	if ( ++p == pe )
		goto _test_eof91;
case 91:
	switch( (*p) ) {
		case 64: goto st21;
		case 78: goto st92;
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
	goto tr7;
st92:
	if ( ++p == pe )
		goto _test_eof92;
case 92:
	switch( (*p) ) {
		case 64: goto st21;
		case 79: goto st93;
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
	goto tr7;
st93:
	if ( ++p == pe )
		goto _test_eof93;
case 93:
	switch( (*p) ) {
		case 64: goto st21;
		case 84: goto st94;
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
	goto tr7;
st94:
	if ( ++p == pe )
		goto _test_eof94;
case 94:
	switch( (*p) ) {
		case 64: goto st21;
		case 79: goto st95;
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
	goto tr7;
st95:
	if ( ++p == pe )
		goto _test_eof95;
case 95:
	switch( (*p) ) {
		case 64: goto st21;
		case 67: goto st96;
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
	goto tr7;
st96:
	if ( ++p == pe )
		goto _test_eof96;
case 96:
	switch( (*p) ) {
		case 64: goto st21;
		case 95: goto st97;
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
	goto tr7;
st97:
	if ( ++p == pe )
		goto _test_eof97;
case 97:
	switch( (*p) ) {
		case 64: goto st21;
		case 95: goto tr95;
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
	goto tr7;
st152:
	if ( ++p == pe )
		goto _test_eof152;
case 152:
	switch( (*p) ) {
		case 123: goto tr196;
		case 124: goto tr197;
	}
	goto tr131;
st153:
	if ( ++p == pe )
		goto _test_eof153;
case 153:
	if ( (*p) == 125 )
		goto tr199;
	goto tr198;
tr123:
#line 1 "NONE"
	{te = p+1;}
#line 771 "wikitext_ragel.rl"
	{act = 27;}
	goto st154;
tr199:
#line 1 "NONE"
	{te = p+1;}
#line 492 "wikitext_ragel.rl"
	{act = 13;}
	goto st154;
st154:
	if ( ++p == pe )
		goto _test_eof154;
case 154:
#line 3729 "wikitext_ragel.c"
	if ( (*p) == 125 )
		goto tr200;
	goto tr0;
	}
	_test_eof98: cs = 98; goto _test_eof; 
	_test_eof1: cs = 1; goto _test_eof; 
	_test_eof99: cs = 99; goto _test_eof; 
	_test_eof2: cs = 2; goto _test_eof; 
	_test_eof3: cs = 3; goto _test_eof; 
	_test_eof4: cs = 4; goto _test_eof; 
	_test_eof5: cs = 5; goto _test_eof; 
	_test_eof6: cs = 6; goto _test_eof; 
	_test_eof100: cs = 100; goto _test_eof; 
	_test_eof101: cs = 101; goto _test_eof; 
	_test_eof102: cs = 102; goto _test_eof; 
	_test_eof103: cs = 103; goto _test_eof; 
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
	_test_eof104: cs = 104; goto _test_eof; 
	_test_eof105: cs = 105; goto _test_eof; 
	_test_eof106: cs = 106; goto _test_eof; 
	_test_eof107: cs = 107; goto _test_eof; 
	_test_eof108: cs = 108; goto _test_eof; 
	_test_eof20: cs = 20; goto _test_eof; 
	_test_eof21: cs = 21; goto _test_eof; 
	_test_eof22: cs = 22; goto _test_eof; 
	_test_eof23: cs = 23; goto _test_eof; 
	_test_eof24: cs = 24; goto _test_eof; 
	_test_eof109: cs = 109; goto _test_eof; 
	_test_eof110: cs = 110; goto _test_eof; 
	_test_eof111: cs = 111; goto _test_eof; 
	_test_eof112: cs = 112; goto _test_eof; 
	_test_eof113: cs = 113; goto _test_eof; 
	_test_eof25: cs = 25; goto _test_eof; 
	_test_eof114: cs = 114; goto _test_eof; 
	_test_eof26: cs = 26; goto _test_eof; 
	_test_eof115: cs = 115; goto _test_eof; 
	_test_eof116: cs = 116; goto _test_eof; 
	_test_eof117: cs = 117; goto _test_eof; 
	_test_eof118: cs = 118; goto _test_eof; 
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
	_test_eof60: cs = 60; goto _test_eof; 
	_test_eof61: cs = 61; goto _test_eof; 
	_test_eof119: cs = 119; goto _test_eof; 
	_test_eof120: cs = 120; goto _test_eof; 
	_test_eof121: cs = 121; goto _test_eof; 
	_test_eof62: cs = 62; goto _test_eof; 
	_test_eof63: cs = 63; goto _test_eof; 
	_test_eof64: cs = 64; goto _test_eof; 
	_test_eof122: cs = 122; goto _test_eof; 
	_test_eof123: cs = 123; goto _test_eof; 
	_test_eof65: cs = 65; goto _test_eof; 
	_test_eof124: cs = 124; goto _test_eof; 
	_test_eof66: cs = 66; goto _test_eof; 
	_test_eof125: cs = 125; goto _test_eof; 
	_test_eof126: cs = 126; goto _test_eof; 
	_test_eof67: cs = 67; goto _test_eof; 
	_test_eof68: cs = 68; goto _test_eof; 
	_test_eof69: cs = 69; goto _test_eof; 
	_test_eof70: cs = 70; goto _test_eof; 
	_test_eof71: cs = 71; goto _test_eof; 
	_test_eof127: cs = 127; goto _test_eof; 
	_test_eof72: cs = 72; goto _test_eof; 
	_test_eof73: cs = 73; goto _test_eof; 
	_test_eof74: cs = 74; goto _test_eof; 
	_test_eof75: cs = 75; goto _test_eof; 
	_test_eof76: cs = 76; goto _test_eof; 
	_test_eof77: cs = 77; goto _test_eof; 
	_test_eof78: cs = 78; goto _test_eof; 
	_test_eof79: cs = 79; goto _test_eof; 
	_test_eof80: cs = 80; goto _test_eof; 
	_test_eof81: cs = 81; goto _test_eof; 
	_test_eof128: cs = 128; goto _test_eof; 
	_test_eof82: cs = 82; goto _test_eof; 
	_test_eof83: cs = 83; goto _test_eof; 
	_test_eof84: cs = 84; goto _test_eof; 
	_test_eof85: cs = 85; goto _test_eof; 
	_test_eof129: cs = 129; goto _test_eof; 
	_test_eof130: cs = 130; goto _test_eof; 
	_test_eof131: cs = 131; goto _test_eof; 
	_test_eof132: cs = 132; goto _test_eof; 
	_test_eof133: cs = 133; goto _test_eof; 
	_test_eof134: cs = 134; goto _test_eof; 
	_test_eof86: cs = 86; goto _test_eof; 
	_test_eof87: cs = 87; goto _test_eof; 
	_test_eof88: cs = 88; goto _test_eof; 
	_test_eof135: cs = 135; goto _test_eof; 
	_test_eof136: cs = 136; goto _test_eof; 
	_test_eof137: cs = 137; goto _test_eof; 
	_test_eof138: cs = 138; goto _test_eof; 
	_test_eof139: cs = 139; goto _test_eof; 
	_test_eof140: cs = 140; goto _test_eof; 
	_test_eof141: cs = 141; goto _test_eof; 
	_test_eof142: cs = 142; goto _test_eof; 
	_test_eof143: cs = 143; goto _test_eof; 
	_test_eof144: cs = 144; goto _test_eof; 
	_test_eof145: cs = 145; goto _test_eof; 
	_test_eof89: cs = 89; goto _test_eof; 
	_test_eof146: cs = 146; goto _test_eof; 
	_test_eof147: cs = 147; goto _test_eof; 
	_test_eof148: cs = 148; goto _test_eof; 
	_test_eof149: cs = 149; goto _test_eof; 
	_test_eof90: cs = 90; goto _test_eof; 
	_test_eof150: cs = 150; goto _test_eof; 
	_test_eof151: cs = 151; goto _test_eof; 
	_test_eof91: cs = 91; goto _test_eof; 
	_test_eof92: cs = 92; goto _test_eof; 
	_test_eof93: cs = 93; goto _test_eof; 
	_test_eof94: cs = 94; goto _test_eof; 
	_test_eof95: cs = 95; goto _test_eof; 
	_test_eof96: cs = 96; goto _test_eof; 
	_test_eof97: cs = 97; goto _test_eof; 
	_test_eof152: cs = 152; goto _test_eof; 
	_test_eof153: cs = 153; goto _test_eof; 
	_test_eof154: cs = 154; goto _test_eof; 

	_test_eof: {}
	if ( p == eof )
	{
	switch ( cs ) {
	case 1: goto tr0;
	case 99: goto tr124;
	case 2: goto tr0;
	case 3: goto tr0;
	case 4: goto tr0;
	case 5: goto tr0;
	case 6: goto tr0;
	case 100: goto tr126;
	case 101: goto tr128;
	case 102: goto tr130;
	case 103: goto tr131;
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
	case 104: goto tr135;
	case 105: goto tr135;
	case 106: goto tr135;
	case 107: goto tr135;
	case 108: goto tr0;
	case 20: goto tr0;
	case 21: goto tr0;
	case 22: goto tr0;
	case 23: goto tr0;
	case 24: goto tr0;
	case 109: goto tr140;
	case 110: goto tr140;
	case 111: goto tr140;
	case 112: goto tr140;
	case 113: goto tr144;
	case 25: goto tr29;
	case 114: goto tr144;
	case 26: goto tr29;
	case 115: goto tr144;
	case 116: goto tr124;
	case 117: goto tr147;
	case 118: goto tr160;
	case 27: goto tr32;
	case 28: goto tr32;
	case 29: goto tr32;
	case 30: goto tr32;
	case 31: goto tr32;
	case 32: goto tr32;
	case 33: goto tr32;
	case 34: goto tr32;
	case 35: goto tr32;
	case 36: goto tr32;
	case 37: goto tr32;
	case 38: goto tr32;
	case 39: goto tr32;
	case 40: goto tr32;
	case 41: goto tr32;
	case 42: goto tr32;
	case 43: goto tr32;
	case 44: goto tr32;
	case 45: goto tr32;
	case 46: goto tr32;
	case 47: goto tr32;
	case 48: goto tr32;
	case 49: goto tr32;
	case 50: goto tr32;
	case 51: goto tr32;
	case 52: goto tr32;
	case 53: goto tr32;
	case 54: goto tr32;
	case 55: goto tr32;
	case 56: goto tr32;
	case 57: goto tr32;
	case 58: goto tr32;
	case 59: goto tr32;
	case 60: goto tr32;
	case 61: goto tr32;
	case 119: goto tr160;
	case 120: goto tr160;
	case 121: goto tr160;
	case 62: goto tr32;
	case 63: goto tr32;
	case 64: goto tr32;
	case 122: goto tr160;
	case 123: goto tr160;
	case 65: goto tr32;
	case 124: goto tr160;
	case 66: goto tr32;
	case 125: goto tr160;
	case 126: goto tr160;
	case 67: goto tr32;
	case 68: goto tr32;
	case 69: goto tr32;
	case 70: goto tr32;
	case 71: goto tr32;
	case 127: goto tr160;
	case 72: goto tr32;
	case 73: goto tr32;
	case 74: goto tr32;
	case 75: goto tr32;
	case 76: goto tr32;
	case 77: goto tr32;
	case 78: goto tr32;
	case 79: goto tr32;
	case 80: goto tr32;
	case 81: goto tr32;
	case 128: goto tr160;
	case 82: goto tr32;
	case 83: goto tr32;
	case 84: goto tr32;
	case 85: goto tr32;
	case 129: goto tr174;
	case 130: goto tr174;
	case 131: goto tr176;
	case 132: goto tr124;
	case 133: goto tr124;
	case 134: goto tr124;
	case 86: goto tr82;
	case 87: goto tr82;
	case 88: goto tr0;
	case 135: goto tr140;
	case 136: goto tr124;
	case 137: goto tr124;
	case 138: goto tr124;
	case 139: goto tr124;
	case 140: goto tr124;
	case 141: goto tr124;
	case 142: goto tr124;
	case 143: goto tr124;
	case 144: goto tr124;
	case 145: goto tr124;
	case 89: goto tr82;
	case 146: goto tr124;
	case 147: goto tr124;
	case 148: goto tr190;
	case 149: goto tr192;
	case 90: goto tr86;
	case 150: goto tr193;
	case 151: goto tr131;
	case 91: goto tr7;
	case 92: goto tr7;
	case 93: goto tr7;
	case 94: goto tr7;
	case 95: goto tr7;
	case 96: goto tr7;
	case 97: goto tr7;
	case 152: goto tr131;
	case 153: goto tr198;
	case 154: goto tr0;
	}
	}

	_out: {}
	}

#line 907 "wikitext_ragel.rl"
    if (cs == wikitext_error)
        rb_raise(eWikitextParserError, "failed before finding a token");
    else if (out->type == NO_TOKEN){
        out->stop = p;
        out->type = END_OF_FILE;
        //rb_raise(eWikitextParserError, "failed to produce a token");
    }
}
