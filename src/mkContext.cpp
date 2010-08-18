/*
 *  mkContext.cpp
 *  MonkVG-XCode
 *
 *  Created by Micah Pearlman on 2/22/09.
 *  Copyright 2009 Monk Games. All rights reserved.
 *
 */
#include "mkContext.h"
//#include "glu.h"
//#include <OpenGLES/ES1/gl.h>
//#include <OpenGLES/ES1/glext.h>

using namespace MonkVG;

//static VGContext *g_context = NULL;

VG_API_CALL VGboolean vgCreateContextSH(VGint width, VGint height)
{
	IContext::instance().Initialize();

	IContext::instance().setWidth( width );
	IContext::instance().setHeight( height );
	
	return VG_TRUE;
}

VG_API_CALL void vgResizeSurfaceSH(VGint width, VGint height)
{
	IContext::instance().setWidth( width );
	IContext::instance().setHeight( height );
#if 0	
	/* setup GL projection */
	glViewport(0,0,width,height);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,width,0,height);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
#endif	
	
}

VG_API_CALL void vgDestroyContextSH()
{
}

VG_API_CALL void VG_API_ENTRY vgSetf (VGParamType type, VGfloat value) VG_API_EXIT {
	IContext::instance().set( type, value );
}

VG_API_CALL void VG_API_ENTRY vgSeti (VGParamType type, VGint value) VG_API_EXIT {
	IContext::instance().set( type, value );
}

VG_API_CALL void VG_API_ENTRY vgSetfv(VGParamType type, VGint count,
									  const VGfloat * values) VG_API_EXIT {
	IContext::instance().set( type, values );
}
VG_API_CALL void VG_API_ENTRY vgSetiv(VGParamType type, VGint count,
									  const VGint * values) VG_API_EXIT {
}

VG_API_CALL VGfloat VG_API_ENTRY vgGetf(VGParamType type) VG_API_EXIT {

}
VG_API_CALL VGint VG_API_ENTRY vgGeti(VGParamType type) VG_API_EXIT {
	
}
VG_API_CALL VGint VG_API_ENTRY vgGetVectorSize(VGParamType type) VG_API_EXIT {
	
}
VG_API_CALL void VG_API_ENTRY vgGetfv(VGParamType type, VGint count, VGfloat * values) VG_API_EXIT {
	
}
VG_API_CALL void VG_API_ENTRY vgGetiv(VGParamType type, VGint count, VGint * values) VG_API_EXIT {
	
}

/* Masking and Clearing */
VG_API_CALL void VG_API_ENTRY vgClear(VGint x, VGint y, VGint width, VGint height) VG_API_EXIT {
	IContext::instance().clear( x, y, width, height );
}


/*--------------------------------------------------
 * Returns the oldest error pending on the current
 * context and clears its error code
 *--------------------------------------------------*/

VG_API_CALL VGErrorCode vgGetError(void)
{
	return IContext::instance().getError();
}


namespace MonkVG {
	
	IContext::IContext() 
		:	_error( VG_NO_ERROR )
		,	_width( 0 )
		,	_height( 0 )
		,	_stroke_line_width( 1.0f )
		,	_stroke_paint( 0 )
		,	_fill_paint( 0 )
		,	_active_matrix( &_path_user_to_surface )
		,	_fill_rule( VG_NON_ZERO )
	{
		_active_matrix->setIdentity();
	}
	
	//// parameters ////
	void IContext::set( VGParamType type, VGfloat f ) {
		switch ( type ) {
			case VG_STROKE_LINE_WIDTH:
				setStrokeLineWidth( f );
				break;
			default:
				setError( VG_ILLEGAL_ARGUMENT_ERROR );
				break;
		}
	}
	
	void IContext::set( VGParamType type, const VGfloat * fv ) {
		switch ( type ) {
			case VG_CLEAR_COLOR:
				setClearColor( fv );
				break;
			default:
				setError( VG_ILLEGAL_ARGUMENT_ERROR );
				break;
		}
	}
	
	void IContext::set( VGParamType type, VGint i ) {
		
		switch ( type ) {
			case VG_MATRIX_MODE:
				setMatrixMode( (VGMatrixMode)i );
				break;
			case VG_FILL_RULE:
				setFillRule( (VGFillRule)i );
				break;
			default:
				break;
		}
		
	}
	void IContext::get( VGParamType type, VGfloat &f ) const {
		switch ( type ) {
			case VG_STROKE_LINE_WIDTH:
				f = getStrokeLineWidth();
				break;
			default:
				IContext::instance().setError( VG_ILLEGAL_ARGUMENT_ERROR );
				break;
		}
		
	}
	
	void IContext::get( VGParamType type, VGfloat *fv ) const {
		switch ( type ) {
			case VG_CLEAR_COLOR:
				getClearColor( fv );
				break;
			default:
				IContext::instance().setError( VG_ILLEGAL_ARGUMENT_ERROR );
				break;
		}
		
	}
	void IContext::get( VGParamType type, VGint ) const {
		
	}
	
}