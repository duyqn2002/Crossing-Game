#include "Texture.h"

unsigned int findWidth(const std::vector<std::string>& form) {
	int max = 0;
	for (const auto& line : form) {
		int length = line.size();
		if (length > max)
			max = length;
	}

	return max;
}

unsigned int findHeight(const std::vector<std::string>& form) {
	return form.size();
}

Texture::Texture(const std::string& body) {
	if (body.size() == 0) {
		return;
	}

	std::stringstream sstream(body);
	std::string temp;

	while (getline(sstream,temp,'\n'))
	{
		m_vecBody.push_back(temp);
	}

	mHeight = findHeight(m_vecBody);
	mWidth = findWidth(m_vecBody);
}

Texture::Texture(const Texture& other) {
	m_vecBody = other.m_vecBody;

	mHeight = other.mHeight;
	mWidth = other.mWidth;
}

Texture& Texture::operator= (const char* body) {
	std::stringstream sstream(body);
	std::string temp;
	while (getline(sstream, temp, '\n'))
	{
		m_vecBody.push_back(temp);
	}

	mHeight = findHeight(m_vecBody);
	mWidth = findWidth(m_vecBody);

	return *this;
}

void Texture::AddLine(const std::string& part) {
	if (mWidth != part.size())
		return;
	m_vecBody.push_back(part);

	mHeight = findHeight(m_vecBody);
	mWidth = findWidth(m_vecBody);
}

int Texture::Height() const{
	return mHeight;
}

int Texture::Width() const{
	return mWidth;
}

std::vector<std::string> Texture::GetTexture() const{
	return m_vecBody;
}