/* -*- Mode: C; indent-tabs-mode:nil; c-basic-offset: 8-*- */

/*
 * This file is part of The Croco Library
 *
 * Copyright (C) 2002-2003 Dodji Seketeli <dodji@seketeli.org>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of version 2.1 of the GNU Lesser General Public
 * License as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
 * USA
 */


/*
 *$Id$
 */
#ifndef __CR_PARSER_H__
#define  __CR_PARSER_H__

#include <glib.h>
#include "cr-parser-input.h"
#include "cr-tknzr.h"
#include "cr-utils.h"
#include "cr-doc-handler.h"

G_BEGIN_DECLS

/**
 *@file
 *The declaration file
 *of the #CRParser class.
 */
typedef struct _CRParser CRParser ;
typedef struct _CRParserPriv CRParserPriv ;


/**
 *The implementation of
 *the SAC parser.
 *The Class is opaque
 *and must be manipulated through
 *the provided methods.
 */
struct _CRParser 
{
        CRParserPriv *priv ;
} ;

CRParser *
cr_parser_new (CRTknzr *a_tknzr) ;

CRParser *
cr_parser_new_from_buf (const guchar *a_buf, gulong a_len,
                        enum CREncoding a_enc, 
                        gboolean a_free_buf) ;
CRParser *
cr_parser_new_from_file (const guchar *a_file_uri, 
                         enum CREncoding a_enc) ;

CRParser *
cr_parser_new_from_input (CRInput *a_input) ;

enum CRStatus
cr_parser_set_tknzr (CRParser *a_this, CRTknzr *a_tknzr) ;

enum CRStatus
cr_parser_try_to_skip_spaces_and_comments (CRParser *a_this) ;


enum CRStatus
cr_parser_set_sac_handler (CRParser *a_this, 
                           CRDocHandler *a_handler) ;

enum CRStatus
cr_parser_get_sac_handler (CRParser *a_this, 
                           CRDocHandler **a_handler) ;
enum CRStatus
cr_parser_set_use_core_grammar (CRParser *a_this,
                                gboolean a_use_core_grammar) ;
enum CRStatus
cr_parser_get_use_core_grammar (CRParser *a_this,
                                gboolean *a_use_core_grammar) ;

enum CRStatus
cr_parser_parse (CRParser *a_this) ;
        
enum CRStatus
cr_parser_parse_file (CRParser *a_this, 
                      const guchar *a_file_uri, 
                      enum CREncoding a_enc) ;

enum CRStatus
cr_parser_parse_buf (CRParser *a_this, const guchar *a_buf, 
                     gulong a_len, enum CREncoding a_enc) ;

enum CRStatus
cr_parser_set_default_sac_handler (CRParser *a_this) ;


enum CRStatus
cr_parser_parse_declaration (CRParser *a_this, GString **a_property,
                             CRTerm **a_expr) ;
enum CRStatus
cr_parser_parse_ruleset (CRParser *a_this) ;

void
cr_parser_destroy (CRParser *a_this) ;
        
G_END_DECLS

#endif /*__CR_PARSER_H__*/
