/** \mainpage gLib2D Documentation
 *
 * \section intro Introduction
 *
 * gLib2D by Geecko - A simple, fast, light-weight 2D graphics library. \n\n
 * This library has been designed to replace the old graphics.c library
 * and to simplify the use of pspgu.\n
 * The goals : keep it simple, keep it small, keep it fast.
 *
 * \section limits Known limitations
 *
 * - Draw & display buffers can't actually be used as real textures. Just a way
 *   to get the vram pointer.
 * - No support for multiples contexts (e.g. sharing coordinates beetween
 *   textures using some gBegin calls at a time).
 * - Manipulating textures (clear, get pixel info...) is not possible.
 * - When some 512*512 rotated, colorized and scaled textures are rendered
 *   at a time, the framerate *could* go under 60 fps.
 *
 * \section install Installation
 *
 * - Simply put glib2d.c and glib2d.h in your source directory. \n
 * - Then add glib2d.o and link "-lpng -ljpeg -lz -lpspgu -lm -lpspvram"
 *   in your Makefile.
 * - You're done !
 *
 * \section copyright License
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version. \n\n
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details. \n\n
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>. \n\n
 *
 * You can support the library by marking your homebrew with
 * "Using gLib2D by Geecko".
 *
 * \section contact Contact
 *
 * Please report bugs or submit ideas at : \n geecko.dev@free.fr \n\n
 * Get the full documentation on : \n http://geecko.dev.free.fr \n\n
 * Also stay tuned on... \n
 * https://github.com/GeeckoDev (contributors would be a plus!) \n
 * http://twitter.com/GeeckoDev
 */

#ifndef GLIB2D_H
#define GLIB2D_H

#ifdef __cplusplus
extern "C" {
#endif

#include <SDL_ttf.h>
#include <stdbool.h>
#if defined(__MACOSX__)
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

/**
 * \def G2D_VOID
 * \brief Generic constant, equals to 0 (do nothing).
 */
#define G2D_VOID 0

/**
 * \def G2D_RGBA(r,g,b,a)
 * \brief Create a g2dColor.
 *
 * This macro creates a g2dColor from 4 values, red, green, blue and alpha.
 * Input range is from 0 to 255.
 */
#define G2D_RGBA(r,g,b,a) ((r)|((g)<<8)|((b)<<16)|((a)<<24))

/**
 * \def G2D_GET_R(color)
 * \brief Get red channel value from a g2dColor.
 */
/**
 * \def G2D_GET_G(color)
 * \brief Get green channel value from a g2dColor.
 */
/**
 * \def G2D_GET_B(color)
 * \brief Get blue channel value from a g2dColor.
 */
/**
 * \def G2D_GET_A(color)
 * \brief Get alpha channel value from a g2dColor.
 */
#define G2D_GET_R(color) (((color)    ) & 0xFF)
#define G2D_GET_G(color) (((color)>>8 ) & 0xFF)
#define G2D_GET_B(color) (((color)>>16) & 0xFF)
#define G2D_GET_A(color) (((color)>>24) & 0xFF)

/**
 * \def G2D_MODULATE(color,luminance,alpha)
 * \brief g2dColor modulation.
 *
 * This macro modulates the luminance & alpha of a g2dColor.
 * Input range is from 0 to 255.
 */
#define G2D_MODULATE(color,luminance,alpha) \
G2D_RGBA((int)(luminance)*G2D_GET_R(color)/255, \
         (int)(luminance)*G2D_GET_G(color)/255, \
         (int)(luminance)*G2D_GET_B(color)/255, \
         (int)(alpha    )*G2D_GET_A(color)/255)

/**
 * \enum g2dColors
 * \brief Colors enumeration.
 *
 * Primary, secondary, tertiary and grayscale colors are defined.
 */
enum g2dColors
{
  // Primary colors
  RED          = 0xFF0000FF,
  GREEN        = 0xFF00FF00,
  BLUE         = 0xFFFF0000,
  // Secondary colors
  CYAN         = 0xFFFFFF00,
  MAGENTA      = 0xFFFF00FF,
  YELLOW       = 0xFF00FFFF,
  // Tertiary colors
  AZURE        = 0xFFFF7F00,
  VIOLET       = 0xFFFF007F,
  ROSE         = 0xFF7F00FF,
  ORANGE       = 0xFF007FFF,
  CHARTREUSE   = 0xFF00FF7F,
  SPRING_GREEN = 0xFF7FFF00,
  // Grayscale
  WHITE        = 0xFFFFFFFF,
  LITEGRAY     = 0xFFBFBFBF,
  GRAY         = 0xFF7F7F7F,
  DARKGRAY     = 0xFF3F3F3F,
  BLACK        = 0xFF000000
};

/**
 * \enum g2dCoord_Mode
 * \brief Coordinates modes enumeration.
 *
 * Choose where the coordinates correspond in the object.
 * Can only be used with g2dSetCoordMode.
 */
/**
 * \enum g2dLine_Mode
 * \brief Line modes enumeration.
 *
 * Change line draw properties.
 * Can only be used with g2dBeginLines.
 */
/**
 * \enum g2dFlip_Mode
 * \brief Flip modes enumeration.
 *
 * Change flip properties.
 * Can only be used with g2dFlip.
 */
/**
 * \enum g2dTex_Mode
 * \brief Texture modes enumeration.
 *
 * Change texture properties.
 * Can only be used with g2dTexLoad.
 */
typedef enum
{
  G2D_UP_LEFT,
  G2D_UP_RIGHT,
  G2D_DOWN_RIGHT,
  G2D_DOWN_LEFT,
  G2D_CENTER
} g2dCoord_Mode;
typedef enum
{
  G2D_STRIP = 1 /**< Make a line strip. */
} g2dLine_Mode;
typedef enum
{
  G2D_VSYNC = 1 /**< Limit the FPS to 60 (synchronized with the screen).
                     Better image quality and less power consumption. */
} g2dFlip_Mode;
typedef enum
{
  G2D_SWIZZLE = 1 /**< Recommended. Use it to get *more* rendering speed. */
} g2dTex_Mode;

/**
 * \var g2dAlpha
 * \brief Alpha type.
 */
/**
 * \var g2dColor
 * \brief Color type.
 */
typedef int g2dAlpha;
typedef unsigned int g2dColor;

/**
 * \struct g2dTexture
 * \brief Image structure.
 */
typedef struct
{
  int tw;         /**< Real texture width. A power of two. */
  int th;         /**< Real texture height. A power of two. */
  int w;          /**< Texture width, as seen when drawing. */
  int h;          /**< Texture height, as seen when drawing. */
  float ratio;    /**< Width/height ratio. */
  bool swizzled;  /**< Is the texture swizzled ? */
  bool can_blend; /**< Can the texture blend ? */
  GLuint id;      /**< Image id. */
} g2dTexture;

/**
 * \brief Get screen width.
 * @returns Screen width in pixels.
 */
int g2dScrW();
/**
 * \brief Get screen height.
 * @returns Screen height in pixels.
 */
int g2dScrH();
/**
 * \brief Set screen mode.
 * @param fullscreen Set fullscreen or windowed mode.
 */
void g2dSetMode(bool fullscreen);
/**
 * \brief Clears screen & depth buffer.
 * @param color Screen clear color
 *
 * This function clears the screen, and clears the zbuffer if depth coordinate
 * is used in the loop. Will automatically init the GU if needed.
 */
void g2dClear(g2dColor color);

/**
 * \brief Clears depth buffer.
 *
 * This function clears the zbuffer to zero (z range 0-65535).
 * Will automatically init the GU if needed.
 */
void g2dClearZ();

/**
 * \brief Begins rectangles rendering.
 * @param tex Pointer to a texture, pass NULL to get a colored rectangle.
 *
 * This function begins object rendering. Resets all properties.
 * One g2dAdd() call per object.
 * Only one texture can be used, but multiple objects can be rendered at a time.
 * g2dBegin*() / g2dEnd() couple can be called multiple times in the loop,
 * to render multiple textures.
 */
void g2dBeginRects(g2dTexture* tex);

/**
 * \brief Begins lines rendering.
 * @param line_mode A g2dLine_Mode constant.
 *
 * This function begins object rendering. Calls g2dReset().
 * Two g2dAdd() calls per object.
 * Pass G2D_LINE_STRIP to make a line strip (two calls, then one per object).
 */
void g2dBeginLines(g2dLine_Mode mode);

/**
 * \brief Begins quads rendering.
 * @param tex Pointer to a texture, pass NULL to get a colored quad.
 *
 * This function begins object rendering. Resets all properties.
 * Four g2dAdd() calls per object, first for the up left corner, then clockwise.
 * Only one texture can be used, but multiple objects can be rendered at a time.
 * g2dBegin*() / g2dEnd() couple can be called multiple times in the loop,
 * to render multiple textures.
 */
void g2dBeginQuads(g2dTexture* tex);

/**
 * \brief Begins points rendering.
 *
 * This function begins object rendering. Resets all properties.
 * One g2dAdd() call per object.
 */
void g2dBeginPoints();

/**
 * \brief Ends object rendering.
 *
 * This function ends object rendering. Must be called after g2dBegin*() to add
 * objects to the display list. Automatically adapts pspgu functionnalities
 * to get the best performance possible.
 */
void g2dEnd();

/**
 * \brief Resets current transformation and attribution.
 *
 * This function must be called during object rendering.
 * Calls g2dResetCoord(), g2dResetRotation(), g2dResetScale(),
 * g2dResetColor(), g2dResetAlpha(), g2dResetCrop() and g2dResetTex().
 */
void g2dReset();

/**
 * \brief Flips the screen.
 * @param flip_mode A g2dFlip_Mode constant.
 *
 * This function must be called at the end of the loop.
 * Renders the whole display list to the draw buffer.
 * Inverts framebuffers to display the whole thing.
 */
void g2dFlip(g2dFlip_Mode mode);

/**
 * \brief Pushes the current transformation & attribution to a new object.
 *
 * This function must be called during object rendering.
 */
void g2dAdd();

/**
 * \brief Saves the current transformation to stack.
 *
 * This function must be called during object rendering.
 * The stack is 64 saves high.
 * Use it like the OpenGL one.
 */
void g2dPush();

/**
 * \brief Restore the current transformation from stack.
 *
 * This function must be called during object rendering.
 * The stack is 64 saves high.
 * Use it like the OpenGL one.
 */
void g2dPop();

/**
 * \brief Frees an image & set its pointer to NULL.
 * @param tex Pointer to the variable which contains the image pointer.
 *
 * This function is used to gain memory when an image is useless.
 * Must pass the pointer to the variable which contains the pointer,
 * to set it to NULL (passing NULL to a g2dBegin* function is safe).
 */
void g2dTexFree(g2dTexture** tex);

/**
 * \brief Generate a texture from a SDL surface.
 * @param surface Pointer to a SDL surface.
 * @returns Pointer to the texture.
 */
g2dTexture* g2dTexFromSDLSurface(SDL_Surface* surface);

/**
 * \brief Loads an image.
 * @param path Path to the file.
 * @param tex_mode A g2dTex_Mode constant.
 * @returns Pointer to the texture.
 *
 * This function loads an image file. There is support for PNG & JPEG files
 * (if USE_PNG and USE_JPEG are defined). Swizzling is enabled only for 16*16+
 * textures (useless on small textures), pass G2D_SWIZZLE to enable it.
 */
g2dTexture* g2dTexLoad(char path[], g2dTex_Mode mode);

/**
 * \brief Resets the current coordinates.
 *
 * This function must be called during object rendering.
 * Sets g2dSetCoordMode() to G2D_UP_LEFT and g2dSetCoordXYZ() to (0,0,0).
 */
void g2dResetCoord();

/**
 * \brief Set coordinate mode.
 * @param coord_mode A gCoord_Mode.
 *
 * This function must be called during object rendering.
 * Defines where the coordinates correspond in the object.
 */
void g2dSetCoordMode(g2dCoord_Mode mode);

/**
 * \brief Gets the current position.
 * @param x Pointer to save the current x (in pixels).
 * @param y Pointer to save the current y (in pixels).
 * @param z Pointer to save the current z (in pixels).
 *
 * This function must be called during object rendering.
 * Parameters are pointers to float, not int !
 * Pass NULL if not needed.
 */
void g2dGetCoordXYZ(float* x, float* y, float* z);

/**
 * \brief Sets the new position.
 * @param x New x, in pixels.
 * @param y New y, in pixels.
 *
 * This function must be called during object rendering.
 */
void g2dSetCoordXY(float x, float y);

/**
 * \brief Sets the new position, with depth support.
 * @param x New x, in pixels.
 * @param y New y, in pixels.
 * @param z New z, in pixels. (front 0-65535 back)
 *
 * This function must be called during object rendering.
 */
void g2dSetCoordXYZ(float x, float y, float z);

/**
 * \brief Sets the new position, relative to the current.
 * @param x New x increment, in pixels.
 * @param y New y increment, in pixels.
 *
 * This function must be called during object rendering.
 */
void g2dSetCoordXYRelative(float x, float y);

/**
 * \brief Sets the new position, with depth support, relative to the current.
 * @param x New x increment, in pixels.
 * @param y New y increment, in pixels.
 * @param z New z increment, in pixels.
 *
 * This function must be called during object rendering.
 */
void g2dSetCoordXYZRelative(float x, float y, float z);

/**
 * \brief Use integer coordinates.
 * @param use false to desactivate (better look, by default),
              true to activate (can be useful when you have glitches).
 *
 * This function must be called during object rendering.
 */
void g2dSetCoordInteger(bool use);

/**
 * \brief Resets the global scale.
 *
 * This function resets the global scale to 1.f.
 * Translations and scales are multiplied by this factor.
 */
void g2dResetGlobalScale();

/**
 * \brief Resets the current scale.
 *
 * This function must be called during object rendering.
 * Sets the scale to the current image size or (10,10).
 */
void g2dResetScale();

/**
 * \brief Gets the global scale.
 * @param scale Pointer to save the global scale (factor).
 *
 * Pass NULL if not needed.
 */
void g2dGetGlobalScale(float* scale);

/**
 * \brief Gets the current scale.
 * @param w Pointer to save the current width (in pixels).
 * @param h Pointer to save the current height (in pixels).
 *
 * This function must be called during object rendering.
 * Parameters are pointers to float, not int !
 * Pass NULL if not needed.
 */
void g2dGetScaleWH(float* w, float* h);

/**
 * \brief Sets the global scale.
 *
 * Translations and scales are multiplied by this factor.
 */
void g2dSetGlobalScale(float scale);

/**
 * \brief Sets the new scale.
 * @param w Width scale factor.
 * @param h Height scale factor.
 *
 * This function must be called during object rendering.
 * g2dResetScale() is called, then width & height scale are
 * multiplied by these values.
 * Negative values can be passed to invert the image.
 */
void g2dSetScale(float w, float h);

/**
 * \brief Sets the new scale, in pixels.
 * @param w New width, in pixels.
 * @param h New height, in pixels.
 *
 * This function must be called during object rendering.
 * Negative values can be passed to invert the image.
 */
void g2dSetScaleWH(float w, float h);

/**
 * \brief Sets the new scale, relative to the current.
 * @param w Width scale factor.
 * @param h Height scale factor.
 *
 * This function must be called during object rendering.
 * Current width & height scale are multiplied by these values.
 * Negative values can be passed to invert the image.
 */
void g2dSetScaleRelative(float w, float h);

/**
 * \brief Sets the new scale, in pixels, relative to the current.
 * @param w New width to increment, in pixels.
 * @param h New height to increment, in pixels.
 *
 * This function must be called during object rendering.
 * Negative values can be passed to invert the image.
 */
void g2dSetScaleWHRelative(float w, float h);

/**
 * \brief Resets the current color.
 *
 * This function must be called during object rendering.
 * Sets g2dSetColor() to WHITE.
 */
void g2dResetColor();

/**
 * \brief Resets the current alpha.
 *
 * This function must be called during object rendering.
 * Sets g2dSetAlpha() to 255.
 */
void g2dResetAlpha();

/**
 * \brief Gets the current alpha.
 * @param alpha Pointer to save the current alpha (0-255).
 *
 * This function must be called during object rendering.
 * Pass NULL if not needed.
 */
void g2dGetAlpha(g2dAlpha* alpha);

/**
 * \brief Sets the new color.
 * @param color The new color.
 *
 * This function must be called during object rendering.
 * Can be used to colorize any object.
 */
void g2dSetColor(g2dColor color);

/**
 * \brief Sets the new alpha.
 * @param alpha The new alpha (0-255).
 *
 * This function must be called during object rendering.
 * Can be used to make any object transparent.
 */
void g2dSetAlpha(g2dAlpha alpha);

/**
 * \brief Sets the new alpha, relative to the current alpha.
 * @param alpha The new alpha increment.
 *
 * This function must be called during object rendering.
 * Can be used to make any object transparent.
 */
void g2dSetAlphaRelative(int alpha);

/**
 * \brief Resets the current rotation.
 *
 * This function must be called during object rendering.
 * Sets g2dSetRotation() to 0°.
 */
void g2dResetRotation();

/**
 * \brief Gets the current rotation, in radians.
 * @param radians Pointer to save the current rotation.
 *
 * This function must be called during object rendering.
 * Pass NULL if not needed.
 */
void g2dGetRotationRad(float* radians);

/**
 * \brief Gets the current rotation, in degrees.
 * @param degrees Pointer to save the current rotation.
 *
 * This function must be called during object rendering.
 * Pass NULL if not needed.
 */
void g2dGetRotation(float* degrees);

/**
 * \brief Sets the new rotation, in radians.
 * @param radians The new angle.
 *
 * This function must be called during object rendering.
 * The rotation center is the actual coordinates.
 */
void g2dSetRotationRad(float radians);

/**
 * \brief Sets the new rotation, in degrees.
 * @param degrees The new angle.
 *
 * This function must be called during object rendering.
 * The rotation center is the actual coordinates.
 */
void g2dSetRotation(float degrees);

/**
 * \brief Sets the new rotation, relative to the current, in radians.
 * @param radians The new angle increment.
 *
 * This function must be called during object rendering.
 * The rotation center is the actual coordinates.
 */
void g2dSetRotationRadRelative(float radians);

/**
 * \brief Sets the new rotation, relative to the current, in degrees.
 * @param degrees The new angle increment.
 *
 * This function must be called during object rendering.
 * The rotation center is the actual coordinates.
 */
void g2dSetRotationRelative(float degrees);

/**
 * \brief Resets the current crop.
 *
 * This function must be called during object rendering.
 * Sets g2dSetCropXY() to (0;0) and g2dSetCropWH() to (tex->w,tex->h).
 */
void g2dResetCrop();

/**
 * \brief Gets the current crop position.
 * @param x Pointer to save the current crop x.
 * @param y Pointer to save the current crop y.
 *
 * This function must be called during object rendering.
 * Pass NULL if not needed.
 */
void g2dGetCropXY(int* x, int* y);

/**
 * \brief Gets the current crop scale.
 * @param w Pointer to save the current crop width.
 * @param h Pointer to save the current crop height.
 *
 * This function must be called during object rendering.
 * Pass NULL if not needed.
 */
void g2dGetCropWH(int* w, int* h);

/**
 * \brief Sets the new crop position.
 * @param x New x, in pixels.
 * @param y New y, in pixels.
 *
 * This function must be called during object rendering. Defines crop position.
 * If the rectangle is larger or next to the image, texture will be repeated
 * when g2dSetTexRepeat is enabled. Useful for a tileset.
 */
void g2dSetCropXY(int x, int y);

/**
 * \brief Sets the new crop size.
 * @param w New width, in pixels.
 * @param h New height, in pixels.
 *
 * This function must be called during object rendering. Defines crop size.
 * If the rectangle is larger or next to the image, texture will be repeated
 * when g2dSetTexRepeat is enabled. Useful for a tileset.
 */
void g2dSetCropWH(int w, int h);

/**
 * \brief Sets the new crop position, relative to the current.
 * @param x New x increment, in pixels.
 * @param y New y increment, in pixels.
 *
 * This function must be called during object rendering. Defines crop position.
 * If the rectangle is larger or next to the image, texture will be repeated
 * when g2dSetTexRepeat is enabled. Useful for a tileset.
 */
void g2dSetCropXYRelative(int x, int y);

/**
 * \brief Sets the new crop size, relative to the current.
 * @param w New width increment, in pixels.
 * @param h New height increment, in pixels.
 *
 * This function must be called during object rendering. Defines crop size.
 * If the rectangle is larger or next to the image, texture will be repeated
 * when g2dSetTexRepeat is enabled. Useful for a tileset.
 */
void g2dSetCropWHRelative(int w, int h);

/**
 * \brief Resets texture properties.
 *
 * This function must be called during object rendering.
 */
void g2dResetTex();

/**
 * \brief Set texture wrap.
 * @param use true to repeat, false to clamp (by default).
 *
 * This function must be called during object rendering.
 */
void g2dSetTexRepeat(bool use);

/**
 * \brief Use alpha blending with the texture.
 * @param use true to activate (better look, by default),
              false to desactivate (better performance).
 *
 * This function must be called during object rendering.
 * Automaticaly disabled when g2dTexture::can_blend is set to false.
 */
void g2dSetTexBlend(bool use);

/**
 * \brief Use the bilinear filter with the texture.
 * @param use true to activate (better look, by default).
              false to desactivate (better performance).
 *
 * This function must be called during object rendering.
 * Only useful when scaling.
 */
void g2dSetTexLinear(bool use);

/**
 * \brief Resets the draw zone to the entire screen.
 *
 * This function can be called everywhere in the loop.
 */
void g2dResetScissor();

/**
 * \brief Sets the draw zone.
 * @param x New x position.
 * @param y New y position.
 * @param w New width.
 * @param h New height.
 *
 * This function can be called everywhere in the loop.
 * Pixel draw will be skipped outside this rectangle.
 */
void g2dSetScissor(int x, int y, int w, int h);

#ifdef __cplusplus
}
#endif

#endif
