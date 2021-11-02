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
	Texture() = default;
	Texture(const string&);
	Texture(const Texture&);
	~Texture() = default;

	// Operator
	Texture& operator= (const char*);
	Texture& operator= (const Texture& other);

	// Method
	void AddString(const string&);

	// Getter
	int Height() const;
	int Width() const;
	vector<string> GetTexture() const;
};

#endif // TEXTURE_H
