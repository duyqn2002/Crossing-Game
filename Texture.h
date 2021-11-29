#ifndef TEXTURE_H
#define TEXTURE_H

#include <vector>
#include <string>
#include <sstream>
#include <fstream>

class Texture {
private:
	std::vector<std::string> mBody;
	int mWidth;
	int mHeight;

public:
	Texture() = default;
	Texture(const char*);
	Texture(const std::string&);
	Texture(const Texture&);

	~Texture() = default;

	// Operator
	Texture& operator= (const char*);
	Texture& operator= (const std::string&);

	bool operator==(const Texture&) const;
	bool operator!=(const Texture&) const;

	// Method
	void LoadFromFile(const std::string&);
	void AddLine(const std::string&);

	// Getter
	int Height() const;
	int Width() const;
	std::vector<std::string> getTexture() const;
};

#endif // TEXTURE_H
