/*___INFO__MARK_BEGIN__*/
/*************************************************************************
 *
 *  The Contents of this file are made available subject to the terms of
 *  the Sun Industry Standards Source License Version 1.2
 *
 *  Sun Microsystems Inc., March, 2001
 *
 *
 *  Sun Industry Standards Source License Version 1.2
 *  =================================================
 *  The contents of this file are subject to the Sun Industry Standards
 *  Source License Version 1.2 (the "License"); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://gridengine.sunsource.net/Gridengine_SISSL_license.html
 *
 *  Software provided under this License is provided on an "AS IS" basis,
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *   The Initial Developer of the Original Code is: Sun Microsystems, Inc.
 *
 *   Copyright: 2001 by Sun Microsystems, Inc.
 *
 *   All Rights Reserved.
 *
 ************************************************************************/
/*___INFO__MARK_END__*/                                   

#include "sge_string.h"
#include "sgermon.h"
#include "sge_log.h"
#include "cull_list.h"

#include "sge_answer.h"
#include "sge_str.h"

#include "msg_sgeobjlib.h"

#define STR_LAYER BASIS_LAYER

/* EB: ADOC: add commets */

const char *
str_list_append_to_dstring(const lList *this_list, dstring *string,
                           const char delimiter)
{
   const char *ret = NULL;

   DENTER(STR_LAYER, "str_list_append_to_dstring");
   if (string != NULL) {
      lListElem *elem = NULL;
      bool printed = false;

      for_each(elem, this_list) {
         sge_dstring_sprintf_append(string, "%s", lGetString(elem, ST_name));
         if (lNext(elem) != NULL) {
            sge_dstring_sprintf_append(string, "%c", delimiter);
         }
         printed = true;
      }
      if (!printed) {
         sge_dstring_sprintf_append(string, "NONE");
      }
      ret = sge_dstring_get_string(string);
   }
   DEXIT;
   return ret;
}

bool 
str_list_parse_from_string(lList **this_list,
                           const char *string, const char *delimitor)
{
   bool ret = true;

   DENTER(STR_LAYER, "str_list_parse_from_dstring");
   if (this_list != NULL && string != NULL && delimitor != NULL) {
      struct saved_vars_s *context = NULL;
      const char *token;

      token = sge_strtok_r(string, delimitor, &context);
      while (token != NULL) {
         lAddElemStr(this_list, ST_name, token, ST_Type);
         token = sge_strtok_r(NULL, delimitor, &context);
      }
      sge_free_saved_vars(context);
   }
   DEXIT;
   return ret;
}

bool
str_list_is_valid(const lList *this_list, lList **answer_list)
{
   bool ret = true;

   DENTER(STR_LAYER, "str_list_is_valid");
   if (this_list != NULL) {
      lListElem *elem;

      for_each(elem, this_list) {
         const char *string = lGetString(elem, ST_name);

         if (string == NULL) {
            answer_list_add(answer_list, MSG_STR_INVALIDSTR, 
                            STATUS_ENOKEY, ANSWER_QUALITY_ERROR);
         }
      }
   }
   DEXIT;
   return ret;
}


