#include "Texture.h"

int findWidth(const std::vector<std::string>& form) {
	int max = 0;
	for (const auto& line : form) {
		auto length = (int)line.size();
		if (length > max)
			max = length;
	}

	return max;
}

 int findHeight(const std::vector<std::string>& form) {
	return (int)form.size();
}

Texture::Texture(const char* body) {
	std::stringstream sstream(body);
	std::string temp;

	while (getline(sstream,temp,'\n'))
	{
		mBody.push_back(temp);
	}

	mHeight = findHeight(mBody);
	mWidth = findWidth(mBody);
}

Texture::Texture(const Texture& other) {
	for (std::string line : other.mBody) {
		mBody.push_back(line);
	}

	mHeight = other.mHeight;
	mWidth = other.mWidth;
}

Texture& Texture::operator= (const char* body) {
	std::stringstream sstream(body);
	std::string temp;

	while (getline(sstream, temp, '\n'))
	{
		mBody.push_back(temp);
	}

	mHeight = findHeight(mBody);
	mWidth = findWidth(mBody);

	return *this;
}

bool Texture::operator==(const Texture& other) const
{
	if (this == &other)
		return true;

	if(other.mBody != mBody)
		return false;

	return true;
}

bool Texture::operator!=(const Texture& other) const
{
	return !operator==(other);
}

void Texture::LoadFromFile(const std::string& filePath) {
	std::string completeFilePath = filePath + ".txt";
	std::ifstream ifs(completeFilePath.c_str());
	if (!ifs) {
		return;
	}

	std::string temp;

	while (getline(ifs, temp, '\n'))
	{
		mBody.push_back(temp);
	}

	mHeight = findHeight(mBody);
	mWidth = findWidth(mBody);
}

void Texture::AddLine(const std::string& part) {
	if (mWidth != part.size())
		return;

	// Update attributes
	mBody.push_back(part);

	mHeight = findHeight(mBody);
	mWidth = findWidth(mBody);
}

int Texture::Height() const{
	return mHeight;
}

int Texture::Width() const{
	return mWidth;
}

std::vector<std::string> Texture::getTexture() const{
	return mBody;
}