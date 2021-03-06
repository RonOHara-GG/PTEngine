GL_FUNCTION(wglCopyContext, BOOL, (HGLRC, HGLRC, UINT))
GL_FUNCTION(wglCreateContext, HGLRC, (HDC))
GL_FUNCTION(wglCreateLayerContext, HGLRC, (HDC, GLint))
GL_FUNCTION(wglDeleteContext, BOOL, (HGLRC))
GL_FUNCTION(wglGetCurrentContext, HGLRC, (VOID))
GL_FUNCTION(wglGetCurrentDC, HDC, (VOID))
GL_FUNCTION(wglGetProcAddress, PROC, (LPCSTR))
GL_FUNCTION(wglMakeCurrent, BOOL, (HDC, HGLRC))
GL_FUNCTION(wglShareLists, BOOL, (HGLRC, HGLRC))
GL_FUNCTION(wglDescribeLayerPlane, BOOL, (HDC, GLint, GLint, UINT, LPLAYERPLANEDESCRIPTOR))
GL_FUNCTION(wglSetLayerPaletteEntries, GLint, (HDC, GLint, GLint, GLint, CONST COLORREF *))
GL_FUNCTION(wglGetLayerPaletteEntries, GLint, (HDC, GLint, GLint, GLint, COLORREF *))
GL_FUNCTION(wglRealizeLayerPalette, BOOL, (HDC, GLint, BOOL))
GL_FUNCTION(wglSwapLayerBuffers, BOOL, (HDC, UINT))
