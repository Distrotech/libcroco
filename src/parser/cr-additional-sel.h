/* -*- Mode: C; indent-tabs-mode:nil; c-basic-offset: 8-*- */

/*
 * This file is part of The Croco Library
 *
 * Copyright (C) 2002-2003 Dodji Seketeli <dodji at seketeli.org>
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

/**
 *@file
 *This file holds the declaration of the
 *#CRAddSel class. 
 */
#ifndef __CR_ADD_SEL_H__
#define __CR_ADD_SEL_H__

#include <stdio.h>
#include <glib.h>
#include "cr-utils.h"
#include "cr-attr-sel.h"
#include "cr-pseudo.h"

G_BEGIN_DECLS

enum AddSelectorType
{
        NO_ADD_SELECTOR = 0 ,
        CLASS_ADD_SELECTOR = 1 ,
        PSEUDO_CLASS_ADD_SELECTOR = 1 << 1,
        ID_ADD_SELECTOR = 1 << 3,
        ATTRIBUTE_ADD_SELECTOR = 1 << 4
} ;

union CRAdditionalSelectorContent
{
        GString *class_name ;
        GString *id_name ;
        CRPseudo *pseudo ;
        CRAttrSel *attr_sel ;
} ;

typedef struct _CRAdditionalSel CRAdditionalSel ;

/**
 *#CRAdditionalSel abstracts
 *an additionnal selector.
 *An additional selector is the selector part
 *that comes after the combination of type selectors.
 *It can be either "a class selector (the .class part),
 *a pseudo class selector, an attribute selector 
 *or an id selector.
 */
struct _CRAdditionalSel
{
        enum AddSelectorType type ;
        union CRAdditionalSelectorContent content ;

        CRAdditionalSel * next ;
        CRAdditionalSel * prev ;
} ;

CRAdditionalSel * cr_additional_sel_new (void) ;

CRAdditionalSel * cr_additional_sel_new_with_type  (enum AddSelectorType a_sel_type) ;

CRAdditionalSel * cr_additional_sel_append (CRAdditionalSel *a_this, 
                                            CRAdditionalSel *a_sel) ;

void cr_additional_sel_set_class_name (CRAdditionalSel *a_this,
                                       GString *a_class_name) ;

void cr_additional_sel_set_id_name (CRAdditionalSel *a_this,
                                    GString *a_id) ;

void cr_additional_sel_set_pseudo (CRAdditionalSel *a_this,
                                   CRPseudo *a_pseudo) ;

void cr_additional_sel_set_attr_sel (CRAdditionalSel *a_this,
                                     CRAttrSel *a_sel) ;

CRAdditionalSel * cr_additional_sel_prepend (CRAdditionalSel *a_this, 
                                             CRAdditionalSel *a_sel) ;

guchar * cr_additional_sel_to_string (CRAdditionalSel *a_this) ;

void cr_additional_sel_dump (CRAdditionalSel *a_this, FILE *a_fp) ;

void cr_additional_sel_destroy (CRAdditionalSel *a_this) ;

G_END_DECLS

#endif /*__CR_ADD_SEL_H*/
