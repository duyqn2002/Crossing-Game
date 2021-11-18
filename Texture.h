#ifndef TEXTURE_H
#define TEXTURE_H

#include <vector>
#include <string>
#include <sstream>

class Texture {
private:
	std::vector<std::string> mBody;
	int mWidth;
	int mHeight;

public:
	Texture() = default;
	Texture(const char* body);
	Texture(const Texture&);

	~Texture() = default;

	// Operator
	Texture& operator= (const char*);

	// Method
	void AddLine(const std::string&);

	// Getter
	int Height() const;
	int Width() const;
	std::vector<std::string> getTexture() const;
};

#endif // TEXTURE_H
