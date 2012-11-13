
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


#line 45 "wikitext_ragel.c"
static const int wikitext_start = 126;
static const int wikitext_first_final = 126;
static const int wikitext_error = 0;

static const int wikitext_en_main = 126;


#line 591 "wikitext_ragel.rl"


// for now we use the scanner as a tokenizer that returns one token at a time, just like ANTLR
// ultimately we could look at embedding all of the transformation inside the scanner itself (combined scanner/parser)
// pass in the last token because that's useful for the scanner to know
// p data pointer (required by Ragel machine); overriden with contents of last_token if supplied
// pe data end pointer (required by Ragel machine)
void next_token(token_t *out, token_t *last_token, char *p, char *pe)
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
    
#line 96 "wikitext_ragel.c"
	{
	cs = wikitext_start;
	ts = 0;
	te = 0;
	act = 0;
	}

#line 633 "wikitext_ragel.rl"
    
#line 106 "wikitext_ragel.c"
	{
	if ( p == pe )
		goto _test_eof;
	switch ( cs )
	{
tr0:
#line 55 "wikitext_ragel.rl"
	{
        out->code_point = ((uint32_t)(*(p - 1)) & 0x1f) << 6 |
            (*p & 0x3f);
    }
#line 582 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(DEFAULT);
            out->column_stop = out->column_start + 1;
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr3:
#line 61 "wikitext_ragel.rl"
	{
        out->code_point = ((uint32_t)(*(p - 2)) & 0x0f) << 12 |
            ((uint32_t)(*(p - 1)) & 0x3f) << 6 |
            (*p & 0x3f);
    }
#line 582 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(DEFAULT);
            out->column_stop = out->column_start + 1;
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr6:
#line 68 "wikitext_ragel.rl"
	{
        out->code_point = ((uint32_t)(*(p - 3)) & 0x07) << 18 |
            ((uint32_t)(*(p - 2)) & 0x3f) << 12 |
            ((uint32_t)(*(p - 1)) & 0x3f) << 6 |
            (*p & 0x3f);
    }
#line 582 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(DEFAULT);
            out->column_stop = out->column_start + 1;
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr7:
#line 471 "wikitext_ragel.rl"
	{{p = ((te))-1;}{
            EMIT(AMP);
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr10:
#line 459 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(DECIMAL_ENTITY);
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr12:
#line 453 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(HEX_ENTITY);
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr14:
#line 447 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(NAMED_ENTITY);
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr18:
#line 441 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(AMP_ENTITY);
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr22:
#line 435 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(QUOT_ENTITY);
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr23:
#line 1 "NONE"
	{	switch( act ) {
	case 27:
	{{p = ((te))-1;}
            EMIT(URI);
            {p++; cs = 126; goto _out;}
        }
	break;
	case 28:
	{{p = ((te))-1;}
            EMIT(MAIL);
            {p++; cs = 126; goto _out;}
        }
	break;
	case 30:
	{{p = ((te))-1;}
            EMIT(URI);
            {p++; cs = 126; goto _out;}
        }
	break;
	case 57:
	{{p = ((te))-1;}
            EMIT(SPECIAL_URI_CHARS);
            {p++; cs = 126; goto _out;}
        }
	break;
	case 58:
	{{p = ((te))-1;}
            EMIT(ALNUM);
            {p++; cs = 126; goto _out;}
        }
	break;
	case 59:
	{{p = ((te))-1;}
            EMIT(PRINTABLE);
            {p++; cs = 126; goto _out;}
        }
	break;
	}
	}
	goto st126;
tr30:
#line 483 "wikitext_ragel.rl"
	{{p = ((te))-1;}{
            EMIT(TAG_START);
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr40:
#line 126 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(BLOCKQUOTE_END);
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr42:
#line 193 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(EM_END);
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr46:
#line 138 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(MATH_END);
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr52:
#line 96 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(NO_WIKI_END);
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr55:
#line 114 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(PRE_END);
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr61:
#line 181 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(STRONG_END);
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr70:
#line 150 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(MATH_END);
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr71:
#line 211 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(TT_END);
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr72:
#line 477 "wikitext_ragel.rl"
	{{p = ((te))-1;}{
            EMIT(TAG_START);
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr81:
#line 120 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(BLOCKQUOTE_START);
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr82:
#line 187 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(EM_START);
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr85:
#line 132 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(MATH_START);
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr90:
#line 90 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(NO_WIKI_START);
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr92:
#line 102 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(PRE_START);
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr97:
#line 175 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(STRONG_START);
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr104:
#line 144 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(MATH_START);
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr105:
#line 205 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(TT_START);
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr116:
#line 108 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(PRE_START);
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr117:
#line 550 "wikitext_ragel.rl"
	{{p = ((te))-1;}{
            EMIT(ALNUM);
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr121:
#line 356 "wikitext_ragel.rl"
	{{p = ((te))-1;}{
            EMIT(URI);
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr129:
#line 386 "wikitext_ragel.rl"
	{{p = ((te))-1;}{
            EMIT(LINK_START);
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr130:
#line 380 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(SPECIAL_LINK_START);
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr132:
#line 562 "wikitext_ragel.rl"
	{{p = ((te))-1;}{
            EMIT(PRINTABLE);
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr142:
#line 50 "wikitext_ragel.rl"
	{
        out->code_point = *p & 0x7f;
    }
#line 582 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(DEFAULT);
            out->column_stop = out->column_start + 1;
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr143:
#line 531 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(CRLF);
            out->column_stop = 1;
            out->line_stop++;
            {p++; cs = 126; goto _out;}
        }}
#line 50 "wikitext_ragel.rl"
	{
        out->code_point = *p & 0x7f;
    }
	goto st126;
tr147:
#line 465 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(QUOT);
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr148:
#line 243 "wikitext_ragel.rl"
	{te = p+1;{
            if (out->column_start == 1              ||
                last_token_type == OL               ||
                last_token_type == UL               ||
                last_token_type == SL               ||
                last_token_type == CL               ||
                last_token_type == BLOCKQUOTE       ||
                last_token_type == BLOCKQUOTE_START)
                EMIT(OL);
            else
                EMIT(PRINTABLE);
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr152:
#line 258 "wikitext_ragel.rl"
	{te = p+1;{
            if (out->column_start == 1              ||
                last_token_type == OL               ||
                last_token_type == UL               ||
                last_token_type == SL               ||
                last_token_type == CL               ||
                last_token_type == BLOCKQUOTE       ||
                last_token_type == BLOCKQUOTE_START)
                EMIT(UL);
            else
                EMIT(PRINTABLE);
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr157:
#line 288 "wikitext_ragel.rl"
	{te = p+1;{
            if (out->column_start == 1              ||
                last_token_type == OL               ||
                last_token_type == UL               ||
                last_token_type == SL               ||
                last_token_type == CL               ||
                last_token_type == BLOCKQUOTE       ||
                last_token_type == BLOCKQUOTE_START)
                EMIT(CL);
            else
                EMIT(PRINTABLE);
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr158:
#line 273 "wikitext_ragel.rl"
	{te = p+1;{
            if (out->column_start == 1              ||
                last_token_type == OL               ||
                last_token_type == UL               ||
                last_token_type == SL               ||
                last_token_type == CL               ||
                last_token_type == BLOCKQUOTE       ||
                last_token_type == BLOCKQUOTE_START)
                EMIT(SL);
            else
                EMIT(PRINTABLE);
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr169:
#line 199 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(TT);
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr173:
#line 531 "wikitext_ragel.rl"
	{te = p;p--;{
            EMIT(CRLF);
            out->column_stop = 1;
            out->line_stop++;
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr174:
#line 531 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(CRLF);
            out->column_stop = 1;
            out->line_stop++;
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr175:
#line 231 "wikitext_ragel.rl"
	{te = p;p--;{
            if (out->column_start == 1 || last_token_type == BLOCKQUOTE)
            {
                REWIND();
                EMIT(PRE);
            }
            else
                EMIT(SPACE);
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr177:
#line 544 "wikitext_ragel.rl"
	{te = p;p--;{
            EMIT(SPECIAL_URI_CHARS);
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr178:
#line 562 "wikitext_ragel.rl"
	{te = p;p--;{
            EMIT(PRINTABLE);
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr179:
#line 471 "wikitext_ragel.rl"
	{te = p;p--;{
            EMIT(AMP);
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr183:
#line 157 "wikitext_ragel.rl"
	{te = p;p--;{
            if (DISTANCE() == 5)
                EMIT(STRONG_EM);
            else if (DISTANCE() == 4)
            {
                p--;
                EMIT(STRONG_EM);
            }
            else if (DISTANCE() == 3)
                EMIT(STRONG);
            else if (DISTANCE() == 2)
                EMIT(EM);
            else
                EMIT(PRINTABLE);
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr187:
#line 157 "wikitext_ragel.rl"
	{te = p+1;{
            if (DISTANCE() == 5)
                EMIT(STRONG_EM);
            else if (DISTANCE() == 4)
            {
                p--;
                EMIT(STRONG_EM);
            }
            else if (DISTANCE() == 3)
                EMIT(STRONG);
            else if (DISTANCE() == 2)
                EMIT(EM);
            else
                EMIT(PRINTABLE);
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr189:
#line 362 "wikitext_ragel.rl"
	{te = p;p--;{
            EMIT(MAIL);
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr193:
#line 368 "wikitext_ragel.rl"
	{te = p;p--;{
            EMIT(PATH);
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr197:
#line 550 "wikitext_ragel.rl"
	{te = p;p--;{
            EMIT(ALNUM);
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr198:
#line 495 "wikitext_ragel.rl"
	{te = p;p--;{
            EMIT(DEFAULT);
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr199:
#line 489 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(TAG_START);
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr201:
#line 477 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(TAG_START);
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr210:
#line 483 "wikitext_ragel.rl"
	{te = p;p--;{
            EMIT(TAG_START);
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr218:
#line 477 "wikitext_ragel.rl"
	{te = p;p--;{
            EMIT(TAG_START);
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr228:
#line 303 "wikitext_ragel.rl"
	{te = p;p--;{
            if (out->column_start == 1 || last_token_type == BLOCKQUOTE || last_token_type == BLOCKQUOTE_START)
            {
                REWIND();
                if (DISTANCE() == 1)
                    EMIT(H1_START);
                else if (DISTANCE() == 2)
                    EMIT(H2_START);
                else if (DISTANCE() == 3)
                    EMIT(H3_START);
                else if (DISTANCE() == 4)
                    EMIT(H4_START);
                else if (DISTANCE() == 5)
                    EMIT(H5_START);
                else if (DISTANCE() == 6)
                    EMIT(H6_START);
                else if (DISTANCE() > 6)
                {
                    p = ts + 6;
                    EMIT(H6_START);
                }
            }
            else if (AT_END() || NEXT_CHAR() == '\n' || NEXT_CHAR() == '\r')
            {
                REWIND();
                if (DISTANCE() == 1)
                    EMIT(H1_END);
                else if (DISTANCE() == 2)
                    EMIT(H2_END);
                else if (DISTANCE() == 3)
                    EMIT(H3_END);
                else if (DISTANCE() == 4)
                    EMIT(H4_END);
                else if (DISTANCE() == 5)
                    EMIT(H5_END);
                else if (DISTANCE() == 6)
                    EMIT(H6_END);
                else if (DISTANCE() > 6)
                {
                    p -= 6; // will scan the H6 on the next scan
                    EMIT(PRINTABLE);
                }
            }
            else
            {
                // note that a H*_END token will never match before a BLOCKQUOTE_END
                REWIND();
                EMIT(PRINTABLE);
            }
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr230:
#line 218 "wikitext_ragel.rl"
	{te = p;p--;{
            if (out->column_start == 1 || last_token_type == BLOCKQUOTE)
                EMIT(BLOCKQUOTE);
            else
            {
                REWIND();
                EMIT(TAG_END);
            }
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr231:
#line 218 "wikitext_ragel.rl"
	{te = p+1;{
            if (out->column_start == 1 || last_token_type == BLOCKQUOTE)
                EMIT(BLOCKQUOTE);
            else
            {
                REWIND();
                EMIT(TAG_END);
            }
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr235:
#line 356 "wikitext_ragel.rl"
	{te = p;p--;{
            EMIT(URI);
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr249:
#line 423 "wikitext_ragel.rl"
	{te = p;p--;{
            EMIT(EXT_LINK_START);
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr251:
#line 386 "wikitext_ragel.rl"
	{te = p;p--;{
            EMIT(LINK_START);
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr252:
#line 429 "wikitext_ragel.rl"
	{te = p;p--;{
            EMIT(EXT_LINK_END);
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr253:
#line 392 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(LINK_END);
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr256:
#line 374 "wikitext_ragel.rl"
	{te = p;p--;{
            EMIT(URI);
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr257:
#line 519 "wikitext_ragel.rl"
	{te = p;p--;{
            EMIT(LEFT_CURLY);
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr258:
#line 507 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(IMG_START);
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr259:
#line 398 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(TABLE_START);
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr260:
#line 417 "wikitext_ragel.rl"
	{te = p;p--;{
            EMIT(SEPARATOR);
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr262:
#line 411 "wikitext_ragel.rl"
	{te = p;p--;{
            EMIT(TABLE_END);
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr263:
#line 404 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(IMG_END);
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr264:
#line 525 "wikitext_ragel.rl"
	{te = p;p--;{
            EMIT(RIGHT_CURLY);
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
tr265:
#line 513 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(IMG_END);
            {p++; cs = 126; goto _out;}
        }}
	goto st126;
st126:
#line 1 "NONE"
	{ts = 0;}
	if ( ++p == pe )
		goto _test_eof126;
case 126:
#line 1 "NONE"
	{ts = p;}
#line 841 "wikitext_ragel.c"
	switch( (*p) ) {
		case 10: goto tr143;
		case 13: goto tr144;
		case 32: goto tr145;
		case 33: goto st129;
		case 34: goto tr147;
		case 35: goto tr148;
		case 38: goto tr150;
		case 39: goto st132;
		case 42: goto tr152;
		case 43: goto st130;
		case 45: goto tr153;
		case 46: goto tr154;
		case 47: goto st143;
		case 58: goto tr157;
		case 59: goto tr158;
		case 60: goto st148;
		case 61: goto tr160;
		case 62: goto tr161;
		case 63: goto st129;
		case 64: goto st130;
		case 70: goto tr162;
		case 72: goto tr163;
		case 77: goto tr164;
		case 83: goto tr165;
		case 91: goto st181;
		case 92: goto st130;
		case 93: goto st183;
		case 94: goto st130;
		case 95: goto tr168;
		case 96: goto tr169;
		case 102: goto tr162;
		case 104: goto tr163;
		case 109: goto tr164;
		case 115: goto tr165;
		case 123: goto st187;
		case 124: goto st188;
		case 125: goto st190;
		case 126: goto st130;
		case 127: goto tr142;
	}
	if ( (*p) < 1 ) {
		if ( (*p) < -32 ) {
			if ( -62 <= (*p) && (*p) <= -33 )
				goto st1;
		} else if ( (*p) > -17 ) {
			if ( -16 <= (*p) && (*p) <= -12 )
				goto st4;
		} else
			goto st2;
	} else if ( (*p) > 31 ) {
		if ( (*p) < 40 ) {
			if ( 36 <= (*p) && (*p) <= 37 )
				goto st130;
		} else if ( (*p) > 44 ) {
			if ( 48 <= (*p) && (*p) <= 122 )
				goto tr156;
		} else
			goto st129;
	} else
		goto tr142;
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
tr144:
#line 50 "wikitext_ragel.rl"
	{
        out->code_point = *p & 0x7f;
    }
	goto st127;
st127:
	if ( ++p == pe )
		goto _test_eof127;
case 127:
#line 959 "wikitext_ragel.c"
	if ( (*p) == 10 )
		goto tr174;
	goto tr173;
tr145:
#line 45 "wikitext_ragel.rl"
	{
        MARK();
    }
	goto st128;
st128:
	if ( ++p == pe )
		goto _test_eof128;
case 128:
#line 973 "wikitext_ragel.c"
	if ( (*p) == 32 )
		goto st128;
	goto tr175;
st129:
	if ( ++p == pe )
		goto _test_eof129;
case 129:
	switch( (*p) ) {
		case 33: goto st129;
		case 44: goto st129;
		case 46: goto st129;
		case 63: goto st129;
	}
	if ( 40 <= (*p) && (*p) <= 41 )
		goto st129;
	goto tr177;
st130:
	if ( ++p == pe )
		goto _test_eof130;
case 130:
	switch( (*p) ) {
		case 43: goto st130;
		case 45: goto st130;
		case 47: goto st130;
		case 64: goto st130;
		case 92: goto st130;
		case 126: goto st130;
	}
	if ( (*p) > 37 ) {
		if ( 94 <= (*p) && (*p) <= 95 )
			goto st130;
	} else if ( (*p) >= 36 )
		goto st130;
	goto tr178;
tr150:
#line 1 "NONE"
	{te = p+1;}
	goto st131;
st131:
	if ( ++p == pe )
		goto _test_eof131;
case 131:
#line 1016 "wikitext_ragel.c"
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
	goto tr179;
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
st132:
	if ( ++p == pe )
		goto _test_eof132;
case 132:
	if ( (*p) == 39 )
		goto st133;
	goto tr183;
st133:
	if ( ++p == pe )
		goto _test_eof133;
case 133:
	if ( (*p) == 39 )
		goto st134;
	goto tr183;
st134:
	if ( ++p == pe )
		goto _test_eof134;
case 134:
	if ( (*p) == 39 )
		goto st135;
	goto tr183;
st135:
	if ( ++p == pe )
		goto _test_eof135;
case 135:
	if ( (*p) == 39 )
		goto tr187;
	goto tr183;
tr153:
#line 1 "NONE"
	{te = p+1;}
#line 562 "wikitext_ragel.rl"
	{act = 59;}
	goto st136;
st136:
	if ( ++p == pe )
		goto _test_eof136;
case 136:
#line 1253 "wikitext_ragel.c"
	switch( (*p) ) {
		case 43: goto st130;
		case 45: goto tr153;
		case 47: goto st130;
		case 64: goto tr188;
		case 92: goto st130;
		case 94: goto st130;
		case 95: goto tr153;
		case 126: goto st130;
	}
	if ( (*p) < 46 ) {
		if ( 36 <= (*p) && (*p) <= 37 )
			goto st130;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st20;
		} else if ( (*p) >= 65 )
			goto st20;
	} else
		goto st20;
	goto tr178;
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
#line 362 "wikitext_ragel.rl"
	{act = 28;}
	goto st137;
st137:
	if ( ++p == pe )
		goto _test_eof137;
case 137:
#line 1362 "wikitext_ragel.c"
	if ( (*p) == 46 )
		goto st23;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st22;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr190;
	} else
		goto tr190;
	goto tr189;
tr190:
#line 1 "NONE"
	{te = p+1;}
#line 362 "wikitext_ragel.rl"
	{act = 28;}
	goto st138;
st138:
	if ( ++p == pe )
		goto _test_eof138;
case 138:
#line 1384 "wikitext_ragel.c"
	if ( (*p) == 46 )
		goto st23;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st22;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr191;
	} else
		goto tr191;
	goto tr189;
tr191:
#line 1 "NONE"
	{te = p+1;}
#line 362 "wikitext_ragel.rl"
	{act = 28;}
	goto st139;
st139:
	if ( ++p == pe )
		goto _test_eof139;
case 139:
#line 1406 "wikitext_ragel.c"
	if ( (*p) == 46 )
		goto st23;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st22;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr192;
	} else
		goto tr192;
	goto tr189;
tr192:
#line 1 "NONE"
	{te = p+1;}
#line 362 "wikitext_ragel.rl"
	{act = 28;}
	goto st140;
st140:
	if ( ++p == pe )
		goto _test_eof140;
case 140:
#line 1428 "wikitext_ragel.c"
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
	goto tr189;
tr188:
#line 1 "NONE"
	{te = p+1;}
#line 562 "wikitext_ragel.rl"
	{act = 59;}
	goto st141;
st141:
	if ( ++p == pe )
		goto _test_eof141;
case 141:
#line 1450 "wikitext_ragel.c"
	switch( (*p) ) {
		case 43: goto st130;
		case 45: goto st130;
		case 47: goto st130;
		case 64: goto st130;
		case 92: goto st130;
		case 126: goto st130;
	}
	if ( (*p) < 65 ) {
		if ( (*p) > 37 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st22;
		} else if ( (*p) >= 36 )
			goto st130;
	} else if ( (*p) > 90 ) {
		if ( (*p) > 95 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st22;
		} else if ( (*p) >= 94 )
			goto st130;
	} else
		goto st22;
	goto tr178;
tr154:
#line 1 "NONE"
	{te = p+1;}
#line 544 "wikitext_ragel.rl"
	{act = 57;}
	goto st142;
st142:
	if ( ++p == pe )
		goto _test_eof142;
case 142:
#line 1484 "wikitext_ragel.c"
	switch( (*p) ) {
		case 33: goto st129;
		case 44: goto st129;
		case 45: goto st20;
		case 46: goto tr154;
		case 63: goto st129;
		case 64: goto st21;
		case 95: goto st20;
	}
	if ( (*p) < 48 ) {
		if ( 40 <= (*p) && (*p) <= 41 )
			goto st129;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st20;
		} else if ( (*p) >= 65 )
			goto st20;
	} else
		goto st20;
	goto tr177;
st143:
	if ( ++p == pe )
		goto _test_eof143;
case 143:
	switch( (*p) ) {
		case 43: goto st130;
		case 45: goto st144;
		case 47: goto st130;
		case 64: goto st130;
		case 92: goto st130;
		case 94: goto st130;
		case 95: goto st144;
		case 126: goto st130;
	}
	if ( (*p) < 46 ) {
		if ( 36 <= (*p) && (*p) <= 37 )
			goto st130;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st145;
		} else if ( (*p) >= 65 )
			goto st145;
	} else
		goto st145;
	goto tr193;
st144:
	if ( ++p == pe )
		goto _test_eof144;
case 144:
	switch( (*p) ) {
		case 43: goto st130;
		case 45: goto st144;
		case 47: goto st143;
		case 64: goto st130;
		case 92: goto st130;
		case 94: goto st130;
		case 95: goto st144;
		case 126: goto st130;
	}
	if ( (*p) < 46 ) {
		if ( 36 <= (*p) && (*p) <= 37 )
			goto st130;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st145;
		} else if ( (*p) >= 65 )
			goto st145;
	} else
		goto st145;
	goto tr193;
st145:
	if ( ++p == pe )
		goto _test_eof145;
case 145:
	switch( (*p) ) {
		case 47: goto st146;
		case 95: goto st145;
	}
	if ( (*p) < 65 ) {
		if ( 45 <= (*p) && (*p) <= 57 )
			goto st145;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st145;
	} else
		goto st145;
	goto tr193;
st146:
	if ( ++p == pe )
		goto _test_eof146;
case 146:
	if ( (*p) == 95 )
		goto st145;
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st145;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st145;
		} else if ( (*p) >= 65 )
			goto st145;
	} else
		goto st145;
	goto tr193;
tr156:
#line 1 "NONE"
	{te = p+1;}
#line 550 "wikitext_ragel.rl"
	{act = 58;}
	goto st147;
st147:
	if ( ++p == pe )
		goto _test_eof147;
case 147:
#line 1603 "wikitext_ragel.c"
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
				goto tr156;
		} else if ( (*p) >= 65 )
			goto tr156;
	} else
		goto tr156;
	goto tr197;
st148:
	if ( ++p == pe )
		goto _test_eof148;
case 148:
	switch( (*p) ) {
		case 33: goto tr199;
		case 47: goto tr200;
		case 66: goto tr202;
		case 69: goto tr203;
		case 77: goto tr204;
		case 78: goto tr205;
		case 80: goto tr206;
		case 83: goto tr207;
		case 84: goto tr208;
		case 98: goto tr202;
		case 101: goto tr203;
		case 109: goto tr204;
		case 110: goto tr205;
		case 112: goto tr209;
		case 115: goto tr207;
		case 116: goto tr208;
	}
	if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr201;
	} else if ( (*p) >= 65 )
		goto tr201;
	goto tr198;
tr200:
#line 1 "NONE"
	{te = p+1;}
	goto st149;
st149:
	if ( ++p == pe )
		goto _test_eof149;
case 149:
#line 1656 "wikitext_ragel.c"
	switch( (*p) ) {
		case 66: goto st25;
		case 69: goto st35;
		case 77: goto st37;
		case 78: goto st41;
		case 80: goto st47;
		case 83: goto st50;
		case 84: goto st56;
		case 98: goto st25;
		case 101: goto st35;
		case 109: goto st37;
		case 110: goto st41;
		case 112: goto st47;
		case 115: goto st50;
		case 116: goto st56;
	}
	goto tr210;
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
		case 77: goto st36;
		case 109: goto st36;
	}
	goto tr30;
st36:
	if ( ++p == pe )
		goto _test_eof36;
case 36:
	if ( (*p) == 62 )
		goto tr42;
	goto tr30;
st37:
	if ( ++p == pe )
		goto _test_eof37;
case 37:
	switch( (*p) ) {
		case 65: goto st38;
		case 97: goto st38;
	}
	goto tr30;
st38:
	if ( ++p == pe )
		goto _test_eof38;
case 38:
	switch( (*p) ) {
		case 84: goto st39;
		case 116: goto st39;
	}
	goto tr30;
st39:
	if ( ++p == pe )
		goto _test_eof39;
case 39:
	switch( (*p) ) {
		case 72: goto st40;
		case 104: goto st40;
	}
	goto tr30;
st40:
	if ( ++p == pe )
		goto _test_eof40;
case 40:
	if ( (*p) == 62 )
		goto tr46;
	goto tr30;
st41:
	if ( ++p == pe )
		goto _test_eof41;
case 41:
	switch( (*p) ) {
		case 79: goto st42;
		case 111: goto st42;
	}
	goto tr30;
st42:
	if ( ++p == pe )
		goto _test_eof42;
case 42:
	switch( (*p) ) {
		case 87: goto st43;
		case 119: goto st43;
	}
	goto tr30;
st43:
	if ( ++p == pe )
		goto _test_eof43;
case 43:
	switch( (*p) ) {
		case 73: goto st44;
		case 105: goto st44;
	}
	goto tr30;
st44:
	if ( ++p == pe )
		goto _test_eof44;
case 44:
	switch( (*p) ) {
		case 75: goto st45;
		case 107: goto st45;
	}
	goto tr30;
st45:
	if ( ++p == pe )
		goto _test_eof45;
case 45:
	switch( (*p) ) {
		case 73: goto st46;
		case 105: goto st46;
	}
	goto tr30;
st46:
	if ( ++p == pe )
		goto _test_eof46;
case 46:
	if ( (*p) == 62 )
		goto tr52;
	goto tr30;
st47:
	if ( ++p == pe )
		goto _test_eof47;
case 47:
	switch( (*p) ) {
		case 82: goto st48;
		case 114: goto st48;
	}
	goto tr30;
st48:
	if ( ++p == pe )
		goto _test_eof48;
case 48:
	switch( (*p) ) {
		case 69: goto st49;
		case 101: goto st49;
	}
	goto tr30;
st49:
	if ( ++p == pe )
		goto _test_eof49;
case 49:
	if ( (*p) == 62 )
		goto tr55;
	goto tr30;
st50:
	if ( ++p == pe )
		goto _test_eof50;
case 50:
	switch( (*p) ) {
		case 84: goto st51;
		case 116: goto st51;
	}
	goto tr30;
st51:
	if ( ++p == pe )
		goto _test_eof51;
case 51:
	switch( (*p) ) {
		case 82: goto st52;
		case 114: goto st52;
	}
	goto tr30;
st52:
	if ( ++p == pe )
		goto _test_eof52;
case 52:
	switch( (*p) ) {
		case 79: goto st53;
		case 111: goto st53;
	}
	goto tr30;
st53:
	if ( ++p == pe )
		goto _test_eof53;
case 53:
	switch( (*p) ) {
		case 78: goto st54;
		case 110: goto st54;
	}
	goto tr30;
st54:
	if ( ++p == pe )
		goto _test_eof54;
case 54:
	switch( (*p) ) {
		case 71: goto st55;
		case 103: goto st55;
	}
	goto tr30;
st55:
	if ( ++p == pe )
		goto _test_eof55;
case 55:
	if ( (*p) == 62 )
		goto tr61;
	goto tr30;
st56:
	if ( ++p == pe )
		goto _test_eof56;
case 56:
	switch( (*p) ) {
		case 73: goto st57;
		case 84: goto st64;
		case 105: goto st57;
		case 116: goto st64;
	}
	goto tr30;
st57:
	if ( ++p == pe )
		goto _test_eof57;
case 57:
	switch( (*p) ) {
		case 77: goto st58;
		case 109: goto st58;
	}
	goto tr30;
st58:
	if ( ++p == pe )
		goto _test_eof58;
case 58:
	switch( (*p) ) {
		case 69: goto st59;
		case 101: goto st59;
	}
	goto tr30;
st59:
	if ( ++p == pe )
		goto _test_eof59;
case 59:
	switch( (*p) ) {
		case 76: goto st60;
		case 108: goto st60;
	}
	goto tr30;
st60:
	if ( ++p == pe )
		goto _test_eof60;
case 60:
	switch( (*p) ) {
		case 73: goto st61;
		case 105: goto st61;
	}
	goto tr30;
st61:
	if ( ++p == pe )
		goto _test_eof61;
case 61:
	switch( (*p) ) {
		case 78: goto st62;
		case 110: goto st62;
	}
	goto tr30;
st62:
	if ( ++p == pe )
		goto _test_eof62;
case 62:
	switch( (*p) ) {
		case 69: goto st63;
		case 101: goto st63;
	}
	goto tr30;
st63:
	if ( ++p == pe )
		goto _test_eof63;
case 63:
	if ( (*p) == 62 )
		goto tr70;
	goto tr30;
st64:
	if ( ++p == pe )
		goto _test_eof64;
case 64:
	if ( (*p) == 62 )
		goto tr71;
	goto tr30;
tr202:
#line 1 "NONE"
	{te = p+1;}
	goto st150;
st150:
	if ( ++p == pe )
		goto _test_eof150;
case 150:
#line 2028 "wikitext_ragel.c"
	switch( (*p) ) {
		case 76: goto st65;
		case 108: goto st65;
	}
	goto tr218;
st65:
	if ( ++p == pe )
		goto _test_eof65;
case 65:
	switch( (*p) ) {
		case 79: goto st66;
		case 111: goto st66;
	}
	goto tr72;
st66:
	if ( ++p == pe )
		goto _test_eof66;
case 66:
	switch( (*p) ) {
		case 67: goto st67;
		case 99: goto st67;
	}
	goto tr72;
st67:
	if ( ++p == pe )
		goto _test_eof67;
case 67:
	switch( (*p) ) {
		case 75: goto st68;
		case 107: goto st68;
	}
	goto tr72;
st68:
	if ( ++p == pe )
		goto _test_eof68;
case 68:
	switch( (*p) ) {
		case 81: goto st69;
		case 113: goto st69;
	}
	goto tr72;
st69:
	if ( ++p == pe )
		goto _test_eof69;
case 69:
	switch( (*p) ) {
		case 85: goto st70;
		case 117: goto st70;
	}
	goto tr72;
st70:
	if ( ++p == pe )
		goto _test_eof70;
case 70:
	switch( (*p) ) {
		case 79: goto st71;
		case 111: goto st71;
	}
	goto tr72;
st71:
	if ( ++p == pe )
		goto _test_eof71;
case 71:
	switch( (*p) ) {
		case 84: goto st72;
		case 116: goto st72;
	}
	goto tr72;
st72:
	if ( ++p == pe )
		goto _test_eof72;
case 72:
	switch( (*p) ) {
		case 69: goto st73;
		case 101: goto st73;
	}
	goto tr72;
st73:
	if ( ++p == pe )
		goto _test_eof73;
case 73:
	if ( (*p) == 62 )
		goto tr81;
	goto tr72;
tr203:
#line 1 "NONE"
	{te = p+1;}
	goto st151;
st151:
	if ( ++p == pe )
		goto _test_eof151;
case 151:
#line 2121 "wikitext_ragel.c"
	switch( (*p) ) {
		case 77: goto st74;
		case 109: goto st74;
	}
	goto tr218;
st74:
	if ( ++p == pe )
		goto _test_eof74;
case 74:
	if ( (*p) == 62 )
		goto tr82;
	goto tr72;
tr204:
#line 1 "NONE"
	{te = p+1;}
	goto st152;
st152:
	if ( ++p == pe )
		goto _test_eof152;
case 152:
#line 2142 "wikitext_ragel.c"
	switch( (*p) ) {
		case 65: goto st75;
		case 97: goto st75;
	}
	goto tr218;
st75:
	if ( ++p == pe )
		goto _test_eof75;
case 75:
	switch( (*p) ) {
		case 84: goto st76;
		case 116: goto st76;
	}
	goto tr72;
st76:
	if ( ++p == pe )
		goto _test_eof76;
case 76:
	switch( (*p) ) {
		case 72: goto st77;
		case 104: goto st77;
	}
	goto tr72;
st77:
	if ( ++p == pe )
		goto _test_eof77;
case 77:
	if ( (*p) == 62 )
		goto tr85;
	goto tr72;
tr205:
#line 1 "NONE"
	{te = p+1;}
	goto st153;
st153:
	if ( ++p == pe )
		goto _test_eof153;
case 153:
#line 2181 "wikitext_ragel.c"
	switch( (*p) ) {
		case 79: goto st78;
		case 111: goto st78;
	}
	goto tr218;
st78:
	if ( ++p == pe )
		goto _test_eof78;
case 78:
	switch( (*p) ) {
		case 87: goto st79;
		case 119: goto st79;
	}
	goto tr72;
st79:
	if ( ++p == pe )
		goto _test_eof79;
case 79:
	switch( (*p) ) {
		case 73: goto st80;
		case 105: goto st80;
	}
	goto tr72;
st80:
	if ( ++p == pe )
		goto _test_eof80;
case 80:
	switch( (*p) ) {
		case 75: goto st81;
		case 107: goto st81;
	}
	goto tr72;
st81:
	if ( ++p == pe )
		goto _test_eof81;
case 81:
	switch( (*p) ) {
		case 73: goto st82;
		case 105: goto st82;
	}
	goto tr72;
st82:
	if ( ++p == pe )
		goto _test_eof82;
case 82:
	if ( (*p) == 62 )
		goto tr90;
	goto tr72;
tr206:
#line 1 "NONE"
	{te = p+1;}
	goto st154;
st154:
	if ( ++p == pe )
		goto _test_eof154;
case 154:
#line 2238 "wikitext_ragel.c"
	switch( (*p) ) {
		case 82: goto st83;
		case 114: goto st83;
	}
	goto tr218;
st83:
	if ( ++p == pe )
		goto _test_eof83;
case 83:
	switch( (*p) ) {
		case 69: goto st84;
		case 101: goto st84;
	}
	goto tr72;
st84:
	if ( ++p == pe )
		goto _test_eof84;
case 84:
	if ( (*p) == 62 )
		goto tr92;
	goto tr72;
tr207:
#line 1 "NONE"
	{te = p+1;}
	goto st155;
st155:
	if ( ++p == pe )
		goto _test_eof155;
case 155:
#line 2268 "wikitext_ragel.c"
	switch( (*p) ) {
		case 84: goto st85;
		case 116: goto st85;
	}
	goto tr218;
st85:
	if ( ++p == pe )
		goto _test_eof85;
case 85:
	switch( (*p) ) {
		case 82: goto st86;
		case 114: goto st86;
	}
	goto tr72;
st86:
	if ( ++p == pe )
		goto _test_eof86;
case 86:
	switch( (*p) ) {
		case 79: goto st87;
		case 111: goto st87;
	}
	goto tr72;
st87:
	if ( ++p == pe )
		goto _test_eof87;
case 87:
	switch( (*p) ) {
		case 78: goto st88;
		case 110: goto st88;
	}
	goto tr72;
st88:
	if ( ++p == pe )
		goto _test_eof88;
case 88:
	switch( (*p) ) {
		case 71: goto st89;
		case 103: goto st89;
	}
	goto tr72;
st89:
	if ( ++p == pe )
		goto _test_eof89;
case 89:
	if ( (*p) == 62 )
		goto tr97;
	goto tr72;
tr208:
#line 1 "NONE"
	{te = p+1;}
	goto st156;
st156:
	if ( ++p == pe )
		goto _test_eof156;
case 156:
#line 2325 "wikitext_ragel.c"
	switch( (*p) ) {
		case 73: goto st90;
		case 84: goto st97;
		case 105: goto st90;
		case 116: goto st97;
	}
	goto tr218;
st90:
	if ( ++p == pe )
		goto _test_eof90;
case 90:
	switch( (*p) ) {
		case 77: goto st91;
		case 109: goto st91;
	}
	goto tr72;
st91:
	if ( ++p == pe )
		goto _test_eof91;
case 91:
	switch( (*p) ) {
		case 69: goto st92;
		case 101: goto st92;
	}
	goto tr72;
st92:
	if ( ++p == pe )
		goto _test_eof92;
case 92:
	switch( (*p) ) {
		case 76: goto st93;
		case 108: goto st93;
	}
	goto tr72;
st93:
	if ( ++p == pe )
		goto _test_eof93;
case 93:
	switch( (*p) ) {
		case 73: goto st94;
		case 105: goto st94;
	}
	goto tr72;
st94:
	if ( ++p == pe )
		goto _test_eof94;
case 94:
	switch( (*p) ) {
		case 78: goto st95;
		case 110: goto st95;
	}
	goto tr72;
st95:
	if ( ++p == pe )
		goto _test_eof95;
case 95:
	switch( (*p) ) {
		case 69: goto st96;
		case 101: goto st96;
	}
	goto tr72;
st96:
	if ( ++p == pe )
		goto _test_eof96;
case 96:
	if ( (*p) == 62 )
		goto tr104;
	goto tr72;
st97:
	if ( ++p == pe )
		goto _test_eof97;
case 97:
	if ( (*p) == 62 )
		goto tr105;
	goto tr72;
tr209:
#line 1 "NONE"
	{te = p+1;}
	goto st157;
st157:
	if ( ++p == pe )
		goto _test_eof157;
case 157:
#line 2409 "wikitext_ragel.c"
	switch( (*p) ) {
		case 82: goto st83;
		case 114: goto st98;
	}
	goto tr218;
st98:
	if ( ++p == pe )
		goto _test_eof98;
case 98:
	switch( (*p) ) {
		case 69: goto st84;
		case 101: goto st99;
	}
	goto tr72;
st99:
	if ( ++p == pe )
		goto _test_eof99;
case 99:
	switch( (*p) ) {
		case 32: goto st100;
		case 62: goto tr92;
	}
	goto tr72;
st100:
	if ( ++p == pe )
		goto _test_eof100;
case 100:
	if ( (*p) == 108 )
		goto st101;
	goto tr72;
st101:
	if ( ++p == pe )
		goto _test_eof101;
case 101:
	if ( (*p) == 97 )
		goto st102;
	goto tr72;
st102:
	if ( ++p == pe )
		goto _test_eof102;
case 102:
	if ( (*p) == 110 )
		goto st103;
	goto tr72;
st103:
	if ( ++p == pe )
		goto _test_eof103;
case 103:
	if ( (*p) == 103 )
		goto st104;
	goto tr72;
st104:
	if ( ++p == pe )
		goto _test_eof104;
case 104:
	if ( (*p) == 61 )
		goto st105;
	goto tr72;
st105:
	if ( ++p == pe )
		goto _test_eof105;
case 105:
	if ( (*p) == 34 )
		goto st106;
	goto tr72;
st106:
	if ( ++p == pe )
		goto _test_eof106;
case 106:
	if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st107;
	} else if ( (*p) >= 65 )
		goto st107;
	goto tr72;
st107:
	if ( ++p == pe )
		goto _test_eof107;
case 107:
	if ( (*p) == 34 )
		goto st108;
	if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st107;
	} else if ( (*p) >= 65 )
		goto st107;
	goto tr72;
st108:
	if ( ++p == pe )
		goto _test_eof108;
case 108:
	if ( (*p) == 62 )
		goto tr116;
	goto tr72;
tr160:
#line 45 "wikitext_ragel.rl"
	{
        MARK();
    }
	goto st158;
st158:
	if ( ++p == pe )
		goto _test_eof158;
case 158:
#line 2514 "wikitext_ragel.c"
	switch( (*p) ) {
		case 32: goto st159;
		case 61: goto tr160;
	}
	goto tr228;
st159:
	if ( ++p == pe )
		goto _test_eof159;
case 159:
	if ( (*p) == 32 )
		goto st159;
	goto tr228;
tr161:
#line 45 "wikitext_ragel.rl"
	{
        MARK();
    }
	goto st160;
st160:
	if ( ++p == pe )
		goto _test_eof160;
case 160:
#line 2537 "wikitext_ragel.c"
	if ( (*p) == 32 )
		goto tr231;
	goto tr230;
tr162:
#line 1 "NONE"
	{te = p+1;}
#line 550 "wikitext_ragel.rl"
	{act = 58;}
	goto st161;
st161:
	if ( ++p == pe )
		goto _test_eof161;
case 161:
#line 2551 "wikitext_ragel.c"
	switch( (*p) ) {
		case 64: goto st21;
		case 84: goto tr232;
		case 95: goto st20;
		case 116: goto tr232;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st20;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr156;
		} else if ( (*p) >= 65 )
			goto tr156;
	} else
		goto tr156;
	goto tr197;
tr232:
#line 1 "NONE"
	{te = p+1;}
#line 550 "wikitext_ragel.rl"
	{act = 58;}
	goto st162;
st162:
	if ( ++p == pe )
		goto _test_eof162;
case 162:
#line 2580 "wikitext_ragel.c"
	switch( (*p) ) {
		case 64: goto st21;
		case 80: goto tr233;
		case 95: goto st20;
		case 112: goto tr233;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st20;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr156;
		} else if ( (*p) >= 65 )
			goto tr156;
	} else
		goto tr156;
	goto tr197;
tr233:
#line 1 "NONE"
	{te = p+1;}
#line 550 "wikitext_ragel.rl"
	{act = 58;}
	goto st163;
st163:
	if ( ++p == pe )
		goto _test_eof163;
case 163:
#line 2609 "wikitext_ragel.c"
	switch( (*p) ) {
		case 58: goto st109;
		case 64: goto st21;
		case 95: goto st20;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st20;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr156;
		} else if ( (*p) >= 65 )
			goto tr156;
	} else
		goto tr156;
	goto tr197;
st109:
	if ( ++p == pe )
		goto _test_eof109;
case 109:
	if ( (*p) == 47 )
		goto st110;
	goto tr117;
st110:
	if ( ++p == pe )
		goto _test_eof110;
case 110:
	if ( (*p) == 47 )
		goto st111;
	goto tr117;
st111:
	if ( ++p == pe )
		goto _test_eof111;
case 111:
	switch( (*p) ) {
		case 45: goto tr120;
		case 61: goto tr120;
		case 95: goto tr120;
		case 126: goto tr120;
	}
	if ( (*p) < 47 ) {
		if ( (*p) > 40 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr120;
		} else if ( (*p) >= 35 )
			goto tr120;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr120;
		} else if ( (*p) >= 64 )
			goto tr120;
	} else
		goto tr120;
	goto tr117;
tr120:
#line 1 "NONE"
	{te = p+1;}
	goto st164;
st164:
	if ( ++p == pe )
		goto _test_eof164;
case 164:
#line 2674 "wikitext_ragel.c"
	switch( (*p) ) {
		case 33: goto st112;
		case 41: goto st112;
		case 44: goto st112;
		case 46: goto st112;
		case 61: goto tr120;
		case 63: goto st112;
		case 95: goto tr120;
		case 126: goto tr120;
	}
	if ( (*p) < 64 ) {
		if ( 35 <= (*p) && (*p) <= 57 )
			goto tr120;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr120;
	} else
		goto tr120;
	goto tr235;
st112:
	if ( ++p == pe )
		goto _test_eof112;
case 112:
	switch( (*p) ) {
		case 33: goto st112;
		case 41: goto st112;
		case 44: goto st112;
		case 46: goto st112;
		case 61: goto tr120;
		case 63: goto st112;
		case 95: goto tr120;
		case 126: goto tr120;
	}
	if ( (*p) < 64 ) {
		if ( 35 <= (*p) && (*p) <= 57 )
			goto tr120;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr120;
	} else
		goto tr120;
	goto tr121;
tr163:
#line 1 "NONE"
	{te = p+1;}
#line 550 "wikitext_ragel.rl"
	{act = 58;}
	goto st165;
st165:
	if ( ++p == pe )
		goto _test_eof165;
case 165:
#line 2727 "wikitext_ragel.c"
	switch( (*p) ) {
		case 64: goto st21;
		case 84: goto tr236;
		case 95: goto st20;
		case 116: goto tr236;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st20;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr156;
		} else if ( (*p) >= 65 )
			goto tr156;
	} else
		goto tr156;
	goto tr197;
tr236:
#line 1 "NONE"
	{te = p+1;}
#line 550 "wikitext_ragel.rl"
	{act = 58;}
	goto st166;
st166:
	if ( ++p == pe )
		goto _test_eof166;
case 166:
#line 2756 "wikitext_ragel.c"
	switch( (*p) ) {
		case 64: goto st21;
		case 84: goto tr237;
		case 95: goto st20;
		case 116: goto tr237;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st20;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr156;
		} else if ( (*p) >= 65 )
			goto tr156;
	} else
		goto tr156;
	goto tr197;
tr237:
#line 1 "NONE"
	{te = p+1;}
#line 550 "wikitext_ragel.rl"
	{act = 58;}
	goto st167;
st167:
	if ( ++p == pe )
		goto _test_eof167;
case 167:
#line 2785 "wikitext_ragel.c"
	switch( (*p) ) {
		case 64: goto st21;
		case 80: goto tr238;
		case 95: goto st20;
		case 112: goto tr238;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st20;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr156;
		} else if ( (*p) >= 65 )
			goto tr156;
	} else
		goto tr156;
	goto tr197;
tr238:
#line 1 "NONE"
	{te = p+1;}
#line 550 "wikitext_ragel.rl"
	{act = 58;}
	goto st168;
st168:
	if ( ++p == pe )
		goto _test_eof168;
case 168:
#line 2814 "wikitext_ragel.c"
	switch( (*p) ) {
		case 58: goto st109;
		case 64: goto st21;
		case 83: goto tr233;
		case 95: goto st20;
		case 115: goto tr233;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st20;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr156;
		} else if ( (*p) >= 65 )
			goto tr156;
	} else
		goto tr156;
	goto tr197;
tr164:
#line 1 "NONE"
	{te = p+1;}
#line 550 "wikitext_ragel.rl"
	{act = 58;}
	goto st169;
st169:
	if ( ++p == pe )
		goto _test_eof169;
case 169:
#line 2844 "wikitext_ragel.c"
	switch( (*p) ) {
		case 64: goto st21;
		case 65: goto tr239;
		case 95: goto st20;
		case 97: goto tr239;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st20;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 98 <= (*p) && (*p) <= 122 )
				goto tr156;
		} else if ( (*p) >= 66 )
			goto tr156;
	} else
		goto tr156;
	goto tr197;
tr239:
#line 1 "NONE"
	{te = p+1;}
#line 550 "wikitext_ragel.rl"
	{act = 58;}
	goto st170;
st170:
	if ( ++p == pe )
		goto _test_eof170;
case 170:
#line 2873 "wikitext_ragel.c"
	switch( (*p) ) {
		case 64: goto st21;
		case 73: goto tr240;
		case 95: goto st20;
		case 105: goto tr240;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st20;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr156;
		} else if ( (*p) >= 65 )
			goto tr156;
	} else
		goto tr156;
	goto tr197;
tr240:
#line 1 "NONE"
	{te = p+1;}
#line 550 "wikitext_ragel.rl"
	{act = 58;}
	goto st171;
st171:
	if ( ++p == pe )
		goto _test_eof171;
case 171:
#line 2902 "wikitext_ragel.c"
	switch( (*p) ) {
		case 64: goto st21;
		case 76: goto tr241;
		case 95: goto st20;
		case 108: goto tr241;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st20;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr156;
		} else if ( (*p) >= 65 )
			goto tr156;
	} else
		goto tr156;
	goto tr197;
tr241:
#line 1 "NONE"
	{te = p+1;}
#line 550 "wikitext_ragel.rl"
	{act = 58;}
	goto st172;
st172:
	if ( ++p == pe )
		goto _test_eof172;
case 172:
#line 2931 "wikitext_ragel.c"
	switch( (*p) ) {
		case 64: goto st21;
		case 84: goto tr242;
		case 95: goto st20;
		case 116: goto tr242;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st20;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr156;
		} else if ( (*p) >= 65 )
			goto tr156;
	} else
		goto tr156;
	goto tr197;
tr242:
#line 1 "NONE"
	{te = p+1;}
#line 550 "wikitext_ragel.rl"
	{act = 58;}
	goto st173;
st173:
	if ( ++p == pe )
		goto _test_eof173;
case 173:
#line 2960 "wikitext_ragel.c"
	switch( (*p) ) {
		case 64: goto st21;
		case 79: goto tr243;
		case 95: goto st20;
		case 111: goto tr243;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st20;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr156;
		} else if ( (*p) >= 65 )
			goto tr156;
	} else
		goto tr156;
	goto tr197;
tr243:
#line 1 "NONE"
	{te = p+1;}
#line 550 "wikitext_ragel.rl"
	{act = 58;}
	goto st174;
st174:
	if ( ++p == pe )
		goto _test_eof174;
case 174:
#line 2989 "wikitext_ragel.c"
	switch( (*p) ) {
		case 58: goto st113;
		case 64: goto st21;
		case 95: goto st20;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st20;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr156;
		} else if ( (*p) >= 65 )
			goto tr156;
	} else
		goto tr156;
	goto tr197;
st113:
	if ( ++p == pe )
		goto _test_eof113;
case 113:
	if ( (*p) == 95 )
		goto st114;
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st114;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st114;
		} else if ( (*p) >= 65 )
			goto st114;
	} else
		goto st114;
	goto tr117;
st114:
	if ( ++p == pe )
		goto _test_eof114;
case 114:
	switch( (*p) ) {
		case 64: goto st115;
		case 95: goto st114;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st114;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st114;
		} else if ( (*p) >= 65 )
			goto st114;
	} else
		goto st114;
	goto tr117;
st115:
	if ( ++p == pe )
		goto _test_eof115;
case 115:
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st116;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st116;
	} else
		goto st116;
	goto tr117;
st116:
	if ( ++p == pe )
		goto _test_eof116;
case 116:
	if ( (*p) == 46 )
		goto st117;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st116;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st116;
	} else
		goto st116;
	goto tr23;
st117:
	if ( ++p == pe )
		goto _test_eof117;
case 117:
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st116;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st118;
	} else
		goto st118;
	goto tr23;
st118:
	if ( ++p == pe )
		goto _test_eof118;
case 118:
	if ( (*p) == 46 )
		goto st117;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st116;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr128;
	} else
		goto tr128;
	goto tr23;
tr128:
#line 1 "NONE"
	{te = p+1;}
#line 356 "wikitext_ragel.rl"
	{act = 27;}
	goto st175;
st175:
	if ( ++p == pe )
		goto _test_eof175;
case 175:
#line 3111 "wikitext_ragel.c"
	if ( (*p) == 46 )
		goto st117;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st116;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr245;
	} else
		goto tr245;
	goto tr235;
tr245:
#line 1 "NONE"
	{te = p+1;}
#line 356 "wikitext_ragel.rl"
	{act = 27;}
	goto st176;
st176:
	if ( ++p == pe )
		goto _test_eof176;
case 176:
#line 3133 "wikitext_ragel.c"
	if ( (*p) == 46 )
		goto st117;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st116;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr246;
	} else
		goto tr246;
	goto tr235;
tr246:
#line 1 "NONE"
	{te = p+1;}
#line 356 "wikitext_ragel.rl"
	{act = 27;}
	goto st177;
st177:
	if ( ++p == pe )
		goto _test_eof177;
case 177:
#line 3155 "wikitext_ragel.c"
	if ( (*p) == 46 )
		goto st117;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st116;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr247;
	} else
		goto tr247;
	goto tr235;
tr247:
#line 1 "NONE"
	{te = p+1;}
#line 356 "wikitext_ragel.rl"
	{act = 27;}
	goto st178;
st178:
	if ( ++p == pe )
		goto _test_eof178;
case 178:
#line 3177 "wikitext_ragel.c"
	if ( (*p) == 46 )
		goto st117;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st116;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st116;
	} else
		goto st116;
	goto tr235;
tr165:
#line 1 "NONE"
	{te = p+1;}
#line 550 "wikitext_ragel.rl"
	{act = 58;}
	goto st179;
st179:
	if ( ++p == pe )
		goto _test_eof179;
case 179:
#line 3199 "wikitext_ragel.c"
	switch( (*p) ) {
		case 64: goto st21;
		case 86: goto tr248;
		case 95: goto st20;
		case 118: goto tr248;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st20;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr156;
		} else if ( (*p) >= 65 )
			goto tr156;
	} else
		goto tr156;
	goto tr197;
tr248:
#line 1 "NONE"
	{te = p+1;}
#line 550 "wikitext_ragel.rl"
	{act = 58;}
	goto st180;
st180:
	if ( ++p == pe )
		goto _test_eof180;
case 180:
#line 3228 "wikitext_ragel.c"
	switch( (*p) ) {
		case 64: goto st21;
		case 78: goto tr233;
		case 95: goto st20;
		case 110: goto tr233;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st20;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr156;
		} else if ( (*p) >= 65 )
			goto tr156;
	} else
		goto tr156;
	goto tr197;
st181:
	if ( ++p == pe )
		goto _test_eof181;
case 181:
	if ( (*p) == 91 )
		goto tr250;
	goto tr249;
tr250:
#line 1 "NONE"
	{te = p+1;}
	goto st182;
st182:
	if ( ++p == pe )
		goto _test_eof182;
case 182:
#line 3262 "wikitext_ragel.c"
	if ( (*p) == 58 )
		goto tr130;
	if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st119;
	} else if ( (*p) >= 65 )
		goto st119;
	goto tr251;
st119:
	if ( ++p == pe )
		goto _test_eof119;
case 119:
	if ( (*p) == 58 )
		goto tr130;
	if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st119;
	} else if ( (*p) >= 65 )
		goto st119;
	goto tr129;
st183:
	if ( ++p == pe )
		goto _test_eof183;
case 183:
	if ( (*p) == 93 )
		goto tr253;
	goto tr252;
tr168:
#line 1 "NONE"
	{te = p+1;}
#line 562 "wikitext_ragel.rl"
	{act = 59;}
	goto st184;
st184:
	if ( ++p == pe )
		goto _test_eof184;
case 184:
#line 3300 "wikitext_ragel.c"
	switch( (*p) ) {
		case 43: goto st130;
		case 45: goto tr153;
		case 47: goto st130;
		case 64: goto tr188;
		case 92: goto st130;
		case 94: goto st130;
		case 95: goto tr254;
		case 126: goto st130;
	}
	if ( (*p) < 46 ) {
		if ( 36 <= (*p) && (*p) <= 37 )
			goto st130;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st20;
		} else if ( (*p) >= 65 )
			goto st20;
	} else
		goto st20;
	goto tr178;
tr254:
#line 1 "NONE"
	{te = p+1;}
#line 562 "wikitext_ragel.rl"
	{act = 59;}
	goto st185;
st185:
	if ( ++p == pe )
		goto _test_eof185;
case 185:
#line 3333 "wikitext_ragel.c"
	switch( (*p) ) {
		case 43: goto st130;
		case 45: goto tr153;
		case 47: goto st130;
		case 64: goto tr188;
		case 78: goto st120;
		case 92: goto st130;
		case 94: goto st130;
		case 95: goto tr153;
		case 126: goto st130;
	}
	if ( (*p) < 46 ) {
		if ( 36 <= (*p) && (*p) <= 37 )
			goto st130;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st20;
		} else if ( (*p) >= 65 )
			goto st20;
	} else
		goto st20;
	goto tr178;
st120:
	if ( ++p == pe )
		goto _test_eof120;
case 120:
	switch( (*p) ) {
		case 64: goto st21;
		case 79: goto st121;
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
	goto tr132;
st121:
	if ( ++p == pe )
		goto _test_eof121;
case 121:
	switch( (*p) ) {
		case 64: goto st21;
		case 84: goto st122;
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
	goto tr132;
st122:
	if ( ++p == pe )
		goto _test_eof122;
case 122:
	switch( (*p) ) {
		case 64: goto st21;
		case 79: goto st123;
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
	goto tr132;
st123:
	if ( ++p == pe )
		goto _test_eof123;
case 123:
	switch( (*p) ) {
		case 64: goto st21;
		case 67: goto st124;
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
	goto tr132;
st124:
	if ( ++p == pe )
		goto _test_eof124;
case 124:
	switch( (*p) ) {
		case 64: goto st21;
		case 95: goto st125;
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
	goto tr132;
st125:
	if ( ++p == pe )
		goto _test_eof125;
case 125:
	switch( (*p) ) {
		case 64: goto st21;
		case 95: goto tr138;
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
	goto tr132;
tr138:
#line 1 "NONE"
	{te = p+1;}
#line 374 "wikitext_ragel.rl"
	{act = 30;}
	goto st186;
st186:
	if ( ++p == pe )
		goto _test_eof186;
case 186:
#line 3491 "wikitext_ragel.c"
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
	goto tr256;
st187:
	if ( ++p == pe )
		goto _test_eof187;
case 187:
	switch( (*p) ) {
		case 123: goto tr258;
		case 124: goto tr259;
	}
	goto tr257;
st188:
	if ( ++p == pe )
		goto _test_eof188;
case 188:
	if ( (*p) == 125 )
		goto st189;
	goto tr260;
st189:
	if ( ++p == pe )
		goto _test_eof189;
case 189:
	if ( (*p) == 125 )
		goto tr263;
	goto tr262;
st190:
	if ( ++p == pe )
		goto _test_eof190;
case 190:
	if ( (*p) == 125 )
		goto tr265;
	goto tr264;
	}
	_test_eof126: cs = 126; goto _test_eof; 
	_test_eof1: cs = 1; goto _test_eof; 
	_test_eof2: cs = 2; goto _test_eof; 
	_test_eof3: cs = 3; goto _test_eof; 
	_test_eof4: cs = 4; goto _test_eof; 
	_test_eof5: cs = 5; goto _test_eof; 
	_test_eof6: cs = 6; goto _test_eof; 
	_test_eof127: cs = 127; goto _test_eof; 
	_test_eof128: cs = 128; goto _test_eof; 
	_test_eof129: cs = 129; goto _test_eof; 
	_test_eof130: cs = 130; goto _test_eof; 
	_test_eof131: cs = 131; goto _test_eof; 
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
	_test_eof132: cs = 132; goto _test_eof; 
	_test_eof133: cs = 133; goto _test_eof; 
	_test_eof134: cs = 134; goto _test_eof; 
	_test_eof135: cs = 135; goto _test_eof; 
	_test_eof136: cs = 136; goto _test_eof; 
	_test_eof20: cs = 20; goto _test_eof; 
	_test_eof21: cs = 21; goto _test_eof; 
	_test_eof22: cs = 22; goto _test_eof; 
	_test_eof23: cs = 23; goto _test_eof; 
	_test_eof24: cs = 24; goto _test_eof; 
	_test_eof137: cs = 137; goto _test_eof; 
	_test_eof138: cs = 138; goto _test_eof; 
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
	_test_eof149: cs = 149; goto _test_eof; 
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
	_test_eof60: cs = 60; goto _test_eof; 
	_test_eof61: cs = 61; goto _test_eof; 
	_test_eof62: cs = 62; goto _test_eof; 
	_test_eof63: cs = 63; goto _test_eof; 
	_test_eof64: cs = 64; goto _test_eof; 
	_test_eof150: cs = 150; goto _test_eof; 
	_test_eof65: cs = 65; goto _test_eof; 
	_test_eof66: cs = 66; goto _test_eof; 
	_test_eof67: cs = 67; goto _test_eof; 
	_test_eof68: cs = 68; goto _test_eof; 
	_test_eof69: cs = 69; goto _test_eof; 
	_test_eof70: cs = 70; goto _test_eof; 
	_test_eof71: cs = 71; goto _test_eof; 
	_test_eof72: cs = 72; goto _test_eof; 
	_test_eof73: cs = 73; goto _test_eof; 
	_test_eof151: cs = 151; goto _test_eof; 
	_test_eof74: cs = 74; goto _test_eof; 
	_test_eof152: cs = 152; goto _test_eof; 
	_test_eof75: cs = 75; goto _test_eof; 
	_test_eof76: cs = 76; goto _test_eof; 
	_test_eof77: cs = 77; goto _test_eof; 
	_test_eof153: cs = 153; goto _test_eof; 
	_test_eof78: cs = 78; goto _test_eof; 
	_test_eof79: cs = 79; goto _test_eof; 
	_test_eof80: cs = 80; goto _test_eof; 
	_test_eof81: cs = 81; goto _test_eof; 
	_test_eof82: cs = 82; goto _test_eof; 
	_test_eof154: cs = 154; goto _test_eof; 
	_test_eof83: cs = 83; goto _test_eof; 
	_test_eof84: cs = 84; goto _test_eof; 
	_test_eof155: cs = 155; goto _test_eof; 
	_test_eof85: cs = 85; goto _test_eof; 
	_test_eof86: cs = 86; goto _test_eof; 
	_test_eof87: cs = 87; goto _test_eof; 
	_test_eof88: cs = 88; goto _test_eof; 
	_test_eof89: cs = 89; goto _test_eof; 
	_test_eof156: cs = 156; goto _test_eof; 
	_test_eof90: cs = 90; goto _test_eof; 
	_test_eof91: cs = 91; goto _test_eof; 
	_test_eof92: cs = 92; goto _test_eof; 
	_test_eof93: cs = 93; goto _test_eof; 
	_test_eof94: cs = 94; goto _test_eof; 
	_test_eof95: cs = 95; goto _test_eof; 
	_test_eof96: cs = 96; goto _test_eof; 
	_test_eof97: cs = 97; goto _test_eof; 
	_test_eof157: cs = 157; goto _test_eof; 
	_test_eof98: cs = 98; goto _test_eof; 
	_test_eof99: cs = 99; goto _test_eof; 
	_test_eof100: cs = 100; goto _test_eof; 
	_test_eof101: cs = 101; goto _test_eof; 
	_test_eof102: cs = 102; goto _test_eof; 
	_test_eof103: cs = 103; goto _test_eof; 
	_test_eof104: cs = 104; goto _test_eof; 
	_test_eof105: cs = 105; goto _test_eof; 
	_test_eof106: cs = 106; goto _test_eof; 
	_test_eof107: cs = 107; goto _test_eof; 
	_test_eof108: cs = 108; goto _test_eof; 
	_test_eof158: cs = 158; goto _test_eof; 
	_test_eof159: cs = 159; goto _test_eof; 
	_test_eof160: cs = 160; goto _test_eof; 
	_test_eof161: cs = 161; goto _test_eof; 
	_test_eof162: cs = 162; goto _test_eof; 
	_test_eof163: cs = 163; goto _test_eof; 
	_test_eof109: cs = 109; goto _test_eof; 
	_test_eof110: cs = 110; goto _test_eof; 
	_test_eof111: cs = 111; goto _test_eof; 
	_test_eof164: cs = 164; goto _test_eof; 
	_test_eof112: cs = 112; goto _test_eof; 
	_test_eof165: cs = 165; goto _test_eof; 
	_test_eof166: cs = 166; goto _test_eof; 
	_test_eof167: cs = 167; goto _test_eof; 
	_test_eof168: cs = 168; goto _test_eof; 
	_test_eof169: cs = 169; goto _test_eof; 
	_test_eof170: cs = 170; goto _test_eof; 
	_test_eof171: cs = 171; goto _test_eof; 
	_test_eof172: cs = 172; goto _test_eof; 
	_test_eof173: cs = 173; goto _test_eof; 
	_test_eof174: cs = 174; goto _test_eof; 
	_test_eof113: cs = 113; goto _test_eof; 
	_test_eof114: cs = 114; goto _test_eof; 
	_test_eof115: cs = 115; goto _test_eof; 
	_test_eof116: cs = 116; goto _test_eof; 
	_test_eof117: cs = 117; goto _test_eof; 
	_test_eof118: cs = 118; goto _test_eof; 
	_test_eof175: cs = 175; goto _test_eof; 
	_test_eof176: cs = 176; goto _test_eof; 
	_test_eof177: cs = 177; goto _test_eof; 
	_test_eof178: cs = 178; goto _test_eof; 
	_test_eof179: cs = 179; goto _test_eof; 
	_test_eof180: cs = 180; goto _test_eof; 
	_test_eof181: cs = 181; goto _test_eof; 
	_test_eof182: cs = 182; goto _test_eof; 
	_test_eof119: cs = 119; goto _test_eof; 
	_test_eof183: cs = 183; goto _test_eof; 
	_test_eof184: cs = 184; goto _test_eof; 
	_test_eof185: cs = 185; goto _test_eof; 
	_test_eof120: cs = 120; goto _test_eof; 
	_test_eof121: cs = 121; goto _test_eof; 
	_test_eof122: cs = 122; goto _test_eof; 
	_test_eof123: cs = 123; goto _test_eof; 
	_test_eof124: cs = 124; goto _test_eof; 
	_test_eof125: cs = 125; goto _test_eof; 
	_test_eof186: cs = 186; goto _test_eof; 
	_test_eof187: cs = 187; goto _test_eof; 
	_test_eof188: cs = 188; goto _test_eof; 
	_test_eof189: cs = 189; goto _test_eof; 
	_test_eof190: cs = 190; goto _test_eof; 

	_test_eof: {}
	if ( p == eof )
	{
	switch ( cs ) {
	case 127: goto tr173;
	case 128: goto tr175;
	case 129: goto tr177;
	case 130: goto tr178;
	case 131: goto tr179;
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
	case 132: goto tr183;
	case 133: goto tr183;
	case 134: goto tr183;
	case 135: goto tr183;
	case 136: goto tr178;
	case 20: goto tr23;
	case 21: goto tr23;
	case 22: goto tr23;
	case 23: goto tr23;
	case 24: goto tr23;
	case 137: goto tr189;
	case 138: goto tr189;
	case 139: goto tr189;
	case 140: goto tr189;
	case 141: goto tr178;
	case 142: goto tr177;
	case 143: goto tr193;
	case 144: goto tr193;
	case 145: goto tr193;
	case 146: goto tr193;
	case 147: goto tr197;
	case 148: goto tr198;
	case 149: goto tr210;
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
	case 58: goto tr30;
	case 59: goto tr30;
	case 60: goto tr30;
	case 61: goto tr30;
	case 62: goto tr30;
	case 63: goto tr30;
	case 64: goto tr30;
	case 150: goto tr218;
	case 65: goto tr72;
	case 66: goto tr72;
	case 67: goto tr72;
	case 68: goto tr72;
	case 69: goto tr72;
	case 70: goto tr72;
	case 71: goto tr72;
	case 72: goto tr72;
	case 73: goto tr72;
	case 151: goto tr218;
	case 74: goto tr72;
	case 152: goto tr218;
	case 75: goto tr72;
	case 76: goto tr72;
	case 77: goto tr72;
	case 153: goto tr218;
	case 78: goto tr72;
	case 79: goto tr72;
	case 80: goto tr72;
	case 81: goto tr72;
	case 82: goto tr72;
	case 154: goto tr218;
	case 83: goto tr72;
	case 84: goto tr72;
	case 155: goto tr218;
	case 85: goto tr72;
	case 86: goto tr72;
	case 87: goto tr72;
	case 88: goto tr72;
	case 89: goto tr72;
	case 156: goto tr218;
	case 90: goto tr72;
	case 91: goto tr72;
	case 92: goto tr72;
	case 93: goto tr72;
	case 94: goto tr72;
	case 95: goto tr72;
	case 96: goto tr72;
	case 97: goto tr72;
	case 157: goto tr218;
	case 98: goto tr72;
	case 99: goto tr72;
	case 100: goto tr72;
	case 101: goto tr72;
	case 102: goto tr72;
	case 103: goto tr72;
	case 104: goto tr72;
	case 105: goto tr72;
	case 106: goto tr72;
	case 107: goto tr72;
	case 108: goto tr72;
	case 158: goto tr228;
	case 159: goto tr228;
	case 160: goto tr230;
	case 161: goto tr197;
	case 162: goto tr197;
	case 163: goto tr197;
	case 109: goto tr117;
	case 110: goto tr117;
	case 111: goto tr117;
	case 164: goto tr235;
	case 112: goto tr121;
	case 165: goto tr197;
	case 166: goto tr197;
	case 167: goto tr197;
	case 168: goto tr197;
	case 169: goto tr197;
	case 170: goto tr197;
	case 171: goto tr197;
	case 172: goto tr197;
	case 173: goto tr197;
	case 174: goto tr197;
	case 113: goto tr117;
	case 114: goto tr117;
	case 115: goto tr117;
	case 116: goto tr23;
	case 117: goto tr23;
	case 118: goto tr23;
	case 175: goto tr235;
	case 176: goto tr235;
	case 177: goto tr235;
	case 178: goto tr235;
	case 179: goto tr197;
	case 180: goto tr197;
	case 181: goto tr249;
	case 182: goto tr251;
	case 119: goto tr129;
	case 183: goto tr252;
	case 184: goto tr178;
	case 185: goto tr178;
	case 120: goto tr132;
	case 121: goto tr132;
	case 122: goto tr132;
	case 123: goto tr132;
	case 124: goto tr132;
	case 125: goto tr132;
	case 186: goto tr256;
	case 187: goto tr257;
	case 188: goto tr260;
	case 189: goto tr262;
	case 190: goto tr264;
	}
	}

	_out: {}
	}

#line 634 "wikitext_ragel.rl"
    if (cs == wikitext_error)
        rb_raise(eWikitextParserError, "failed before finding a token");
    else if (out->type == NO_TOKEN)
        rb_raise(eWikitextParserError, "failed to produce a token");
}
