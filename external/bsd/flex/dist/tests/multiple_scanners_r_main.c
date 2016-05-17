/*
 * This file is part of flex.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 
 * Neither the name of the University nor the names of its contributors
 * may be used to endorse or promote products derived from this software
 * without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE.
 */

#include "multiple_scanners_r_1.h"
#include "multiple_scanners_r_2.h"

int
main ( int argc, char** argv )
{
    (void)argc;
    (void)argv;

    int S1_ok=1, S2_ok=1;
    FILE * fp;
    YY_BUFFER_STATE buff1, buff2;
    yyscan_t scan1, scan2;
    
    S1_lex_init(&scan1);
    S2_lex_init(&scan2);

    S1_set_out(stdout,scan1);
    S2_set_out(S1_get_out(scan1),scan2);
    
    buff1 = S1__scan_string("foo on bar off", scan1);
    buff2 = S2__scan_string("on blah blah off foo on bar off", scan2);

    /* scan simultaneously. */
    while(S1_ok || S2_ok)
    {
        if (S1_ok)
            S1_ok = S1_lex(scan1);
        if (S2_ok)
            S2_ok = S2_lex(scan2);
    }
    S1__delete_buffer(buff1, scan1);
    S2__delete_buffer(buff2, scan2);

    S1_lex_destroy(scan1);
    S2_lex_destroy(scan2);
    printf("TEST RETURNING OK.\n");
    return 0;
}


/* vim:set tabstop=8 softtabstop=4 shiftwidth=4: */
