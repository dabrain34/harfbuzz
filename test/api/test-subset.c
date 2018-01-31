/*
 * Copyright © 2011  Google, Inc.
 *
 *  This is part of HarfBuzz, a text shaping library.
 *
 * Permission is hereby granted, without written agreement and without
 * license or royalty fees, to use, copy, modify, and distribute this
 * software and its documentation for any purpose, provided that the
 * above copyright notice and the following two paragraphs appear in
 * all copies of this software.
 *
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE TO ANY PARTY FOR
 * DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES
 * ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN
 * IF THE COPYRIGHT HOLDER HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 *
 * THE COPYRIGHT HOLDER SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING,
 * BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS
 * ON AN "AS IS" BASIS, AND THE COPYRIGHT HOLDER HAS NO OBLIGATION TO
 * PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
 *
 * Google Author(s): Garret Rieger
 */

#include "hb-test.h"

/* Unit tests for hb-subset.h */

static const char test_data[] = "OTTO";

static void
test_subset (void)
{
  hb_blob_t *font_blob = hb_blob_create(test_data, sizeof(test_data),
					HB_MEMORY_MODE_READONLY, NULL, NULL);
  hb_face_t *face = hb_face_create(font_blob, 0);

  hb_subset_profile_t *profile = hb_subset_profile_create();
  hb_subset_input_t *input = hb_subset_input_create();
  hb_subset_face_t *subset_face = hb_subset_face_create(face);

  char output_data[100];
  hb_blob_t *output = hb_blob_create(output_data, sizeof(output_data),
				     HB_MEMORY_MODE_WRITABLE, NULL, NULL);

  g_assert(hb_subset(profile, input, subset_face, output));
  g_assert_cmpmem(test_data, 4, output_data, sizeof(output));

  hb_blob_destroy(output);
  hb_subset_face_destroy(subset_face);
  hb_subset_input_destroy(input);
  hb_subset_profile_destroy(profile);
  hb_face_destroy(face);
  hb_blob_destroy(font_blob);
}

int
main (int argc, char **argv)
{
  hb_test_init (&argc, &argv);

  hb_test_add (test_subset);

  return hb_test_run();
}
