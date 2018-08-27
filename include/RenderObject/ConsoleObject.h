#ifndef _CONSOLE_OBJECT_H_
#define _CONSOLE_OBJECT_H_
#include "Object.h"
#include "glm/glm.hpp"
#include "BasicObject.h"
#include "../String.h"
#include "ObjectProvider.h"
#include "../Texture/Textures.h"

struct CommandHistory {
	std::string text;
	int height, width;
	Texture* tex;
};
namespace ConsoleObject
{
	class ConsoleObject : public Object
	{
	public:
		FontFamily* font_;

		ConsoleObject(std::string pFontName, glm::vec2 pPos, glm::vec2 pDim) : Object(), fontName_(pFontName)
		{
			auto prov = (ShaderProvider*)GetProvider<ShaderProvider>();
			shader_ = prov->Get("Font");
			shader_->Activate();
			auto prov2 = (FontProvider*)GetProvider<FontProvider>();
			font_ = prov2->GetFont(pFontName);

			p_ = shader_->GetHandle("MVP");
			textColor_ = shader_->GetHandle("textColor");

			shader_->Deactivate();

			pos_ = glm::vec4(pPos, 0, 0);
			pos_.z = pDim.x - pPos.x;
			pos_.w = pDim.y - pPos.y;
		}

		GLuint textColor_;

		GLuint p_;

		void ConstructBG()
		{
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			auto tex = SEGL::GenerateTexture2D<unsigned char*>(1, 1, NULL,
				GL_RED, GL_RED,
				GL_LINEAR, GL_LINEAR,
				GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);

			unsigned char pixel[1] = { bg_.w * 255 };
			glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 1, 1, GL_RED, GL_UNSIGNED_BYTE, pixel);
			auto texture = new Texture(tex);

			std::vector<glm::vec4> data = {
				{pos_.x, pos_.y + pos_.w, 0.f, 0.f},
				{pos_.x, pos_.y, 0.f, 1.f},
				{pos_.x + pos_.z, pos_.y, 1.f, 1.f},

				{pos_.x, pos_.y + pos_.w, 0.f, 0.f},
				{pos_.x + pos_.z, pos_.y, 1.f, 1.f},
				{pos_.x + pos_.z, pos_.y + pos_.w, 1.f, 0.f},
			};
			auto prov = (ObjectProvider*)GetProvider<ObjectProvider>();
			background_ = prov->CreateObj(data, texture);


			auto ch = CommandHistory();
			ch.height = 100;
		}

		void Render(glm::mat4 P) {
			shader_->Activate();
			background_->BeginRender();
			glUniform3f(textColor_, bg_.x, bg_.y, bg_.z);
			glUniformMatrix4fv(p_, 1, GL_FALSE, &P[0][0]);
			background_->Render();
			background_->EndRender();
			for(int i = 0; i < history_.size(); ++i)
			{
				int offset = history_[0].height * i;
				float x = pos_.x + padding_;
				float y = pos_.y + offset + padding_;
				GLfloat v[6][4] = {
					{ x, y + history_[0].height, 0.0f, 0.f},
					{ x, y, 0.0f, 1.f},
					{ x + history_[0].width, y, 1.0f, 1.f},

					{ x, y + history_[0].height, 0.0f, 0.f},
					{ x + history_[0].width, y, 1.0f, 1.f},
					{ x + history_[0].width, y + history_[0].height, 1.0f, 0.f}
				};
				glBindTexture(GL_TEXTURE_2D, history_[i].tex->_Handle());
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * 4 * 6, NULL);
				glDrawArrays(GL_TRIANGLES, 0, 6);
			}
			shader_->Deactivate();

			SEGL::ErrorCheck(__LINE__, __FILE__);
		}

	void InitBuffers() override
	{
		ConstructBG();
	};
	void Render() override {};
protected:
	glm::vec4 pos_;
	std::vector<CommandHistory> history_;
	PassthruObject * background_;
	std::string fontName_;
	glm::vec4 bg_ = glm::vec4(0.f, 0.f, 0.f, 0.4f);
	glm::vec4 text_ = glm::vec4(1.f, 1.f, 1.f, 1.f);
	int padding_ = 5;
};

}
#endif _CONSOLE_OBJECT_H_