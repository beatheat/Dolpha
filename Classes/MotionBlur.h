#pragma once

#include<cocos2d.h>

USING_NS_CC;

class MotionBlur
{
private:
	GLProgram *shader = nullptr;
public:
	GLProgram *GetBlurShader()
	{
		return shader;
	}
public:
	static MotionBlur *motionblur;
	static MotionBlur *getInstance()
	{
		if (motionblur == nullptr)
		{
			motionblur = new MotionBlur;
			motionblur->shader = new GLProgram();
			CCLOG("%d",motionblur->shader->initWithFilenames("motionblur.vsh", "motionblur.fsh"));
			motionblur->shader->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);

			motionblur->shader->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);

			motionblur->shader->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);

			motionblur->shader->link();

			motionblur->shader->updateUniforms();

			ShaderCache::getInstance()->addGLProgram(motionblur->shader, "MotionBlur");
		}
		return motionblur;
	}

};