/*******************************************************************************
 * Size: 10 px
 * Bpp: 4
 * Opts: --bpp 4 --size 10 --no-compress --font SpaceMono-Regular.ttf --symbols /\|.,:-_=+*()&^%$#@!?><~`'" ; --format lvgl -o askii_art.c
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef ASKII_ART
#define ASKII_ART 1
#endif

#if ASKII_ART

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */

    /* U+0021 "!" */
    0x57, 0x57, 0x57, 0x57, 0x57, 0x22, 0x79,

    /* U+0022 "\"" */
    0x6a, 0x98, 0x37, 0x54, 0x2, 0x21,

    /* U+0023 "#" */
    0x3, 0x86, 0x50, 0x3c, 0xdd, 0xc4, 0x3, 0x86,
    0x50, 0x3c, 0xdd, 0xc4, 0x2, 0x75, 0x40,

    /* U+0024 "$" */
    0x0, 0x11, 0x0, 0x3, 0xcb, 0x20, 0xc, 0x77,
    0xb0, 0x8, 0xda, 0x20, 0x7, 0x68, 0xd0, 0xb,
    0xa9, 0xc0, 0x0, 0x89, 0x10,

    /* U+0025 "%" */
    0x2a, 0xa2, 0x0, 0x63, 0x36, 0x0, 0x18, 0x82,
    0x83, 0x0, 0x67, 0x0, 0x28, 0x28, 0x91, 0x0,
    0x45, 0x18, 0x0, 0x19, 0x93,

    /* U+0026 "&" */
    0xb, 0xca, 0x0, 0x67, 0x0, 0x0, 0x58, 0x0,
    0xd0, 0xa, 0xcc, 0xf9, 0x58, 0x0, 0xd0, 0x67,
    0x0, 0xd0, 0xb, 0xcc, 0xd0,

    /* U+0027 "'" */
    0x79, 0x46, 0x12,

    /* U+0028 "(" */
    0x0, 0x6b, 0x50, 0x96, 0x0, 0x3a, 0x0, 0x6,
    0x60, 0x0, 0x75, 0x0, 0x7, 0x50, 0x0, 0x66,
    0x0, 0x3, 0xa0, 0x0, 0xa, 0x60, 0x0, 0x6,
    0xb5,

    /* U+0029 ")" */
    0x3b, 0x70, 0x0, 0x5, 0xb0, 0x0, 0x8, 0x50,
    0x0, 0x48, 0x0, 0x3, 0x90, 0x0, 0x39, 0x0,
    0x4, 0x80, 0x0, 0x85, 0x0, 0x5b, 0x3, 0xb7,
    0x0,

    /* U+002A "*" */
    0x3, 0x45, 0x20, 0x7, 0xbb, 0x90, 0x4a, 0xde,
    0xa6, 0x7, 0xbb, 0x80, 0x4, 0x46, 0x40,

    /* U+002B "+" */
    0x0, 0x0, 0x0, 0x0, 0x46, 0x0, 0xb, 0xcd,
    0xb1, 0x0, 0x46, 0x0, 0x0, 0x46, 0x0,

    /* U+002C "," */
    0x12, 0x7b, 0x46,

    /* U+002D "-" */
    0x4b, 0xb6,

    /* U+002E "." */
    0x12, 0x79,

    /* U+002F "/" */
    0x0, 0x9, 0x0, 0x47, 0x0, 0xa2, 0x0, 0xb0,
    0x4, 0x70, 0xa, 0x20, 0xb, 0x0, 0x47, 0x0,
    0x92, 0x0, 0x0, 0x0,

    /* U+003A ":" */
    0x79, 0x12, 0x0, 0x12, 0x79,

    /* U+003B ";" */
    0x79, 0x12, 0x0, 0x12, 0x7b, 0x46,

    /* U+003C "<" */
    0x0, 0x0, 0x51, 0x5, 0xbb, 0x70, 0xb, 0x20,
    0x0, 0x7, 0xca, 0x40, 0x0, 0x2, 0x81,

    /* U+003D "=" */
    0xb, 0xbb, 0xb1, 0xb, 0xbb, 0xb1,

    /* U+003E ">" */
    0x6, 0x10, 0x0, 0x6, 0xbb, 0x60, 0x0, 0x1,
    0xa2, 0x4, 0x9c, 0x80, 0x8, 0x30, 0x0,

    /* U+003F "?" */
    0x6, 0xcc, 0x80, 0x2c, 0x0, 0xa4, 0x24, 0x0,
    0x94, 0x0, 0x5c, 0x90, 0x0, 0x82, 0x0, 0x0,
    0x31, 0x0, 0x0, 0xb5, 0x0,

    /* U+0040 "@" */
    0x2b, 0xbb, 0xa1, 0xa, 0xa6, 0x68, 0x76, 0xe,
    0x3a, 0x92, 0xb, 0x3a, 0x75, 0xd, 0x3a, 0x1c,
    0xa8, 0xc7,

    /* U+005C "\\" */
    0x81, 0x0, 0x56, 0x0, 0xb, 0x0, 0xa, 0x10,
    0x5, 0x60, 0x0, 0xb0, 0x0, 0xa1, 0x0, 0x56,
    0x0, 0xa, 0x0, 0x0,

    /* U+005E "^" */
    0x0, 0x88, 0x0, 0x5, 0x86, 0x70, 0xc, 0x0,
    0xc1, 0x1, 0x0, 0x10,

    /* U+005F "_" */
    0x2b, 0xbb, 0xb4,

    /* U+0060 "`" */
    0x57, 0x2,

    /* U+007C "|" */
    0x46, 0x46, 0x46, 0x46, 0x46, 0x46, 0x46, 0x46,
    0x46, 0x46,

    /* U+007E "~" */
    0x4, 0xb2, 0x63, 0x27, 0x1b, 0x60
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 98, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 98, .box_w = 2, .box_h = 7, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 7, .adv_w = 98, .box_w = 4, .box_h = 3, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 13, .adv_w = 98, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 28, .adv_w = 98, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 49, .adv_w = 98, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 70, .adv_w = 98, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 91, .adv_w = 98, .box_w = 2, .box_h = 3, .ofs_x = 2, .ofs_y = 4},
    {.bitmap_index = 94, .adv_w = 98, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 119, .adv_w = 98, .box_w = 5, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 144, .adv_w = 98, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 159, .adv_w = 98, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 174, .adv_w = 98, .box_w = 2, .box_h = 3, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 177, .adv_w = 98, .box_w = 4, .box_h = 1, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 179, .adv_w = 98, .box_w = 2, .box_h = 2, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 181, .adv_w = 98, .box_w = 4, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 201, .adv_w = 98, .box_w = 2, .box_h = 5, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 206, .adv_w = 98, .box_w = 2, .box_h = 6, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 212, .adv_w = 98, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 227, .adv_w = 98, .box_w = 6, .box_h = 2, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 233, .adv_w = 98, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 248, .adv_w = 98, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 269, .adv_w = 98, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 287, .adv_w = 98, .box_w = 4, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 307, .adv_w = 98, .box_w = 6, .box_h = 4, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 319, .adv_w = 98, .box_w = 6, .box_h = 1, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 322, .adv_w = 98, .box_w = 2, .box_h = 2, .ofs_x = 2, .ofs_y = 5},
    {.bitmap_index = 324, .adv_w = 98, .box_w = 2, .box_h = 10, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 334, .adv_w = 98, .box_w = 6, .box_h = 2, .ofs_x = 0, .ofs_y = 2}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_1[] = {
    0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x22,
    0x24, 0x25, 0x26, 0x42, 0x44
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 16, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 58, .range_length = 69, .glyph_id_start = 17,
        .unicode_list = unicode_list_1, .glyph_id_ofs_list = NULL, .list_length = 13, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 2,
    .bpp = 4,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif
};

extern const lv_font_t comfortaa_24;


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t askii_art = {
#else
lv_font_t askii_art = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 10,          /*The maximum line height required by the font*/
    .base_line = 2,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = &comfortaa_24,
#endif
    .user_data = NULL,
};



#endif /*#if ASKII_ART*/

