#ifndef _IMAGE_PROVIDER_H_
#define _IMAGE_PROVIDER_H_
#include "../../BaseProvider.h"
#include "../Textures.h"
#include "Reader/ImageReader.h"
#include "Reader/SDLImageReader.h"
#include "Reader/FreeImageReader.h"
#include "Reader/SEImageReader.h"
#include <vector>

class ImageProvider : public BaseProvider
{
public:
	ImageProvider() : BaseProvider()
	{
		readers_.push_back(new FreeImageReader());
		readers_.push_back(new SDLImageReader());
		readers_.push_back(new SEImageReader());

		reader_ = readers_.at(0);
	} 

	Texture* LoadPNG(std::string pFile)
	{
		return Load(pFile.c_str(), DDS);
	}

	Texture* LoadTGA(std::string pFile)
	{
		return Load(pFile.c_str(), TGA);
	}

	Texture* LoadDDS(std::string pFile)
	{
		return Load(pFile.c_str(), DDS);
	}

	bool IsInit() override { return reader_->IsInit(); }
	std::string GetKey() { return ImageProvider::GetKeyStatic(); };
	static std::string GetKeyStatic() { return "Image"; }
private:
	ImageReader* reader_;
	std::vector<ImageReader*> readers_;
	enum FileType {TGA, DDS, PNG};
	std::string FileTypeStr(FileType pType)
	{
		switch(pType)
		{
			case FileType::TGA:
				return "TGA";
				break;
			case FileType::DDS:
				return "DDS";
				break;
			default:
			case FileType::PNG:
				return "PNG";
				break;
		}
	}

	Texture* Render(const char* pFile, FileType pType, ImageReader* reader)
	{
		switch(pType)
		{
			case FileType::TGA:
				return ((*reader).LoadTGA(pFile));
				break;
			case FileType::DDS:
				return ((*reader).LoadDDS(pFile));
				break;
			default:
			case FileType::PNG:
				return ((*reader).LoadPNG(pFile));
				break;
		}
	}
	Texture* Load(const char* pFile, FileType pType)
	{

		Texture* tex = nullptr;
		tex = Render(pFile, pType, reader_);
		if(tex == nullptr)
		{
			for(auto& reader: readers_)
			{
				if(reader_ != reader)
				{
					tex = Render(pFile, pType, reader);
					if (tex != nullptr)
					{
						fprintf(stdout, "Switching image provider to %s\n", reader->Str().c_str());
						reader_ = reader;
						break;
					}
				}
			}
		}

		return tex;
	}

};

#endif _IMAGE_PROVIDER_H_ 