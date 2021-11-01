#ifndef TEXTURE_H
#define TEXTURE_H

#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Texture {
private:
	vector<string> m_vecBody;
	int mWidth;
	int mHeight;
public:
	Texture();
	Texture(const string&);
	Texture(const Texture&);
	~Texture() = default;

	Texture& operator= (const char*);
	void AddString(const string&);

	int Height() const;
	int Width() const;

	vector<string> GetTexture() const;
};

#endif // TEXTURE_H
