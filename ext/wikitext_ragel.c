
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
static const int wikitext_start = 105;
static const int wikitext_first_final = 105;
static const int wikitext_error = 0;

static const int wikitext_en_main = 105;


#line 533 "wikitext_ragel.rl"


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

#line 575 "wikitext_ragel.rl"
    
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
#line 524 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(DEFAULT);
            out->column_stop = out->column_start + 1;
            {p++; cs = 105; goto _out;}
        }}
	goto st105;
tr3:
#line 61 "wikitext_ragel.rl"
	{
        out->code_point = ((uint32_t)(*(p - 2)) & 0x0f) << 12 |
            ((uint32_t)(*(p - 1)) & 0x3f) << 6 |
            (*p & 0x3f);
    }
#line 524 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(DEFAULT);
            out->column_stop = out->column_start + 1;
            {p++; cs = 105; goto _out;}
        }}
	goto st105;
tr6:
#line 68 "wikitext_ragel.rl"
	{
        out->code_point = ((uint32_t)(*(p - 3)) & 0x07) << 18 |
            ((uint32_t)(*(p - 2)) & 0x3f) << 12 |
            ((uint32_t)(*(p - 1)) & 0x3f) << 6 |
            (*p & 0x3f);
    }
#line 524 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(DEFAULT);
            out->column_stop = out->column_start + 1;
            {p++; cs = 105; goto _out;}
        }}
	goto st105;
tr7:
#line 413 "wikitext_ragel.rl"
	{{p = ((te))-1;}{
            EMIT(AMP);
            {p++; cs = 105; goto _out;}
        }}
	goto st105;
tr10:
#line 401 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(DECIMAL_ENTITY);
            {p++; cs = 105; goto _out;}
        }}
	goto st105;
tr12:
#line 395 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(HEX_ENTITY);
            {p++; cs = 105; goto _out;}
        }}
	goto st105;
tr14:
#line 389 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(NAMED_ENTITY);
            {p++; cs = 105; goto _out;}
        }}
	goto st105;
tr18:
#line 383 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(AMP_ENTITY);
            {p++; cs = 105; goto _out;}
        }}
	goto st105;
tr22:
#line 377 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(QUOT_ENTITY);
            {p++; cs = 105; goto _out;}
        }}
	goto st105;
tr23:
#line 1 "NONE"
	{	switch( act ) {
	case 23:
	{{p = ((te))-1;}
            EMIT(URI);
            {p++; cs = 105; goto _out;}
        }
	break;
	case 24:
	{{p = ((te))-1;}
            EMIT(MAIL);
            {p++; cs = 105; goto _out;}
        }
	break;
	case 51:
	{{p = ((te))-1;}
            EMIT(SPECIAL_URI_CHARS);
            {p++; cs = 105; goto _out;}
        }
	break;
	case 52:
	{{p = ((te))-1;}
            EMIT(ALNUM);
            {p++; cs = 105; goto _out;}
        }
	break;
	case 53:
	{{p = ((te))-1;}
            EMIT(PRINTABLE);
            {p++; cs = 105; goto _out;}
        }
	break;
	}
	}
	goto st105;
tr30:
#line 425 "wikitext_ragel.rl"
	{{p = ((te))-1;}{
            EMIT(LESS);
            {p++; cs = 105; goto _out;}
        }}
	goto st105;
tr40:
#line 126 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(BLOCKQUOTE_END);
            {p++; cs = 105; goto _out;}
        }}
	goto st105;
tr42:
#line 181 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(EM_END);
            {p++; cs = 105; goto _out;}
        }}
	goto st105;
tr46:
#line 138 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(MATH_END);
            {p++; cs = 105; goto _out;}
        }}
	goto st105;
tr52:
#line 96 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(NO_WIKI_END);
            {p++; cs = 105; goto _out;}
        }}
	goto st105;
tr55:
#line 114 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(PRE_END);
            {p++; cs = 105; goto _out;}
        }}
	goto st105;
tr61:
#line 169 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(STRONG_END);
            {p++; cs = 105; goto _out;}
        }}
	goto st105;
tr63:
#line 199 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(TT_END);
            {p++; cs = 105; goto _out;}
        }}
	goto st105;
tr64:
#line 419 "wikitext_ragel.rl"
	{{p = ((te))-1;}{
            EMIT(LESS);
            {p++; cs = 105; goto _out;}
        }}
	goto st105;
tr73:
#line 120 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(BLOCKQUOTE_START);
            {p++; cs = 105; goto _out;}
        }}
	goto st105;
tr74:
#line 175 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(EM_START);
            {p++; cs = 105; goto _out;}
        }}
	goto st105;
tr77:
#line 132 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(MATH_START);
            {p++; cs = 105; goto _out;}
        }}
	goto st105;
tr82:
#line 90 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(NO_WIKI_START);
            {p++; cs = 105; goto _out;}
        }}
	goto st105;
tr84:
#line 102 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(PRE_START);
            {p++; cs = 105; goto _out;}
        }}
	goto st105;
tr89:
#line 163 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(STRONG_START);
            {p++; cs = 105; goto _out;}
        }}
	goto st105;
tr90:
#line 193 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(TT_START);
            {p++; cs = 105; goto _out;}
        }}
	goto st105;
tr101:
#line 108 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(PRE_START);
            {p++; cs = 105; goto _out;}
        }}
	goto st105;
tr102:
#line 492 "wikitext_ragel.rl"
	{{p = ((te))-1;}{
            EMIT(ALNUM);
            {p++; cs = 105; goto _out;}
        }}
	goto st105;
tr106:
#line 310 "wikitext_ragel.rl"
	{{p = ((te))-1;}{
            EMIT(URI);
            {p++; cs = 105; goto _out;}
        }}
	goto st105;
tr117:
#line 50 "wikitext_ragel.rl"
	{
        out->code_point = *p & 0x7f;
    }
#line 524 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(DEFAULT);
            out->column_stop = out->column_start + 1;
            {p++; cs = 105; goto _out;}
        }}
	goto st105;
tr118:
#line 473 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(CRLF);
            out->column_stop = 1;
            out->line_stop++;
            {p++; cs = 105; goto _out;}
        }}
#line 50 "wikitext_ragel.rl"
	{
        out->code_point = *p & 0x7f;
    }
	goto st105;
tr122:
#line 407 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(QUOT);
            {p++; cs = 105; goto _out;}
        }}
	goto st105;
tr123:
#line 231 "wikitext_ragel.rl"
	{te = p+1;{
            if (out->column_start == 1              ||
                last_token_type == OL               ||
                last_token_type == UL               ||
                last_token_type == BLOCKQUOTE       ||
                last_token_type == BLOCKQUOTE_START)
                EMIT(OL);
            else
                EMIT(PRINTABLE);
            {p++; cs = 105; goto _out;}
        }}
	goto st105;
tr127:
#line 244 "wikitext_ragel.rl"
	{te = p+1;{
            if (out->column_start == 1              ||
                last_token_type == OL               ||
                last_token_type == UL               ||
                last_token_type == BLOCKQUOTE       ||
                last_token_type == BLOCKQUOTE_START)
                EMIT(UL);
            else
                EMIT(PRINTABLE);
            {p++; cs = 105; goto _out;}
        }}
	goto st105;
tr141:
#line 187 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(TT);
            {p++; cs = 105; goto _out;}
        }}
	goto st105;
tr145:
#line 473 "wikitext_ragel.rl"
	{te = p;p--;{
            EMIT(CRLF);
            out->column_stop = 1;
            out->line_stop++;
            {p++; cs = 105; goto _out;}
        }}
	goto st105;
tr146:
#line 473 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(CRLF);
            out->column_stop = 1;
            out->line_stop++;
            {p++; cs = 105; goto _out;}
        }}
	goto st105;
tr147:
#line 219 "wikitext_ragel.rl"
	{te = p;p--;{
            if (out->column_start == 1 || last_token_type == BLOCKQUOTE)
            {
                REWIND();
                EMIT(PRE);
            }
            else
                EMIT(SPACE);
            {p++; cs = 105; goto _out;}
        }}
	goto st105;
tr149:
#line 486 "wikitext_ragel.rl"
	{te = p;p--;{
            EMIT(SPECIAL_URI_CHARS);
            {p++; cs = 105; goto _out;}
        }}
	goto st105;
tr150:
#line 504 "wikitext_ragel.rl"
	{te = p;p--;{
            EMIT(PRINTABLE);
            {p++; cs = 105; goto _out;}
        }}
	goto st105;
tr151:
#line 413 "wikitext_ragel.rl"
	{te = p;p--;{
            EMIT(AMP);
            {p++; cs = 105; goto _out;}
        }}
	goto st105;
tr155:
#line 145 "wikitext_ragel.rl"
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
            {p++; cs = 105; goto _out;}
        }}
	goto st105;
tr159:
#line 145 "wikitext_ragel.rl"
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
            {p++; cs = 105; goto _out;}
        }}
	goto st105;
tr161:
#line 316 "wikitext_ragel.rl"
	{te = p;p--;{
            EMIT(MAIL);
            {p++; cs = 105; goto _out;}
        }}
	goto st105;
tr165:
#line 322 "wikitext_ragel.rl"
	{te = p;p--;{
            EMIT(PATH);
            {p++; cs = 105; goto _out;}
        }}
	goto st105;
tr169:
#line 492 "wikitext_ragel.rl"
	{te = p;p--;{
            EMIT(ALNUM);
            {p++; cs = 105; goto _out;}
        }}
	goto st105;
tr170:
#line 437 "wikitext_ragel.rl"
	{te = p;p--;{
            EMIT(DEFAULT);
            {p++; cs = 105; goto _out;}
        }}
	goto st105;
tr171:
#line 431 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(LESS);
            {p++; cs = 105; goto _out;}
        }}
	goto st105;
tr173:
#line 419 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(LESS);
            {p++; cs = 105; goto _out;}
        }}
	goto st105;
tr182:
#line 425 "wikitext_ragel.rl"
	{te = p;p--;{
            EMIT(LESS);
            {p++; cs = 105; goto _out;}
        }}
	goto st105;
tr190:
#line 419 "wikitext_ragel.rl"
	{te = p;p--;{
            EMIT(LESS);
            {p++; cs = 105; goto _out;}
        }}
	goto st105;
tr199:
#line 257 "wikitext_ragel.rl"
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
            {p++; cs = 105; goto _out;}
        }}
	goto st105;
tr201:
#line 206 "wikitext_ragel.rl"
	{te = p;p--;{
            if (out->column_start == 1 || last_token_type == BLOCKQUOTE)
                EMIT(BLOCKQUOTE);
            else
            {
                REWIND();
                EMIT(GREATER);
            }
            {p++; cs = 105; goto _out;}
        }}
	goto st105;
tr202:
#line 206 "wikitext_ragel.rl"
	{te = p+1;{
            if (out->column_start == 1 || last_token_type == BLOCKQUOTE)
                EMIT(BLOCKQUOTE);
            else
            {
                REWIND();
                EMIT(GREATER);
            }
            {p++; cs = 105; goto _out;}
        }}
	goto st105;
tr206:
#line 310 "wikitext_ragel.rl"
	{te = p;p--;{
            EMIT(URI);
            {p++; cs = 105; goto _out;}
        }}
	goto st105;
tr220:
#line 365 "wikitext_ragel.rl"
	{te = p;p--;{
            EMIT(EXT_LINK_START);
            {p++; cs = 105; goto _out;}
        }}
	goto st105;
tr221:
#line 328 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(LINK_START);
            {p++; cs = 105; goto _out;}
        }}
	goto st105;
tr222:
#line 371 "wikitext_ragel.rl"
	{te = p;p--;{
            EMIT(EXT_LINK_END);
            {p++; cs = 105; goto _out;}
        }}
	goto st105;
tr223:
#line 334 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(LINK_END);
            {p++; cs = 105; goto _out;}
        }}
	goto st105;
tr224:
#line 461 "wikitext_ragel.rl"
	{te = p;p--;{
            EMIT(LEFT_CURLY);
            {p++; cs = 105; goto _out;}
        }}
	goto st105;
tr225:
#line 449 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(IMG_START);
            {p++; cs = 105; goto _out;}
        }}
	goto st105;
tr226:
#line 340 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(TABLE_START);
            {p++; cs = 105; goto _out;}
        }}
	goto st105;
tr227:
#line 359 "wikitext_ragel.rl"
	{te = p;p--;{
            EMIT(SEPARATOR);
            {p++; cs = 105; goto _out;}
        }}
	goto st105;
tr229:
#line 353 "wikitext_ragel.rl"
	{te = p;p--;{
            EMIT(TABLE_END);
            {p++; cs = 105; goto _out;}
        }}
	goto st105;
tr230:
#line 346 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(IMG_END);
            {p++; cs = 105; goto _out;}
        }}
	goto st105;
tr231:
#line 467 "wikitext_ragel.rl"
	{te = p;p--;{
            EMIT(RIGHT_CURLY);
            {p++; cs = 105; goto _out;}
        }}
	goto st105;
tr232:
#line 455 "wikitext_ragel.rl"
	{te = p+1;{
            EMIT(IMG_END);
            {p++; cs = 105; goto _out;}
        }}
	goto st105;
st105:
#line 1 "NONE"
	{ts = 0;}
	if ( ++p == pe )
		goto _test_eof105;
case 105:
#line 1 "NONE"
	{ts = p;}
#line 757 "wikitext_ragel.c"
	switch( (*p) ) {
		case 10: goto tr118;
		case 13: goto tr119;
		case 32: goto tr120;
		case 33: goto st108;
		case 34: goto tr122;
		case 35: goto tr123;
		case 38: goto tr125;
		case 39: goto st111;
		case 42: goto tr127;
		case 43: goto st109;
		case 45: goto tr128;
		case 46: goto tr129;
		case 47: goto st122;
		case 60: goto st127;
		case 61: goto tr133;
		case 62: goto tr134;
		case 64: goto st109;
		case 70: goto tr135;
		case 72: goto tr136;
		case 77: goto tr137;
		case 83: goto tr138;
		case 91: goto st160;
		case 92: goto st109;
		case 93: goto st161;
		case 94: goto st109;
		case 95: goto tr128;
		case 96: goto tr141;
		case 102: goto tr135;
		case 104: goto tr136;
		case 109: goto tr137;
		case 115: goto tr138;
		case 123: goto st162;
		case 124: goto st163;
		case 125: goto st165;
		case 126: goto st109;
		case 127: goto tr117;
	}
	if ( (*p) < 36 ) {
		if ( (*p) < -32 ) {
			if ( -62 <= (*p) && (*p) <= -33 )
				goto st1;
		} else if ( (*p) > -17 ) {
			if ( (*p) > -12 ) {
				if ( 1 <= (*p) && (*p) <= 31 )
					goto tr117;
			} else if ( (*p) >= -16 )
				goto st4;
		} else
			goto st2;
	} else if ( (*p) > 37 ) {
		if ( (*p) < 48 ) {
			if ( 40 <= (*p) && (*p) <= 44 )
				goto st108;
		} else if ( (*p) > 57 ) {
			if ( (*p) > 63 ) {
				if ( 65 <= (*p) && (*p) <= 122 )
					goto tr131;
			} else if ( (*p) >= 58 )
				goto st108;
		} else
			goto tr131;
	} else
		goto st109;
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
tr119:
#line 50 "wikitext_ragel.rl"
	{
        out->code_point = *p & 0x7f;
    }
	goto st106;
st106:
	if ( ++p == pe )
		goto _test_eof106;
case 106:
#line 878 "wikitext_ragel.c"
	if ( (*p) == 10 )
		goto tr146;
	goto tr145;
tr120:
#line 45 "wikitext_ragel.rl"
	{
        MARK();
    }
	goto st107;
st107:
	if ( ++p == pe )
		goto _test_eof107;
case 107:
#line 892 "wikitext_ragel.c"
	if ( (*p) == 32 )
		goto st107;
	goto tr147;
st108:
	if ( ++p == pe )
		goto _test_eof108;
case 108:
	switch( (*p) ) {
		case 33: goto st108;
		case 44: goto st108;
		case 46: goto st108;
		case 63: goto st108;
	}
	if ( (*p) > 41 ) {
		if ( 58 <= (*p) && (*p) <= 59 )
			goto st108;
	} else if ( (*p) >= 40 )
		goto st108;
	goto tr149;
st109:
	if ( ++p == pe )
		goto _test_eof109;
case 109:
	switch( (*p) ) {
		case 43: goto st109;
		case 45: goto st109;
		case 47: goto st109;
		case 64: goto st109;
		case 92: goto st109;
		case 126: goto st109;
	}
	if ( (*p) > 37 ) {
		if ( 94 <= (*p) && (*p) <= 95 )
			goto st109;
	} else if ( (*p) >= 36 )
		goto st109;
	goto tr150;
tr125:
#line 1 "NONE"
	{te = p+1;}
	goto st110;
st110:
	if ( ++p == pe )
		goto _test_eof110;
case 110:
#line 938 "wikitext_ragel.c"
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
	goto tr151;
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
st111:
	if ( ++p == pe )
		goto _test_eof111;
case 111:
	if ( (*p) == 39 )
		goto st112;
	goto tr155;
st112:
	if ( ++p == pe )
		goto _test_eof112;
case 112:
	if ( (*p) == 39 )
		goto st113;
	goto tr155;
st113:
	if ( ++p == pe )
		goto _test_eof113;
case 113:
	if ( (*p) == 39 )
		goto st114;
	goto tr155;
st114:
	if ( ++p == pe )
		goto _test_eof114;
case 114:
	if ( (*p) == 39 )
		goto tr159;
	goto tr155;
tr128:
#line 1 "NONE"
	{te = p+1;}
#line 504 "wikitext_ragel.rl"
	{act = 53;}
	goto st115;
st115:
	if ( ++p == pe )
		goto _test_eof115;
case 115:
#line 1175 "wikitext_ragel.c"
	switch( (*p) ) {
		case 43: goto st109;
		case 45: goto tr128;
		case 47: goto st109;
		case 64: goto tr160;
		case 92: goto st109;
		case 94: goto st109;
		case 95: goto tr128;
		case 126: goto st109;
	}
	if ( (*p) < 46 ) {
		if ( 36 <= (*p) && (*p) <= 37 )
			goto st109;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st20;
		} else if ( (*p) >= 65 )
			goto st20;
	} else
		goto st20;
	goto tr150;
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
#line 316 "wikitext_ragel.rl"
	{act = 24;}
	goto st116;
st116:
	if ( ++p == pe )
		goto _test_eof116;
case 116:
#line 1284 "wikitext_ragel.c"
	if ( (*p) == 46 )
		goto st23;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st22;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr162;
	} else
		goto tr162;
	goto tr161;
tr162:
#line 1 "NONE"
	{te = p+1;}
#line 316 "wikitext_ragel.rl"
	{act = 24;}
	goto st117;
st117:
	if ( ++p == pe )
		goto _test_eof117;
case 117:
#line 1306 "wikitext_ragel.c"
	if ( (*p) == 46 )
		goto st23;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st22;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr163;
	} else
		goto tr163;
	goto tr161;
tr163:
#line 1 "NONE"
	{te = p+1;}
#line 316 "wikitext_ragel.rl"
	{act = 24;}
	goto st118;
st118:
	if ( ++p == pe )
		goto _test_eof118;
case 118:
#line 1328 "wikitext_ragel.c"
	if ( (*p) == 46 )
		goto st23;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st22;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr164;
	} else
		goto tr164;
	goto tr161;
tr164:
#line 1 "NONE"
	{te = p+1;}
#line 316 "wikitext_ragel.rl"
	{act = 24;}
	goto st119;
st119:
	if ( ++p == pe )
		goto _test_eof119;
case 119:
#line 1350 "wikitext_ragel.c"
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
	goto tr161;
tr160:
#line 1 "NONE"
	{te = p+1;}
#line 504 "wikitext_ragel.rl"
	{act = 53;}
	goto st120;
st120:
	if ( ++p == pe )
		goto _test_eof120;
case 120:
#line 1372 "wikitext_ragel.c"
	switch( (*p) ) {
		case 43: goto st109;
		case 45: goto st109;
		case 47: goto st109;
		case 64: goto st109;
		case 92: goto st109;
		case 126: goto st109;
	}
	if ( (*p) < 65 ) {
		if ( (*p) > 37 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st22;
		} else if ( (*p) >= 36 )
			goto st109;
	} else if ( (*p) > 90 ) {
		if ( (*p) > 95 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st22;
		} else if ( (*p) >= 94 )
			goto st109;
	} else
		goto st22;
	goto tr150;
tr129:
#line 1 "NONE"
	{te = p+1;}
#line 486 "wikitext_ragel.rl"
	{act = 51;}
	goto st121;
st121:
	if ( ++p == pe )
		goto _test_eof121;
case 121:
#line 1406 "wikitext_ragel.c"
	switch( (*p) ) {
		case 33: goto st108;
		case 44: goto st108;
		case 45: goto st20;
		case 46: goto tr129;
		case 63: goto st108;
		case 64: goto st21;
		case 95: goto st20;
	}
	if ( (*p) < 58 ) {
		if ( (*p) > 41 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st20;
		} else if ( (*p) >= 40 )
			goto st108;
	} else if ( (*p) > 59 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st20;
		} else if ( (*p) >= 65 )
			goto st20;
	} else
		goto st108;
	goto tr149;
st122:
	if ( ++p == pe )
		goto _test_eof122;
case 122:
	switch( (*p) ) {
		case 43: goto st109;
		case 45: goto st123;
		case 47: goto st109;
		case 64: goto st109;
		case 92: goto st109;
		case 94: goto st109;
		case 95: goto st123;
		case 126: goto st109;
	}
	if ( (*p) < 46 ) {
		if ( 36 <= (*p) && (*p) <= 37 )
			goto st109;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st124;
		} else if ( (*p) >= 65 )
			goto st124;
	} else
		goto st124;
	goto tr165;
st123:
	if ( ++p == pe )
		goto _test_eof123;
case 123:
	switch( (*p) ) {
		case 43: goto st109;
		case 45: goto st123;
		case 47: goto st122;
		case 64: goto st109;
		case 92: goto st109;
		case 94: goto st109;
		case 95: goto st123;
		case 126: goto st109;
	}
	if ( (*p) < 46 ) {
		if ( 36 <= (*p) && (*p) <= 37 )
			goto st109;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st124;
		} else if ( (*p) >= 65 )
			goto st124;
	} else
		goto st124;
	goto tr165;
st124:
	if ( ++p == pe )
		goto _test_eof124;
case 124:
	switch( (*p) ) {
		case 47: goto st125;
		case 95: goto st124;
	}
	if ( (*p) < 65 ) {
		if ( 45 <= (*p) && (*p) <= 57 )
			goto st124;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st124;
	} else
		goto st124;
	goto tr165;
st125:
	if ( ++p == pe )
		goto _test_eof125;
case 125:
	if ( (*p) == 95 )
		goto st124;
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st124;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st124;
		} else if ( (*p) >= 65 )
			goto st124;
	} else
		goto st124;
	goto tr165;
tr131:
#line 1 "NONE"
	{te = p+1;}
#line 492 "wikitext_ragel.rl"
	{act = 52;}
	goto st126;
st126:
	if ( ++p == pe )
		goto _test_eof126;
case 126:
#line 1528 "wikitext_ragel.c"
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
				goto tr131;
		} else if ( (*p) >= 65 )
			goto tr131;
	} else
		goto tr131;
	goto tr169;
st127:
	if ( ++p == pe )
		goto _test_eof127;
case 127:
	switch( (*p) ) {
		case 33: goto tr171;
		case 47: goto tr172;
		case 66: goto tr174;
		case 69: goto tr175;
		case 77: goto tr176;
		case 78: goto tr177;
		case 80: goto tr178;
		case 83: goto tr179;
		case 84: goto tr180;
		case 98: goto tr174;
		case 101: goto tr175;
		case 109: goto tr176;
		case 110: goto tr177;
		case 112: goto tr181;
		case 115: goto tr179;
		case 116: goto tr180;
	}
	if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr173;
	} else if ( (*p) >= 65 )
		goto tr173;
	goto tr170;
tr172:
#line 1 "NONE"
	{te = p+1;}
	goto st128;
st128:
	if ( ++p == pe )
		goto _test_eof128;
case 128:
#line 1581 "wikitext_ragel.c"
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
	goto tr182;
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
		case 84: goto st57;
		case 116: goto st57;
	}
	goto tr30;
st57:
	if ( ++p == pe )
		goto _test_eof57;
case 57:
	if ( (*p) == 62 )
		goto tr63;
	goto tr30;
tr174:
#line 1 "NONE"
	{te = p+1;}
	goto st129;
st129:
	if ( ++p == pe )
		goto _test_eof129;
case 129:
#line 1890 "wikitext_ragel.c"
	switch( (*p) ) {
		case 76: goto st58;
		case 108: goto st58;
	}
	goto tr190;
st58:
	if ( ++p == pe )
		goto _test_eof58;
case 58:
	switch( (*p) ) {
		case 79: goto st59;
		case 111: goto st59;
	}
	goto tr64;
st59:
	if ( ++p == pe )
		goto _test_eof59;
case 59:
	switch( (*p) ) {
		case 67: goto st60;
		case 99: goto st60;
	}
	goto tr64;
st60:
	if ( ++p == pe )
		goto _test_eof60;
case 60:
	switch( (*p) ) {
		case 75: goto st61;
		case 107: goto st61;
	}
	goto tr64;
st61:
	if ( ++p == pe )
		goto _test_eof61;
case 61:
	switch( (*p) ) {
		case 81: goto st62;
		case 113: goto st62;
	}
	goto tr64;
st62:
	if ( ++p == pe )
		goto _test_eof62;
case 62:
	switch( (*p) ) {
		case 85: goto st63;
		case 117: goto st63;
	}
	goto tr64;
st63:
	if ( ++p == pe )
		goto _test_eof63;
case 63:
	switch( (*p) ) {
		case 79: goto st64;
		case 111: goto st64;
	}
	goto tr64;
st64:
	if ( ++p == pe )
		goto _test_eof64;
case 64:
	switch( (*p) ) {
		case 84: goto st65;
		case 116: goto st65;
	}
	goto tr64;
st65:
	if ( ++p == pe )
		goto _test_eof65;
case 65:
	switch( (*p) ) {
		case 69: goto st66;
		case 101: goto st66;
	}
	goto tr64;
st66:
	if ( ++p == pe )
		goto _test_eof66;
case 66:
	if ( (*p) == 62 )
		goto tr73;
	goto tr64;
tr175:
#line 1 "NONE"
	{te = p+1;}
	goto st130;
st130:
	if ( ++p == pe )
		goto _test_eof130;
case 130:
#line 1983 "wikitext_ragel.c"
	switch( (*p) ) {
		case 77: goto st67;
		case 109: goto st67;
	}
	goto tr190;
st67:
	if ( ++p == pe )
		goto _test_eof67;
case 67:
	if ( (*p) == 62 )
		goto tr74;
	goto tr64;
tr176:
#line 1 "NONE"
	{te = p+1;}
	goto st131;
st131:
	if ( ++p == pe )
		goto _test_eof131;
case 131:
#line 2004 "wikitext_ragel.c"
	switch( (*p) ) {
		case 65: goto st68;
		case 97: goto st68;
	}
	goto tr190;
st68:
	if ( ++p == pe )
		goto _test_eof68;
case 68:
	switch( (*p) ) {
		case 84: goto st69;
		case 116: goto st69;
	}
	goto tr64;
st69:
	if ( ++p == pe )
		goto _test_eof69;
case 69:
	switch( (*p) ) {
		case 72: goto st70;
		case 104: goto st70;
	}
	goto tr64;
st70:
	if ( ++p == pe )
		goto _test_eof70;
case 70:
	if ( (*p) == 62 )
		goto tr77;
	goto tr64;
tr177:
#line 1 "NONE"
	{te = p+1;}
	goto st132;
st132:
	if ( ++p == pe )
		goto _test_eof132;
case 132:
#line 2043 "wikitext_ragel.c"
	switch( (*p) ) {
		case 79: goto st71;
		case 111: goto st71;
	}
	goto tr190;
st71:
	if ( ++p == pe )
		goto _test_eof71;
case 71:
	switch( (*p) ) {
		case 87: goto st72;
		case 119: goto st72;
	}
	goto tr64;
st72:
	if ( ++p == pe )
		goto _test_eof72;
case 72:
	switch( (*p) ) {
		case 73: goto st73;
		case 105: goto st73;
	}
	goto tr64;
st73:
	if ( ++p == pe )
		goto _test_eof73;
case 73:
	switch( (*p) ) {
		case 75: goto st74;
		case 107: goto st74;
	}
	goto tr64;
st74:
	if ( ++p == pe )
		goto _test_eof74;
case 74:
	switch( (*p) ) {
		case 73: goto st75;
		case 105: goto st75;
	}
	goto tr64;
st75:
	if ( ++p == pe )
		goto _test_eof75;
case 75:
	if ( (*p) == 62 )
		goto tr82;
	goto tr64;
tr178:
#line 1 "NONE"
	{te = p+1;}
	goto st133;
st133:
	if ( ++p == pe )
		goto _test_eof133;
case 133:
#line 2100 "wikitext_ragel.c"
	switch( (*p) ) {
		case 82: goto st76;
		case 114: goto st76;
	}
	goto tr190;
st76:
	if ( ++p == pe )
		goto _test_eof76;
case 76:
	switch( (*p) ) {
		case 69: goto st77;
		case 101: goto st77;
	}
	goto tr64;
st77:
	if ( ++p == pe )
		goto _test_eof77;
case 77:
	if ( (*p) == 62 )
		goto tr84;
	goto tr64;
tr179:
#line 1 "NONE"
	{te = p+1;}
	goto st134;
st134:
	if ( ++p == pe )
		goto _test_eof134;
case 134:
#line 2130 "wikitext_ragel.c"
	switch( (*p) ) {
		case 84: goto st78;
		case 116: goto st78;
	}
	goto tr190;
st78:
	if ( ++p == pe )
		goto _test_eof78;
case 78:
	switch( (*p) ) {
		case 82: goto st79;
		case 114: goto st79;
	}
	goto tr64;
st79:
	if ( ++p == pe )
		goto _test_eof79;
case 79:
	switch( (*p) ) {
		case 79: goto st80;
		case 111: goto st80;
	}
	goto tr64;
st80:
	if ( ++p == pe )
		goto _test_eof80;
case 80:
	switch( (*p) ) {
		case 78: goto st81;
		case 110: goto st81;
	}
	goto tr64;
st81:
	if ( ++p == pe )
		goto _test_eof81;
case 81:
	switch( (*p) ) {
		case 71: goto st82;
		case 103: goto st82;
	}
	goto tr64;
st82:
	if ( ++p == pe )
		goto _test_eof82;
case 82:
	if ( (*p) == 62 )
		goto tr89;
	goto tr64;
tr180:
#line 1 "NONE"
	{te = p+1;}
	goto st135;
st135:
	if ( ++p == pe )
		goto _test_eof135;
case 135:
#line 2187 "wikitext_ragel.c"
	switch( (*p) ) {
		case 84: goto st83;
		case 116: goto st83;
	}
	goto tr190;
st83:
	if ( ++p == pe )
		goto _test_eof83;
case 83:
	if ( (*p) == 62 )
		goto tr90;
	goto tr64;
tr181:
#line 1 "NONE"
	{te = p+1;}
	goto st136;
st136:
	if ( ++p == pe )
		goto _test_eof136;
case 136:
#line 2208 "wikitext_ragel.c"
	switch( (*p) ) {
		case 82: goto st76;
		case 114: goto st84;
	}
	goto tr190;
st84:
	if ( ++p == pe )
		goto _test_eof84;
case 84:
	switch( (*p) ) {
		case 69: goto st77;
		case 101: goto st85;
	}
	goto tr64;
st85:
	if ( ++p == pe )
		goto _test_eof85;
case 85:
	switch( (*p) ) {
		case 32: goto st86;
		case 62: goto tr84;
	}
	goto tr64;
st86:
	if ( ++p == pe )
		goto _test_eof86;
case 86:
	if ( (*p) == 108 )
		goto st87;
	goto tr64;
st87:
	if ( ++p == pe )
		goto _test_eof87;
case 87:
	if ( (*p) == 97 )
		goto st88;
	goto tr64;
st88:
	if ( ++p == pe )
		goto _test_eof88;
case 88:
	if ( (*p) == 110 )
		goto st89;
	goto tr64;
st89:
	if ( ++p == pe )
		goto _test_eof89;
case 89:
	if ( (*p) == 103 )
		goto st90;
	goto tr64;
st90:
	if ( ++p == pe )
		goto _test_eof90;
case 90:
	if ( (*p) == 61 )
		goto st91;
	goto tr64;
st91:
	if ( ++p == pe )
		goto _test_eof91;
case 91:
	if ( (*p) == 34 )
		goto st92;
	goto tr64;
st92:
	if ( ++p == pe )
		goto _test_eof92;
case 92:
	if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st93;
	} else if ( (*p) >= 65 )
		goto st93;
	goto tr64;
st93:
	if ( ++p == pe )
		goto _test_eof93;
case 93:
	if ( (*p) == 34 )
		goto st94;
	if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st93;
	} else if ( (*p) >= 65 )
		goto st93;
	goto tr64;
st94:
	if ( ++p == pe )
		goto _test_eof94;
case 94:
	if ( (*p) == 62 )
		goto tr101;
	goto tr64;
tr133:
#line 45 "wikitext_ragel.rl"
	{
        MARK();
    }
	goto st137;
st137:
	if ( ++p == pe )
		goto _test_eof137;
case 137:
#line 2313 "wikitext_ragel.c"
	switch( (*p) ) {
		case 32: goto st138;
		case 61: goto tr133;
	}
	goto tr199;
st138:
	if ( ++p == pe )
		goto _test_eof138;
case 138:
	if ( (*p) == 32 )
		goto st138;
	goto tr199;
tr134:
#line 45 "wikitext_ragel.rl"
	{
        MARK();
    }
	goto st139;
st139:
	if ( ++p == pe )
		goto _test_eof139;
case 139:
#line 2336 "wikitext_ragel.c"
	if ( (*p) == 32 )
		goto tr202;
	goto tr201;
tr135:
#line 1 "NONE"
	{te = p+1;}
#line 492 "wikitext_ragel.rl"
	{act = 52;}
	goto st140;
st140:
	if ( ++p == pe )
		goto _test_eof140;
case 140:
#line 2350 "wikitext_ragel.c"
	switch( (*p) ) {
		case 64: goto st21;
		case 84: goto tr203;
		case 95: goto st20;
		case 116: goto tr203;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st20;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr131;
		} else if ( (*p) >= 65 )
			goto tr131;
	} else
		goto tr131;
	goto tr169;
tr203:
#line 1 "NONE"
	{te = p+1;}
#line 492 "wikitext_ragel.rl"
	{act = 52;}
	goto st141;
st141:
	if ( ++p == pe )
		goto _test_eof141;
case 141:
#line 2379 "wikitext_ragel.c"
	switch( (*p) ) {
		case 64: goto st21;
		case 80: goto tr204;
		case 95: goto st20;
		case 112: goto tr204;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st20;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr131;
		} else if ( (*p) >= 65 )
			goto tr131;
	} else
		goto tr131;
	goto tr169;
tr204:
#line 1 "NONE"
	{te = p+1;}
#line 492 "wikitext_ragel.rl"
	{act = 52;}
	goto st142;
st142:
	if ( ++p == pe )
		goto _test_eof142;
case 142:
#line 2408 "wikitext_ragel.c"
	switch( (*p) ) {
		case 58: goto st95;
		case 64: goto st21;
		case 95: goto st20;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st20;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr131;
		} else if ( (*p) >= 65 )
			goto tr131;
	} else
		goto tr131;
	goto tr169;
st95:
	if ( ++p == pe )
		goto _test_eof95;
case 95:
	if ( (*p) == 47 )
		goto st96;
	goto tr102;
st96:
	if ( ++p == pe )
		goto _test_eof96;
case 96:
	if ( (*p) == 47 )
		goto st97;
	goto tr102;
st97:
	if ( ++p == pe )
		goto _test_eof97;
case 97:
	switch( (*p) ) {
		case 45: goto tr105;
		case 61: goto tr105;
		case 95: goto tr105;
		case 126: goto tr105;
	}
	if ( (*p) < 47 ) {
		if ( (*p) > 40 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr105;
		} else if ( (*p) >= 35 )
			goto tr105;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr105;
		} else if ( (*p) >= 64 )
			goto tr105;
	} else
		goto tr105;
	goto tr102;
tr105:
#line 1 "NONE"
	{te = p+1;}
	goto st143;
st143:
	if ( ++p == pe )
		goto _test_eof143;
case 143:
#line 2473 "wikitext_ragel.c"
	switch( (*p) ) {
		case 33: goto st98;
		case 41: goto st98;
		case 44: goto st98;
		case 46: goto st98;
		case 61: goto tr105;
		case 63: goto st98;
		case 95: goto tr105;
		case 126: goto tr105;
	}
	if ( (*p) < 58 ) {
		if ( 35 <= (*p) && (*p) <= 57 )
			goto tr105;
	} else if ( (*p) > 59 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr105;
		} else if ( (*p) >= 64 )
			goto tr105;
	} else
		goto st98;
	goto tr206;
st98:
	if ( ++p == pe )
		goto _test_eof98;
case 98:
	switch( (*p) ) {
		case 33: goto st98;
		case 41: goto st98;
		case 44: goto st98;
		case 46: goto st98;
		case 61: goto tr105;
		case 63: goto st98;
		case 95: goto tr105;
		case 126: goto tr105;
	}
	if ( (*p) < 58 ) {
		if ( 35 <= (*p) && (*p) <= 57 )
			goto tr105;
	} else if ( (*p) > 59 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr105;
		} else if ( (*p) >= 64 )
			goto tr105;
	} else
		goto st98;
	goto tr106;
tr136:
#line 1 "NONE"
	{te = p+1;}
#line 492 "wikitext_ragel.rl"
	{act = 52;}
	goto st144;
st144:
	if ( ++p == pe )
		goto _test_eof144;
case 144:
#line 2532 "wikitext_ragel.c"
	switch( (*p) ) {
		case 64: goto st21;
		case 84: goto tr207;
		case 95: goto st20;
		case 116: goto tr207;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st20;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr131;
		} else if ( (*p) >= 65 )
			goto tr131;
	} else
		goto tr131;
	goto tr169;
tr207:
#line 1 "NONE"
	{te = p+1;}
#line 492 "wikitext_ragel.rl"
	{act = 52;}
	goto st145;
st145:
	if ( ++p == pe )
		goto _test_eof145;
case 145:
#line 2561 "wikitext_ragel.c"
	switch( (*p) ) {
		case 64: goto st21;
		case 84: goto tr208;
		case 95: goto st20;
		case 116: goto tr208;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st20;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr131;
		} else if ( (*p) >= 65 )
			goto tr131;
	} else
		goto tr131;
	goto tr169;
tr208:
#line 1 "NONE"
	{te = p+1;}
#line 492 "wikitext_ragel.rl"
	{act = 52;}
	goto st146;
st146:
	if ( ++p == pe )
		goto _test_eof146;
case 146:
#line 2590 "wikitext_ragel.c"
	switch( (*p) ) {
		case 64: goto st21;
		case 80: goto tr209;
		case 95: goto st20;
		case 112: goto tr209;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st20;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr131;
		} else if ( (*p) >= 65 )
			goto tr131;
	} else
		goto tr131;
	goto tr169;
tr209:
#line 1 "NONE"
	{te = p+1;}
#line 492 "wikitext_ragel.rl"
	{act = 52;}
	goto st147;
st147:
	if ( ++p == pe )
		goto _test_eof147;
case 147:
#line 2619 "wikitext_ragel.c"
	switch( (*p) ) {
		case 58: goto st95;
		case 64: goto st21;
		case 83: goto tr204;
		case 95: goto st20;
		case 115: goto tr204;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st20;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr131;
		} else if ( (*p) >= 65 )
			goto tr131;
	} else
		goto tr131;
	goto tr169;
tr137:
#line 1 "NONE"
	{te = p+1;}
#line 492 "wikitext_ragel.rl"
	{act = 52;}
	goto st148;
st148:
	if ( ++p == pe )
		goto _test_eof148;
case 148:
#line 2649 "wikitext_ragel.c"
	switch( (*p) ) {
		case 64: goto st21;
		case 65: goto tr210;
		case 95: goto st20;
		case 97: goto tr210;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st20;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 98 <= (*p) && (*p) <= 122 )
				goto tr131;
		} else if ( (*p) >= 66 )
			goto tr131;
	} else
		goto tr131;
	goto tr169;
tr210:
#line 1 "NONE"
	{te = p+1;}
#line 492 "wikitext_ragel.rl"
	{act = 52;}
	goto st149;
st149:
	if ( ++p == pe )
		goto _test_eof149;
case 149:
#line 2678 "wikitext_ragel.c"
	switch( (*p) ) {
		case 64: goto st21;
		case 73: goto tr211;
		case 95: goto st20;
		case 105: goto tr211;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st20;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr131;
		} else if ( (*p) >= 65 )
			goto tr131;
	} else
		goto tr131;
	goto tr169;
tr211:
#line 1 "NONE"
	{te = p+1;}
#line 492 "wikitext_ragel.rl"
	{act = 52;}
	goto st150;
st150:
	if ( ++p == pe )
		goto _test_eof150;
case 150:
#line 2707 "wikitext_ragel.c"
	switch( (*p) ) {
		case 64: goto st21;
		case 76: goto tr212;
		case 95: goto st20;
		case 108: goto tr212;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st20;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr131;
		} else if ( (*p) >= 65 )
			goto tr131;
	} else
		goto tr131;
	goto tr169;
tr212:
#line 1 "NONE"
	{te = p+1;}
#line 492 "wikitext_ragel.rl"
	{act = 52;}
	goto st151;
st151:
	if ( ++p == pe )
		goto _test_eof151;
case 151:
#line 2736 "wikitext_ragel.c"
	switch( (*p) ) {
		case 64: goto st21;
		case 84: goto tr213;
		case 95: goto st20;
		case 116: goto tr213;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st20;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr131;
		} else if ( (*p) >= 65 )
			goto tr131;
	} else
		goto tr131;
	goto tr169;
tr213:
#line 1 "NONE"
	{te = p+1;}
#line 492 "wikitext_ragel.rl"
	{act = 52;}
	goto st152;
st152:
	if ( ++p == pe )
		goto _test_eof152;
case 152:
#line 2765 "wikitext_ragel.c"
	switch( (*p) ) {
		case 64: goto st21;
		case 79: goto tr214;
		case 95: goto st20;
		case 111: goto tr214;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st20;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr131;
		} else if ( (*p) >= 65 )
			goto tr131;
	} else
		goto tr131;
	goto tr169;
tr214:
#line 1 "NONE"
	{te = p+1;}
#line 492 "wikitext_ragel.rl"
	{act = 52;}
	goto st153;
st153:
	if ( ++p == pe )
		goto _test_eof153;
case 153:
#line 2794 "wikitext_ragel.c"
	switch( (*p) ) {
		case 58: goto st99;
		case 64: goto st21;
		case 95: goto st20;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st20;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr131;
		} else if ( (*p) >= 65 )
			goto tr131;
	} else
		goto tr131;
	goto tr169;
st99:
	if ( ++p == pe )
		goto _test_eof99;
case 99:
	if ( (*p) == 95 )
		goto st100;
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st100;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st100;
		} else if ( (*p) >= 65 )
			goto st100;
	} else
		goto st100;
	goto tr102;
st100:
	if ( ++p == pe )
		goto _test_eof100;
case 100:
	switch( (*p) ) {
		case 64: goto st101;
		case 95: goto st100;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st100;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st100;
		} else if ( (*p) >= 65 )
			goto st100;
	} else
		goto st100;
	goto tr102;
st101:
	if ( ++p == pe )
		goto _test_eof101;
case 101:
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st102;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st102;
	} else
		goto st102;
	goto tr102;
st102:
	if ( ++p == pe )
		goto _test_eof102;
case 102:
	if ( (*p) == 46 )
		goto st103;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st102;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st102;
	} else
		goto st102;
	goto tr23;
st103:
	if ( ++p == pe )
		goto _test_eof103;
case 103:
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st102;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st104;
	} else
		goto st104;
	goto tr23;
st104:
	if ( ++p == pe )
		goto _test_eof104;
case 104:
	if ( (*p) == 46 )
		goto st103;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st102;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr113;
	} else
		goto tr113;
	goto tr23;
tr113:
#line 1 "NONE"
	{te = p+1;}
#line 310 "wikitext_ragel.rl"
	{act = 23;}
	goto st154;
st154:
	if ( ++p == pe )
		goto _test_eof154;
case 154:
#line 2916 "wikitext_ragel.c"
	if ( (*p) == 46 )
		goto st103;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st102;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr216;
	} else
		goto tr216;
	goto tr206;
tr216:
#line 1 "NONE"
	{te = p+1;}
#line 310 "wikitext_ragel.rl"
	{act = 23;}
	goto st155;
st155:
	if ( ++p == pe )
		goto _test_eof155;
case 155:
#line 2938 "wikitext_ragel.c"
	if ( (*p) == 46 )
		goto st103;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st102;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr217;
	} else
		goto tr217;
	goto tr206;
tr217:
#line 1 "NONE"
	{te = p+1;}
#line 310 "wikitext_ragel.rl"
	{act = 23;}
	goto st156;
st156:
	if ( ++p == pe )
		goto _test_eof156;
case 156:
#line 2960 "wikitext_ragel.c"
	if ( (*p) == 46 )
		goto st103;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st102;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr218;
	} else
		goto tr218;
	goto tr206;
tr218:
#line 1 "NONE"
	{te = p+1;}
#line 310 "wikitext_ragel.rl"
	{act = 23;}
	goto st157;
st157:
	if ( ++p == pe )
		goto _test_eof157;
case 157:
#line 2982 "wikitext_ragel.c"
	if ( (*p) == 46 )
		goto st103;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st102;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st102;
	} else
		goto st102;
	goto tr206;
tr138:
#line 1 "NONE"
	{te = p+1;}
#line 492 "wikitext_ragel.rl"
	{act = 52;}
	goto st158;
st158:
	if ( ++p == pe )
		goto _test_eof158;
case 158:
#line 3004 "wikitext_ragel.c"
	switch( (*p) ) {
		case 64: goto st21;
		case 86: goto tr219;
		case 95: goto st20;
		case 118: goto tr219;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st20;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr131;
		} else if ( (*p) >= 65 )
			goto tr131;
	} else
		goto tr131;
	goto tr169;
tr219:
#line 1 "NONE"
	{te = p+1;}
#line 492 "wikitext_ragel.rl"
	{act = 52;}
	goto st159;
st159:
	if ( ++p == pe )
		goto _test_eof159;
case 159:
#line 3033 "wikitext_ragel.c"
	switch( (*p) ) {
		case 64: goto st21;
		case 78: goto tr204;
		case 95: goto st20;
		case 110: goto tr204;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st20;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr131;
		} else if ( (*p) >= 65 )
			goto tr131;
	} else
		goto tr131;
	goto tr169;
st160:
	if ( ++p == pe )
		goto _test_eof160;
case 160:
	if ( (*p) == 91 )
		goto tr221;
	goto tr220;
st161:
	if ( ++p == pe )
		goto _test_eof161;
case 161:
	if ( (*p) == 93 )
		goto tr223;
	goto tr222;
st162:
	if ( ++p == pe )
		goto _test_eof162;
case 162:
	switch( (*p) ) {
		case 123: goto tr225;
		case 124: goto tr226;
	}
	goto tr224;
st163:
	if ( ++p == pe )
		goto _test_eof163;
case 163:
	if ( (*p) == 125 )
		goto st164;
	goto tr227;
st164:
	if ( ++p == pe )
		goto _test_eof164;
case 164:
	if ( (*p) == 125 )
		goto tr230;
	goto tr229;
st165:
	if ( ++p == pe )
		goto _test_eof165;
case 165:
	if ( (*p) == 125 )
		goto tr232;
	goto tr231;
	}
	_test_eof105: cs = 105; goto _test_eof; 
	_test_eof1: cs = 1; goto _test_eof; 
	_test_eof2: cs = 2; goto _test_eof; 
	_test_eof3: cs = 3; goto _test_eof; 
	_test_eof4: cs = 4; goto _test_eof; 
	_test_eof5: cs = 5; goto _test_eof; 
	_test_eof6: cs = 6; goto _test_eof; 
	_test_eof106: cs = 106; goto _test_eof; 
	_test_eof107: cs = 107; goto _test_eof; 
	_test_eof108: cs = 108; goto _test_eof; 
	_test_eof109: cs = 109; goto _test_eof; 
	_test_eof110: cs = 110; goto _test_eof; 
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
	_test_eof111: cs = 111; goto _test_eof; 
	_test_eof112: cs = 112; goto _test_eof; 
	_test_eof113: cs = 113; goto _test_eof; 
	_test_eof114: cs = 114; goto _test_eof; 
	_test_eof115: cs = 115; goto _test_eof; 
	_test_eof20: cs = 20; goto _test_eof; 
	_test_eof21: cs = 21; goto _test_eof; 
	_test_eof22: cs = 22; goto _test_eof; 
	_test_eof23: cs = 23; goto _test_eof; 
	_test_eof24: cs = 24; goto _test_eof; 
	_test_eof116: cs = 116; goto _test_eof; 
	_test_eof117: cs = 117; goto _test_eof; 
	_test_eof118: cs = 118; goto _test_eof; 
	_test_eof119: cs = 119; goto _test_eof; 
	_test_eof120: cs = 120; goto _test_eof; 
	_test_eof121: cs = 121; goto _test_eof; 
	_test_eof122: cs = 122; goto _test_eof; 
	_test_eof123: cs = 123; goto _test_eof; 
	_test_eof124: cs = 124; goto _test_eof; 
	_test_eof125: cs = 125; goto _test_eof; 
	_test_eof126: cs = 126; goto _test_eof; 
	_test_eof127: cs = 127; goto _test_eof; 
	_test_eof128: cs = 128; goto _test_eof; 
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
	_test_eof129: cs = 129; goto _test_eof; 
	_test_eof58: cs = 58; goto _test_eof; 
	_test_eof59: cs = 59; goto _test_eof; 
	_test_eof60: cs = 60; goto _test_eof; 
	_test_eof61: cs = 61; goto _test_eof; 
	_test_eof62: cs = 62; goto _test_eof; 
	_test_eof63: cs = 63; goto _test_eof; 
	_test_eof64: cs = 64; goto _test_eof; 
	_test_eof65: cs = 65; goto _test_eof; 
	_test_eof66: cs = 66; goto _test_eof; 
	_test_eof130: cs = 130; goto _test_eof; 
	_test_eof67: cs = 67; goto _test_eof; 
	_test_eof131: cs = 131; goto _test_eof; 
	_test_eof68: cs = 68; goto _test_eof; 
	_test_eof69: cs = 69; goto _test_eof; 
	_test_eof70: cs = 70; goto _test_eof; 
	_test_eof132: cs = 132; goto _test_eof; 
	_test_eof71: cs = 71; goto _test_eof; 
	_test_eof72: cs = 72; goto _test_eof; 
	_test_eof73: cs = 73; goto _test_eof; 
	_test_eof74: cs = 74; goto _test_eof; 
	_test_eof75: cs = 75; goto _test_eof; 
	_test_eof133: cs = 133; goto _test_eof; 
	_test_eof76: cs = 76; goto _test_eof; 
	_test_eof77: cs = 77; goto _test_eof; 
	_test_eof134: cs = 134; goto _test_eof; 
	_test_eof78: cs = 78; goto _test_eof; 
	_test_eof79: cs = 79; goto _test_eof; 
	_test_eof80: cs = 80; goto _test_eof; 
	_test_eof81: cs = 81; goto _test_eof; 
	_test_eof82: cs = 82; goto _test_eof; 
	_test_eof135: cs = 135; goto _test_eof; 
	_test_eof83: cs = 83; goto _test_eof; 
	_test_eof136: cs = 136; goto _test_eof; 
	_test_eof84: cs = 84; goto _test_eof; 
	_test_eof85: cs = 85; goto _test_eof; 
	_test_eof86: cs = 86; goto _test_eof; 
	_test_eof87: cs = 87; goto _test_eof; 
	_test_eof88: cs = 88; goto _test_eof; 
	_test_eof89: cs = 89; goto _test_eof; 
	_test_eof90: cs = 90; goto _test_eof; 
	_test_eof91: cs = 91; goto _test_eof; 
	_test_eof92: cs = 92; goto _test_eof; 
	_test_eof93: cs = 93; goto _test_eof; 
	_test_eof94: cs = 94; goto _test_eof; 
	_test_eof137: cs = 137; goto _test_eof; 
	_test_eof138: cs = 138; goto _test_eof; 
	_test_eof139: cs = 139; goto _test_eof; 
	_test_eof140: cs = 140; goto _test_eof; 
	_test_eof141: cs = 141; goto _test_eof; 
	_test_eof142: cs = 142; goto _test_eof; 
	_test_eof95: cs = 95; goto _test_eof; 
	_test_eof96: cs = 96; goto _test_eof; 
	_test_eof97: cs = 97; goto _test_eof; 
	_test_eof143: cs = 143; goto _test_eof; 
	_test_eof98: cs = 98; goto _test_eof; 
	_test_eof144: cs = 144; goto _test_eof; 
	_test_eof145: cs = 145; goto _test_eof; 
	_test_eof146: cs = 146; goto _test_eof; 
	_test_eof147: cs = 147; goto _test_eof; 
	_test_eof148: cs = 148; goto _test_eof; 
	_test_eof149: cs = 149; goto _test_eof; 
	_test_eof150: cs = 150; goto _test_eof; 
	_test_eof151: cs = 151; goto _test_eof; 
	_test_eof152: cs = 152; goto _test_eof; 
	_test_eof153: cs = 153; goto _test_eof; 
	_test_eof99: cs = 99; goto _test_eof; 
	_test_eof100: cs = 100; goto _test_eof; 
	_test_eof101: cs = 101; goto _test_eof; 
	_test_eof102: cs = 102; goto _test_eof; 
	_test_eof103: cs = 103; goto _test_eof; 
	_test_eof104: cs = 104; goto _test_eof; 
	_test_eof154: cs = 154; goto _test_eof; 
	_test_eof155: cs = 155; goto _test_eof; 
	_test_eof156: cs = 156; goto _test_eof; 
	_test_eof157: cs = 157; goto _test_eof; 
	_test_eof158: cs = 158; goto _test_eof; 
	_test_eof159: cs = 159; goto _test_eof; 
	_test_eof160: cs = 160; goto _test_eof; 
	_test_eof161: cs = 161; goto _test_eof; 
	_test_eof162: cs = 162; goto _test_eof; 
	_test_eof163: cs = 163; goto _test_eof; 
	_test_eof164: cs = 164; goto _test_eof; 
	_test_eof165: cs = 165; goto _test_eof; 

	_test_eof: {}
	if ( p == eof )
	{
	switch ( cs ) {
	case 106: goto tr145;
	case 107: goto tr147;
	case 108: goto tr149;
	case 109: goto tr150;
	case 110: goto tr151;
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
	case 111: goto tr155;
	case 112: goto tr155;
	case 113: goto tr155;
	case 114: goto tr155;
	case 115: goto tr150;
	case 20: goto tr23;
	case 21: goto tr23;
	case 22: goto tr23;
	case 23: goto tr23;
	case 24: goto tr23;
	case 116: goto tr161;
	case 117: goto tr161;
	case 118: goto tr161;
	case 119: goto tr161;
	case 120: goto tr150;
	case 121: goto tr149;
	case 122: goto tr165;
	case 123: goto tr165;
	case 124: goto tr165;
	case 125: goto tr165;
	case 126: goto tr169;
	case 127: goto tr170;
	case 128: goto tr182;
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
	case 129: goto tr190;
	case 58: goto tr64;
	case 59: goto tr64;
	case 60: goto tr64;
	case 61: goto tr64;
	case 62: goto tr64;
	case 63: goto tr64;
	case 64: goto tr64;
	case 65: goto tr64;
	case 66: goto tr64;
	case 130: goto tr190;
	case 67: goto tr64;
	case 131: goto tr190;
	case 68: goto tr64;
	case 69: goto tr64;
	case 70: goto tr64;
	case 132: goto tr190;
	case 71: goto tr64;
	case 72: goto tr64;
	case 73: goto tr64;
	case 74: goto tr64;
	case 75: goto tr64;
	case 133: goto tr190;
	case 76: goto tr64;
	case 77: goto tr64;
	case 134: goto tr190;
	case 78: goto tr64;
	case 79: goto tr64;
	case 80: goto tr64;
	case 81: goto tr64;
	case 82: goto tr64;
	case 135: goto tr190;
	case 83: goto tr64;
	case 136: goto tr190;
	case 84: goto tr64;
	case 85: goto tr64;
	case 86: goto tr64;
	case 87: goto tr64;
	case 88: goto tr64;
	case 89: goto tr64;
	case 90: goto tr64;
	case 91: goto tr64;
	case 92: goto tr64;
	case 93: goto tr64;
	case 94: goto tr64;
	case 137: goto tr199;
	case 138: goto tr199;
	case 139: goto tr201;
	case 140: goto tr169;
	case 141: goto tr169;
	case 142: goto tr169;
	case 95: goto tr102;
	case 96: goto tr102;
	case 97: goto tr102;
	case 143: goto tr206;
	case 98: goto tr106;
	case 144: goto tr169;
	case 145: goto tr169;
	case 146: goto tr169;
	case 147: goto tr169;
	case 148: goto tr169;
	case 149: goto tr169;
	case 150: goto tr169;
	case 151: goto tr169;
	case 152: goto tr169;
	case 153: goto tr169;
	case 99: goto tr102;
	case 100: goto tr102;
	case 101: goto tr102;
	case 102: goto tr23;
	case 103: goto tr23;
	case 104: goto tr23;
	case 154: goto tr206;
	case 155: goto tr206;
	case 156: goto tr206;
	case 157: goto tr206;
	case 158: goto tr169;
	case 159: goto tr169;
	case 160: goto tr220;
	case 161: goto tr222;
	case 162: goto tr224;
	case 163: goto tr227;
	case 164: goto tr229;
	case 165: goto tr231;
	}
	}

	_out: {}
	}

#line 576 "wikitext_ragel.rl"
    if (cs == wikitext_error)
        rb_raise(eWikitextParserError, "failed before finding a token");
    else if (out->type == NO_TOKEN)
        rb_raise(eWikitextParserError, "failed to produce a token");
}
