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

#include <string.h>
#include <glib.h>
#include "cr-simple-sel.h"


/**
 *The constructor of #CRSimpleSel.
 *
 *@return the new instance of #CRSimpleSel.
 */
CRSimpleSel *
cr_simple_sel_new (void)
{
        CRSimpleSel *result = NULL ;

        result = g_try_malloc (sizeof (CRSimpleSel)) ;
        if (!result)
        {
                cr_utils_trace_info ("Out of memory") ;
                return NULL ;
        }
        memset (result, 0, sizeof (CRSimpleSel)) ;

        return result ;
}

/**
 *Appends a simpe selector to the current list of simple selector.
 *
 *@param a_this the this pointer of the current instance of #CRSimpleSel.
 *@param a_sel the simple selector to append.
 *@return the new list upon successfull completion, an error code otherwise.
 */
CRSimpleSel *
cr_simple_sel_append_simple_sel (CRSimpleSel *a_this, CRSimpleSel *a_sel)
{
        CRSimpleSel *cur = NULL ;

        g_return_val_if_fail (a_sel, NULL) ;

        if (a_this == NULL)
                return a_sel ;

        for (cur = a_this ; cur->next ; cur = cur->next) ;

        cur->next = a_sel ;
        a_sel->prev = cur ;

        return a_this ;
}

/**
 *Prepends a simple selector to the current list of simple selectors.
 *@param a_this the this pointer of the current instance of #CRSimpleSel.
 *@param a_sel the simple selector to prepend.
 *@return the new list upon successfull completion, an error code otherwise.
 */
CRSimpleSel *
cr_simple_sel_prepend_simple_sel (CRSimpleSel *a_this, CRSimpleSel *a_sel)
{
        g_return_val_if_fail (a_sel, NULL) ;

        if (a_this == NULL)
                return a_sel ;

        a_sel->next = a_this ;
        a_this->prev = a_sel ;

        return a_sel ;
}

guchar *
cr_simple_sel_to_string (CRSimpleSel *a_this)
{
        GString * str_buf = NULL ;
        guchar *result = NULL ;

        CRSimpleSel *cur = NULL ;

        g_return_val_if_fail (a_this,  NULL) ;

        str_buf = g_string_new (NULL) ;
        for (cur = a_this ; cur ; cur = cur->next)
        {
                if (cur->name)
                {
                        guchar * str = g_strndup (cur->name->str, 
                                                  cur->name->len) ;
                        if (str)
                        {
                                switch (cur->combinator)
                                {
                                case COMB_WS:
                                        g_string_append_printf 
                                                (str_buf, " ") ;
                                        break ;

                                case COMB_PLUS:
                                        g_string_append_printf 
                                                (str_buf, "+") ;
                                        break ;

                                case COMB_GT:
                                        g_string_append_printf 
                                                (str_buf, ">") ;
                                        break ;

                                default:
                                        break ;
                                }
                       
                                g_string_append_printf (str_buf,"%s",str) ;
                                g_free (str) ;
                                str = NULL ;
                        }                        
                }

                if (cur->add_sel)
                {
                        guchar *tmp_str = NULL ;
                        
                        tmp_str = cr_additional_sel_to_string 
                                (cur->add_sel) ;
                        if (tmp_str)
                        {
                                g_string_append_printf 
                                        (str_buf, "%s", tmp_str) ;
                                g_free (tmp_str) ;
                                tmp_str = NULL ;
                        }
                }
        }

        if (str_buf)
        {
                result = str_buf->str ;
                g_string_free (str_buf, FALSE) ;
                str_buf = NULL ;
        }

        return result ;
}

/**
 *Dumps the selector to a file.
 *TODO: add the support of unicode in the dump.
 *
 *@param a_this the current instance of #CRSimpleSel.
 *@param a_fp the destination file pointer.
 *@return CR_OK upon successfull completion, an error code
 *otherwise.
 */
enum CRStatus
cr_simple_sel_dump (CRSimpleSel *a_this, FILE *a_fp)
{
        guchar *tmp_str = NULL ;

        g_return_val_if_fail (a_fp, CR_BAD_PARAM_ERROR) ;

        if (a_this)
        {
                tmp_str = cr_simple_sel_to_string (a_this) ;
                if (tmp_str)
                {
                        fprintf (a_fp, "%s", tmp_str) ;
                        g_free (tmp_str) ;
                        tmp_str = NULL ;
                }
        }

        return CR_OK ;
}


/**
 *The destructor of the current instance of
 *#CRSimpleSel.
 *@param a_this the this pointer of the current instance of #CRSimpleSel.
 *
 */
void
cr_simple_sel_destroy (CRSimpleSel *a_this)
{
        g_return_if_fail (a_this) ;

        if (a_this->name)
        {
                g_string_free (a_this->name, TRUE) ;
                a_this->name = NULL ;
        }

        if (a_this->add_sel)
        {
                cr_additional_sel_destroy (a_this->add_sel) ;
                a_this->add_sel = NULL ;
        }

        if (a_this->next)
        {
                cr_simple_sel_destroy (a_this->next) ;
        }

        if (a_this)
        {
                g_free (a_this) ;
        }
}

