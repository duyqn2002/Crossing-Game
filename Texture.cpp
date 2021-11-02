#include "Texture.h"

Texture::Texture(const string& body) {
	stringstream sstream(body);
	string temp;
	while (getline(sstream,temp,'\n'))
	{
		m_vecBody.push_back(temp);
	}

	mHeight = m_vecBody.size();
	mWidth = m_vecBody[0].size();
}

Texture::Texture(const Texture& other) {
	m_vecBody = other.m_vecBody;

	mHeight = other.mHeight;
	mWidth = other.mWidth;
}

Texture& Texture::operator= (const Texture& other) {
	if (this == &other) {
		m_vecBody = other.m_vecBody;

		mHeight = other.mHeight;
		mWidth = other.mWidth;
	}
	return *this;
}

Texture& Texture::operator= (const char* body) {
	stringstream sstream(body);
	string temp;
	while (getline(sstream, temp, '\n'))
	{
		temp;
		m_vecBody.push_back(temp);
	}

	mHeight = m_vecBody.size();
	mWidth = m_vecBody[0].size();
	return *this;
}

void Texture::AddString(const string& part) {
	if (mWidth != part.size())
		return;
	m_vecBody.push_back(part);
	mHeight += 1;
}

int Texture::Height() const{
	return mHeight;
}

int Texture::Width() const{
	return mWidth;
}

vector<string> Texture::GetTexture() const{
	return m_vecBody;
}